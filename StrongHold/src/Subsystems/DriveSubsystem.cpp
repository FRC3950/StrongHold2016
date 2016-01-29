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
	victor1 = RobotMap::driveSubsystemVictor1;
	victor2 = RobotMap::driveSubsystemVictor2;
	victor3 = RobotMap::driveSubsystemVictor3;
	victor4 = RobotMap::driveSubsystemVictor4;
    robotDrive41 = RobotMap::driveSubsystemRobotDrive41;

    robotDrive41->SetSafetyEnabled(true);
    robotDrive41->SetExpiration(0.1);
    robotDrive41->SetSensitivity(0.5);
    robotDrive41->SetMaxOutput(1.0);

    robotDrive41->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
    robotDrive41->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
}

void DriveSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new DriveCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void DriveSubsystem::EnableDriveSubsystem(){
	bool enable = false;
	float expiration = 1.0;
//	SetSafetyMode(*victor1, enable, expiration);
//	SetSafetyMode(*victor2, enable, expiration);
//	SetSafetyMode(*victor3, enable, expiration);
//	SetSafetyMode(*victor4, enable, expiration);
	robotDrive41->SetSafetyEnabled(enable);

	if (enable)
	{
		robotDrive41->SetSafetyEnabled(expiration);
	}

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

	robotDrive41->ArcadeDrive(twist,y);
}
