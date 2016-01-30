#ifndef DriveSubsystemClimbCommand_H
#define DriveSubsystemClimbCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ClimbCommand: public CommandBase
{
public:
	ClimbCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
