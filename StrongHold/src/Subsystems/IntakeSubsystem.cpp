#include "IntakeSubsystem.h"
#include "../RobotMap.h"

IntakeSubsystem::IntakeSubsystem() :
		Subsystem("ExampleSubsystem")
{
	intakeMotor = RobotMap::intakeSubsystemRollerVictor;
	manipulatorMotor = RobotMap::intakeSubsystemManipulatorVictor;
	photoSensor = RobotMap::intakeSubsystemPhotoSensor;
}

void IntakeSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

//TO DO: make constants for motor values
void IntakeSubsystem::SetIntakeMotors(IntakeDirection id, bool usePhotoSensor) {
	float speed = 0.0f;

	if (id == IntakeDirection::in){
		if (!usePhotoSensor || (usePhotoSensor && !IsBallLoaded())) {
			speed = -1.0f;
		}
	}
	else if (id == IntakeDirection::out) {
		speed = 1.0f;
	}

	intakeMotor->Set(speed);
}
bool IntakeSubsystem::IsBallLoaded() {

	return false;
}

void IntakeSubsystem::MoveManipulator(float vertVelocity) {


}

void IntakeSubsystem::SetManipulatorSeekPosition(ManipulatorPos pos) {


}

bool IntakeSubsystem::hasManipulatorReachedPos() {

	return true;
}

void IntakeSubsystem::cancelManipulatorSeek() {


}

