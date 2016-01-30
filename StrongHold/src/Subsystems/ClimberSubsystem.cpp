#include "ClimberSubsystem.h"
#include "../RobotMap.h"


ClimberSubsystem::ClimberSubsystem() :
		Subsystem("ExampleSubsystem")
{
	solenoid1 = RobotMap::climberSubsystemSolenoid1;
	solenoid2 = RobotMap::climberSubsystemSolenoid2;
}

void ClimberSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void ClimberSubsystem::LaunchClimber(){

}
