#include "ShootCommand.h"
#include "../Robot.h"
#include "../Logging.h"
#include "../ConfigKeys.h"
#include "../Config/ConfigInstanceMgr.h"

ShootCommand::ShootCommand()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::shooterSubsystem.get());
}

// Called just before this Command runs the first time
void ShootCommand::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void ShootCommand::Execute()
{
	if (!inited) {
		inited = true;
		Robot::shooterSubsystem->SetTargetSpeed(getTargetRotationsPerSecond());
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ShootCommand::IsFinished()
{
//	if (Robot::shooterSubsystem->HasHitTargetSpeed()){
//		SmartDashboard::PutBoolean("Has hit target speed", true);
//	}
//	SmartDashboard::PutBoolean("Has hit target speed", false);
	return false;
}

// Called once after isFinished returns true
void ShootCommand::End()
{
	cleanup();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootCommand::Interrupted()
{
	cleanup();
}

void ShootCommand::cleanup() {
	inited = false;
	Robot::shooterSubsystem->SetTargetSpeed(0);
}
