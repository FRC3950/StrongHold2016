/*
 * SmartDashboardKeys.h
 *
 *  Created on: Feb 12, 2016
 *      Author: RoboGym
 */

#ifndef SRC_SMARTDASHBOARDKEYS_H_
#define SRC_SMARTDASHBOARDKEYS_H_

#include <string>

namespace SmartDashboardKeys {
	extern const std::string ShooterRotsPerSecKey;
	extern const std::string DriveGearStateKey;

	extern const std::string FrontLeftDriveAvgCurrentKey;
	extern const std::string FrontRightDriveAvgCurrentKey;

	extern const std::string BackLeftDriveAvgCurrentKey;
	extern const std::string BackRightDriveAvgCurrentKey;

	extern const std::string FrontLeftDriveConsecEpochsAboveThresholdKey;
	extern const std::string FrontRightDriveConsecEpochsAboveThresholdKey;

	extern const std::string BackLeftDriveConsecEpochsAboveThresholdKey;
	extern const std::string BackRightDriveConsecEpochsAboveThresholdKey;

}



#endif /* SRC_SMARTDASHBOARDKEYS_H_ */
