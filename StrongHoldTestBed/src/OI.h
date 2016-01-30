#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	Joystick *joystick;
public:
	OI();
	float getJoystickX();
	float getJoystickY();
	float getjoystickTwist();
};

#endif
