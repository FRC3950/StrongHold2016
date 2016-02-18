#include "DriveSubsystem.h"
#include "../ConfigKeys.h"
#include "../Config/ConfigInstanceMgr.h"
#include "../SmartDashBoardKeys.h"
#include "../Logging.h"
#include "../RobotMap.h"
#include "../Commands/DriveCommand.h"

namespace
{
	const bool DRIVE_SAFETY_ENABLED_DEFAULT = false;
	const float DRIVE_SAFETY_TIME_OUT_DEFAULT = 1.0;

	const std::string HighGear = "High Gear";
	const std::string LowGear = "Low Gear";

	const double EXP_AVG_CURRENT_ALPHA_DEFAULT = 0.8;
	double ExpAvgCurrentAlpha = EXP_AVG_CURRENT_ALPHA_DEFAULT;

	const double TRIP_SAFETY_ACTION_CURRENT_AVG_DEFAULT = 50.00;
	double TripSafetyActionCurrentAvg  = TRIP_SAFETY_ACTION_CURRENT_AVG_DEFAULT;

	const double RESET_OVERLOAD_CONDITION_AVG_CURRENT_LEVEL_DEFAULT = 35.00;
	double ResetOverloadConditionAvgCurrentLevel = RESET_OVERLOAD_CONDITION_AVG_CURRENT_LEVEL_DEFAULT;

	const unsigned int SAFETY_ACTION_MIN_TIME_STEPS_CHECK_THRESHOLD_DEFAULT = 10;
	unsigned int SafetyActionMinTimeStepsCheckThreshold = SAFETY_ACTION_MIN_TIME_STEPS_CHECK_THRESHOLD_DEFAULT;

#if 0
	void SetSafetyMode(Talon& motor, bool enabled, float timeout) {
		Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "DriveSubsystem::SetSafteyMode() = %s, timeout=%f",
			enabled ? "TRUE" : "FALSE", timeout);

		motor.SetSafetyEnabled(enabled);
		motor.SetExpiration(timeout);
	}
#endif

	void VictorSetSafetyMode(Victor& motor, bool enabled, float timeout) {
			Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "DriveSubsystem::SetSafteyMode() = %s, timeout=%f",
				enabled ? "TRUE" : "FALSE", timeout);

			motor.SetSafetyEnabled(enabled);
			motor.SetExpiration(timeout);
		}

	void UpdateDashBoardGearState(DriveSubsystem::Gear state){
		SmartDashboard::PutString(SmartDashboardKeys::DriveGearStateKey, state == DriveSubsystem::Gear::HighGear? HighGear : LowGear);
	}

	bool ConfigInited = false;

	void InitSubsystemConfiguration()
	{
	    ConfigMgr *configMgr = ConfigInstanceMgr::getInstance();

	    if (!ConfigInited) {
	    	ExpAvgCurrentAlpha = configMgr->getDoubleVal(ConfigKeys::Drive_ExpAvgCurrentAlphaKey, EXP_AVG_CURRENT_ALPHA_DEFAULT);
	    	TripSafetyActionCurrentAvg = configMgr->getDoubleVal(ConfigKeys::Drive_TripSafetyActionCurrentAvgKey, TRIP_SAFETY_ACTION_CURRENT_AVG_DEFAULT);
	    	ResetOverloadConditionAvgCurrentLevel = configMgr->getDoubleVal(ConfigKeys::Drive_ResetOverloadConditionAvgCurrentLevelKey, RESET_OVERLOAD_CONDITION_AVG_CURRENT_LEVEL_DEFAULT);
	    	SafetyActionMinTimeStepsCheckThreshold = configMgr->getIntVal(ConfigKeys::Drive_SafetyActionMinTimeStepsCheckThresholdKey, SAFETY_ACTION_MIN_TIME_STEPS_CHECK_THRESHOLD_DEFAULT);


			Logger* logger = Logger::GetInstance();

			logger->Log(DriveSubsystemLogId, Logger::kINFO, "DriveSubsystem: Exponential Avg Alpha = %g\n", ExpAvgCurrentAlpha);
			logger->Log(DriveSubsystemLogId, Logger::kINFO, "DriveSubsystem: Trip Safety Action Current = %g\n", TripSafetyActionCurrentAvg);
			logger->Log(DriveSubsystemLogId, Logger::kINFO, "DriveSubsystem: Reset Overload Condition Avg Current Level = %g\n", ResetOverloadConditionAvgCurrentLevel);
			logger->Log(DriveSubsystemLogId, Logger::kINFO, "DriveSubsystem: Safety Action Min Time Steps Check Threshold = %d\n", SafetyActionMinTimeStepsCheckThreshold);

	      	ConfigInited = true;
	    }
	}
}

