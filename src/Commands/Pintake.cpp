#include "Pintake.h"
#include "Subsystems/Bincher.h"

Pintake::Pintake()
{
	Requires(Bincher::GetInstance());
}

// Called just before this Command runs the first time
void Pintake::Initialize()
{
	Bincher::GetInstance()->Actuate(true);
}

// Called repeatedly when this Command is scheduled to run
void Pintake::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool Pintake::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void Pintake::End()
{
	Bincher::GetInstance()->Actuate(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Pintake::Interrupted()
{
	End();
}