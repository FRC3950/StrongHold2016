#ifndef DriveSubsystem_H
#define DriveSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "RobotMap.h"

class DriveSubsystem: public Subsystem
{
public:
	enum DriveMode {
		drive,
		climb
	};

	enum Gear {
		high,
		low
	};
	DriveSubsystem();
	void InitDefaultCommand();
	void EnableDriveSubsystem();
	void ArcadeDrive(float y,float twist);
	void Climb(float y);
	void ToggleHighLowGear();
	void SetGear(Gear g);
	Gear GetGearState();
	void SetMode(DriveMode dm);

	DriveMode GetMode() const {
		return mode;
	}

	bool inDriveMode() const {
		return (GetMode() == drive);
	}

	bool inClimbMode() const {
		return (GetMode() == climb);
	}

private:
	void syncDriveModeToHardware();

	// It's desirable that everything possible be put under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<Victor> victor1;
	std::shared_ptr<Victor> victor2;
	std::shared_ptr<Victor> victor3;
	std::shared_ptr<Victor> victor4;
	std::shared_ptr<RobotDrive> robotDrive;
	std::shared_ptr<Solenoid> powerTakeOffSolenoid;
	std::shared_ptr<DoubleSolenoid> gearSwitchSolenoid;

	DriveMode mode;
};

#endif
