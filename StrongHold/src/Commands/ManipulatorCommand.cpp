#include "ManipulatorCommand.h"
#include "../Robot.h"
#include "../UtilFun.h"

namespace {
	float joyStickPositiveEpsilon = 0.2;
	float joyStickNegitiveEpsilon = -0.2;

	float HoldPosSpeedPrecent = .05;

	double HoldPosRange = 1;



}
ManipulatorCommand::ManipulatorCommand()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::manipulatorSubsystem.get());
	holdPos = 0.0;
	holdPosSet = false;
}

// Called just before this Command runs the first time
void ManipulatorCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ManipulatorCommand::Execute()
{
	float y = Robot::oi->getManipulatorSpeed();
	y =  ModifyJoystickValues(y,3.0f);
	y = ZeroIfInRangeInclusive(y,joyStickPositiveEpsilon,joyStickNegitiveEpsilon);
	Robot::manipulatorSubsystem->MoveManipulator(y);

	// end of code for manual control. beginning of code for holding position
	/*
	if (y == 0 && !holdPosSet){
		// checks if the joystick was let go of and the target point has not been set
		holdPos = Robot::manipulatorSubsystem->GetManipulatorPos();
		holdPosSet = true;
	}
	float speed = 0;
	if (y == 0 && !IsInRangeOfHoldPos() && holdPosSet){
		//checks if the manipulator is out of range of the target pos

		// if its out of range it calculates a speed based on the difference between
		// the target and the position
		speed = holdPos - Robot::manipulatorSubsystem->GetManipulatorPos();
		speed *= HoldPosSpeedPrecent;
		if (speed > 1){
			speed = 1;
		}
		else if (speed < -1) {
			speed = -1;
		}
		Robot::manipulatorSubsystem->MoveManipulator(speed);
	}
	else if (y == 0 && IsInRangeOfHoldPos()){
		// checks if the manipulator has hit the target and if so sets the movement is 0
		Robot::manipulatorSubsystem->MoveManipulator(0.0);
	}
	if (holdPosSet && y != 0){ // resets the holdPosSet bool if the driver began moving the
		                       // manipulator agian
		holdPosSet = false;
	}
	*/
}

// Make this return true when this Command no longer needs to run execute()
bool ManipulatorCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ManipulatorCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ManipulatorCommand::Interrupted()
{

}
bool ManipulatorCommand::IsInRangeOfHoldPos(){
	if (Robot::manipulatorSubsystem->GetManipulatorPos() > (holdPos - HoldPosRange) &&
			Robot::manipulatorSubsystem->GetManipulatorPos() < (holdPos + HoldPosRange)) {
		return true;
	}
	return false;
}
