#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"
#include "AHRS.h"


/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
 
// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
//const int LEFTMOTOR = 1;
//const int RIGHTMOTOR = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
//const int RANGE_FINDER_PORT = 1;
//const int RANGE_FINDER_MODULE = 1;

class RobotMap {
private:

public:
	static std::shared_ptr<Victor> driveSubsystemVictor1;
	static std::shared_ptr<Victor> driveSubsystemVictor2;
	static std::shared_ptr<Victor> driveSubsystemVictor3;
	static std::shared_ptr<Victor> driveSubsystemVictor4;
	static std::shared_ptr<RobotDrive> driveSubsystemRobotDrive41;
	static std::shared_ptr<DoubleSolenoid> driveSubsystemShifterSolenoid;
	static std::shared_ptr<Solenoid> driveSubsystemPowerTakeOffSolenoid;

	static std::shared_ptr<Victor> intakeSubsystemRollerVictor;
	static std::shared_ptr<CANTalon> intakeSubsystemManipulatorMotor;
	static std::shared_ptr<AnalogInput> intakeSubsystemPhotoSensor;
	static std::shared_ptr<DigitalInput> intakeSubsystemUpperLimitSwitch;
	static std::shared_ptr<CANTalon> shooterSubsystemShooterWheelTalon;
	static std::shared_ptr<Solenoid> shooterSubsystemShooterCoverSolenoid;

	static std::shared_ptr<CANTalon> uptakeSubsystemIndexerTalon;

//	static std::shared_ptr<Solenoid> climberSubsystemSolenoid1;
//	static std::shared_ptr<Solenoid> climberSubsystemSolenoid2;

	static std::shared_ptr<Victor> climberSubsystemMotor;
	static std::shared_ptr<DigitalInput> climberSubsystemLimitSwitch;

	static std::shared_ptr<AHRS> ahrs;

	static std::shared_ptr<PowerDistributionPanel> pdp;

	static void init();
};

#endif


