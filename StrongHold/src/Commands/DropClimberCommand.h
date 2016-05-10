#ifndef DropClimberCommand_H
#define DropClimberCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DropClimberCommand: public CommandBase
{
public:
	DropClimberCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool Inited = false;
	void CleanUp();
};

#endif
