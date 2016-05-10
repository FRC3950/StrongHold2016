#ifndef AutoRotateCommand_H
#define AutoRotateCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class AutoRotateCommand: public CommandBase
{
public:
	AutoRotateCommand(double time);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double runTime;
	bool inited = false;
	double startTime = 0.0;
	void CleanUp();
};

#endif
