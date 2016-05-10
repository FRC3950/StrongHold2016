#include "VisionOnCommand.h"
#include "Robot.h"
#include "../Logging.h"
namespace {
	double delay = .1;
}
VisionOnCommand::VisionOnCommand()
{
	// Use Requires() here to declare subsystem dependencies
	 Requires(Robot::visionSubsystem.get());
	 Logger::GetInstance()->Log(VisionTargetingLogId, Logger::kTRACE, "VisionOnCommand:VisionOnCommand() -> Enter");
	 lastTime = 0;
}

// Called just before this Command runses the first time
void VisionOnCommand::Initialize()
{
	DriverStation::ReportError("I am in VisionOnCommand::Initialize()\n");
	Logger::GetInstance()->Log(VisionTargetingLogId, Logger::kTRACE, "VisionOnCommand::Initialized() -> Enter");
	cleanUp();
}

// Called repeatedly when this Command is scheduled to run
void VisionOnCommand::Execute()
{
	double currTime  = Timer::GetFPGATimestamp();

	if (lastTime == 0) {
		Robot::visionSubsystem->On();
		lastTime = currTime;
	}

	if (currTime > (lastTime + delay)){
		//Logger::GetInstance()->Log(VisionTargetingLogId, Logger::kTRACE, "VisionOnCommand::Executing() -> Enter");
		Robot::visionSubsystem->GrabImage();
		lastTime = currTime;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool VisionOnCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void VisionOnCommand::End()
{
	cleanUp();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VisionOnCommand::Interrupted()
{
	cleanUp();
}

void VisionOnCommand::cleanUp()
{
	if (lastTime != 0) {
		Robot::visionSubsystem->Off();
	}

	lastTime = 0;
}
