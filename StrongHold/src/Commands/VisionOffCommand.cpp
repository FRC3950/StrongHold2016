#include "VisionOffCommand.h"
#include "Robot.h"

VisionOffCommand::VisionOffCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	DriverStation::ReportError("I am in VisionOffCommand::VisionOffCommand()\n");
//	Requires(Robot::visionSubsystem.get());
}

// Called just before this Command runs the first time
void VisionOffCommand::Initialize()
{
	DriverStation::ReportError("I am in VisionOffCommand::Initialize()\n");
}

// Called repeatedly when this Command is scheduled to run
void VisionOffCommand::Execute()
{
	DriverStation::ReportError("I am in VisionOffCommand::Execute()\n");
//	Robot::visionSubsystem->Off();
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
