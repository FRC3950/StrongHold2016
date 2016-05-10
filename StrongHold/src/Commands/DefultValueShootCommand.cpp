#include "DefultValueShootCommand.h"

DefultValueShootCommand::DefultValueShootCommand()  : ShootCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

DefultValueShootCommand::~DefultValueShootCommand(){

}
float DefultValueShootCommand::getTargetRotationsPerSecond(){
	return 156.00;
}
// Called just before this Command runs the first time
