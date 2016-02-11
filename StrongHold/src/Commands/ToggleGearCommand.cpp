#include "../Robot.h"
#include "ToggleGearCommand.h"

ToggleGearCommand::ToggleGearCommand()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::driveSubsystem.get());
}

// Called just before this Command runs the first time
void ToggleGearCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ToggleGearCommand::Execute()
{
	Robot::driveSubsystem->ToggleHighLowGear();
}

// Make this return true when this Command no longer needs to run execute()
bool ToggleGearCommand::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ToggleGearCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleGearCommand::Interrupted()
{

}
