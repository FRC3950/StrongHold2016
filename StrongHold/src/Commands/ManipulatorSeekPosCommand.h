#ifndef ManipulatorSeekPosCommand_H
#define ManipulatorSeekPosCommand_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "../Subsystems/ManipulatorSubsystem.h"

class ManipulatorSeekPosCommand: public CommandBase
{
private:
	bool hasInitalized = false;
	ManipulatorSubsystem::SeekManipulatorPos targetPos;
public:
	ManipulatorSeekPosCommand(ManipulatorSubsystem::SeekManipulatorPos pos);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
