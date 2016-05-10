#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	std::shared_ptr<Joystick> joystick;
	std::shared_ptr<Joystick> xBoxControler;
	std::shared_ptr<JoystickButton> LaunchClimberButton;
	std::shared_ptr<JoystickButton> ToggleHoodButton;
	std::shared_ptr<JoystickButton> HomePosButton;   //may condense these three buttons later
	std::shared_ptr<JoystickButton> IntakePosButton; //
	std::shared_ptr<JoystickButton> DownPosButton;   //____
	std::shared_ptr<JoystickButton> ReadyShootButton;// may be unnecessary
	std::shared_ptr<JoystickButton> ShootButton;
	std::shared_ptr<JoystickButton> ShiftGearButton;
	std::shared_ptr<JoystickButton> PowerTakeOffButton;
	std::shared_ptr<JoystickButton> ResetToDriveButton;
	std::shared_ptr<JoystickButton> VisionOnButton;
	std::shared_ptr<JoystickButton> VisionOffButton;
	std::shared_ptr<JoystickButton> IntakeButton;
	std::shared_ptr<JoystickButton> StopIntakeButton;
	std::shared_ptr<JoystickButton> OuttakeButton;
	std::shared_ptr<JoystickButton> KillIntakeAndShootCommand;
	std::shared_ptr<JoystickButton> ToggleTwistControlButton;
	std::shared_ptr<JoystickButton> ToggleDriveDirectionButton;
	std::shared_ptr<JoystickButton> dropClimberButton;
	//possibly add shoot buttons for different distances or just base it off vision.

public:
	OI();
	float getJoystickX();
	float getJoystickY();
	float getjoystickTwist();

	float getManipulatorSpeed();
	bool getOuttakeTrigger();

	bool getLaunchClimberButton();
	bool getOuttakeButton();
	bool getDropClimberButton();
};

#endif
