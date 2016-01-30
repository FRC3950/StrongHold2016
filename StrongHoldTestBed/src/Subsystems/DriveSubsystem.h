#ifndef DriveSubsystem_H
#define DriveSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "RobotMap.h"

class DriveSubsystem: public Subsystem
{
private:
	// It's desirable that everything possible be put under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<Talon> talon1;
	std::shared_ptr<Talon> talon2;
	std::shared_ptr<Talon> talon3;
	std::shared_ptr<Talon> talon4;
	std::shared_ptr<RobotDrive> robotDrive41;

public:
	DriveSubsystem();
	void InitDefaultCommand();
	void EnableDriveSubsystem();
	void ArcadeDrive(float y,float twist);
};

#endif
