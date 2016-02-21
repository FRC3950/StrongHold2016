#ifndef ManipulatorSubsystem_H
#define ManipulatorSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class ManipulatorSubsystem: public Subsystem
{
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	enum SeekManipulatorPos {
		None,
		Up,
		Intake,
		Down
	};
	ManipulatorSubsystem();
	void InitDefaultCommand();

	void FindHomePosition(bool forceFind);
	void MoveManipulator(float vertVelocity);

	bool SetManipulatorSeekPosition(SeekManipulatorPos pos);
	bool hasManipulatorReachedPos();
	void cancelManipulatorSeek();

private:
	bool CheckUpperLimitSwitch();
	std::shared_ptr<CANTalon> manipulatorMotor;
	std::shared_ptr<DigitalInput> upperLimitSwitch;
	bool homePositionSet = false;
	SeekManipulatorPos seekPos = None;
	double manipMotorCountTarget = 0.0;


};

#endif
