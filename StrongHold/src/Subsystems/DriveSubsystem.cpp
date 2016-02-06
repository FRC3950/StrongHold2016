#include "DriveSubsystem.h"
#include "../ConfigKeys.h"
#include "../Config/ConfigInstanceMgr.h"
#include "../Logging.h"
#include "../RobotMap.h"
#include "../Commands/DriveCommand.h"

namespace
{
	const bool DRIVE_SAFETY_ENABLED_DEFAULT = false;
	const float DRIVE_SAFETY_TIME_OUT_DEFAULT = 1.0;
	const float Y_VAL_EPSILON_RANGE = .05;
	const float TWIST_VAL_EPSILON_RANGE = .05;

#if 0
	void SetSafetyMode(Talon& motor, bool enabled, float timeout) {
		Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "DriveSubsystem::SetSafteyMode() = %s, timeout=%f",
			enabled ? "TRUE" : "FALSE", timeout);

		motor.SetSafetyEnabled(enabled);
		motor.SetExpiration(timeout);
	}
#endif

	void VictorSetSafetyMode(Victor& motor, bool enabled, float timeout) {
			Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "DriveSubsystem::SetSafteyMode() = %s, timeout=%f",
				enabled ? "TRUE" : "FALSE", timeout);

			motor.SetSafetyEnabled(enabled);
			motor.SetExpiration(timeout);
		}
}
DriveSubsystem::DriveSubsystem() :
		Subsystem("DriveSubsystem")
{
	victor1 = RobotMap::driveSubsystemVictor1;
	victor2 = RobotMap::driveSubsystemVictor2;
	victor3 = RobotMap::driveSubsystemVictor3;
	victor4 = RobotMap::driveSubsystemVictor4;
    robotDrive = RobotMap::driveSubsystemRobotDrive41;
    powerTakeOffSolenoid = RobotMap::driveSubsystemPowerTakeOffSolenoid;
    gearSwitchSolenoid = RobotMap::driveSubsystemShifterSolenoid;

    robotDrive->SetSafetyEnabled(true);
    robotDrive->SetExpiration(0.1);
    robotDrive->SetSensitivity(0.5);
    robotDrive->SetMaxOutput(1.0);

    robotDrive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
    robotDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);

    syncDriveModeToHardware();
}

void DriveSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new DriveCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void DriveSubsystem::EnableDriveSubsystem() {
	ConfigMgr *configMgr = ConfigInstanceMgr::getInstance();

	float expiration = 0.0;

	bool enable = configMgr->getBoolVal(ConfigKeys::Drive_EnableSafety, DRIVE_SAFETY_ENABLED_DEFAULT);

	if (enable)
	{
		expiration = configMgr->getDoubleVal(ConfigKeys::Drive_SafetyTimeOut, DRIVE_SAFETY_TIME_OUT_DEFAULT);
	}

	Logger::GetInstance()->Log(DriveSubsystemLogId,Logger::kINFO, "DriveSubsystem:EnableDriveSubsystem() ->SafetyEnable=%s, timeout=%f\n",
			enable ? "TRUE" : "FALSE",
			expiration);

	VictorSetSafetyMode(*victor1, enable, expiration);
	VictorSetSafetyMode(*victor2, enable, expiration);
	VictorSetSafetyMode(*victor3, enable, expiration);
	VictorSetSafetyMode(*victor4, enable, expiration);
	robotDrive->SetSafetyEnabled(enable);

	if (enable)
	{
		robotDrive->SetSafetyEnabled(expiration);
	}

    syncDriveModeToHardware();

	/*
	talon1->EnableControl();
	talon2->EnableControl();
	talon3->EnableControl();
	talon4->EnableControl();
	*/

	victor1->Set(0);
	victor2->Set(0);
	victor3->Set(0);
	victor4->Set(0);
}

void DriveSubsystem::ArcadeDrive(float y, float twist) {
	Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "DriveSubsystem::ArcadeDrive()->y = %f, twist=%f", y, twist);

	if (!inDriveMode())
	{
		Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kERROR, "DriveSubsystem::ArcadeDrive called but NOT in drive mode. IGNORING!");
		return;
	}

	robotDrive->ArcadeDrive(inRangeExclusive(twist, TWIST_VAL_EPSILON_RANGE),inRangeExclusive(y, Y_VAL_EPSILON_RANGE));
}

void DriveSubsystem::Climb(float y) {
	Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "DriveSubsystem::Climb()->y = %f", y);

	if (!inClimbMode())
	{
		Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kERROR, "DriveSubsystem::Climb called but NOT in climb mode. IGNORING!");
		return;
	}

	//TO DO: climb code
}

void DriveSubsystem::ToggleHighLowGear(){
	if (gearSwitchSolenoid->Get() == DoubleSolenoid::Value::kForward){
		gearSwitchSolenoid->Set(DoubleSolenoid::Value::kReverse);
	}
	else{
		gearSwitchSolenoid->Set(DoubleSolenoid::Value::kForward);
	}
}

void DriveSubsystem::SetGear(Gear g){
	if (g == Gear::high){
		gearSwitchSolenoid->Set(DoubleSolenoid::Value::kForward);
	}
	else{
		gearSwitchSolenoid->Set(DoubleSolenoid::Value::kReverse);
	}
}

DriveSubsystem::Gear DriveSubsystem::GetGearState() {
	if (gearSwitchSolenoid->Get() == DoubleSolenoid::Value::kForward) {
		return Gear::high;
	}
	else {
		return Gear::low;
	}
}

void DriveSubsystem::syncDriveModeToHardware() {
	if (powerTakeOffSolenoid->Get() == DoubleSolenoid::Value::kForward) {
		mode = DriveMode::drive;
	}
	else {
		mode = DriveMode::climb;
	}
}
void DriveSubsystem::SetMode(DriveSubsystem::DriveMode dm) {
	if (dm == DriveMode::drive) {
		powerTakeOffSolenoid->Set(DoubleSolenoid::Value::kForward);
		mode = DriveMode::drive;
	}
	else {
		powerTakeOffSolenoid->Set(DoubleSolenoid::Value::kReverse);
		mode = DriveMode::climb;
	}
}
float DriveSubsystem::inRangeExclusive(float val, float range){
	if (val < range && val > -range){
		return 0;
	}
	return val;
}

