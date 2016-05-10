#ifndef IntakeCommand_H
#define IntakeCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class IntakeCommand: public CommandBase
{
public:
	IntakeCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	void InitMembers();
	void Cleanup();
	bool WaitBallLoadedState();
	bool WaitTimeState();
	bool isBallDetectedOnStart;

	enum State {
		Init,
		WaitBallLoaded,
		WaitTime,
		ReleseWait,
		Done
	};

	State currState;
	double startTime;
	double runTime;
	double timeWaited;
};

#endif
