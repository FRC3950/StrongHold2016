#include "OverrideIntakeCommand.h"
#include "../Robot.h"

OverrideIntakeCommand::OverrideIntakeCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires (Robot::intakeSubsystem.get());
}

// Called just before this Command runs the first time
void OverrideIntakeCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void OverrideIntakeCommand::Execute()
{
	Robot::intakeSubsystem->SetIntakeMotor(IntakeSubsystem::In);
}

// Make this return true when this Command no longer needs to run execute()
bool OverrideIntakeCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void OverrideIntakeCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OverrideIntakeCommand::Interrupted()
{

}