DriveSubsystem::DriveSubsystem() :
		Subsystem("DriveSubsystem"),
		avgMotorCurrents(4, 0.0)
{
	victor1 = RobotMap::driveSubsystemVictor1;
	victor2 = RobotMap::driveSubsystemVictor2;
	victor3 = RobotMap::driveSubsystemVictor3;
	victor4 = RobotMap::driveSubsystemVictor4;
    robotDrive = RobotMap::driveSubsystemRobotDrive41;
    powerTakeOffSolenoid = RobotMap::driveSubsystemPowerTakeOffSolenoid;
    gearSwitchSolenoid = RobotMap::driveSubsystemShifterSolenoid;

    robotDrive->SetSafetyEnabled(true);
    robotDrive->SetExpiration(0.1);
    robotDrive->SetSensitivity(0.5);
    robotDrive->SetMaxOutput(1.0);

    robotDrive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
    robotDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);

	InitSubsystemConfiguration();

    SyncDriveModeToHardware();

    ResetAvgMotorCurrents();
}

void DriveSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new DriveCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void DriveSubsystem::EnableDriveSubsystem() {
	ConfigMgr *configMgr = ConfigInstanceMgr::getInstance();

	float expiration = 0.0;

	bool enable = configMgr->getBoolVal(ConfigKeys::Drive_EnableSafety, DRIVE_SAFETY_ENABLED_DEFAULT);

	if (enable)
	{
		expiration = configMgr->getDoubleVal(ConfigKeys::Drive_SafetyTimeOut, DRIVE_SAFETY_TIME_OUT_DEFAULT);
	}

	Logger::GetInstance()->Log(DriveSubsystemLogId,Logger::kINFO, "DriveSubsystem:EnableDriveSubsystem() ->SafetyEnable=%s, timeout=%f\n",
			enable ? "TRUE" : "FALSE",
			expiration);

	VictorSetSafetyMode(*victor1, enable, expiration);
	VictorSetSafetyMode(*victor2, enable, expiration);
	VictorSetSafetyMode(*victor3, enable, expiration);
	VictorSetSafetyMode(*victor4, enable, expiration);
	robotDrive->SetSafetyEnabled(enable);

	if (enable)
	{
		robotDrive->SetSafetyEnabled(expiration);
	}

    SyncDriveModeToHardware();

	/*
	talon1->EnableControl();
	talon2->EnableControl();
	talon3->EnableControl();
	talon4->EnableControl();
	*/

	victor1->Set(0);
	victor2->Set(0);
	victor3->Set(0);
	victor4->Set(0);

	SetGear(Gear::LowGear);
}

void DriveSubsystem::ArcadeDrive(float y, float twist) {
	Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "DriveSubsystem::ArcadeDrive()->y = %f, twist=%f", y, twist);

	if (!InDriveMode())
	{
		Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kERROR, "DriveSubsystem::ArcadeDrive called but NOT in drive mode. IGNORING!");
		return;
	}

	if (overloadCondition) {
		Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kWARNING, "DriveSubsystem::ArcadeDrive called but in overload condition, y and twist reset to 0.0!");
		twist = 0.0;
		y = 0.0;
	}

	robotDrive->ArcadeDrive(twist,y);
}

void DriveSubsystem::Climb(float y) {
	Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kTRACE, "DriveSubsystem::Climb()->y = %f", y);

	if (!InClimbMode())
	{
		Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kERROR, "DriveSubsystem::Climb called but NOT in climb mode. IGNORING!");
		return;
	}

	if (overloadCondition) {
		Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kWARNING, "DriveSubsystem::Climb called but in overload condition, y reset to 0.0!");
		y = 0.0;
	}

	//TO DO: climb code
	robotDrive->ArcadeDrive(0,y);
}

void DriveSubsystem::ToggleHighLowGear(){
	if (gearSwitchSolenoid->Get()){
		gearSwitchSolenoid->Set(false);
		UpdateDashBoardGearState(Gear::LowGear);
	}
	else{
		gearSwitchSolenoid->Set(true);
		UpdateDashBoardGearState(Gear::HighGear);
	}
}

