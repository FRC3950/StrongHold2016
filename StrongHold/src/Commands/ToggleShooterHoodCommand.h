#ifndef ToggleShooterHoodCommand_H
#define ToggleShooterHoodCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ToggleShooterHoodCommand: public CommandBase
{
public:
	ToggleShooterHoodCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
