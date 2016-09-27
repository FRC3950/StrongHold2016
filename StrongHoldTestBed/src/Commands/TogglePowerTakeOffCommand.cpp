#include "TogglePowerTakeOffCommand.h"
#include "Robot.h"

TogglePowerTakeOffCommand::TogglePowerTakeOffCommand()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::driveSubsystem.get());
}

// Called just before this Command runs the first time
void TogglePowerTakeOffCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void TogglePowerTakeOffCommand::Execute()
{
	Robot::driveSubsystem->TogglePowerTakeOff();
}

// Make this return true when this Command no longer needs to run execute()
bool TogglePowerTakeOffCommand::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void TogglePowerTakeOffCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TogglePowerTakeOffCommand::Interrupted()
{

}
