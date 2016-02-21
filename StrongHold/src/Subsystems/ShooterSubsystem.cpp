#include "ShooterSubsystem.h"
#include "../RobotMap.h"
#include "../Logging.h"
#include "../ConfigKeys.h"
#include "../Config/ConfigInstanceMgr.h"

namespace {
	const float CONVERSION_RATIO_ROTATIONS_TO_COUNTS = 2048;

	const double SHOOTER_VOLTAGE_DEFAULT = 0.01;

	const double MIN_ELAPSED_TIME_FOR_SPEED_CHECK = 0.01;

	const double SHOOTER_WHEEL_ROTS_PER_SEC_EPSILON_DEFAULT = 3.0;
	double ShooterWheelRotsPerSecEpsilon = SHOOTER_WHEEL_ROTS_PER_SEC_EPSILON_DEFAULT;
	double ShooterMotorCountsPerSecEpsilon = 0;

	const double SHOOTER_MOTOR_SMALL_ERROR_SMOOTHING_FACTOR_DEFAULT = 0.01;
	double ShooterMotorSmallErrorSmoothingFactor = SHOOTER_MOTOR_SMALL_ERROR_SMOOTHING_FACTOR_DEFAULT;

	const double SHOOTER_MOTOR_LARGE_ERROR_SMOOTHING_FACTOR_DEFAULT = .50;
	double ShooterMotorLargeErrorSmoothingFactor = SHOOTER_MOTOR_LARGE_ERROR_SMOOTHING_FACTOR_DEFAULT;

	inline double ConvertRotationstoCounts(double rotations) {
		return rotations * CONVERSION_RATIO_ROTATIONS_TO_COUNTS;
	}

	inline double ConvertCountsPerSecToRotationsPerSec(double countsPerSec) {
		return countsPerSec / CONVERSION_RATIO_ROTATIONS_TO_COUNTS;
	}

	inline bool InRange(double val, double target, double range) {
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
	    	ShooterWheelRotsPerSecEpsilon = configMgr->getDoubleVal(ConfigKeys::Shooter_RotsPerSecEpsilonKey, SHOOTER_WHEEL_ROTS_PER_SEC_EPSILON_DEFAULT);
	    	ShooterMotorCountsPerSecEpsilon = ConvertRotationstoCounts(ShooterWheelRotsPerSecEpsilon);

	    	ShooterMotorLargeErrorSmoothingFactor = configMgr->getDoubleVal(ConfigKeys::Shooter_LargeErrorSmoothingFactorKey, SHOOTER_MOTOR_LARGE_ERROR_SMOOTHING_FACTOR_DEFAULT);
	    	ShooterMotorSmallErrorSmoothingFactor = configMgr->getDoubleVal(ConfigKeys::Shooter_SmallErrorSmoothingFactorKey, SHOOTER_MOTOR_SMALL_ERROR_SMOOTHING_FACTOR_DEFAULT);


			Logger* logger = Logger::GetInstance();

			logger->Log(ShooterSubsystemLogId,Logger::kINFO, "ShooterSubsystem: Rotations / Sec Epsilon = %g\n", ShooterWheelRotsPerSecEpsilon);
			logger->Log(ShooterSubsystemLogId,Logger::kINFO, "ShooterSubsystem: Small Error Smoothing Factor = %g\n", ShooterMotorSmallErrorSmoothingFactor);
			logger->Log(ShooterSubsystemLogId,Logger::kINFO, "ShooterSubsystem: Large Error Smoothing Factor = %g\n", ShooterMotorLargeErrorSmoothingFactor);

	      	ConfigInited = true;
	    }
	}
}

const float ShooterSubsystem::MinRotationsPerSec = 5.0f;
const float ShooterSubsystem::MaxRotationsPerSec = 500.0f;

ShooterSubsystem::ShooterSubsystem() :
		Subsystem("ShooterSubsystem")
{
	hoodSolenoid = RobotMap::shooterSubsystemShooterCoverSolenoid;
	shooterMotor = RobotMap::shooterSubsystemShooterWheelTalon;

	shooterMotor->SetControlMode(CANTalon::kPercentVbus);
	shooterMotor->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	shooterMotor->Set(0.0f);
	shooterMotor->SetSafetyEnabled(false);
	shooterMotor->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
	//shooterMotor->ConfigEncoderCodesPerRev(1024);

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
	Logger *logger = Logger::GetInstance();
	logger->Log(ShooterSubsystemLogId, Logger::kTRACE, "SetTargetSpeed Entered");

	if (rotsPerSec <= 0) {
		targetCountsPerSec = 0.0;
		shooterMotor->Set(0.0);
		logger->Log(ShooterSubsystemLogId, Logger::kTRACE, "SetTargetSpeed: Target Counts per second: %g", targetCountsPerSec);
		return;
	}

	shooterMotor->SetPosition(0.0);
	Wait(0.5);
	targetCountsPerSec = ConvertRotationstoCounts(rotsPerSec);
	lastCountsReadTime = Timer::GetFPGATimestamp();
	lastCounts = 0.0;//fabs(shooterMotor->GetPosition());
	logger->Log(ShooterSubsystemLogId, Logger::kTRACE, "Target Counts per second: %g", targetCountsPerSec);
	logger->Log(ShooterSubsystemLogId, Logger::kTRACE, "Epsilon - %g", ShooterMotorCountsPerSecEpsilon);
	logger->Log(ShooterSubsystemLogId, Logger::kTRACE, "last count read time: %g", lastCountsReadTime);
	logger->Log(ShooterSubsystemLogId, Logger::kTRACE, "last counts read: %g", lastCounts);
	shooterMotor->Set(SHOOTER_VOLTAGE_DEFAULT);

	logger->Log(ShooterSubsystemLogId, Logger::kTRACE, "SetTargetSpeed Exit");
}


