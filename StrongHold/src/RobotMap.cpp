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
std::shared_ptr<Solenoid> RobotMap::driveSubsystemShifterSolenoid;
std::shared_ptr<Solenoid> RobotMap::driveSubsystemPowerTakeOffSolenoid;
std::shared_ptr<Talon> RobotMap::intakeSubsystemRollerVictor;
std::shared_ptr<CANTalon> RobotMap::intakeSubsystemManipulatorMotor;
std::shared_ptr<DigitalInput> RobotMap::intakeSubsystemUpperLimitSwitch;
std::shared_ptr<AnalogInput> RobotMap::intakeSubsystemPhotoSensor;
std::shared_ptr<CANTalon> RobotMap::shooterSubsystemShooterWheelTalon;
std::shared_ptr<CANTalon> RobotMap::uptakeSubsystemIndexerTalon;
std::shared_ptr<Solenoid> RobotMap::shooterSubsystemShooterCoverSolenoid;
//std::shared_ptr<Solenoid> RobotMap::climberSubsystemSolenoid1;
//std::shared_ptr<Solenoid> RobotMap::climberSubsystemSolenoid2;
std::shared_ptr<Talon> RobotMap::climberSubsystemMotor;
std::shared_ptr<CANTalon> RobotMap::climberSubsystemMotor2;
std::shared_ptr<DigitalInput> RobotMap::climberSubsystemLimitSwitch;
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

    driveSubsystemShifterSolenoid.reset(new Solenoid(0));

    driveSubsystemPowerTakeOffSolenoid.reset(new Solenoid(1));


    intakeSubsystemRollerVictor.reset(new Talon(5));

    intakeSubsystemManipulatorMotor.reset(new CANTalon(1));

    intakeSubsystemPhotoSensor.reset(new AnalogInput(0));

#if NOT_YET
    intakeSubsystemUpperLimitSwitch.reset(new DigitalInput(0));

    uptakeSubsystemIndexerTalon.reset(new CANTalon(1));
#endif


    climberSubsystemMotor.reset(new Talon(4));
    climberSubsystemMotor2.reset(new CANTalon(2));

    climberSubsystemLimitSwitch.reset(new DigitalInput(0));

    shooterSubsystemShooterCoverSolenoid.reset(new Solenoid(2));

    shooterSubsystemShooterWheelTalon.reset(new CANTalon(0));

    //ahrs.reset(new AHRS(SPI::Port::kMXP));

    pdp.reset(new PowerDistributionPanel(0));

     /* Communicate w/navX MXP via the MXP SPI Bus.                                       */
     /* Alternatively:  I2C::Port::kMXP, SerialPort::Port::kMXP or SerialPort::Port::kUSB */
     /* See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface/ for details.   */
}


