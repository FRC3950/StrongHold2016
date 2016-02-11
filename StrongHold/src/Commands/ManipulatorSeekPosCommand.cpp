#include "ManipulatorSeekPosCommand.h"
#include "Robot.h"

ManipulatorSeekPosCommand::ManipulatorSeekPosCommand(IntakeSubsystem::SeekManipulatorPos pos)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::intakeSubsystem.get());
	targetPos = pos;
}

// Called just before this Command runs the first time
void ManipulatorSeekPosCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ManipulatorSeekPosCommand::Execute()
{
	if (!hasInitalized){
		Robot::intakeSubsystem->SetManipulatorSeekPosition(targetPos);
		hasInitalized = true;
	}


}

// Make this return true when this Command no longer needs to run execute()
bool ManipulatorSeekPosCommand::IsFinished()
{
	return Robot::intakeSubsystem->hasManipulatorReachedPos();
}

// Called once after isFinished returns true
void ManipulatorSeekPosCommand::End()
{
	hasInitalized = false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ManipulatorSeekPosCommand::Interrupted()
{
	if (hasInitalized){
		Robot::intakeSubsystem->cancelManipulatorSeek();
		hasInitalized = false;
	}
}
