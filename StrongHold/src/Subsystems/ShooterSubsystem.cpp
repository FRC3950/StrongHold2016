#include "ShooterSubsystem.h"
#include "../RobotMap.h"

ShooterSubsystem::ShooterSubsystem() :
		Subsystem("ExampleSubsystem")
{
	hoodSolenoid = RobotMap::shooterSubsystemShooterCoverSolenoid;
}

void ShooterSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void ShooterSubsystem::SetHoodState(HoodState hs){
	if (hs == HoodState::open){
		hoodSolenoid.get()->Set(true);
	}
	else if (hs == HoodState::closed){
		hoodSolenoid.get()->Set(false);
	}

}
void ShooterSubsystem::ToggleHood(){
	if (hoodSolenoid->Get() == true){
		hoodSolenoid->Set(false);
	}
	else {
		hoodSolenoid->Set(true);
	}
}

ShooterSubsystem::HoodState ShooterSubsystem::GetHoodState(){
	return hoodSolenoid->Get() == true ? HoodState::open : HoodState::closed;
}
