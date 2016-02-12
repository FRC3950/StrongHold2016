#include "ShootCommand.h"
#include "../Robot.h"
#include "../Logging.h"
#include "../ConfigKeys.h"
#include "../Config/ConfigInstanceMgr.h"


namespace {
	float SHOOTER_WHEELS_ROTATIONS_PER_SECOND_DEFAULT = 100;
	float ShooterWheelsRotationsPerSecond = SHOOTER_WHEELS_ROTATIONS_PER_SECOND_DEFAULT;
}
ShootCommand::ShootCommand()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::shooterSubsystem.get());
}

// Called just before this Command runs the first time
void ShootCommand::Initialize()
{
    ConfigMgr *configMgr = ConfigInstanceMgr::getInstance();

	ShooterWheelsRotationsPerSecond = configMgr->getFloatVal(ConfigKeys::Shooter_RotsPerSecEpsilonKey, SHOOTER_WHEELS_ROTATIONS_PER_SECOND_DEFAULT);

	Logger* logger = Logger::GetInstance();

	logger->Log(ShooterSubsystemLogId,Logger::kINFO, "ShooterCommand: Wheels Rotations / Sec  = %g\n", ShooterWheelsRotationsPerSecond);
}

// Called repeatedly when this Command is scheduled to run
void ShootCommand::Execute()
{
	if (!inited) {
		inited = true;
		Robot::shooterSubsystem->SetTargetSpeed(ShooterWheelsRotationsPerSecond);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ShootCommand::IsFinished()
{
	return Robot::shooterSubsystem->HasHitTargetSpeed();
}

// Called once after isFinished returns true
void ShootCommand::End()
{
	inited = false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootCommand::Interrupted()
{
	inited = false;
}
