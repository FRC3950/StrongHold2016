#include "DropClimberCommand.h"
#include "Robot.h"

DropClimberCommand::DropClimberCommand()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::climberSubsystem.get());
}

// Called just before this Command runs the first time
void DropClimberCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void DropClimberCommand::Execute()
{
	if (!Inited)  {
		Robot::climberSubsystem->dropClimber();
		Inited = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DropClimberCommand::IsFinished()
{
	if (!Robot::oi->getDropClimberButton()) {
		return true;
	}
	else {
		return false;
	}
}

// Called once after isFinished returns true
void DropClimberCommand::End()
{
	CleanUp();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DropClimberCommand::Interrupted()
{
	CleanUp();
}
void DropClimberCommand::CleanUp(){
	Robot::climberSubsystem->stopClimber();
	Inited = false;
}
