#include "../Robot.h"
#include "IntakeCommand.h"
#include "../Logging.h"

namespace {
	const double DEFAULT_RUN_TIME = 0;
}
IntakeCommand::IntakeCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::intakeSubsystem.get());
	InitMembers();
}

// Called just before this Command runs the first time
void IntakeCommand::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void IntakeCommand::Execute()
{
	if (currState == Init) {
		Robot::intakeSubsystem->SetIntakeMotor(IntakeSubsystem::In);
		currState = WaitBallLoaded;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool IntakeCommand::IsFinished()
{
	switch (currState) {
	case Init:
		return false;

	case WaitBallLoaded:
		return WaitBallLoadedState();

	case WaitTime:
		return WaitTimeState();

	case Done:
		return true;

	default:
		Logger::GetInstance()->Log(IntakeSubsystemLogId, Logger::kERROR, "IntakeCommand::IsFinished->Unrecognized state %d, switching to Done State", currState);
		return false;
	}
}

bool IntakeCommand::WaitBallLoadedState() {
	if (Robot::intakeSubsystem->IsBallLoaded()) {
		startTime = Timer::GetFPGATimestamp();
		currState = WaitTime;
	}

	return false;
}

bool IntakeCommand::WaitTimeState() {
	double currTime = Timer::GetFPGATimestamp();

	if (currTime > startTime) {
		startTime = currTime;
		return false;
	}

	timeWaited += (currTime - startTime);

	if (timeWaited >= runTime) {
		Robot::intakeSubsystem->SetIntakeMotor(IntakeSubsystem::Neutral);
		currState = Done;
		return true;
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
}

void IntakeCommand::Cleanup()
{
	InitMembers();
	Robot::intakeSubsystem->SetIntakeMotor(IntakeSubsystem::Neutral);
}
