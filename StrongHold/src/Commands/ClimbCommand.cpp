#include <Commands/ClimbCommand.h>
#include "../Robot.h"
#include "../Logging.h"
#include "JoystickConstants.h"
#include "../UtilFun.h"


ClimbCommand::ClimbCommand()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::driveSubsystem.get());
	Logger::GetInstance()->Log(ClimbingLogId, Logger::kTRACE, "Climb Constructor Call");
}

// Called just before this Command runs the first time
void ClimbCommand::Initialize()
{
	Logger::GetInstance()->Log(ClimbingLogId, Logger::kTRACE, "Climb intit");
}

// Called repeatedly when this Command is scheduled to run
void ClimbCommand::Execute()
{
	Logger::GetInstance()->Log(ClimbingLogId, Logger::kTRACE, "ClimbCommand::Execute Enter() %d", Robot::driveSubsystem->InClimbMode());
	if (!Robot::driveSubsystem->InClimbMode()) {
		Robot::driveSubsystem->SetMode(DriveSubsystem::ClimbingMode);
	}
	float y = Robot::oi->getJoystickY();

	y = ZeroIfInRangeInclusive(y,-Y_VAL_EPSILON_RANGE,Y_VAL_EPSILON_RANGE);
	Robot::driveSubsystem->Climb(y);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimbCommand::IsFinished()
{
	Logger::GetInstance()->Log(ClimbingLogId, Logger::kTRACE, "ClimbCommand::IsFinished() Enter");
	return false;
}

// Called once after isFinished returns true
void ClimbCommand::End()
{
	Logger::GetInstance()->Log(ClimbingLogId, Logger::kTRACE, "ClimbCommand::End() Enter");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimbCommand::Interrupted()
{
	Logger::GetInstance()->Log(ClimbingLogId, Logger::kTRACE, "ClimbCommand::Interrupted() Enter");
}
