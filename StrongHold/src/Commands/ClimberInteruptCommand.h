#ifndef ClimberInteruptCommand_H
#define ClimberInteruptCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ClimberInteruptCommand: public CommandBase
{
public:
	ClimberInteruptCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
