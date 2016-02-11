#ifndef AutoDriveCommand_H
#define AutoDriveCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class AutoDriveCommand: public CommandBase
{
public:
	AutoDriveCommand(double time);
	AutoDriveCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	void CleanUp();
	double startTime;
	double runTime = 2;
	bool inited = false;
};

#endif
