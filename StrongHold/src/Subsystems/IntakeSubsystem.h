#ifndef IntakeSubsystem_H
#define IntakeSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class IntakeSubsystem: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<Victor> intakeMotor;
	std::shared_ptr<Victor> manipulatorMotor;

public:
	enum IntakeDirection {
		out,
		neutral,
		in
	};
	IntakeSubsystem();
	void InitDefaultCommand();
	void SetIntakeMotors(IntakeDirection id);
};

#endif
