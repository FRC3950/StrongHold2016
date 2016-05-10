#ifndef VisionOnCommand_H
#define VisionOnCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class VisionOnCommand: public CommandBase
{

public:
	VisionOnCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	void cleanUp();

	double lastTime = 0;
};

#endif
