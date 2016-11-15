#include "../Robot.h"
#include <Commands/LaunchClimberCommand.h>

LaunchClimberCommand::LaunchClimberCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::climberSubsystem.get());
}

// Called just before this Command runs the first time
void LaunchClimberCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void LaunchClimberCommand::Execute()
{
		Robot::climberSubsystem->LaunchClimber();
	}

// Make this return true when this Command no longer needs to run execute()
bool LaunchClimberCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void LaunchClimberCommand::End()
{
	CleanUp();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LaunchClimberCommand::Interrupted()
{
	CleanUp();
}
void LaunchClimberCommand::CleanUp(){
	Robot::climberSubsystem->stopClimber();
	init = false;
}
