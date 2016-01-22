/*
 * Robot.h
 *
 *  Created on: Jan 19, 2016
 *      Author: RoboGym
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include <memory>
#include "WPILIB.h"
#include "OI.h"
#include "Subsystems/DriveSubsystem.h"

class Robot: public IterativeRobot {
public:
	std::unique_ptr<Command> autonomousCommand;
	static std::unique_ptr<OI> oi;
	LiveWindow *lw = LiveWindow::GetInstance();

	static std::shared_ptr<DriveSubsystem> driveSubsystem;

	virtual void RobotInit();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();

private:
	std::unique_ptr<SendableChooser> chooser;
};

#endif /* SRC_ROBOT_H_ */
