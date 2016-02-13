/*
 * PassRPSShootCommand.cpp
 *
 *  Created on: Feb 12, 2016
 *      Author: RoboGym
 */

#include <Commands/PassRPSShootCommand.h>
#include "../Robot.h"
#include "../Logging.h"
#include "../ConfigKeys.h"
#include "../Config/ConfigInstanceMgr.h"
#include "../Subsystems/ShooterSubsystem.h"

namespace {
	float SHOOTER_WHEELS_ROTATIONS_PER_SECOND_DEFAULT = 100;
}

PassRPSShootCommand::PassRPSShootCommand(float rps) : ShootCommand() {
	targetRPS = rps;
}

PassRPSShootCommand::PassRPSShootCommand() : ShootCommand() {
    ConfigMgr *configMgr = ConfigInstanceMgr::getInstance();

	targetRPS = configMgr->getFloatVal(ConfigKeys::Shooter_RotsPerSecEpsilonKey, SHOOTER_WHEELS_ROTATIONS_PER_SECOND_DEFAULT);

	Logger* logger = Logger::GetInstance();

	logger->Log(ShooterSubsystemLogId,Logger::kINFO, "PassRPSShooterCommand: Wheels Rotations / Sec  = %f\n", targetRPS);
}

PassRPSShootCommand::~PassRPSShootCommand() {
	// TODO Auto-generated destructor stub
}

float PassRPSShootCommand::getTargetRotationsPerSecond(){
	return targetRPS;
}
