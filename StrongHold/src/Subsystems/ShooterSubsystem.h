#ifndef ShooterSubsystem_H
#define ShooterSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class ShooterSubsystem: public Subsystem
{
public:
	enum HoodState{
			open,closed
		};

	ShooterSubsystem();
	void InitDefaultCommand();
	void ToggleHood();
	void SetHoodState(HoodState hs);
	HoodState GetHoodState();
	void SetTargetSpeed(float rotsPerSec);
	bool HasHitTargetSpeed();

	static const float MinRotationsPerSec;
	static const float MaxRotationsPerSec;

private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<Solenoid> hoodSolenoid;
	std::shared_ptr<CANTalon> shooterMotor;
	double targetCountsPerSec;
	double lastCountsReadTime;
	double lastCounts;
};

#endif
