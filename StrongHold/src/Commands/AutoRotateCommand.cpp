#include "AutoRotateCommand.h"
#include "Robot.h"
namespace {
	float AutoRotateSpeed = 0.9;
}


AutoRotateCommand::AutoRotateCommand(double time) : runTime(time)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::driveSubsystem.get());
}

// Called just before this Command runs the first time
void AutoRotateCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void AutoRotateCommand::Execute()
{
	if (!inited) {
				startTime = Timer::GetFPGATimestamp();
				inited = true;

		}
		Robot::driveSubsystem->ArcadeDrive(0,AutoRotateSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool AutoRotateCommand::IsFinished()
{
	if (inited && (Timer::GetFPGATimestamp() >= (startTime + runTime))) {
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void AutoRotateCommand::End()
{
	CleanUp();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoRotateCommand::Interrupted()
{
	CleanUp();
}
void AutoRotateCommand::CleanUp()
{
	Robot::driveSubsystem->ArcadeDrive(0.0,0.0);
}
