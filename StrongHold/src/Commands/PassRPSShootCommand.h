/*
 * PassRPSShootCommand.h
 *
 *  Created on: Feb 12, 2016
 *      Author: RoboGym
 */
#include "ShootCommand.h"

#ifndef SRC_COMMANDS_PASSRPSSHOOTCOMMAND_H_
#define SRC_COMMANDS_PASSRPSSHOOTCOMMAND_H_

class PassRPSShootCommand : ShootCommand{
public:
	PassRPSShootCommand(float rps);
	PassRPSShootCommand();

	virtual ~PassRPSShootCommand();

protected:
	virtual float getTargetRotationsPerSecond() override;

private:
	double targetRPS;
};

#endif /* SRC_COMMANDS_PASSRPSSHOOTCOMMAND_H_ */
