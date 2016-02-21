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

	enum SeekManipulatorPos {
		None,
		Up,
		Intake,
		Down
	};

	IntakeSubsystem();
	void InitDefaultCommand();
	void FindHomePosition(bool forceFind);

	void SetIntakeMotor(IntakeDirection id);
	bool IsBallLoaded();

	// For the operator to manually move the arm.
	void MoveManipulator(float vertVelocity);

	bool SetManipulatorSeekPosition(SeekManipulatorPos pos);
	bool hasManipulatorReachedPos();
	void cancelManipulatorSeek();

private:
	bool CheckUpperLimitSwitch();

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<Talon> intakeMotor;
	std::shared_ptr<CANTalon> manipulatorMotor;
	std::shared_ptr<AnalogInput> photoSensor;
	std::shared_ptr<DigitalInput> upperLimitSwitch;
	bool homePositionSet = false;
	SeekManipulatorPos seekPos = None;
	double manipMotorCountTarget = 0.0;
};

#endif
