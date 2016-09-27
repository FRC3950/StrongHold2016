#include "OI.h"
#include "Commands\TogglePowerTakeOffCommand.h"

OI::OI() {
	// Process operator interface input here.
	joystick = new Joystick(0);
	xBoxControler = new Joystick(1);
	SolenoidTest = new JoystickButton(joystick,3);

	SolenoidTest->WhenPressed(new TogglePowerTakeOffCommand());
}

float OI::getJoystickX(){
	return joystick->GetX();
}

float OI::getJoystickY(){
	return joystick->GetY();
}

float OI::getjoystickTwist(){
	return joystick->GetTwist();
}
float OI::getManipulatorSpeed(){
	return xBoxControler->GetAxis(Joystick::AxisType::kYAxis);
}

