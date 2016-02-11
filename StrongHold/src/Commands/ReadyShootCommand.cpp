#include "../Robot.h"
#include "ReadyShootCommand.h"

ReadyShootCommand::ReadyShootCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::intakeSubsystem.get());
	startTime = 0.0f;
}

// Called just before this Command runs the first time
void ReadyShootCommand::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void ReadyShootCommand::Execute()
{
	if (!inited) {
		startTime = Timer::GetFPGATimestamp();
		inited = true;

	}

	// Do more stuff
	Robot::intakeSubsystem->SetIntakeMotor(IntakeSubsystem::In, false);
}

// Make this return true when this Command no longer needs to run execute()
bool ReadyShootCommand::IsFinished()
{
	// compares the current time to the start time of the command
	// plus the time we want the command to run to determine when
	// we want the command to finish
	if (inited && (Timer::GetFPGATimestamp() >= (startTime + runTime))) {
		return true;
	}

	return false;
}

// Called once after isFinished returns true
void ReadyShootCommand::End()
{
	CleanUp();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReadyShootCommand::Interrupted()
{
	CleanUp();
}
void ReadyShootCommand::CleanUp(){
	inited = false;
	Robot::intakeSubsystem->SetIntakeMotor(IntakeSubsystem::Neutral, false);
}
