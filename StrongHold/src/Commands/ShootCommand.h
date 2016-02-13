#ifndef ShootCommand_H
#define ShootCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShootCommand: public CommandBase
{
public:
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

protected:
	 ShootCommand();
	 virtual float getTargetRotationsPerSecond() = 0;

private:
	void cleanup();

	bool inited = false;
};

#endif
