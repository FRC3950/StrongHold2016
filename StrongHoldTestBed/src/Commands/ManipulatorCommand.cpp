#include "ManipulatorCommand.h"
#include "../Robot.h"
#include "../UtilFun.h"

namespace {
	float joyStickPositiveEpsilon = 0.5;
	float joyStickNegitiveEpsilon = -0.5;

}
ManipulatorCommand::ManipulatorCommand()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::intakeSubsystem.get());
}

// Called just before this Command runs the first time
void ManipulatorCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ManipulatorCommand::Execute()
{
	float y = Robot::oi->getManipulatorSpeed();
	Robot::intakeSubsystem->MoveManipulator(ZeroIfInRangeInclusive(y,joyStickPositiveEpsilon,joyStickNegitiveEpsilon));

}

// Make this return true when this Command no longer needs to run execute()
bool ManipulatorCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ManipulatorCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ManipulatorCommand::Interrupted()
{

}
