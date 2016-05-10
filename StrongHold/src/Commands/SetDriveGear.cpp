#include "SetDriveGear.h"
#include "Robot.h"

SetDriveGear::SetDriveGear(DriveSubsystem::Gear g)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::driveSubsystem.get());
	gear = g;
}

// Called just before this Command runs the first time
void SetDriveGear::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void SetDriveGear::Execute()
{
	Robot::driveSubsystem->SetGear(gear);
}

// Make this return true when this Command no longer needs to run execute()
bool SetDriveGear::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void SetDriveGear::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetDriveGear::Interrupted()
{

}
