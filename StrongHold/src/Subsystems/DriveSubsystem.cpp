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
	const int ABOVE_AVG_CURR_CONSEC_EPOCH_THRESHOLD_DEFAULT = 1;
	int AboveAvgCurrConsecEpochThreshold = ABOVE_AVG_CURR_CONSEC_EPOCH_THRESHOLD_DEFAULT;

#if 0
	void SetSafetyMode(Talon& motor, bool enabled, float timeout) {
		Logger::GetInstance()->Log(DriveMotorSafetyLogId, Logger::kTRACE, "DriveSubsystem::SetSafteyMode() = %s, timeout=%f",
			enabled ? "TRUE" : "FALSE", timeout);

		motor.SetSafetyEnabled(enabled);
		motor.SetExpiration(timeout);
	}
#endif

	void VictorSetSafetyMode(Victor& motor, bool enabled, float timeout) {
			Logger::GetInstance()->Log(DriveMotorSafetyLogId, Logger::kTRACE, "DriveSubsystem::SetSafteyMode() = %s, timeout=%f",
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
	    	AboveAvgCurrConsecEpochThreshold = configMgr->getIntVal(ConfigKeys::Drive_AboveAvgCurrConsecEpochThresholdKey, ABOVE_AVG_CURR_CONSEC_EPOCH_THRESHOLD_DEFAULT);



			Logger* logger = Logger::GetInstance();

			logger->Log(DriveMotorSafetyLogId, Logger::kINFO, "DriveSubsystem: Exponential Avg Alpha = %g\n", ExpAvgCurrentAlpha);
			logger->Log(DriveMotorSafetyLogId, Logger::kINFO, "DriveSubsystem: Trip Safety Action Current = %g\n", TripSafetyActionCurrentAvg);
			logger->Log(DriveMotorSafetyLogId, Logger::kINFO, "DriveSubsystem: Reset Overload Condition Avg Current Level = %g\n", ResetOverloadConditionAvgCurrentLevel);
			logger->Log(DriveMotorSafetyLogId, Logger::kINFO, "DriveSubsystem: Safety Action Min Time Steps Check Threshold = %u\n", SafetyActionMinTimeStepsCheckThreshold);
			logger->Log(DriveMotorSafetyLogId, Logger::kINFO, "DriveSubsystem: Above Avg Curr Consec Epoch Threshold = %u\n", SafetyActionMinTimeStepsCheckThreshold);

	      	ConfigInited = true;
	    }
	}
}

DriveSubsystem::DriveSubsystem() :
		Subsystem("DriveSubsystem"),
		avgMotorCurrents(DriveMotorCurrents::numMotors, 0.0),
		aboveAvgCurrentThresholdEpochCounts(DriveMotorCurrents::numMotors, 0)
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

	Logger::GetInstance()->Log(DrivingLogId,Logger::kINFO, "DriveSubsystem:EnableDriveSubsystem() ->SafetyEnable=%s, timeout=%f\n",
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
	Logger::GetInstance()->Log(DrivingLogId, Logger::kTRACE, "DriveSubsystem::ArcadeDrive()->y = %f, twist=%f", y, twist);

	if (!InDriveMode())
	{
		Logger::GetInstance()->Log(DrivingLogId, Logger::kERROR, "DriveSubsystem::ArcadeDrive called but NOT in drive mode. IGNORING!");
		return;
	}

	if (overloadCondition) {
		Logger::GetInstance()->Log(DrivingLogId, Logger::kWARNING, "DriveSubsystem::ArcadeDrive called but in overload condition, y and twist reset to 0.0!");
		twist = 0.0;
		y = 0.0;
	}

	robotDrive->ArcadeDrive(twist,y);
}

