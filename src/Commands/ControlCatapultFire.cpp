#include "OI.h"
#include "Subsystems/CatapultFire.h"
#include "Subsystems/IntakeHorizontal.h"
#include "Commands/ControlCatapultFire.h"
#include "Commands/ReloadCatapult.h"

/// Default constructor of the class.
ControlCatapultFire::ControlCatapultFire()
	: m_nextCommand(new ReloadCatapult(BTN_PRESET_2))
	, timer(new Timer())
	, m_waiting(false)
{
	Requires(CatapultFire::GetInstance());
	//Requires(IntakeHorizontal::GetInstance());
}

/// Called just before this Command runs the first time.
void ControlCatapultFire::Initialize()
{
	CatapultFire::GetInstance()->Actuate(false);
	if(IntakeHorizontal::GetInstance()->IsExtended() == false)
	{
		IntakeHorizontal::GetInstance()->Actuate(true);
		m_waiting = true;
	}
	else {
		m_waiting = false;
	}
	timer->Reset();
	timer->Start();
}


void ControlCatapultFire::Execute()
{
	if(!m_waiting or timer->Get() > .25)
	{
		CatapultFire::GetInstance()->Actuate(true);
		m_waiting = false;
	}

}

/// Make this return true when this Command no longer needs to run execute().
/// \return always false since this is the default command and should never finish.
bool ControlCatapultFire::IsFinished()
{
	return not OI::GetInstance()->gamepad->GetRawButton(BTN_SHOOT);
}

/// Called once after isFinished returns true
void ControlCatapultFire::End()
{
	CatapultFire::GetInstance()->Actuate(false);
	if(!m_waiting and timer->Get() < 3.0) m_nextCommand->Start();
}

/// Called when another command which requires one or more of the same
/// subsystems is scheduled to run
void ControlCatapultFire::Interrupted()
{
	// Do not call the normal End(); We don't want to start the next command if we're interrupted.
	CatapultFire::GetInstance()->Actuate(false);
}
