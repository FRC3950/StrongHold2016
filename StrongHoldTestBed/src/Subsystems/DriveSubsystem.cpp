#include "DriveSubsystem.h"
#include "../Logging.h"
#include "../RobotMap.h"
#include "../Commands/DriveCommand.h"

namespace
{
	void SetSafetyMode(Talon& motor, bool enabled, float timeout) {
		Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "DriveSubsystem::SetSafteyMode() = %s, timeout=%f",
			enabled ? "TRUE" : "FALSE", timeout);

		motor.SetSafetyEnabled(enabled);
		motor.SetExpiration(timeout);
	}
}
DriveSubsystem::DriveSubsystem() :
		Subsystem("DriveSubsystem")
{
    talon1 = RobotMap::driveSubsystemTalon1;
    talon2 = RobotMap::driveSubsystemTalon2;
    talon3 = RobotMap::driveSubsystemTalon3;
    talon4 = RobotMap::driveSubsystemTalon4;
    robotDrive = RobotMap::driveSubsystemRobotDrive41;

    powerTakeOffSolenoid = RobotMap::testSolenoid;

    robotDrive->SetSafetyEnabled(true);
    robotDrive->SetExpiration(0.1);
    robotDrive->SetSensitivity(0.5);
    robotDrive->SetMaxOutput(1.0);

    robotDrive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
    robotDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
}

void DriveSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new DriveCommand());
//	talon1->SetControlMode(Talon::kPercentVbus);
//	talon2->SetControlMode(Talon::kPercentVbus);
//	talon3->SetControlMode(Talon::kPercentVbus);
//	talon4->SetControlMode(Talon::kPercentVbus);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void DriveSubsystem::EnableDriveSubsystem(){
	bool enable = false;
	float expiration = 1.0;
	SetSafetyMode(*talon1, enable, expiration);
	SetSafetyMode(*talon2, enable, expiration);
	SetSafetyMode(*talon3, enable, expiration);
	SetSafetyMode(*talon4, enable, expiration);
	robotDrive->SetSafetyEnabled(enable);

	if (enable)
	{
		robotDrive->SetSafetyEnabled(expiration);
	}

	/*
	talon1->EnableControl();
	talon2->EnableControl();
	talon3->EnableControl();
	talon4->EnableControl();
	*/

	talon1->Set(0);
	talon2->Set(0);
	talon3->Set(0);
	talon4->Set(0);
}

void DriveSubsystem::ArcadeDrive(float y, float twist) {
	Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "DriveSubsystem::ArcadeDrive()->y = %f, twist=%f", y, twist);

	robotDrive->ArcadeDrive(twist,y);
}
void DriveSubsystem::TogglePowerTakeOff(){
	if (powerTakeOffSolenoid->Get() == DoubleSolenoid::Value::kForward){
		powerTakeOffSolenoid->Set(DoubleSolenoid::Value::kReverse);
	}
	else {
		powerTakeOffSolenoid->Set(DoubleSolenoid::Value::kForward);
	}


}
