#ifndef CONTROL_SHOOTER_MOTOR_H
#define CONTROL_SHOOTER_MOTOR_H

#include <WPILib.h>

/** Default command for driving the chassis.
 *
 * The default for the chassis is to be driven manually by a human operator.
 * This command reads the inputs from joysticks using the IO (operator interface) class
 * and controls the chassis via its public methods.
 */
class ControlShooterMotor: public Command
{
	enum PresetButton { kX, kY, kA, kB };
private:
	PresetButton preset;
	float wheelSpeed;
public:
	ControlShooterMotor();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif