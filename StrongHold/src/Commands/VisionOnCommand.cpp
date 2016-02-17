#include "VisionOnCommand.h"
#include "Robot.h"

VisionOnCommand::VisionOnCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
//	DriverStation::ReportError("I am in VisionOnCommand::VisionOnCommand()\n");
//	Requires(Robot::visionSubsystem.get());
}

// Called just before this Command runses the first time
void VisionOnCommand::Initialize()
{
//	DriverStation::ReportError("I am in VisionOnCommand::Initialize()\n");
}

// Called repeatedly when this Command is scheduled to run
void VisionOnCommand::Execute()
{
//	DriverStation::ReportError("I am in VisionOnCommand::Execute()\n");
//	Robot::visionSubsystem->On();
}

// Make this return true when this Command no longer needs to run execute()
bool VisionOnCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void VisionOnCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VisionOnCommand::Interrupted()
{

}
