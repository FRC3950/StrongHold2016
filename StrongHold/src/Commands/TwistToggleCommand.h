#ifndef TwistToggleCommand_H
#define TwistToggleCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class TwistToggleCommand: public CommandBase
{
public:
	TwistToggleCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
