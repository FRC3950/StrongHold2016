#include "StopShooterCommand.h"
#include "Robot.h"
#include "Logging.h"
StopShooterCommand::StopShooterCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::shooterSubsystem.get());
}

// Called just before this Command runs the first time
void StopShooterCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void StopShooterCommand::Execute()
{
	Robot::shooterSubsystem->SetTargetSpeed(0);
	Logger *logger = Logger::GetInstance();

	logger->Log(ShooterSubsystemLogId, Logger::kTRACE, "StopShooterCommand::Execute -> Enter");
}

// Make this return true when this Command no longer needs to run execute()
bool StopShooterCommand::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void StopShooterCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopShooterCommand::Interrupted()
{

}
