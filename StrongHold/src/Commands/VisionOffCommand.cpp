#include "VisionOffCommand.h"
#include "Robot.h"
#include "Logging.h"

VisionOffCommand::VisionOffCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Logger::GetInstance()->Log(VisionTargetingLogId, Logger::kTRACE, "VisionOffCommand::VisionOffCommand() -> Enter");
	Requires(Robot::visionSubsystem.get());
}

// Called just before this Command runs the first time
void VisionOffCommand::Initialize()
{
	Logger::GetInstance()->Log(VisionTargetingLogId, Logger::kTRACE, "VisionOffCommand::Initialized() -> Enter");
}

// Called repeatedly when this Command is scheduled to run
void VisionOffCommand::Execute()
{
	Logger::GetInstance()->Log(VisionTargetingLogId, Logger::kTRACE, "VisionOffCommand::Executed() -> Enter");
	Robot::visionSubsystem->Off();
}

// Make this return true when this Command no longer needs to run execute()
bool VisionOffCommand::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void VisionOffCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VisionOffCommand::Interrupted()
{

}
