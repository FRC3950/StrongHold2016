#include "ManipulatorSeekPosCommand.h"
#include "Robot.h"
#include "Logging.h"

ManipulatorSeekPosCommand::ManipulatorSeekPosCommand(ManipulatorSubsystem::SeekManipulatorPos pos)
{
	Logger *logger = Logger::GetInstance();

	logger->Log(ManipulatorLogId, Logger::kTRACE, "ManipulatorSeekPosCommand::ctor Created Joystick Buttons");

	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::manipulatorSubsystem.get());
	targetPos = pos;

	logger->Log(ManipulatorLogId, Logger::kTRACE, "ManipulatorSeekPosCommand::ctor Created Joystick Buttons");
}

// Called just before this Command runs the first time
void ManipulatorSeekPosCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ManipulatorSeekPosCommand::Execute()
{
	if (!hasInitalized){
		Robot::manipulatorSubsystem->SetManipulatorSeekPosition(targetPos);
		hasInitalized = true;
	}


}

// Make this return true when this Command no longer needs to run execute()
bool ManipulatorSeekPosCommand::IsFinished()
{
	return Robot::manipulatorSubsystem->hasManipulatorReachedPos();
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
		Robot::manipulatorSubsystem->cancelManipulatorSeek();
		hasInitalized = false;
	}
}