void DriveSubsystem::Climb(float y) {
	Logger::GetInstance()->Log(ClimbingLogId, Logger::kTRACE, "DriveSubsystem::Climb()->y = %f", y);

	if (!InClimbMode())
	{
		Logger::GetInstance()->Log(ClimbingLogId, Logger::kERROR, "DriveSubsystem::Climb called but NOT in climb mode. IGNORING!");
		return;
	}

	if (overloadCondition) {
		Logger::GetInstance()->Log(ClimbingLogId, Logger::kWARNING, "DriveSubsystem::Climb called but in overload condition, y reset to 0.0!");
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
	for (unsigned int currId = DriveMotorCurrents::firstMotor;
		 currId < DriveMotorCurrents::numMotors;
		 ++currId) {
		avgMotorCurrents[currId] = 0.0;
		aboveAvgCurrentThresholdEpochCounts[currId] = 0;
	}

	timeStep = 0;
	overloadCondition = false;
}

DriveSubsystem::SafetyCurrentAction DriveSubsystem::CheckAvgMotorCurrent(DriveMotorCurrents::MotorId motorId) {
	if ((avgMotorCurrents[motorId] >= TripSafetyActionCurrentAvg) &&
		(aboveAvgCurrentThresholdEpochCounts[motorId] >= AboveAvgCurrConsecEpochThreshold))	{
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

	const std::string* AboveAvgCurrentThresholdEpochCountsSmartDashBoardKeys[] = {
		&SmartDashboardKeys::FrontLeftDriveConsecEpochsAboveThresholdKey,
		&SmartDashboardKeys::FrontRightDriveConsecEpochsAboveThresholdKey,
		&SmartDashboardKeys::BackLeftDriveConsecEpochsAboveThresholdKey,
		&SmartDashboardKeys::BackRightDriveConsecEpochsAboveThresholdKey
	};
}

void DriveSubsystem::OutputAvgMotorCurrent(DriveMotorCurrents::MotorId motorId) const {
	SmartDashboard::PutNumber(*AvgSmartDashBoardKeys[motorId], avgMotorCurrents[motorId]);
	SmartDashboard::PutNumber(*AboveAvgCurrentThresholdEpochCountsSmartDashBoardKeys[motorId], aboveAvgCurrentThresholdEpochCounts[motorId]);
}

void DriveSubsystem::AvgNewMotorCurrents(const DriveMotorCurrents &currents)
{
	SafetyCurrentAction pendingAction = NoAction;
	int motorsBelowAvgCurrentCount = 0;

	if (timeStep++ > 0)
	{
		for (unsigned int currMotorId = DriveMotorCurrents::firstMotor; currMotorId <= DriveMotorCurrents::lastMotor; ++currMotorId)
		{
			avgMotorCurrents[currMotorId] = (ExpAvgCurrentAlpha * currents.getCurrent(static_cast<DriveMotorCurrents::MotorId>(currMotorId))) + ((1 - ExpAvgCurrentAlpha) * avgMotorCurrents[currMotorId]);

			if (avgMotorCurrents[currMotorId] >= TripSafetyActionCurrentAvg) {
				++aboveAvgCurrentThresholdEpochCounts[currMotorId];
			}
			else {
				aboveAvgCurrentThresholdEpochCounts[currMotorId] = 0;
			}

			OutputAvgMotorCurrent(static_cast<DriveMotorCurrents::MotorId>(currMotorId));

			if (timeStep >= SafetyActionMinTimeStepsCheckThreshold) {
				if (pendingAction == NoAction) {
					// Check to see if a new action should be taken?
					SafetyCurrentAction newAction = CheckAvgMotorCurrent(static_cast<DriveMotorCurrents::MotorId>(currMotorId));

					// Does the current motor, motorId, requires no action be taken.
					if (newAction == NoAction) {
						// Are we in an overloadCondition and is the current motor's avg current below the reset threshold
						if (overloadCondition && (avgMotorCurrents[currMotorId] < ResetOverloadConditionAvgCurrentLevel)) {
							// Count this as a good motor.
							++motorsBelowAvgCurrentCount;
						}
					}
					else {
						// Set the pending action.
						pendingAction = newAction;
					}
				}
			}
		}
	}
	else
	{
		for (unsigned int currMotorId = DriveMotorCurrents::firstMotor; currMotorId <= DriveMotorCurrents::lastMotor; ++currMotorId)
		{
			avgMotorCurrents[currMotorId] = currents.getCurrent(static_cast<DriveMotorCurrents::MotorId>(currMotorId));
			aboveAvgCurrentThresholdEpochCounts[currMotorId] = 0;
			OutputAvgMotorCurrent(static_cast<DriveMotorCurrents::MotorId>(currMotorId));
		}
	}

	switch (pendingAction) {
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


