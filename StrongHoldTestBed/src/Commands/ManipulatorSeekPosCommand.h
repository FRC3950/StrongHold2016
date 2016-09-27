#ifndef ManipulatorSeekPosCommand_H
#define ManipulatorSeekPosCommand_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "../Subsystems/IntakeSubsystem.h"

class ManipulatorSeekPosCommand: public CommandBase
{
private:
	bool hasInitalized = false;
	IntakeSubsystem::SeekManipulatorPos targetPos;
public:
	ManipulatorSeekPosCommand(IntakeSubsystem::SeekManipulatorPos pos);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
