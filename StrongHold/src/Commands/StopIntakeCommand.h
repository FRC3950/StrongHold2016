#ifndef IntakeWaitingCommand_H
#define IntakeWaitingCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class StopIntakeCommand: public CommandBase
{
public:
	StopIntakeCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
