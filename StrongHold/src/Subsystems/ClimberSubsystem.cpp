#include "ClimberSubsystem.h"
#include "../RobotMap.h"
#include "../Commands/StopClimberCommand.h"


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
	//SetDefaultCommand(new StopClimberCommand());

}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void ClimberSubsystem::LaunchClimber(){
		motor->Set(1.0);
}
void ClimberSubsystem::stopClimber(){
	motor->Set(0.0);
}
void ClimberSubsystem::RetractClimber(){
	motor->Set(-1,0);
}
bool ClimberSubsystem::inClimbState(){
	return limitSwitch->Get();
}
