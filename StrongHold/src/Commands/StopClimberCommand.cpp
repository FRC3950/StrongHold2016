#include "StopClimberCommand.h"
#include "../Robot.h"

StopClimberCommand::StopClimberCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);

}

// Called just before this Command runs the first time
void StopClimberCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void StopClimberCommand::Execute()
{
	Robot::climberSubsystem->stopClimber();
}

// Make this return true when this Command no longer needs to run execute()
bool StopClimberCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void StopClimberCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopClimberCommand::Interrupted()
{

}
