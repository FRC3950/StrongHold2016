#include "RetractClimberCommand.h"
#include "../Robot.h"

RetractClimberCommand::RetractClimberCommand()
{
	// Use Requires() here to declare subsystem dependencies
	Requires (Robot::climberSubsystem.get());
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void RetractClimberCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void RetractClimberCommand::Execute()
{
	Robot::climberSubsystem->RetractClimber();
}

// Make this return true when this Command no longer needs to run execute()
bool RetractClimberCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RetractClimberCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RetractClimberCommand::Interrupted()
{

}
