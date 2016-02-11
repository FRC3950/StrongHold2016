#include "OI.h"
#include "Subsystems/IntakeSubsystem.h"
#include "Commands/LaunchClimberCommand.h"
#include "Commands/ToggleShooterHoodCommand.h"
#include "Commands/ManipulatorSeekPosCommand.h"
#include "Commands/ShootCommand.h"
#include "Commands/ShootCommandGroup.h"

OI::OI() {
	// Process operator interface input here.
	//joystick.reset(new Joystick(0));
	xBoxControler.reset(new Joystick(1));

	LaunchClimberButton.reset(new JoystickButton(xBoxControler.get(),0));
	ToggleHoodButton.reset(new JoystickButton(xBoxControler.get(),1));
	HomePosButton.reset(new JoystickButton(xBoxControler.get(),2));
	IntakePosButton.reset(new JoystickButton(xBoxControler.get(),3));
	DownPosButton.reset(new JoystickButton(xBoxControler.get(),4));
	ReadyShootButton.reset(new JoystickButton(xBoxControler.get(),5));
	ShootButton.reset(new JoystickButton(xBoxControler.get(),6));

	//LaunchClimberButton->WhenPressed(new LaunchClimberCommand());
	//ToggleHoodButton->WhenPressed(new ToggleShooterHoodCommand());
	//HomePosButton->WhenPressed(new ManipulatorSeekPosCommand(IntakeSubsystem::SeekManipulatorPos::Up));
	//IntakePosButton->WhenPressed(new ManipulatorSeekPosCommand(IntakeSubsystem::SeekManipulatorPos::Intake));
	//DownPosButton->WhenPressed(new ManipulatorSeekPosCommand(IntakeSubsystem::SeekManipulatorPos::Down));
	ReadyShootButton->WhenPressed(new ShootCommand());
	//ShootButton->WhenPressed(new ShootCommandGroup());
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
