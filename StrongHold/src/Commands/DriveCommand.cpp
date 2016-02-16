#include "DriveCommand.h"
#include "../Logging.h"
#include "../Robot.h"
#include "../Subsystems/DriveSubsystem.h"
#include <math.h>
namespace{
	const float JOYSTICK_Y_DEFAULT_MODIFIER = 1.0f;
	const float JOYSTICK_TWIST_DEFAULT_MODIFIER = .9f;

	const float Y_VAL_EPSILON_RANGE = .02;
	const float TWIST_VAL_EPSILON_RANGE = .02;

	const float FLOOR = 0.001f; // do not set to zero

	float ModifyJoystickValues(float val,float power){
		float out = pow(val,power);
		if ((val < 0 && out > 0)||(val > 0 && out < 0)) {
			out *= -1;
		}
		return out;
	}
	float inRangeExclusive(float val, float range){
		if (val < range && val > -range){
			return 0;
		}
		return val;
	}
	float floorVal(float val){
		if (val > 0.0 && val < FLOOR){
			return FLOOR;
		}
		else if (val < 0.0 && val > (-FLOOR)){
			return -FLOOR;
		}
		return val;
	}
}
DriveCommand::DriveCommand()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::driveSubsystem.get());
}

// Called just before this Command runs the first time
void DriveCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void DriveCommand::Execute()
{
	Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "DriveCommand::Execute Enter()");

	if (!Robot::driveSubsystem->inDriveMode()) {
		Robot::driveSubsystem->SetMode(DriveSubsystem::drive);
	}
	//float x = Robot::oi->getJoystickX();
	float y = -Robot::oi->getJoystickY();
	float twist = -Robot::oi->getjoystickTwist();

	Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "DriveCommand::Execute()Raw values: y=%f, twist=%f", y, twist);

	y = inRangeExclusive(y,Y_VAL_EPSILON_RANGE);
	twist = inRangeExclusive(twist, TWIST_VAL_EPSILON_RANGE);

	Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "DriveCommand::Execute() After inRange y=%f, twist=%f", y, twist);

	y *= JOYSTICK_Y_DEFAULT_MODIFIER;
	twist *= JOYSTICK_TWIST_DEFAULT_MODIFIER;

	Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "DriveCommand::Execute() After Modifier y=%f, twist=%f", y, twist);

	y = ModifyJoystickValues(y,2.0f);
	//twist = ModifyJoystickValues(twist,2.0f);

	Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "DriveCommand::Execute() After squaring y=%f, twist=%f", y, twist);

	y = floorVal(y);
	twist = floorVal(twist);

	Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "DriveCommand::Execute() After flooring y=%f, twist=%f", y, twist);

	Robot::driveSubsystem->ArcadeDrive(y,twist);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void DriveCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveCommand::Interrupted()
{
}
