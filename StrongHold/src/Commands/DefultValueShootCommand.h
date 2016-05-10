#ifndef DefultValueShootCommand_H
#define DefultValueShootCommand_H

#include "../CommandBase.h"
#include "ShootCommand.h"
#include "WPILib.h"

class DefultValueShootCommand: public ShootCommand
{
public:
	DefultValueShootCommand();
	virtual ~DefultValueShootCommand();
protected:
	virtual float getTargetRotationsPerSecond() override;
};

#endif
