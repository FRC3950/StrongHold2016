#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	Joystick *joystick;
	Joystick *xBoxControler;
	JoystickButton *SolenoidTest;
public:
	OI();
	float getJoystickX();
	float getJoystickY();
	float getjoystickTwist();
	float getManipulatorSpeed();
};

#endif
