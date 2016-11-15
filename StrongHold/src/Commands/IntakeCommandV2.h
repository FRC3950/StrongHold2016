#ifndef IntakeCommandV2_H
#define IntakeCommandV2_H

#include "../CommandBase.h"
#include "WPILib.h"

class IntakeCommandV2: public CommandBase
{
public:
	IntakeCommandV2();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
