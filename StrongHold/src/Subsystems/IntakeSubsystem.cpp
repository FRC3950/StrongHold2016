#include "IntakeSubsystem.h"
#include "../RobotMap.h"

IntakeSubsystem::IntakeSubsystem() :
		Subsystem("ExampleSubsystem")
{
	intakeMotor = RobotMap::intakeSubsystemRollerVictor;
	manipulatorMotor = RobotMap::intakeSubsystemManipulatorVictor;
}

void IntakeSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

//TO DO: make constants for motor values
void IntakeSubsystem::SetIntakeMotors(IntakeDirection id){
	if (id == IntakeDirection::in){
		intakeMotor->Set(-1.0f);
	}
	else if (id == IntakeDirection::neutral){
		intakeMotor->Set(0.0f);
	}
	else{
		intakeMotor->Set(1.0f);
	}
}
