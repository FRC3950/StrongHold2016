#ifndef ToggleGearCommand_H
#define ToggleGearCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ToggleGearCommand: public CommandBase
{
public:
	ToggleGearCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
