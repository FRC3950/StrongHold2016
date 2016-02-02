#include "ShooterSubsystem.h"
#include "../RobotMap.h"
#include "../Logging.h"
#include "../ConfigKeys.h"
#include "../Config/ConfigInstanceMgr.h"

namespace {
	const float CONVERSION_RATIO_ROTATIONS_TO_COUNTS = 512;

	const double SHOOTER_VOLTAGE_DEFAULT = 0.01;

	const double SHOOTER_ROTS_PER_SEC_EPSILON_DEFAULT = 10.0;
	double ShooterRotsPerSecEpsilon = SHOOTER_ROTS_PER_SEC_EPSILON_DEFAULT;

	const double CLIMBER_MOTOR_SMALL_ERROR_SMOOTHING_FACTOR_DEFAULT = .10;
	double ShooterMotorSmallErrorSmoothingFactor = CLIMBER_MOTOR_SMALL_ERROR_SMOOTHING_FACTOR_DEFAULT;

	const double CLIMBER_MOTOR_LARGE_ERROR_SMOOTHING_FACTOR_DEFAULT = .50;
	double ShooterMotorLargeErrorSmoothingFactor = CLIMBER_MOTOR_LARGE_ERROR_SMOOTHING_FACTOR_DEFAULT;

	inline double ConvertRotationstoCounts(double rotations) {
		return rotations * CONVERSION_RATIO_ROTATIONS_TO_COUNTS;
	}
	bool InRange(double val, double target, double range) {
		if (val > (target - range) && val < (target + range)){
			return true;
		}
		return false;
	}

	double DeltaFromSpeedTarget(double currSpeed, double target, double epsilon) {
		double delta = currSpeed - target;

		if (fabs(delta) <= fabs(epsilon)) {
			return 0.0;
		}

		return delta;
	}

	bool ConfigInited = false;

	void InitSubsystemConfiguration()
	{
	    ConfigMgr *configMgr = ConfigInstanceMgr::getInstance();

	    if (!ConfigInited) {
	    	ShooterRotsPerSecEpsilon = configMgr->getDoubleVal(ConfigKeys::Shooter_RotsPerSecEpsilonKey, SHOOTER_ROTS_PER_SEC_EPSILON_DEFAULT);

	    	ShooterMotorLargeErrorSmoothingFactor = configMgr->getDoubleVal(ConfigKeys::Shooter_LargeErrorSmoothingFactorKey, CLIMBER_MOTOR_LARGE_ERROR_SMOOTHING_FACTOR_DEFAULT);
	    	ShooterMotorSmallErrorSmoothingFactor = configMgr->getDoubleVal(ConfigKeys::Shooter_SmallErrorSmoothingFactorKey, CLIMBER_MOTOR_SMALL_ERROR_SMOOTHING_FACTOR_DEFAULT);


			Logger* logger = Logger::GetInstance();

			logger->Log(ShooterSubsystemLogId,Logger::kINFO, "ShooterSubsystem: Rotations / Sec Epsilon = %g\n", ShooterRotsPerSecEpsilon);
			logger->Log(ShooterSubsystemLogId,Logger::kINFO, "ShooterSubsystem: Small Error Smoothing Factor = %g\n", ShooterMotorSmallErrorSmoothingFactor);
			logger->Log(ShooterSubsystemLogId,Logger::kINFO, "ShooterSubsystem: Large Error Smoothing Factor = %g\n", ShooterMotorLargeErrorSmoothingFactor);

	      	ConfigInited = true;
	    }
	}
}

ShooterSubsystem::ShooterSubsystem() :
		Subsystem("ExampleSubsystem")
{
	hoodSolenoid = RobotMap::shooterSubsystemShooterCoverSolenoid;
	shooterMotor = RobotMap::shooterSubsystemShooterWheelTalon;

	shooterMotor->SetControlMode(CANTalon::kPercentVbus);
	shooterMotor->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	shooterMotor->Set(0.0f);
	shooterMotor->SetSafetyEnabled(false);

	targetCountsPerSec = 0.0f;
	lastCountsReadTime = 0.0f;
	lastCounts = 0.0f;

	InitSubsystemConfiguration();
}

void ShooterSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void ShooterSubsystem::SetHoodState(HoodState hs){
	if (hs == HoodState::open){
		hoodSolenoid.get()->Set(true);
	}
	else if (hs == HoodState::closed){
		hoodSolenoid.get()->Set(false);
	}

}
void ShooterSubsystem::ToggleHood(){
	if (hoodSolenoid->Get() == true){
		hoodSolenoid->Set(false);
	}
	else {
		hoodSolenoid->Set(true);
	}
}

ShooterSubsystem::HoodState ShooterSubsystem::GetHoodState(){
	return hoodSolenoid->Get() == true ? HoodState::open : HoodState::closed;
}


void ShooterSubsystem::SetTargetSpeed(float rotsPerSec){
	if (rotsPerSec <= 0) {
		// Error TBD
		shooterMotor->Set(0.0);
		return;
	}

	targetCountsPerSec = ConvertRotationstoCounts(rotsPerSec);
	lastCountsReadTime = Timer::GetFPGATimestamp();
	lastCounts = fabs(shooterMotor->GetPosition());

	shooterMotor->Set(SHOOTER_VOLTAGE_DEFAULT);
}


bool ShooterSubsystem::HasHitTargetSpeed() {
	double currTime = Timer::GetFPGATimestamp();
	double currCounts = fabs(shooterMotor->GetPosition());

	// Check for rollover and discard:
	if ((currTime < lastCountsReadTime) || (currCounts < lastCounts)) {
		lastCountsReadTime = currTime;
		lastCounts = currCounts;
		return false;
	}

	double currSpeed = (currCounts - lastCounts) / (currTime - lastCountsReadTime);

	if (InRange(currSpeed, targetCountsPerSec, 10))
	{
		return true;
	}

	double ratio = currSpeed / targetCountsPerSec;

	double error = 1.0 - ratio;

	double voltage = shooterMotor->Get();

	double smoothingFactor;

	if (error >= 0.5) {
		smoothingFactor = ShooterMotorLargeErrorSmoothingFactor;
	}
	else {
		smoothingFactor = ShooterMotorSmallErrorSmoothingFactor;
	}

	voltage += error * smoothingFactor;

	if (voltage > 1.0) {
		voltage = 1.0;
	}
	else if (voltage < -1.0) {
		voltage = -1.0;
	}

	shooterMotor->Set(voltage);

	lastCounts = currCounts;
	lastCountsReadTime = currTime;

	return false;
}
