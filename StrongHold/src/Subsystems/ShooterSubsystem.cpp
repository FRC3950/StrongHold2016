#include "ShooterSubsystem.h"
#include "../RobotMap.h"


namespace {
	const float CONVERSION_RATIO_ROTATIONS_TO_COUNTS = 512;

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

const double SHOOTER_VOLTAGE_DEFAULT = 0.01;

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

	double delta = DeltaFromSpeedTarget(currSpeed, targetCountsPerSec, 10);

	double ratio = currSpeed / targetCountsPerSec;

	double accelFactor = 1.0 - ratio;

	double voltage = shooterMotor->Get();

	const double AccelerationScaleValue = .10;

	voltage += accelFactor * AccelerationScaleValue;

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