void DriveSubsystem::SetGear(Gear g){
	if (g == Gear::HighGear){
		gearSwitchSolenoid->Set(true);
	}
	else{
		gearSwitchSolenoid->Set(false);
	}
	UpdateDashBoardGearState(g);
}

DriveSubsystem::Gear DriveSubsystem::GetGearState() {
	if (gearSwitchSolenoid->Get()) {
		return Gear::HighGear;
	}
	else {
		return Gear::LowGear;
	}
}

void DriveSubsystem::SyncDriveModeToHardware() {
	if (powerTakeOffSolenoid->Get()) {
		mode = DriveMode::ClimbingMode;
	}
	else {
		mode = DriveMode::DrivingMode;
	}
}
void DriveSubsystem::SetMode(DriveSubsystem::DriveMode dm) {
	if (dm == DriveMode::DrivingMode) {
		powerTakeOffSolenoid->Set(false);
		mode = DriveMode::DrivingMode;
	}
	else {
		powerTakeOffSolenoid->Set(true);
		mode = DriveMode::ClimbingMode;
	}
}

void DriveSubsystem::ResetAvgMotorCurrents() {
	for (double &curr : avgMotorCurrents)
	{
		curr = 0.0;
	}
	timeStep = 0;
	overloadCondition = false;
}

DriveSubsystem::SafetyCurrentAction DriveSubsystem::CheckAvgMotorCurrent(double avgCurrent) {
	if (avgCurrent >= TripSafetyActionCurrentAvg) {
		if (InDriveMode()) {
			if (GetGearState() == Gear::HighGear) {
				return LowGearAction;
			}

			return NoAction;
		}
		else {
			if (GetGearState() == Gear::HighGear) {
				return NoAction;
			}
		}
	}

	return NoAction;
}

namespace {
	const std::string* AvgSmartDashBoardKeys[] = {
		 &SmartDashboardKeys::FrontLeftDriveAvgCurrentKey,
		 &SmartDashboardKeys::FrontRightDriveAvgCurrentKey,
		 &SmartDashboardKeys::BackLeftDriveAvgCurrentKey,
		 &SmartDashboardKeys::BackRightDriveAvgCurrentKey
	};
}

void DriveSubsystem::AvgNewMotorCurrents(const DriveMotorCurrents &currents)
{
	SafetyCurrentAction action = NoAction;
	int motorsBelowAvgCurrentCount = 0;

	if (timeStep++ > 0)
	{
		for (unsigned int motorId = DriveMotorCurrents::firstMotor; motorId <= DriveMotorCurrents::lastMotor; ++motorId)
		{
			avgMotorCurrents[motorId] = (ExpAvgCurrentAlpha * currents.getCurrent(static_cast<DriveMotorCurrents::MotorId>(motorId))) + ((1 - ExpAvgCurrentAlpha) * avgMotorCurrents[motorId]);
			SmartDashboard::PutNumber(*AvgSmartDashBoardKeys[motorId], avgMotorCurrents[motorId]);

			if (timeStep >= SafetyActionMinTimeStepsCheckThreshold) {
				SafetyCurrentAction result = CheckAvgMotorCurrent(avgMotorCurrents[motorId]);

				if (result == NoAction) {
					if (overloadCondition && (avgMotorCurrents[motorId] < ResetOverloadConditionAvgCurrentLevel)) {
						++motorsBelowAvgCurrentCount;
					}
				}

				if (action == NoAction) {
					action = result;
				}
			}
		}
	}
	else
	{
		for (unsigned int motorId = DriveMotorCurrents::firstMotor; motorId <= DriveMotorCurrents::lastMotor; ++motorId)
		{
			avgMotorCurrents[motorId] = currents.getCurrent(static_cast<DriveMotorCurrents::MotorId>(motorId));
			SmartDashboard::PutNumber(*AvgSmartDashBoardKeys[motorId], avgMotorCurrents[motorId]);
		}
	}

	switch (action) {
	case NoAction:
	default:
		if (overloadCondition && (motorsBelowAvgCurrentCount >= DriveMotorCurrents::numMotors)) {
			overloadCondition = false;
		}
		break;

	case LowGearAction:
		SetGear(LowGear);
		break;

	case StopAction:
		robotDrive->ArcadeDrive(0.0, 0.0);
		overloadCondition = true;
		break;
	}
}


