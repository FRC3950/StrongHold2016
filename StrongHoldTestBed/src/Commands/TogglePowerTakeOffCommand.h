#ifndef TogglePowerTakeOffCommand_H
#define TogglePowerTakeOffCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class TogglePowerTakeOffCommand: public CommandBase
{
public:
	TogglePowerTakeOffCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
