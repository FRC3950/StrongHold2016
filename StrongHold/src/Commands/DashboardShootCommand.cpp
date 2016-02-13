/*
 * DashboardShootCommand.cpp
 *
 *  Created on: Feb 12, 2016
 *      Author: RoboGym
 */

#include <Commands/DashboardShootCommand.h>
#include "../SmartDashboardKeys.h"
#include "../Subsystems/ShooterSubsystem.h"
#include <algorithm>

DashboardShootCommand::DashboardShootCommand() : ShootCommand() {

}

DashboardShootCommand::~DashboardShootCommand() {
	// TODO Auto-generated destructor stub
}
float DashboardShootCommand::getTargetRotationsPerSecond(){
	double rotsPerSec = SmartDashboard::GetNumber(SmartDashboardKeys::ShooterRotsPerSecKey, 0);

	if (rotsPerSec <= 0.0f) {
		rotsPerSec = 0.0f;
	}
	else {
		if (rotsPerSec < ShooterSubsystem::MinRotationsPerSec) {
			rotsPerSec = ShooterSubsystem::MinRotationsPerSec;
		}
		else if (rotsPerSec > ShooterSubsystem::MaxRotationsPerSec) {
			rotsPerSec = ShooterSubsystem::MaxRotationsPerSec;
		}
	}

	SmartDashboard::PutNumber(SmartDashboardKeys::ShooterRotsPerSecKey, rotsPerSec);

	return rotsPerSec;
}
