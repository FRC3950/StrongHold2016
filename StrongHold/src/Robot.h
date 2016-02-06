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
#include "AHRS.h"
#include "Subsystems/DriveSubsystem.h"
#include "Subsystems/IntakeSubsystem.h"
#include "Subsystems/ClimberSubsystem.h"
#include "Subsystems/ShooterSubsystem.h"
#include "DriveMotorCurrents.h"


class Robot: public IterativeRobot {
public:
	std::unique_ptr<Command> autonomousCommand;
	static std::unique_ptr<OI> oi;
	LiveWindow *lw = LiveWindow::GetInstance();

	static std::shared_ptr<DriveSubsystem> driveSubsystem;
	static std::shared_ptr<IntakeSubsystem> intakeSubsystem;
	static std::shared_ptr<ClimberSubsystem> climberSubsystem;
	static std::shared_ptr<PowerDistributionPanel> pdp;

	static DriveMotorCurrents getDriveMotorCurrents();

	virtual void RobotInit();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();

private:
	void OutputNavxData();
	void OutputMotorCurrents();

	std::unique_ptr<SendableChooser> chooser;
	std::shared_ptr<AHRS> ahrs;
};

#endif /* SRC_ROBOT_H_ */
