#include "IntakeSubsystem.h"
#include "../RobotMap.h"
#include "../Logging.h"
#include "../ConfigKeys.h"
#include "../Config/ConfigInstanceMgr.h"
#include "../Commands/IntakeCommand.h"
#include "../Commands/StopIntakeCommand.h"
#include <math.h>

namespace {

	inline double convertDistanceToVoltage(double distance) {
		return ((4.282) * exp(-0.158 * distance)) + 0.395;
	}

	const float PhotoSensorTargetVoltage = 2.5;//convertDistanceToVoltage(5.0);
}

IntakeSubsystem::IntakeSubsystem() :
		Subsystem("IntakeSubsystem")
{
	intakeMotor = RobotMap::intakeSubsystemRollerVictor;
	photoSensor = RobotMap::intakeSubsystemPhotoSensor;
	rampLimitSwitch = RobotMap::intakeSubsystemRampLimitSwitch;
}

void IntakeSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new StopIntakeCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.



//TO DO: make constants for motor values
void IntakeSubsystem::SetIntakeMotor(IntakeDirection id) {
	float speed = 0.0f;

	Logger *logger = Logger::GetInstance();

	logger->Log(IntakeSubsystemLogId, Logger::kTRACE, "IntakeSubsystem::SetIntakeMotor: Direction=%d", id);

	if (id == IntakeDirection::In){
		speed = -1.0f;
	}
	else if (id == IntakeDirection::Out) {
		speed = 1.0f;
	}

	logger->Log(IntakeSubsystemLogId, Logger::kTRACE, "IntakeSubsystem::SetIntakeMotor: speed = %f", speed);

	intakeMotor->Set(speed);
}
bool IntakeSubsystem::IsBallLoaded() {
	SmartDashboard::PutNumber("Photo Sensor target value (Volts)", PhotoSensorTargetVoltage);

	//Logger *logger = Logger::GetInstance();

	//float sensorVoltage = photoSensor->GetVoltage();

	//logger->Log(IntakeSubsystemLogId, Logger::kTRACE, "IntakeSubsystem::IsBallLoaded ->Sensor is %f, Threshold = %f",sensorVoltage, PhotoSensorTargetVoltage);

	if (!rampLimitSwitch->Get()){
		return true;
	}
	return false;
}


