#include <Commands/ClimbCommand.h>
#include "../Robot.h"
#include "../Logging.h"


ClimbCommand::ClimbCommand()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::driveSubsystem.get());
}

// Called just before this Command runs the first time
void ClimbCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ClimbCommand::Execute()
{
	Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "ClimbCommand::Execute Enter()");
	if (!Robot::driveSubsystem->InClimbMode()) {
		Robot::driveSubsystem->SetMode(DriveSubsystem::ClimbingMode);
	}
	float y = Robot::oi->getJoystickY();
	Robot::driveSubsystem->Climb(y);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimbCommand::IsFinished()
{
	Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "ClimbCommand::IsFinished() Enter");
	return false;
}

// Called once after isFinished returns true
void ClimbCommand::End()
{
	Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "ClimbCommand::End() Enter");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimbCommand::Interrupted()
{
	Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "ClimbCommand::Interrupted() Enter");
}
