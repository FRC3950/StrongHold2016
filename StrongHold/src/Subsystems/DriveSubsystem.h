#ifndef DriveSubsystem_H
#define DriveSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "RobotMap.h"
#include "DriveMotorCurrents.h"

class DriveSubsystem: public Subsystem
{
public:
	enum DriveMode {
		DrivingMode,
		ClimbingMode
	};

	enum Gear {
		HighGear,
		LowGear
	};

	enum SafetyCurrentAction {
		NoAction,
		LowGearAction,
		StopAction
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
	void ClearOverloadCondition() { overloadCondition = false; }

	SafetyCurrentAction CheckAvgMotorCurrent(DriveMotorCurrents::MotorId motorId);

	DriveMode GetMode() const {
		return mode;
	}

	bool InDriveMode() const {
		return (GetMode() == DrivingMode);
	}

	bool InClimbMode() const {
		return (GetMode() == ClimbingMode);
	}

	void ResetAvgMotorCurrents();

	void AvgNewMotorCurrents(const DriveMotorCurrents &currents);

	bool twistMode = true;
	bool ToggleDriveDirection = false;
private:
	void SyncDriveModeToHardware();
	void OutputAvgMotorCurrent(DriveMotorCurrents::MotorId motorId) const;

	// It's desirable that everything possible be put under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<Victor> victor1;
	std::shared_ptr<Victor> victor2;
	std::shared_ptr<Victor> victor3;
	std::shared_ptr<Victor> victor4;
	std::shared_ptr<RobotDrive> robotDrive;
	std::shared_ptr<Solenoid> powerTakeOffSolenoid;
	std::shared_ptr<Solenoid> gearSwitchSolenoid;

	DriveMode mode;

	std::vector<double> avgMotorCurrents;
	std::vector<int> aboveAvgCurrentThresholdEpochCounts;

	unsigned timeStep;
	bool overloadCondition = false;


};

#endif
