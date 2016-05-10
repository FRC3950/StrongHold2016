#include "HoodSubsystem.h"
#include "../RobotMap.h"

HoodSubsystem::HoodSubsystem() :
		Subsystem("ExampleSubsystem")
{
	hoodSolenoid = RobotMap::shooterSubsystemShooterCoverSolenoid;

}

void HoodSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}
void HoodSubsystem::SetHoodState(HoodState hs){
	if (hs == HoodState::open){
		hoodSolenoid.get()->Set(true);
	}
	else if (hs == HoodState::closed){
		hoodSolenoid.get()->Set(false);
	}

}
void HoodSubsystem::ToggleHood(){
	if (hoodSolenoid->Get() == true){
		hoodSolenoid->Set(false);
	}
	else {
		hoodSolenoid->Set(true);
	}
}

HoodSubsystem::HoodState HoodSubsystem::GetHoodState(){
	return hoodSolenoid->Get() == true ? HoodState::open : HoodState::closed;
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
