#ifndef ReadyShootCommand_H
#define ReadyShootCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ReadyShootCommand: public CommandBase
{
public:
	ReadyShootCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	void CleanUp();
	double startTime;
	const double runTime = 2;
	bool inited = false;
};

#endif
