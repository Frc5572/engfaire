#include "shooter.h"
#include "arduino_i2c.h"
#include "ports.h"
#include "gear.h"
#include <cmath>
#include <Timer.h>
#include "drivetrain.h"
#include "gear.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>

SHOOTER_MOTOR_TYPE *m_launcher;
SHOOTER_INDEXER_MOTOR_TYPE *m_indexer;
AGITATOR_MOTOR_TYPE *m_agitator;

void shooter::init() {
	m_launcher = SHOOTER_MOTOR;
	m_indexer = SHOOTER_PRIME_MOTOR; //Intake motor
	m_agitator = AGITATOR_MOTOR;
	if(DEBUG){
		SmartDashboard::PutString("Shooter Init ","Init Finished");
	}
}

void shooter::shoot(bool *is_indexer, double timenow) {
	static float DataR, DataL, DataS;
	static int info_data1, info_data2;
	static char a1;
	static char a2;

	arduino_i2c::ReadI2C(&a1, &a2, &DataS, &DataR, &DataL, &info_data1, &info_data2);
	if(DEBUG){
		SmartDashboard::PutNumber("ShooterPower", DataS);
		SmartDashboard::PutNumber("Actual RPMs", double(info_data1));
		//SmartDashboard::PutNumber("Target RPMs", double(info_data2));
		SmartDashboard::PutString("Code 1", &a1);

	}
	shooter::run(-DataS);

	if (a1 == 'I' && a2 == 'N' && !*is_indexer) {
		m_agitator->Set(frc::Relay::kOn);
		m_indexer->Set(INDEXER_POWER);
		*is_indexer = true;
		if(DEBUG){
			SmartDashboard::PutString("Code 1", &a1);
			//SmartDashboard::PutString("Code 2", &a2);
		}
	}
}

void shooter::stop() {
	arduino_i2c::Send_ST_Arduino();
	m_launcher->Set(0);
	m_indexer->Set(0);
	m_agitator->Set(frc::Relay::kOff);
}

void shooter::run(float power) {
	m_launcher->Set(power);
}

void shooter::agitator_run() {
	m_agitator->Set(frc::Relay::kOn);
}

void shooter::agitator_stop() {
	m_agitator->Set(frc::Relay::kOff);
}

void shooter::indexer_run() {
	m_indexer->Set(INDEXER_POWER);
}

void shooter::indexer_stop() {
	m_indexer->Set(0.0);
}
