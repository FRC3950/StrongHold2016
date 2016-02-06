#include "Robot.h"
#include "Logging.h"
#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/ExampleCommand.h"
#include "CommandBase.h"
#include "Config/CsvConfigFileReader.h"
#include "Config/ConfigInstanceMgr.h"


static const std::string ConfigFileName = "/home/lvuser/RobotConfig.csv";

std::shared_ptr<DriveSubsystem> Robot::driveSubsystem;
std::shared_ptr<IntakeSubsystem> Robot::intakeSubsystem;
std::shared_ptr<ClimberSubsystem> Robot::climberSubsystem;
std::shared_ptr<PowerDistributionPanel> Robot::pdp;
std::unique_ptr<OI> Robot::oi;


namespace
{
	const std::string DefaultAutoStr = "Default Auto";

	const std::string IMUStr = "IMU";
	const std::string GyroStr = "Gyro";
	const double DriveVictorMaxCurrent = 12.0;

	enum DriveMotorVictor {
		FrontLeftVictor = 0,
		FrontRightVictor,
		BackLeftVictor,
		BackRightVictor
	};
}

DriveMotorCurrents Robot::getDriveMotorCurrents(){
	return DriveMotorCurrents(
			pdp->GetCurrent(FrontLeftVictor),
			pdp->GetCurrent(FrontRightVictor),
			pdp->GetCurrent(BackLeftVictor),
			pdp->GetCurrent(BackRightVictor));
}
void Robot::RobotInit()
{
	Logger *logger = Logger::GetInstance(true, true);
	logger->SetLoggingLevel(Logger::kTRACE);
	logger->SetLoggingMask(DefaultLoggingMask);
	logger->Log(RobotLogId, Logger::kTRACE, "RobotInit::Entered");
	ConfigInstanceMgr::getInstance(ConfigFileName, false);

	try
	{
		RobotMap::init();
	}
	catch (std::exception& ex ) {
		std::string err_string = "Error initializing RobotMap:  ";
		err_string += ex.what();
		DriverStation::ReportError(err_string.c_str());
	}

	ahrs = RobotMap::ahrs;

	CommandBase::init();
	driveSubsystem.reset(new DriveSubsystem());
	intakeSubsystem.reset(new IntakeSubsystem());
	climberSubsystem.reset(new ClimberSubsystem());


	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());


	chooser.reset(new SendableChooser());
	chooser->AddDefault(DefaultAutoStr, new ExampleCommand());
	//chooser->AddObject("My Auto", new MyAutoCommand());

	// FIX ME!	SmartDashboard::PutData("Auto Modes", chooser);

	if (ahrs) {
		LiveWindow::GetInstance()->AddSensor(IMUStr, GyroStr, ahrs);
	}
}

/**
 * This function is called once each time the robot enters Disabled mode.
 * You can use it to reset any subsystem information you want to clear when
 * the robot is disabled.
 */
void Robot::DisabledInit()
{
}

void Robot::DisabledPeriodic()
{
	Scheduler::GetInstance()->Run();
}

