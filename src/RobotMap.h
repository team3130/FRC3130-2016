#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

//Drive Motors
	const int LEFTMOTOR = 0;
	const int RIGHTMOTOR = 1;

//Intake Motors
	const int INTAKEMOTOR = 4;
//Shooter Motors
	const int SHOOTERMOTOR = 5;

//Pneumatics Ports
	const int COMPRESSOR = 0;
#endif
