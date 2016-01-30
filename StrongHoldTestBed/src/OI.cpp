#include "OI.h"

OI::OI() {
	// Process operator interface input here.
	joystick = new Joystick(0);
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