/**
 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
 * Dashboard, remove all of the chooser code and uncomment the GetString code to get the auto name from the text box
 * below the Gyro
 *
 * You can add additional auto modes by adding additional commands to the chooser code above (like the commented example)
 * or additional comparisons to the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit()
{
	/* std::string autoSelected = SmartDashboard::GetString("Auto Selector", "Default");
	if(autoSelected == "My Auto") {
		autonomousCommand.reset(new MyAutoCommand());
	} else {
		autonomousCommand.reset(new ExampleCommand());
	} */

	//autonomousCommand.reset(new ExampleCommand());
	//autonomousCommand.reset((Command *) chooser->GetSelected());

	if (autonomousCommand != NULL)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic()
{
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit()
{
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	if (autonomousCommand != NULL)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic()
{
	OutputNavxData();
	OutputMotorCurrents();
	Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic()
{
	LiveWindow::GetInstance()->Run();
}

void Robot::OutputMotorCurrents()
{
	DriveMotorCurrents currents = getDriveMotorCurrents();

	SmartDashboard::PutNumber(  "Front Left Drive Motor", currents.getCurrent(DriveMotorCurrents::frontLeft));
	SmartDashboard::PutNumber(  "Front Right Drive Motor", currents.getCurrent(DriveMotorCurrents::frontRight));
	SmartDashboard::PutNumber(  "Back Left Drive Motor", currents.getCurrent(DriveMotorCurrents::backLeft));
	SmartDashboard::PutNumber(  "Back Right Drive Motor", currents.getCurrent(DriveMotorCurrents::backRight));

	bool goodCurrent = true;
	if (currents.getCurrent(DriveMotorCurrents::frontLeft) > DriveVictorMaxCurrent ||
			currents.getCurrent(DriveMotorCurrents::frontRight) > DriveVictorMaxCurrent ||
			currents.getCurrent(DriveMotorCurrents::backLeft) > DriveVictorMaxCurrent||
			currents.getCurrent(DriveMotorCurrents::backRight) > DriveVictorMaxCurrent){
		goodCurrent = false;

	}
	SmartDashboard::PutString("Drive Motor Current", goodCurrent ? "NORMAL" : "OVERLOADED");
}
void Robot::OutputNavxData()
{
	 if ( !ahrs ) return;

	bool reset_yaw_button_pressed = DriverStation::GetInstance().GetStickButton(0,1);
	if ( reset_yaw_button_pressed ) {
		ahrs->ZeroYaw();
	}

	SmartDashboard::PutBoolean( "IMU_Connected",        ahrs->IsConnected());
	SmartDashboard::PutNumber(  "IMU_Yaw",              ahrs->GetYaw());
	SmartDashboard::PutNumber(  "IMU_Pitch",            ahrs->GetPitch());
	SmartDashboard::PutNumber(  "IMU_Roll",             ahrs->GetRoll());
	SmartDashboard::PutNumber(  "IMU_CompassHeading",   ahrs->GetCompassHeading());
	SmartDashboard::PutNumber(  "IMU_Update_Count",     ahrs->GetUpdateCount());
	SmartDashboard::PutNumber(  "IMU_Byte_Count",       ahrs->GetByteCount());

	/* These functions are compatible w/the WPI Gyro Class */
	SmartDashboard::PutNumber(  "IMU_TotalYaw",         ahrs->GetAngle());
	SmartDashboard::PutNumber(  "IMU_YawRateDPS",       ahrs->GetRate());

	SmartDashboard::PutNumber(  "IMU_Accel_X",          ahrs->GetWorldLinearAccelX());
	SmartDashboard::PutNumber(  "IMU_Accel_Y",          ahrs->GetWorldLinearAccelY());
	SmartDashboard::PutBoolean( "IMU_IsMoving",         ahrs->IsMoving());
	SmartDashboard::PutNumber(  "IMU_Temp_C",           ahrs->GetTempC());
	SmartDashboard::PutBoolean( "IMU_IsCalibrating",    ahrs->IsCalibrating());

	SmartDashboard::PutNumber(  "Velocity_X",           ahrs->GetVelocityX() );
	SmartDashboard::PutNumber(  "Velocity_Y",           ahrs->GetVelocityY() );
	SmartDashboard::PutNumber(  "Displacement_X",       ahrs->GetDisplacementX() );
	SmartDashboard::PutNumber(  "Displacement_Y",       ahrs->GetDisplacementY() );

	/* Display Raw Gyro/Accelerometer/Magnetometer Values                       */
	/* NOTE:  These values are not normally necessary, but are made available   */
	/* for advanced users.  Before using this data, please consider whether     */
	/* the processed data (see above) will suit your needs.                     */

	SmartDashboard::PutNumber(  "RawGyro_X",            ahrs->GetRawGyroX());
	SmartDashboard::PutNumber(  "RawGyro_Y",            ahrs->GetRawGyroY());
	SmartDashboard::PutNumber(  "RawGyro_Z",            ahrs->GetRawGyroZ());
	SmartDashboard::PutNumber(  "RawAccel_X",           ahrs->GetRawAccelX());
	SmartDashboard::PutNumber(  "RawAccel_Y",           ahrs->GetRawAccelY());
	SmartDashboard::PutNumber(  "RawAccel_Z",           ahrs->GetRawAccelZ());
	SmartDashboard::PutNumber(  "RawMag_X",             ahrs->GetRawMagX());
	SmartDashboard::PutNumber(  "RawMag_Y",             ahrs->GetRawMagY());
	SmartDashboard::PutNumber(  "RawMag_Z",             ahrs->GetRawMagZ());
	SmartDashboard::PutNumber(  "IMU_Temp_C",           ahrs->GetTempC());
	/* Omnimount Yaw Axis Information                                           */
	/* For more info, see http://navx-mxp.kauailabs.com/installation/omnimount  */
	AHRS::BoardYawAxis yaw_axis = ahrs->GetBoardYawAxis();
	SmartDashboard::PutString(  "YawAxisDirection",     yaw_axis.up ? "Up" : "Down" );
	SmartDashboard::PutNumber(  "YawAxis",              yaw_axis.board_axis );

	/* Sensor Board Information                                                 */
	SmartDashboard::PutString(  "FirmwareVersion",      ahrs->GetFirmwareVersion());

	/* Quaternion Data                                                          */
	/* Quaternions are fascinating, and are the most compact representation of  */
	/* orientation data.  All of the Yaw, Pitch and Roll Values can be derived  */
	/* from the Quaternions.  If interested in motion processing, knowledge of  */
	/* Quaternions is highly recommended.                                       */
	SmartDashboard::PutNumber(  "QuaternionW",          ahrs->GetQuaternionW());
	SmartDashboard::PutNumber(  "QuaternionX",          ahrs->GetQuaternionX());
	SmartDashboard::PutNumber(  "QuaternionY",          ahrs->GetQuaternionY());
	SmartDashboard::PutNumber(  "QuaternionZ",          ahrs->GetQuaternionZ());
}

START_ROBOT_CLASS(Robot)
