#include "DriveSubsystemInteruptCommand.h"
#include "../Robot.h"

DriveSubsystemInteruptCommand::DriveSubsystemInteruptCommand()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::driveSubsystem.get());
}

// Called just before this Command runs the first time
void DriveSubsystemInteruptCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void DriveSubsystemInteruptCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool DriveSubsystemInteruptCommand::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void DriveSubsystemInteruptCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveSubsystemInteruptCommand::Interrupted()
{

}
