#ifndef RetractClimberCommand_H
#define RetractClimberCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class RetractClimberCommand: public CommandBase
{
public:
	RetractClimberCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
