#include "ClimberSubsystem.h"
#include "../RobotMap.h"


ClimberSubsystem::ClimberSubsystem() :
		Subsystem("ExampleSubsystem")
{
	motor = RobotMap::climberSubsystemMotor;
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
	if (!limitSwitch->Get()){
		motor->Set(1.0);
	}
}
void ClimberSubsystem::stopClimber(){
	motor->Set(0.0);
}
bool ClimberSubsystem::inClimbState(){
	return limitSwitch->Get();
}
