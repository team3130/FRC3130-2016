#include "OI.h"
#include "RobotMap.h"
#include "Commands/ReloadCatapult.h"
#include "Commands/Pintake.h"
#include "Commands/CameraAim.h"
#include "Commands/ControlCatapultFire.h"
#include "Commands/DriveShiftUp.h"
#include "Commands/DriveShiftDown.h"
#include "Commands/DriveStreightTest.h"

OI* OI::m_pInstance = NULL;

OI::OI()
{
	// Process operator interface input here.
	stickL = new Joystick(0);
	stickR = new Joystick(1);
	gamepad = new Joystick(2);

	preset1 	= new JoystickButton(gamepad, BTN_PRESET_1);
	preset2 	= new JoystickButton(gamepad, BTN_PRESET_2);
	intakePin 	= new JoystickButton(gamepad, BTN_INTAKEPIN);
	aimLeft 	= new JoystickButton(stickR, BTN_AIMLEFT);
	aimRight	= new JoystickButton(stickR, BTN_AIMRIGHT);
	fire    	= new JoystickButton(gamepad, BTN_SHOOT);
	shiftDown  	= new JoystickButton(stickL, BTN_SHIFT);
	shiftUp		= new JoystickButton(stickR, BTN_SHIFT);
	streight	= new JoystickButton(stickR, 10);

	preset1->WhenPressed(new ReloadCatapult(BTN_PRESET_1));
	preset2->WhenPressed(new ReloadCatapult(BTN_PRESET_2));
	intakePin->ToggleWhenPressed(new Pintake());
	aimLeft->WhileHeld(new CameraAim(CameraAim::kLeft));
	aimRight->WhileHeld(new CameraAim(CameraAim::kRight));
	fire->WhileHeld(new ControlCatapultFire());
	shiftUp->WhenPressed(new DriveShiftUp());
	shiftDown->WhenPressed(new DriveShiftDown());
	streight->WhileHeld(new DriveStreightTest());

	//SMD Input for Auton
	//Creates Radio Buttons for selection of Auton positions
	positionChooser = new SendableChooser();
	positionChooser->AddDefault("Low Bar",new int(1));
	positionChooser->AddObject("Position 2", new int(2));
	positionChooser->AddObject("Position 3", new int(3));
	positionChooser->AddObject("Position 4", new int(4));
	positionChooser->AddObject("position 5", new int(5));
	SmartDashboard::PutData("Auton Position",positionChooser);
}

double OI::ReturnAutonAngle()
{

	double angle;
	switch(*(int *)positionChooser->GetSelected()){
		case 1:
			angle = Preferences::GetInstance()->GetDouble("Auton Turn Angle LowBar", -45);
			break;
		case 2:
			angle = Preferences::GetInstance()->GetDouble("Auton Turn Angle Position2",-25);
			break;
		case 3:
			angle = Preferences::GetInstance()->GetDouble("Auton Turn Angle Position3",0);
			break;
		case 4:
			angle = Preferences::GetInstance()->GetDouble("Auton Turn Angle Position4",0);
			break;
		case 5:
			angle = Preferences::GetInstance()->GetDouble("Auton Turn Angle Position5",25);
			break;
	}
	return angle;
}

OI* OI::GetInstance()
{
	if(!m_pInstance) m_pInstance = new OI;
	return m_pInstance;
}
