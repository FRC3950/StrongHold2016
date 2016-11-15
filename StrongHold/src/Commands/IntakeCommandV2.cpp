#include "IntakeCommandV2.h"
#include "../Robot.h"

IntakeCommandV2::IntakeCommandV2()
{
	Requires (Robot::intakeSubsystem.get());
}

// Called just before this Command runs the first time
void IntakeCommandV2::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void IntakeCommandV2::Execute()
{
	if(Robot::intakeSubsystem->IsBallLoaded() == false){
		Robot::intakeSubsystem->SetIntakeMotor(IntakeSubsystem::In);
	}
	else{
		Robot::intakeSubsystem->SetIntakeMotor(IntakeSubsystem::Neutral);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool IntakeCommandV2::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void IntakeCommandV2::End()
{
	Robot::intakeSubsystem->SetIntakeMotor(IntakeSubsystem::Neutral);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeCommandV2::Interrupted()
{

}
