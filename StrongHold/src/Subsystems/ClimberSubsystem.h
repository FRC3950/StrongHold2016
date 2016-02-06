#ifndef ClimberSubsystem_H
#define ClimberSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class ClimberSubsystem: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<Solenoid> solenoid1;
	std::shared_ptr<Solenoid> solenoid2;
public:
	ClimberSubsystem();
	void InitDefaultCommand();
	void LaunchClimber();
};

#endif
