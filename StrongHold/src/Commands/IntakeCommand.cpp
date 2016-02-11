#include "../Robot.h"
#include "IntakeCommand.h"

IntakeCommand::IntakeCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::intakeSubsystem.get());
}

// Called just before this Command runs the first time
void IntakeCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void IntakeCommand::Execute()
{
	Robot::intakeSubsystem->SetIntakeMotor(IntakeSubsystem::In, true);
}

// Make this return true when this Command no longer needs to run execute()
bool IntakeCommand::IsFinished()
{
	return Robot::intakeSubsystem->IsBallLoaded();
}

// Called once after isFinished returns true
void IntakeCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeCommand::Interrupted()
{

}
