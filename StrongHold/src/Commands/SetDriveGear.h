#ifndef SetDriveGear_H
#define SetDriveGear_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "../Subsystems/DriveSubsystem.h"

class SetDriveGear: public CommandBase
{
public:
	SetDriveGear(DriveSubsystem::Gear g);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	DriveSubsystem::Gear gear;
};

#endif
