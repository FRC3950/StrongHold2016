/*
 * DashboardShootCommand.h
 *
 *  Created on: Feb 12, 2016
 *      Author: RoboGym
 */
#include "ShootCommand.h"
#ifndef SRC_COMMANDS_DASHBOARDSHOOTCOMMAND_H_
#define SRC_COMMANDS_DASHBOARDSHOOTCOMMAND_H_

class DashboardShootCommand : public ShootCommand {
public:
	DashboardShootCommand();
	virtual ~DashboardShootCommand();

protected:
	virtual float getTargetRotationsPerSecond() override;
};

#endif /* SRC_COMMANDS_DASHBOARDSHOOTCOMMAND_H_ */
