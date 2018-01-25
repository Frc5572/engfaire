#include "ground_gear.h"
#include "CanTalonSRX.h"
#include <VictorSP.h>
#include <DigitalInput.h>
#include <Timer.h>
#include <SmartDashboard/SmartDashboard.h>
#include <iostream>
#include <PowerDistributionPanel.h>
#include "arduino_i2c.h"

#define MOTOR CanTalonSRX
#define LIMIT_SWITCH frc::DigitalInput
#define AXLE_SPEED .43
#define ROLLER_SPEED .7

MOTOR *main_axle, *roller;
LIMIT_SWITCH*top;
bool dropping = false; // Whether or not the mech is dropping
frc::Timer t; // Timer for dropping
int state = 0;
bool ledon = false;
/*
 States:
 0: Do nothing
 1: Go down
 2: Go up
 3: Go up, then down
 */

void logset(std::string v, MOTOR *m, double p) {
	m->Set(p);
	//std::cout << v << ":" << p << std::endl;
}

void ground_gear::init() {
	main_axle = new MOTOR(7);
	roller = new MOTOR(9);
	top = new LIMIT_SWITCH(0);
}

void ground_gear::stop() {
	logset("main", main_axle, 0);
}

void ground_gear::update() {
	if (state == 0) { // Do nothing
		dropping = false; // We are not dropping
		logset("main", main_axle, 0);
	}
	frc::SmartDashboard::PutNumber("Top", top->Get());
	frc::SmartDashboard::PutNumber("State", state);
	/* If we've hit a limit switch */
	if (!top->Get() && state == 3) {
		state = 1; // Set state to going down
		dropping = true; // Indicate we are dropping
		t.Start(); // Start drop time
	} else if (!top->Get() && state != 1) {
		state = 0;
	}
	if (t.Get() > .3) { // After .2 seconds dropping
		state = 0; // Stop moving
		t.Stop();
		t.Reset(); // Reset timer for next drop
	}
	if (state == 1) { // If going down
		logset("main", main_axle, AXLE_SPEED);
		logset("roller", roller, -ROLLER_SPEED);
	}
	if (state == 2 || state == 3) { // If going up
		logset("main", main_axle, -AXLE_SPEED);
	}
}

void ground_gear::up() {
	main_axle->SetOverrideBrakeType(CanTalonSRX::kBrakeOverride_OverrideBrake); // Set to brake mode
	if (!top->Get())
		return;
	state = 2; // Set state to going up
}

void ground_gear::down() {
	main_axle->SetOverrideBrakeType(CanTalonSRX::kBrakeOverride_OverrideCoast); // Set to coast mode
	if (top->Get())
		return;
	state = 1; // Set state to going down
	dropping = true; // Indicate we are dropping
	t.Start(); // Start drop time
}

void ground_gear::roll(bool m) {
	if (!dropping)
		logset("roller", roller, m ? ROLLER_SPEED : 0);
}

void ground_gear::rollpower(double m) {
		roller->Set(m);
}
