#ifndef LaunchClimber_H
#define LaunchClimber_H

#include "../CommandBase.h"
#include "WPILib.h"

class LaunchClimberCommand: public CommandBase
{
public:
	LaunchClimberCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	void CleanUp();
	bool init;
};

#endif
