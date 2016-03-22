#include "ManipulatorSubsystem.h"
#include "../Commands/ManipulatorCommand.h"
#include "../RobotMap.h"
#include "../Logging.h"
#include "../UtilFun.h"

namespace {
	double UpPosCount = 0.0;
	double IntakePosCount = 997.0;
	double DownPosCount = 1350.00;

	double LessThanPosMotorSpeed = .5;
	double GreaterThanPosMotorSpeed = -.5;

	double speedMod = .005;

	double SeekPosRagePositive = 10;
	double SeekPosRangeNegitive = -10;

	const float UP_MANIPULATOR_SPEED = -0.5;
	const float DOWN_MANIPULATOR_SPEED = 0.5;

	const float HOME_POS_FINDING_SPEED = UP_MANIPULATOR_SPEED;


	auto SeekPosToCountsMap = std::map<ManipulatorSubsystem::SeekManipulatorPos, double>() = {
			{ ManipulatorSubsystem::Up, UpPosCount },
			{ ManipulatorSubsystem::Down, DownPosCount },
			{ ManipulatorSubsystem::Intake, IntakePosCount }
	};
}
ManipulatorSubsystem::ManipulatorSubsystem() :
		Subsystem("ManipulatorSubsystem")
{
	manipulatorMotor = RobotMap::intakeSubsystemManipulatorMotor;
#if UPPER_LIMIT_SWITCH
	upperLimitSwitch = RobotMap::intakeSubsystemUpperLimitSwitch;
#endif
	FindHomePosition(true);
}

void ManipulatorSubsystem::InitDefaultCommand()
{
	SetDefaultCommand(new ManipulatorCommand());
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}
bool ManipulatorSubsystem::CheckUpperLimitSwitch()
{
	bool limitHit = false;

	if (upperLimitSwitch) {
		uint32_t switchState = upperLimitSwitch->Get();
		// This assumes the limit switch is normally closed
		// and reading non-zero
		// When it reads zero, the switch is open, indicating the limit was hit.
		limitHit = (switchState == 0) ? false : true;

		if (limitHit)
		{
			Logger::GetInstance()->Log(IntakeSubsystemLogId, Logger::kWARNING, "*** Intake Upper Limit Switch Hit ***");

		}
	}
	return limitHit;
}
void ManipulatorSubsystem::FindHomePosition(bool forceFind) {

	// Check to see if the pot floor has already been
	// found.  Don't check for it again.
	if (!forceFind && homePositionSet) {
		return;
	}

	if (upperLimitSwitch) {
		if (!CheckUpperLimitSwitch()) {
			manipulatorMotor->Set(HOME_POS_FINDING_SPEED);
			while (!CheckUpperLimitSwitch()) {
	//                System.out.println("Moving the shooter down.");
			}
		}
	}

	manipulatorMotor->Set(0.0);
	manipulatorMotor->SetPosition(0.0);
	homePositionSet = true;
}
void ManipulatorSubsystem::MoveManipulator(float vertVelocity) {
	if (vertVelocity > 0 && CheckUpperLimitSwitch()){
		vertVelocity = 0;
	}
	manipulatorMotor->Set(vertVelocity);
	SmartDashboard::PutNumber("Current manipulator pos", GetManipulatorPos());
}

bool ManipulatorSubsystem::SetManipulatorSeekPosition(SeekManipulatorPos pos) {
	auto it = SeekPosToCountsMap.find(pos);

	if (it == SeekPosToCountsMap.end()) {
		return false;
	}

	seekPos = pos;
	manipMotorCountTarget = it->second;
	hasManipulatorReachedPos();
	return true;
}

bool ManipulatorSubsystem::hasManipulatorReachedPos() {
	if (seekPos == None){
		manipulatorMotor->Set(0.0);
		return true;
	}

	double currPos = manipulatorMotor->GetPosition();

	if (InRangeInclusive(currPos,SeekPosRagePositive,SeekPosRangeNegitive)){
		manipulatorMotor->Set(0.0);
		seekPos = None;
		return true;
	}
	else {
		double speed = (manipMotorCountTarget - currPos) * speedMod;
		if (speed > 1){
			speed = 1;
		}
		else if (speed < -1) {
			speed = -1;
		}
		manipulatorMotor->Set(speed);
	}
//	else if (currPos > manipMotorCountTarget){
//		if (!CheckUpperLimitSwitch()){
//			manipulatorMotor->Set(GreaterThanPosMotorSpeed);
//		}
//		else {
//			manipulatorMotor->Set(0.0);
//			seekPos = None;
//			return true;
//		}
//	}
//	else {
//		manipulatorMotor->Set(LessThanPosMotorSpeed);
//	}

	return false;
}

void ManipulatorSubsystem::cancelManipulatorSeek() {
	seekPos = None;
	manipulatorMotor->Set(0.0);

}
double ManipulatorSubsystem::GetManipulatorPos(){
	return manipulatorMotor->GetPosition();
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
