#ifndef ShooterSubsystemPID_H
#define ShooterSubsystemPID_H

#include "Commands/PIDSubsystem.h"
#include "WPILib.h"

class ShooterSubsystemPID: public PIDSubsystem
{
public:
	ShooterSubsystemPID();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();
private:
	std::shared_ptr<CANTalon> shooterMotor;
};

#endif
