#include "ToggleDriveDirectionCommand.h"
#include "Robot.h"

ToggleDriveDirectionCommand::ToggleDriveDirectionCommand()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::driveSubsystem.get());
}

// Called just before this Command runs the first time
void ToggleDriveDirectionCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ToggleDriveDirectionCommand::Execute()
{
	Robot::driveSubsystem->ToggleDriveDirection = !Robot::driveSubsystem->ToggleDriveDirection;
}

// Make this return true when this Command no longer needs to run execute()
bool ToggleDriveDirectionCommand::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ToggleDriveDirectionCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleDriveDirectionCommand::Interrupted()
{

}
