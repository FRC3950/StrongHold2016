#ifndef OverrideIntakeCommand_H
#define OverrideIntakeCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class OverrideIntakeCommand: public CommandBase
{
public:
	OverrideIntakeCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
