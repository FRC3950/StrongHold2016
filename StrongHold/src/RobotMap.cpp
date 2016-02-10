/*
 * RobotMap.cpp
 *
 *  Created on: Jan 15, 2016
 *      Author: RoboGym
 */
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"


#include <iostream>

std::shared_ptr<Victor> RobotMap::driveSubsystemVictor1;
std::shared_ptr<Victor> RobotMap::driveSubsystemVictor2;
std::shared_ptr<Victor> RobotMap::driveSubsystemVictor3;
std::shared_ptr<Victor> RobotMap::driveSubsystemVictor4;
std::shared_ptr<RobotDrive> RobotMap::driveSubsystemRobotDrive41;
std::shared_ptr<DoubleSolenoid> RobotMap::driveSubsystemShifterSolenoid;
std::shared_ptr<DoubleSolenoid> RobotMap::driveSubsystemPowerTakeOffSolenoid;
std::shared_ptr<Victor> RobotMap::intakeSubsystemRollerVictor;
std::shared_ptr<CANTalon> RobotMap::intakeSubsystemManipulatorMotor;
std::shared_ptr<DigitalInput> RobotMap::intakeSubsystemUpperLimitSwitch;
std::shared_ptr<AnalogInput> RobotMap::intakeSubsystemPhotoSensor;
std::shared_ptr<CANTalon> RobotMap::shooterSubsystemShooterWheelTalon;
std::shared_ptr<CANTalon> RobotMap::uptakeSubsystemIndexerTalon;
std::shared_ptr<Solenoid> RobotMap::shooterSubsystemShooterCoverSolenoid;
std::shared_ptr<Solenoid> RobotMap::climberSubsystemSolenoid1;
std::shared_ptr<Solenoid> RobotMap::climberSubsystemSolenoid2;
std::shared_ptr<AHRS> RobotMap::ahrs;
std::shared_ptr<PowerDistributionPanel> RobotMap::pdp;


void RobotMap::init(){
    LiveWindow *lw = LiveWindow::GetInstance();

    driveSubsystemVictor1.reset(new Victor(0));
    lw->AddActuator("DriveSubsystem", "Victor 1", driveSubsystemVictor1);

    driveSubsystemVictor2.reset(new Victor(1));
    lw->AddActuator("DriveSubsystem", "Victor 2", driveSubsystemVictor2);

    driveSubsystemVictor3.reset(new Victor(2));
    lw->AddActuator("DriveSubsystem", "Victor 3", driveSubsystemVictor3);

    driveSubsystemVictor4.reset(new Victor(3));
    lw->AddActuator("DriveSubsystem", "Victor 4", driveSubsystemVictor4);

    driveSubsystemRobotDrive41.reset(new RobotDrive(driveSubsystemVictor1, driveSubsystemVictor2,
              driveSubsystemVictor3, driveSubsystemVictor4));

    driveSubsystemShifterSolenoid.reset(new DoubleSolenoid(0, 1));

    driveSubsystemPowerTakeOffSolenoid.reset(new DoubleSolenoid(2, 3));

    intakeSubsystemRollerVictor.reset(new Victor(4));

    intakeSubsystemManipulatorMotor.reset(new CANTalon(5));

    intakeSubsystemUpperLimitSwitch.reset(new DigitalInput(0));

    shooterSubsystemShooterWheelTalon.reset(new CANTalon(0));

    uptakeSubsystemIndexerTalon.reset(new CANTalon(1));

    shooterSubsystemShooterCoverSolenoid.reset(new Solenoid(2));

	climberSubsystemSolenoid1.reset(new Solenoid(4, 5));

	climberSubsystemSolenoid2.reset(new Solenoid(6, 7));

	pdp.reset(new PowerDistributionPanel(0));


    /* Communicate w/navX MXP via the MXP SPI Bus.                                       */
     /* Alternatively:  I2C::Port::kMXP, SerialPort::Port::kMXP or SerialPort::Port::kUSB */
     /* See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface/ for details.   */
     ahrs.reset(new AHRS(SPI::Port::kMXP));
}


