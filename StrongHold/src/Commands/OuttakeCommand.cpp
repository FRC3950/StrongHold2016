#include "../Robot.h"
#include "OuttakeCommand.h"
#include "../Logging.h"

OuttakeCommand::OuttakeCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::intakeSubsystem.get());
	Logger *logger = Logger::GetInstance();

	logger->Log(IntakeSubsystemLogId, Logger::kTRACE, "OuttakeCommand::ctor Entering");
}

// Called just before this Command runs the first time
void OuttakeCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void OuttakeCommand::Execute()
{
	Robot::intakeSubsystem->SetIntakeMotor(IntakeSubsystem::Out);
}

// Make this return true when this Command no longer needs to run execute()
bool OuttakeCommand::IsFinished()
{
	Logger::GetInstance()->Log(IntakeSubsystemLogId, Logger::kTRACE, "OuttakeCommand::IsFinished");
	if (Robot::oi->getOuttakeTrigger() || !Robot::oi->getOuttakeButton()){
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void OuttakeCommand::End()
{
	Robot::intakeSubsystem->SetIntakeMotor(IntakeSubsystem::Neutral);

	Logger::GetInstance()->Log(IntakeSubsystemLogId, Logger::kTRACE, "OuttakeCommand::End");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OuttakeCommand::Interrupted()
{
	Robot::intakeSubsystem->SetIntakeMotor(IntakeSubsystem::Neutral);
	Logger::GetInstance()->Log(IntakeSubsystemLogId, Logger::kTRACE, "OuttakeCommand::Interrupted");
}
