#include "climber.h"
#include "ports.h"
#include <DoubleSolenoid.h>
#include <WPILib.h>

frc::DoubleSolenoid *primer;
CLIMBER_MOTOR_TYPE *climbe;

void climber::init() {
	primer = new frc::DoubleSolenoid(12, CLIMBER_DOUBLE_SOLENOID_ID);
	climbe = CLIMBER_MOTOR;
	primer->Set(DoubleSolenoid::kForward);
}

void climber::prime() {
	primer->Set(DoubleSolenoid::kReverse);
}

void climber::piston_reset() {
	primer->Set(DoubleSolenoid::kForward);
}

void climber::piston_stop() {
	primer->Set(DoubleSolenoid::kOff);
}

void climber::climb(double a) {
	climbe->Set(a);
}