bool ShooterSubsystem::HasHitTargetSpeed() {
	Logger *logger = Logger::GetInstance();
	logger->Log(ShooterSubsystemLogId, Logger::kTRACE, "HasHitTargetSpeed Entered");

	if (targetCountsPerSec <= 0.0) {
		shooterMotor->Set(0.0);
		logger->Log(ShooterSubsystemLogId, Logger::kTRACE, "HasHitTargetSpeed: targetCountsPerSec <= 0.0, shutting off motor. Returning true.");

		return true;
	}

	double currTime = Timer::GetFPGATimestamp();
	double currCounts = fabs(shooterMotor->GetPosition());

	// Check for rollover and discard:
	if ((currTime < lastCountsReadTime) || (currCounts < lastCounts)) {
		lastCountsReadTime = currTime;
		lastCounts = currCounts;
		logger->Log(ShooterSubsystemLogId, Logger::kTRACE, "Time or Counts has rolled over.  Resetting lastCountsReadTime=%g, lastCounts=%g",
					lastCountsReadTime, lastCounts);
		logger->Log(ShooterSubsystemLogId, Logger::kTRACE, "HasHitTargetSpeed Exit, Returning False");
		return false;
	}

	if ((currTime - lastCountsReadTime) < MIN_ELAPSED_TIME_FOR_SPEED_CHECK) {
		logger->Log(ShooterSubsystemLogId, Logger::kTRACE, "Waiting for at least .01 second to elapse, Returning false.");

		return false;
	}
	double currSpeed = (currCounts - lastCounts) / (currTime - lastCountsReadTime);

	logger->Log(ShooterSubsystemLogId, Logger::kTRACE, "currSpeed=%g, currCounts=%g, lastCounts=%g, currTime=%g, lastCountsReadTime=%g",
			    currSpeed, currCounts, lastCounts, currTime, lastCountsReadTime);

	logger->Log(ShooterSubsystemLogId, Logger::kTRACE, "currSpeed=%g rots/sec",
			    ConvertCountsPerSecToRotationsPerSec(currSpeed));

	if (InRange(currSpeed, targetCountsPerSec, ShooterMotorCountsPerSecEpsilon))
	{
		logger->Log(ShooterSubsystemLogId, Logger::kINFO, "Hit Target Speed: currSpeed=%g, targetCountsPerSec=%g, epsilon=%g Returning True.",
				    currSpeed, targetCountsPerSec, ShooterMotorCountsPerSecEpsilon);

		return true;
	}

	double ratio = currSpeed / targetCountsPerSec;

	double error = 1.0 - ratio;

	double currVoltage = fabs(shooterMotor->Get());

	double smoothingFactor = ShooterMotorSmallErrorSmoothingFactor;

	logger->Log(ShooterSubsystemLogId, Logger::kTRACE, "Ratio=%g, Error=%g, currVoltage=%g, smoothingFactor=%g",
			    ratio, error, currVoltage, smoothingFactor);

	double newVoltage = currVoltage + (error * smoothingFactor);

	if (SHOOTER_VOLTAGE_DEFAULT > 0) {
		newVoltage = newVoltage >= SHOOTER_VOLTAGE_DEFAULT ? newVoltage : SHOOTER_VOLTAGE_DEFAULT;
	}
	else {
		newVoltage = newVoltage <= SHOOTER_VOLTAGE_DEFAULT ? newVoltage : SHOOTER_VOLTAGE_DEFAULT;
	}

	newVoltage = -newVoltage;

	logger->Log(ShooterSubsystemLogId, Logger::kTRACE, "New Voltage = %g Before Capping",
			    newVoltage);

	if (newVoltage > 1.0) {
		newVoltage = 1.0;
	}
	else if (newVoltage < -1.0) {
		newVoltage = -1.0;
	}

	logger->Log(ShooterSubsystemLogId, Logger::kTRACE, "New Voltage After Capping = %g",
			    newVoltage);

	shooterMotor->Set(newVoltage);

	lastCounts = currCounts;
	lastCountsReadTime = currTime;

	logger->Log(ShooterSubsystemLogId, Logger::kTRACE, "HasHitTargetSpeed Exit -> Returning false");

	return false;
}
