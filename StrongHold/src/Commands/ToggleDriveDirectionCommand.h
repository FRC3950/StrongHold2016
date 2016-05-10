#ifndef ToggleDriveDirectionCommand_H
#define ToggleDriveDirectionCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ToggleDriveDirectionCommand: public CommandBase
{
public:
	ToggleDriveDirectionCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
