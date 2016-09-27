#include "ShooterSubsystemPID.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"

ShooterSubsystemPID::ShooterSubsystemPID() :
		PIDSubsystem("ShooterSubsystemPID", 1.0, 0.0, 0.0)
{
	// Use these to get going:
	// SetSetpoint() -  Sets where the PID controller should move the system
	//                  to
	Enable();
	shooterMotor = RobotMap::shooterSubsystemShooterWheelTalon;
	shooterMotor->SetControlMode(CANTalon::kPercentVbus);
	shooterMotor->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	shooterMotor->Set(0.0f);
	shooterMotor->SetSafetyEnabled(false);
	shooterMotor->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
}

double ShooterSubsystemPID::ReturnPIDInput()
{
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	// yourPot->SetAverageVoltage() / kYourMaxVoltage;
	SmartDashboard::PutNumber("current Rotations per second of shooter", shooterMotor->GetSpeed());
	return shooterMotor->GetSpeed();
}

void ShooterSubsystemPID::UsePIDOutput(double output)
{
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);
	shooterMotor->Set(output);
}

void ShooterSubsystemPID::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//setDefaultCommand(new MySpecialCommand());
}
