#include "OI.h"
#include "Logging.h"
#include "Subsystems/IntakeSubsystem.h"
#include "Commands/LaunchClimberCommand.h"
#include "Commands/ToggleShooterHoodCommand.h"
#include "Commands/ManipulatorSeekPosCommand.h"
#include "Commands/DashboardShootCommand.h"
#include "Commands/DefultValueShootCommand.h"
#include "Commands/ShootCommandGroup.h"
#include "Commands/ToggleGearCommand.h"
#include "Commands/ClimbCommand.h"
#include "Commands/DriveSubsystemInteruptCommand.h"
#include "Commands/VisionOnCommand.h"
#include "Commands/VisionOffCommand.h"
#include "Commands/IntakeCommand.h"
#include "Commands/OuttakeCommand.h"
#include "Commands/StopIntakeCommand.h"
#include "Commands/StopShootAndIntakeCommandGroup.h"
#include "Commands/TwistToggleCommand.h"
#include "Commands/ToggleDriveDirectionCommand.h"
#include "Commands/DropClimberCommand.h"

OI::OI() {
	// Process operator interface input here.
	Logger *logger = Logger::GetInstance();

	logger->Log(OILogId, Logger::kTRACE, "OI::ctor Entering");

#if 1
	joystick.reset(new Joystick(0));
	xBoxControler.reset(new Joystick(1));

	logger->Log(OILogId, Logger::kTRACE, "OI::ctor Created Joysticks");

	LaunchClimberButton.reset(new JoystickButton(xBoxControler.get(),3));
	ToggleHoodButton.reset(new JoystickButton(xBoxControler.get(),6));
	//HomePosButton.reset(new JoystickButton(xBoxControler.get(),2));
	//IntakePosButton.reset(new JoystickButton(xBoxControler.get(),4));
	//DownPosButton.reset(new JoystickButton(xBoxControler.get(),3));
	ReadyShootButton.reset(new JoystickButton(xBoxControler.get(),1));
	//ShootButton.reset(new JoystickButton(xBoxControler.get(),6));
	//IntakeButton.reset(new JoystickButton(xBoxControler.get(),5));
	//StopIntakeButton.reset(new JoystickButton(xBoxControler.get(),2));
	OuttakeButton.reset(new JoystickButton(xBoxControler.get(),5));
	ShiftGearButton.reset(new JoystickButton(joystick.get(),4));
	PowerTakeOffButton.reset(new JoystickButton(joystick.get(),9));
	ResetToDriveButton.reset(new JoystickButton(joystick.get(),12));
	VisionOnButton.reset(new JoystickButton(joystick.get(),7));
	VisionOffButton.reset(new JoystickButton(joystick.get(),8));
	KillIntakeAndShootCommand.reset(new JoystickButton(xBoxControler.get(),2));
	ToggleTwistControlButton.reset(new JoystickButton(joystick.get(),5));
	ToggleDriveDirectionButton.reset(new JoystickButton(joystick.get(),6));
	dropClimberButton.reset(new JoystickButton(xBoxControler.get(),4));

#endif
	logger->Log(OILogId, Logger::kTRACE, "OI::ctor Created Joystick Buttons");

	//IntakePosButton->WhenPressed(new ManipulatorSeekPosCommand(ManipulatorSubsystem::SeekManipulatorPos::Intake));

	logger->Log(OILogId, Logger::kTRACE, "OI::ctor Intake Command assigned.");

#if 1
	LaunchClimberButton->WhenPressed(new LaunchClimberCommand());
	ToggleHoodButton->WhenPressed(new ToggleShooterHoodCommand());
	//IntakePosButton->WhenPressed(new ManipulatorSeekPosCommand(ManipulatorSubsystem::SeekManipulatorPos::Intake));
	//DownPosButton->WhenPressed(new ManipulatorSeekPosCommand(ManipulatorSubsystem::SeekManipulatorPos::Down));
	ReadyShootButton->WhenPressed(new DefultValueShootCommand());
	//ShootButton->WhenPressed(new ShootCommandGroup());
	ShiftGearButton->WhenPressed(new ToggleGearCommand());
	PowerTakeOffButton->WhenPressed(new ClimbCommand());
	ResetToDriveButton->WhenPressed(new DriveSubsystemInteruptCommand());
//	IntakeButton->WhenPressed(new IntakeCommand());
//	StopIntakeButton->WhenPressed(new StopIntakeCommand());
	OuttakeButton->WhileHeld(new OuttakeCommand());
	VisionOnButton->WhenPressed(new VisionOnCommand());
	VisionOffButton->WhenPressed(new VisionOffCommand());
	KillIntakeAndShootCommand->WhenPressed(new StopShootAndIntakeCommandGroup());
	ToggleTwistControlButton->WhenPressed(new TwistToggleCommand());
	ToggleDriveDirectionButton->WhenPressed(new ToggleDriveDirectionCommand());
	dropClimberButton->WhenPressed(new DropClimberCommand());
#endif

	logger->Log(OILogId, Logger::kTRACE, "OI::ctor Assigned Commands to Joystick Buttons");

	logger->Log(OILogId, Logger::kTRACE, "OI::ctor Exiting");
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
bool OI::getOuttakeTrigger() {
	return xBoxControler->GetAxis(Joystick::AxisType::kThrottleAxis) > .5f;
}
bool OI::getLaunchClimberButton() {
	return LaunchClimberButton->Get();
}
bool OI::getOuttakeButton(){
	return OuttakeButton->Get();
}
bool OI::getDropClimberButton() {
	return dropClimberButton->Get();
}
