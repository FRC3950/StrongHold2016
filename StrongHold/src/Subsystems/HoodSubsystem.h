#ifndef HoodSubsystem_H
#define HoodSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class HoodSubsystem: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	HoodSubsystem();
	void InitDefaultCommand();
	enum HoodState{
		open,closed
	};
	void ToggleHood();
	void SetHoodState(HoodState hs);
	HoodState GetHoodState();
	std::shared_ptr<Solenoid> hoodSolenoid;
};

#endif
