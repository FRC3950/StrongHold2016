#include "AutoDriveCommand.h"
#include "../Robot.h"

namespace {
	const float AutoMoveSpeed = 1.0;
	const float DriveTimeDefault = 2.0;
}
AutoDriveCommand::AutoDriveCommand(double time)
	: runTime(time)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::driveSubsystem.get());
	if (runTime < 0){
		runTime = 0;
	}
	startTime = 0.0f;
}

AutoDriveCommand::AutoDriveCommand() : AutoDriveCommand(DriveTimeDefault){


}
// Called just before this Command runs the first time
void AutoDriveCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void AutoDriveCommand::Execute()
{
	if (!inited) {
			startTime = Timer::GetFPGATimestamp();
			inited = true;

	}
	Robot::driveSubsystem->ArcadeDrive(AutoMoveSpeed,0);
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveCommand::IsFinished()
{
	if (inited && (Timer::GetFPGATimestamp() >= (startTime + runTime))) {

		return true;
	}
	return false;
}

// Called once after isFinished returns true
void AutoDriveCommand::End()
{
	CleanUp();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDriveCommand::Interrupted()
{
	CleanUp();
}
void AutoDriveCommand::CleanUp()
{
	Robot::driveSubsystem->ArcadeDrive(0.0,0.0);
}
