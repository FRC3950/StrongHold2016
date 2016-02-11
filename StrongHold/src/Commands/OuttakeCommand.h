#ifndef OuttakeCommand_H
#define OuttakeCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class OuttakeCommand: public CommandBase
{
public:
	OuttakeCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
