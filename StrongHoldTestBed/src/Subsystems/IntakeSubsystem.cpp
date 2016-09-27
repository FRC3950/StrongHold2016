#include "IntakeSubsystem.h"
#include "../Commands/ManipulatorCommand.h"
#include "../RobotMap.h"
#include "../Logging.h"
//#include "../ConfigKeys.h"
//#include "../Config/ConfigInstanceMgr.h"
#include <map>
#include "UtilFun.h"

namespace {
	double UpPosCount = 0.0;
	double IntakePosCount = 500.0;
	double DownPosCount = 1000.00;

	double LessThanPosMotorSpeed = .5;
	double GreaterThanPosMotorSpeed = -.5;

	double SeekPosRagePositive = 0.5;
	double SeekPosRangeNegitive = -0.5;

	double PhotoSensorTargetVoltage = 4.0;


	auto SeekPosToCountsMap = std::map<IntakeSubsystem::SeekManipulatorPos, double>() = {
			{ IntakeSubsystem::Up, UpPosCount },
			{ IntakeSubsystem::Down, DownPosCount },
			{ IntakeSubsystem::Intake, IntakePosCount }
	};
}

IntakeSubsystem::IntakeSubsystem() :
		Subsystem("ExampleSubsystem")
{
	intakeMotor = RobotMap::intakeSubsystemIntakeMotor;
	manipulatorMotor = RobotMap::intakeManipulatorIntakeMotor;
	photoSensor = RobotMap::photoSensor;
	upperLimitSwitch = RobotMap::intakeSubsystemUperLimitSwitch;
}

void IntakeSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ManipulatorCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.


bool IntakeSubsystem::CheckUpperLimitSwitch()
{
	uint32_t switchState = upperLimitSwitch->Get();
	// This assumes the limit switch is normally closed
	// and reading non-zero
	// When it reads zero, the switch is open, indicating the limit was hit.
	bool limitHit = (switchState == 0) ? false : true;

	if (limitHit)
	{
		Logger::GetInstance()->Log(IntakeSubsystemLogId, Logger::kWARNING, "*** Intake Upper Limit Switch Hit ***");
	}

	return limitHit;
}

const float UP_MANIPULATOR_SPEED = -0.5;
const float DOWN_MANIPULATOR_SPEED = 0.5;

const float HOME_POS_FINDING_SPEED = UP_MANIPULATOR_SPEED;

void IntakeSubsystem::findHomePosition(bool forceFind) {

	// Check to see if the pot floor has already been
	// found.  Don't check for it again.
	if (!forceFind && homePositionSet) {
		return;
	}

	if (!CheckUpperLimitSwitch()) {
		manipulatorMotor->Set(HOME_POS_FINDING_SPEED);
		while (!CheckUpperLimitSwitch()) {
//                System.out.println("Moving the shooter down.");
		}
	}

	manipulatorMotor->Set(0.0);
	manipulatorMotor->SetPosition(0.0);
	homePositionSet = true;
}

//TO DO: make constants for motor values
void IntakeSubsystem::SetIntakeMotor(IntakeDirection id, bool usePhotoSensor) {
	float speed = 0.0f;

	if (id == IntakeDirection::In){
		if (!usePhotoSensor || (usePhotoSensor && !IsBallLoaded())) {
			speed = -1.0f;
		}
	}
	else if (id == IntakeDirection::Out) {
		speed = 1.0f;
	}

	intakeMotor->Set(speed);
}
bool IntakeSubsystem::IsBallLoaded() {
	if (photoSensor->GetVoltage() > PhotoSensorTargetVoltage){
		return true;
	}
	return false;
}

void IntakeSubsystem::MoveManipulator(float vertVelocity) {
	if (vertVelocity > 0 && CheckUpperLimitSwitch()){
		vertVelocity = 0;
	}
	manipulatorMotor->Set(vertVelocity);

}

bool IntakeSubsystem::SetManipulatorSeekPosition(SeekManipulatorPos pos) {
	auto it = SeekPosToCountsMap.find(pos);

	if (it == SeekPosToCountsMap.end()) {
		return false;
	}

	seekPos = pos;
	manipMotorCountTarget = it->second;
	hasManipulatorReachedPos();
	return true;
}

bool IntakeSubsystem::hasManipulatorReachedPos() {
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
	else if (currPos > manipMotorCountTarget){
		if (!CheckUpperLimitSwitch()){
			manipulatorMotor->Set(GreaterThanPosMotorSpeed);
		}
		else {
			manipulatorMotor->Set(0.0);
			seekPos = None;
			return true;
		}
	}
	else {
		manipulatorMotor->Set(LessThanPosMotorSpeed);
	}
	return false;
}

void IntakeSubsystem::cancelManipulatorSeek() {
	seekPos = None;
	manipulatorMotor->Set(0.0);
}

