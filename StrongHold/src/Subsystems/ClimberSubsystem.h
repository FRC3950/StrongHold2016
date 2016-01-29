#ifndef ClimberSubsystem_H
#define ClimberSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class ClimberSubsystem: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	ClimberSubsystem();
	void InitDefaultCommand();
};

#endif
