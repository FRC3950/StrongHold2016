#ifndef IntakeCommand_H
#define IntakeCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class IntakeCommand: public CommandBase
{
public:
	IntakeCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
