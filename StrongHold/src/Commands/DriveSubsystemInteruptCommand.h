#ifndef DriveSubsystemInteruptCommand_H
#define DriveSubsystemInteruptCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveSubsystemInteruptCommand: public CommandBase
{
public:
	DriveSubsystemInteruptCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
