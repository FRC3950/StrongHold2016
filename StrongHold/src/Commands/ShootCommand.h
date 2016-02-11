#ifndef ShootCommand_H
#define ShootCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShootCommand: public CommandBase
{
public:
	ShootCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	bool inited = false;
};

#endif
