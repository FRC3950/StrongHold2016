#ifndef StopShooterCommand_H
#define StopShooterCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class StopShooterCommand: public CommandBase
{
public:
	StopShooterCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
