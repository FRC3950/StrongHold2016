#include "../Robot.h"
#include "IntakeCommand.h"
#include "../Logging.h"


namespace {
	const double DEFAULT_RUN_TIME = 1.0;
}
IntakeCommand::IntakeCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::intakeSubsystem.get());
	InitMembers();
	isBallDetectedOnStart = false;
}

// Called just before this Command runs the first time
void IntakeCommand::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void IntakeCommand::Execute()
{
	if (currState == Init && Robot::oi->getOuttakeTrigger()) {
		Logger *logger = Logger::GetInstance();
		logger->Log(IntakeSubsystemLogId, Logger::kTRACE, "IntakeCommand::Execute->Setting Intake to In");

		Robot::intakeSubsystem->SetIntakeMotor(IntakeSubsystem::In);
		if (Robot::intakeSubsystem->IsBallLoaded()){
			isBallDetectedOnStart = true;
		}
		currState = WaitBallLoaded;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool IntakeCommand::IsFinished()
{
	Logger *logger = Logger::GetInstance();

	switch (currState) {
	case Init:
		logger->Log(IntakeSubsystemLogId, Logger::kTRACE, "IntakeCommand::IsFinished->currState = Init");
		return false;

	case WaitBallLoaded:
		logger->Log(IntakeSubsystemLogId, Logger::kTRACE, "IntakeCommand::IsFinished->currState = WaitBallLoaded");
		return WaitBallLoadedState();

	case WaitTime:
		logger->Log(IntakeSubsystemLogId, Logger::kTRACE, "IntakeCommand::IsFinished->currState = WaitTime");
		return WaitTimeState();

	case ReleseWait:
		if (Robot::oi->getOuttakeTrigger()){
			return false;
		}
		else {
			currState = Done;
			return true;
		}

	case Done:
		logger->Log(IntakeSubsystemLogId, Logger::kTRACE, "IntakeCommand::IsFinished->currState = Done");
		return true;

	default:
		logger->Log(IntakeSubsystemLogId, Logger::kERROR, "IntakeCommand::IsFinished->Unrecognized state %d, switching to Done State", currState);
		return false;
	}
}

bool IntakeCommand::WaitBallLoadedState() {
	if (Robot::intakeSubsystem->IsBallLoaded() && !isBallDetectedOnStart) {
		Logger *logger = Logger::GetInstance();
		logger->Log(IntakeSubsystemLogId, Logger::kTRACE, "IntakeCommand::WaitBallLoadedState->Ball is LOADED!");
		startTime = Timer::GetFPGATimestamp();
		currState = WaitTime;
	}
	if (!Robot::oi->getOuttakeTrigger()){
		Robot::intakeSubsystem->SetIntakeMotor(IntakeSubsystem::Neutral);
		Cleanup();
	}

	return false;
}

bool IntakeCommand::WaitTimeState() {
	Logger *logger = Logger::GetInstance();
	double currTime = Timer::GetFPGATimestamp();

	if (currTime < startTime) {
		logger->Log(IntakeSubsystemLogId, Logger::kTRACE, "IntakeCommand::WaitTimeState->TIME ROLL OVER RESETTING!");

		startTime = currTime;
		return false;
	}

	timeWaited = (currTime - startTime);

	if (timeWaited >= runTime) {
		Robot::intakeSubsystem->SetIntakeMotor(IntakeSubsystem::Neutral);
		currState = ReleseWait;
		logger->Log(IntakeSubsystemLogId, Logger::kTRACE, "IntakeCommand::WaitTimeState->WAIT TIME EXCEEDED! RETURNING true");
	}
	if (!Robot::oi->getOuttakeTrigger()){
		Robot::intakeSubsystem->SetIntakeMotor(IntakeSubsystem::Neutral);
		Cleanup();
	}

	return false;
}

// Called once after isFinished returns true
void IntakeCommand::End()
{
	Cleanup();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeCommand::Interrupted()
{
	Cleanup();
}

void IntakeCommand::InitMembers() {
	currState = Init;
	timeWaited = 0.0;
	runTime = DEFAULT_RUN_TIME;
	isBallDetectedOnStart = false;
}

void IntakeCommand::Cleanup()
{
	InitMembers();
	Robot::intakeSubsystem->SetIntakeMotor(IntakeSubsystem::Neutral);
}
