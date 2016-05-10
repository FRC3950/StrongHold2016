#include "ClimberSubsystem.h"
#include "../RobotMap.h"


ClimberSubsystem::ClimberSubsystem() :
		Subsystem("ExampleSubsystem")
{
	motor = RobotMap::climberSubsystemMotor;
	motor2 = RobotMap::climberSubsystemMotor2;
	limitSwitch = RobotMap::climberSubsystemLimitSwitch;
}

void ClimberSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void ClimberSubsystem::LaunchClimber(){
//	if (!limitSwitch->Get()){
		motor->Set(0.5f);
		motor2->Set(0.5f);
//	}
}
void ClimberSubsystem::stopClimber(){
	motor->Set(0.0);
	motor2->Set(0.0);
}
void ClimberSubsystem::dropClimber() {
	motor->Set(-0.3);
	motor2->Set(-0.3);
}
bool ClimberSubsystem::inClimbState(){
	return false;//limitSwitch->Get();
}
