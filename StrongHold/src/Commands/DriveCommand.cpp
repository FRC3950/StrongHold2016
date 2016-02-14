#include "DriveCommand.h"
#include "../Logging.h"
#include "../Robot.h"
#include "../Subsystems/DriveSubsystem.h"
namespace{
	const float JOYSTICK_Y_DEFAULT_MODIFYER = 1.0f;
	const float JOYSTICK_TWIST_DEFAULT_MODIFYER = 0.7f;
}
DriveCommand::DriveCommand()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::driveSubsystem.get());
}

// Called just before this Command runs the first time
void DriveCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void DriveCommand::Execute()
{
	Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "DriveCommand::Execute Enter()");

	if (!Robot::driveSubsystem->inDriveMode()) {
		Robot::driveSubsystem->SetMode(DriveSubsystem::drive);
	}
	//float x = Robot::oi->getJoystickX();
	float y = -Robot::oi->getJoystickY();
	float twist = -Robot::oi->getjoystickTwist();

	y *= JOYSTICK_Y_DEFAULT_MODIFYER;
	twist *= JOYSTICK_TWIST_DEFAULT_MODIFYER;

	Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "DriveCommand::Execute() y=%f, twist=%f", y, twist);

	Robot::driveSubsystem->ArcadeDrive(y,twist);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void DriveCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveCommand::Interrupted()
{
}
