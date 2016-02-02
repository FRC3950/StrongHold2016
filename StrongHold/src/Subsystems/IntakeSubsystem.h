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
	std::shared_ptr<AnalogInput> photoSensor;

public:
	enum IntakeDirection {
		out,
		neutral,
		in
	};

	enum ManipulatorPos {
		up,
		down,
		intake
	};

	IntakeSubsystem();
	void InitDefaultCommand();
	void SetIntakeMotors(IntakeDirection id, bool usePhotoSensor);
	bool IsBallLoaded();

	// For the operator to manually move the arm.
	void MoveManipulator(float vertVelocity);

	void SetManipulatorSeekPosition(ManipulatorPos pos);
	bool hasManipulatorReachedPos();
	void cancelManipulatorSeek();

};

#endif
