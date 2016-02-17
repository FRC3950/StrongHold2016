#ifndef VisionOffCommand_H
#define VisionOffCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class VisionOffCommand: public CommandBase
{
public:
	VisionOffCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
