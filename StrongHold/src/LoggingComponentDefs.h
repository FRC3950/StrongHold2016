#if !defined(LOGGING_COMPONENT_DEFS_H)

#define LOGGING_COMPONENT_DEFS_H

#include "Logger.h"

const unsigned int RobotLogId				= 1U << 0; 	//0x00000001U;
const unsigned int GantrySubsystemLogId 	= 1U << 1;  //0x00000002U;
const unsigned int TemporaryLogId           = 1U << 2;  //0x00000004U;
const unsigned int IntakeSubsystemLogId 	= 1U << 3;  //0x00000008U;
const unsigned int PneumaticsSubsystemLogId	= 1U << 4;  //0x00000010U;
const unsigned int ShooterSubsystemLogId	= 1U << 5;	//0x00000020U;
const unsigned int VisionTargetingLogId		= 1U << 6;	//0x00000040U;
const unsigned int ConfigurationLogId		= 1U << 7;  //0x00000080U;
const unsigned int OILogId					= 1U << 8;  //0x00000100U;
const unsigned int DrivingLogId             = 1U << 9;  //0x00000200U;
const unsigned int ClimbingLogId            = 1U << 10; //0x00000400U;
const unsigned int DriveMotorSafetyLogId    = 1U << 11; //0x00000800U;
const unsigned int ManipulatorLogId			= 1U << 12; //0x00001000U
const unsigned int DriveSubsystemLogId = (DrivingLogId | ClimbingLogId | DriveMotorSafetyLogId);

const unsigned int DefaultLoggingMask = (ManipulatorLogId | OILogId | ClimbingLogId | RobotLogId | ShooterSubsystemLogId | ConfigurationLogId | VisionTargetingLogId | GantrySubsystemLogId);
const Logger::MessageType DefaultLoggingLevel = Logger::kINFO;

#endif
