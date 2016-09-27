#ifndef ManipulatorCommand_H
#define ManipulatorCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ManipulatorCommand: public CommandBase
{
public:
	ManipulatorCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
