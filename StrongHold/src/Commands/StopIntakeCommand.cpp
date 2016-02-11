#include "../Robot.h"
#include <Commands/StopIntakeCommand.h>

StopIntakeCommand::StopIntakeCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::intakeSubsystem.get());
}

// Called just before this Command runs the first time
void StopIntakeCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void StopIntakeCommand::Execute()
{
	Robot::intakeSubsystem->SetIntakeMotor(IntakeSubsystem::Neutral,false);
}

// Make this return true when this Command no longer needs to run execute()
bool StopIntakeCommand::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void StopIntakeCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopIntakeCommand::Interrupted()
{

}
