#include "../robot.h"
#include "TwistToggleCommand.h"

TwistToggleCommand::TwistToggleCommand()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::driveSubsystem.get());
}

// Called just before this Command runs the first time
void TwistToggleCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void TwistToggleCommand::Execute()
{
	Robot::driveSubsystem->twistMode = !Robot::driveSubsystem->twistMode;
}

// Make this return true when this Command no longer needs to run execute()
bool TwistToggleCommand::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void TwistToggleCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TwistToggleCommand::Interrupted()
{

}
