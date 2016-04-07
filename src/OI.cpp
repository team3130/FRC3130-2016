#include "OI.h"
#include "RobotMap.h"
#include "Commands/ReloadCatapult.h"
#include "Commands/Pintake.h"
#include "Commands/CameraAim.h"
#include "Commands/ControlCatapultFire.h"
#include "Commands/DriveShiftUp.h"
#include "Commands/DriveShiftDown.h"
#include "Commands/DriveStreightTest.h"
#include "Commands/HandleStopPoints.h"
#include "Commands/WipeStopPoints.h"
#include "Commands/SaveStopPoints.h"
#include "Commands/TestStopPoints.h"

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
	savePoints	= new SaveStopPoints();
	addPoint	= new HandleStopPoints();
	wipePoints 	= new WipeStopPoints();
	testPoints	= new TestStopPoints();

	preset1->WhenPressed(new ReloadCatapult(BTN_PRESET_1));
	preset2->WhenPressed(new ReloadCatapult(BTN_PRESET_2));
	intakePin->ToggleWhenPressed(new Pintake());
	aimLeft->WhileHeld(new CameraAim(CameraAim::kLeft));
	aimRight->WhileHeld(new CameraAim(CameraAim::kRight));
	fire->WhileHeld(new ControlCatapultFire());
	shiftUp->WhenPressed(new DriveShiftUp());
	shiftDown->WhenPressed(new DriveShiftDown());
	streight->WhileHeld(new DriveStreightTest());

	SmartDashboard::PutData("Save Data", savePoints);
	SmartDashboard::PutData("Wipe Stop Data", wipePoints);
	SmartDashboard::PutData("Add Point", addPoint);
	SmartDashboard::PutData("Test Points", testPoints);

	//SMD Input for Auton
	//Creates Radio Buttons for selection of Auton positions
	positionChooser = new SendableChooser();
	positionChooser->AddDefault("Low Bar",new int(1));
	positionChooser->AddObject("Position 2", new int(2));
	positionChooser->AddObject("Position 3", new int(3));
	positionChooser->AddObject("Position 4", new int(4));
	positionChooser->AddObject("position 5", new int(5));
	SmartDashboard::PutData("Auton Position",positionChooser);

	//Creates Radio Buttons for selection of Auton defenses
	defenseChooser = new SendableChooser();
	defenseChooser->AddDefault("Low Bar", new int(1));
	defenseChooser->AddObject("Moat", new int(2));
	defenseChooser->AddObject("Ramparts", new int(3));
	defenseChooser->AddObject("Rough Terrain", new int(4));
	defenseChooser->AddObject("Rock Wall", new int(5));
	SmartDashboard::PutData("Auton Defense",defenseChooser);
}

double OI::ReturnAutonAngle()
{

	double angle;
	switch(*(int *)positionChooser->GetSelected()){
		case 1:
			angle = Preferences::GetInstance()->GetDouble("Auton Turn Angle LowBar", -45);
			break;
		case 2:
			angle = Preferences::GetInstance()->GetDouble("Auton Turn Angle Position2",-28);
			break;
		case 3:
			angle = Preferences::GetInstance()->GetDouble("Auton Turn Angle Position3",-15);
			break;
		case 4:
			angle = Preferences::GetInstance()->GetDouble("Auton Turn Angle Position4",0);
			break;
		case 5:
			angle = Preferences::GetInstance()->GetDouble("Auton Turn Angle Position5",15);
			break;
	}
	return angle;
}

double OI::ReturnAutonDistance()
{
	double dist;
	switch(*(int *)defenseChooser->GetSelected()){
		case 1:
			dist = Preferences::GetInstance()->GetDouble("Low Bar Drive Distance", 140);
			break;
		case 2:
			dist = Preferences::GetInstance()->GetDouble("Moat Drive Distance", 150);
			break;
		case 3:
			dist = Preferences::GetInstance()->GetDouble("Ramparts Drive Distance", 140);
			break;
		case 4:
			dist = Preferences::GetInstance()->GetDouble("Rough Terrain Drive Distance", 140);
			break;
		case 5:
			dist = Preferences::GetInstance()->GetDouble("Rock Wall Drive Distance", 140);
			break;
	}
	if(*(int *)positionChooser->GetSelected() == 2 || *(int *)positionChooser->GetSelected() == 5) dist += 49;
	return dist;
}

OI* OI::GetInstance()
{
	if(!m_pInstance) m_pInstance = new OI;
	return m_pInstance;
}
