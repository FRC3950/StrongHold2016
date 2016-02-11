#include "ToggleShooterHoodCommand.h"
#include "../Robot.h"

ToggleShooterHoodCommand::ToggleShooterHoodCommand()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::shooterSubsystem.get());
}

// Called just before this Command runs the first time
void ToggleShooterHoodCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ToggleShooterHoodCommand::Execute()
{
	Robot::shooterSubsystem->ToggleHood();
}

// Make this return true when this Command no longer needs to run execute()
bool ToggleShooterHoodCommand::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ToggleShooterHoodCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleShooterHoodCommand::Interrupted()
{

}
