#ifndef IntakeSubsystem_H
#define IntakeSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class IntakeSubsystem: public Subsystem
{
public:
	enum IntakeDirection {
		Out,
		Neutral,
		In
	};



	IntakeSubsystem();
	void InitDefaultCommand();


	void SetIntakeMotor(IntakeDirection id);
	bool IsBallLoaded();

	// For the operator to manually move the arm.


private:

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<Talon> intakeMotor;
	std::shared_ptr<AnalogInput> photoSensor;
};

#endif
