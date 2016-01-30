#ifndef UptakeSubsystem_H
#define UptakeSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class UptakeSubsystem: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	UptakeSubsystem();
	void InitDefaultCommand();
};

#endif
