
#include "autonomous.h"
#include "arduino_i2c.h"
#include "shooter.h"
#include "ports.h"
#include "gear.h"
#include <Timer.h>
#include "drivetrain.h"
#include "gear.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>


void autonomous::auto5(RobotBase *rb) {
	DriveStraight(rb, 'R','1'); //rb is robot base,
	drivetrain::retract_versa();
	Rotate(rb, 'R','2');
	DriveStraight(rb, 'R','3'); //rb is robot base,
	gear::open();
	Wait(0.2);
	DriveBack();
	gear::close();
	//Rotate(rb, 'R','4');
	//DriveStraight(rb, 'R','5');
	//Rotate(rb, 'R','6');
	//DriveStraight(rb, 'R','7');
	arduino_i2c::Send('S','T','0','0','0','0');
}

/*
void autonomous::auto1(RobotBase *rb){ //Central peg red and shooting
	static char a1, a2;
	static float DataS, DataR, DataL;
	static int info_data1, info_data2;
	bool start_shooting = true;

	DriveStraight(rb, 'A','1'); //rb is robot base, '4' is the A4 command for the arduino
	arduino_i2c::ReadI2C(&a1, &a2, &DataS, &DataR, &DataL, &info_data1, &info_data2);
	//shooter::run(SHOOTER_INIT_POWER2);
	gear::open();
	Wait(0.4);
	DriveBack2();
	drivetrain::retract_versa();
	Rotate(rb, 'A','2'); //rb is robot base, '7' is the A7 command for the arduino
	arduino_i2c::Send('A', '3', '0','0','0','0');
	// std::cout << "Sent C3" << std::endl;
	while (rb->IsEnabled() && rb->IsAutonomous()){
		arduino_i2c::ReadI2C(&a1, &a2, &DataS, &DataR, &DataL, &info_data1, &info_data2); // Get Power values
		//shooter::run(-DataS);

		if(DEBUG){
			//SmartDashboard::PutString("Auto Debug", "I am in A8 Function");
			SmartDashboard::PutNumber("ShooterPower", DataS);
			//SmartDashboard::PutNumber("LeftPower", DataL);
			//SmartDashboard::PutNumber("RightPower", DataR);
			//SmartDashboard::PutString("Code 1", &a1);
			//SmartDashboard::PutString("Code 2", &a2);
			//SmartDashboard::PutNumber("Distance", info_data1); //Measured by the ultrasound
			//SmartDashboard::PutNumber("Target RPMs", info_data2); //RPMs calculated by the arduino function
		}

		if(start_shooting){
			//shooter::indexer_run();
			//shooter::agitator_run();
			start_shooting = false;
		}
		Wait(.001); // Delays the cycle for 1 ms
	}
	//shooter::indexer_stop();
	//shooter::agitator_stop();
	arduino_i2c::Send('S','T','0','0','0','0');
	gear::close();
}

*/

void autonomous::auto1(RobotBase *rb){ //Central peg red and shooting
	static char a1, a2;
	static float DataS, DataR, DataL;
	static int info_data1, info_data2;
	DriveStraight(rb, 'A','1'); //rb is robot base, '4' is the A4 command for the arduino
	arduino_i2c::ReadI2C(&a1, &a2, &DataS, &DataR, &DataL, &info_data1, &info_data2);
	gear::open();
	Wait(0.4);
	DriveBack2();
	drivetrain::retract_versa();
	arduino_i2c::Send('S','T','0','0','0','0');
	gear::close();
}

void autonomous::auto3(RobotBase *rb){ //Central peg red and shooting
	static char a1, a2;
	static float DataS, DataR, DataL;
	static int info_data1, info_data2;

	DriveStraight(rb, 'C','1'); //rb is robot base, '4' is the A4 command for the arduino
	arduino_i2c::ReadI2C(&a1, &a2, &DataS, &DataR, &DataL, &info_data1, &info_data2);
	gear::open();
	Wait(0.4);
	DriveBack2();
	drivetrain::retract_versa();
	arduino_i2c::Send('S','T','0','0','0','0');
	gear::close();
}

/*
void autonomous::auto3(RobotBase *rb){ //Central peg red and shooting
	static char a1, a2;
	static float DataS, DataR, DataL;
	static int info_data1, info_data2;
	bool start_shooting = true;

	DriveStraight(rb, 'C','1'); //rb is robot base, '4' is the A4 command for the arduino
	arduino_i2c::ReadI2C(&a1, &a2, &DataS, &DataR, &DataL, &info_data1, &info_data2);
	//shooter::run(SHOOTER_INIT_POWER2);
	gear::open();
	Wait(0.4);
	DriveBack2();
	drivetrain::retract_versa();
	Rotate(rb, 'C','2'); //rb is robot base, '7' is the A7 command for the arduino
	arduino_i2c::Send('C', '3', '0','0','0','0');
	std::cout << "Sent C3" << std::endl;
	while (rb->IsEnabled() && rb->IsAutonomous()){
		arduino_i2c::ReadI2C(&a1, &a2, &DataS, &DataR, &DataL, &info_data1, &info_data2); // Get Power values
		//shooter::run(-DataS);

		if(DEBUG){
			//SmartDashboard::PutString("Auto Debug", "I am in A8 Function");
			SmartDashboard::PutNumber("ShooterPower", DataS);
			//SmartDashboard::PutNumber("LeftPower", DataL);
			//SmartDashboard::PutNumber("RightPower", DataR);
			//SmartDashboard::PutString("Code 1", &a1);
			//SmartDashboard::PutString("Code 2", &a2);
			//SmartDashboard::PutNumber("Distance", info_data1); //Measured by the ultrasound
			//SmartDashboard::PutNumber("Target RPMs", info_data2); //RPMs calculated by the arduino function
		}

		if(start_shooting){
			//shooter::indexer_run();
			//shooter::agitator_run();
			start_shooting = false;
		}
		Wait(.001); // Delays the cycle for 1 ms
	}
	//shooter::indexer_stop();
	//shooter::agitator_stop();
	arduino_i2c::Send('S','T','0','0','0','0');
	gear::close();
}

*/

void autonomous::auto4(RobotBase *rb){ // Left Peg and shooting
	static char a1, a2;
	static float DataS, DataR, DataL;
	static int info_data1, info_data2;

	bool start_shooting = true;
	static union {
		float Float;
		uint8_t Byte[4];
	}Transmit_data;
	Transmit_data.Float = 0.0;

	//drivetrain::retract_versa();

	DriveStraight(rb, 'A','4'); //rb is robot base, '4' is the A4 command for the arduino
	drivetrain::retract_versa();
	Rotate(rb, 'A','5');
	DriveStraight(rb, 'A','6'); //rb is robot base, '6' is the A6 command for the arduino
	arduino_i2c::ReadI2C(&a1, &a2, &DataS, &DataR, &DataL, &info_data1, &info_data2);
	//shooter::run(SHOOTER_INIT_POWER1);//   //Starts the shooter up with the power defined in shooter.h
	//gear::open();
	//Wait(0.2);
	DriveBack();
	Rotate(rb, 'A','7'); //rb is robot base, '7' is the A7 command for the arduino
	arduino_i2c::Send('A','8',Transmit_data.Byte[0], Transmit_data.Byte[1], Transmit_data.Byte[2], Transmit_data.Byte[3]);
	while (rb->IsEnabled() && rb->IsAutonomous()){
		arduino_i2c::ReadI2C(&a1, &a2, &DataS, &DataR, &DataL, &info_data1, &info_data2); // Get Power values
		//shooter::run(-DataS);
		if(DEBUG){
			SmartDashboard::PutString("Auto Debug", "I am in A8 Function");
			SmartDashboard::PutNumber("ShooterPower", DataS);
			SmartDashboard::PutNumber("LeftPower", DataL);
			SmartDashboard::PutNumber("RightPower", DataR);
			SmartDashboard::PutString("Code 1", &a1);
			SmartDashboard::PutString("Code 2", &a2);
			SmartDashboard::PutNumber("Distance", info_data1); //Measured by the ultrasound
			SmartDashboard::PutNumber("Target RPMs", info_data2); //RPMs calculated by the arduino function
		}
		if(start_shooting){ //(a1 == 'I' && a2 == 'N' && start_shooting){
			if(DEBUG){
				SmartDashboard::PutString("Auto Debug", "I am in A8 Indexer");
				SmartDashboard::PutNumber("ShooterPower", DataS);
				SmartDashboard::PutNumber("LeftPower", DataL);
				SmartDashboard::PutNumber("RightPower", DataR);
				SmartDashboard::PutString("Code 1", &a1);
				SmartDashboard::PutString("Code 2", &a2);
			}
			//shooter::indexer_run();
			//shooter::agitator_run();
			start_shooting = false;
		}
		Wait(.001); // Delays the cycle for 1 ms
	}
	//shooter::indexer_stop();
	//shooter::agitator_stop();
	arduino_i2c::Send_ST_Arduino();
	gear::close();
}

void autonomous::auto6(RobotBase *rb){ // Right Peg and shooting
	static char a1, a2;
	static float DataS, DataR, DataL;
	static int info_data1, info_data2;
	//bool gear_is_dropped = false;
	bool start_shooting = true;
	static union {
		float Float;
		uint8_t Byte[4];
	}Transmit_data;
	Transmit_data.Float = 0.0;

	DriveStraight(rb, 'S','1'); //rb is robot base, '4' is the A4 command for the arduino
	drivetrain::retract_versa();
	Rotate(rb, 'S','2');
	DriveStraight(rb, 'S','3'); //rb is robot base, '6' is the A6 command for the arduino
	arduino_i2c::ReadI2C(&a1, &a2, &DataS, &DataR, &DataL, &info_data1, &info_data2);
	//shooter::run(SHOOTER_INIT_POWER1);// //Starts the shooter up with the power defined in shooter.h
	gear::open();
	Wait(0.2);
	DriveBack();
	Rotate(rb, 'S','4'); //rb is robot base, '7' is the A7 command for the arduino
	arduino_i2c::Send('S','5',Transmit_data.Byte[0], Transmit_data.Byte[1], Transmit_data.Byte[2], Transmit_data.Byte[3]);
	while (rb->IsEnabled() && rb->IsAutonomous()){
		arduino_i2c::ReadI2C(&a1, &a2, &DataS, &DataR, &DataL, &info_data1, &info_data2); // Get Power values
		//shooter::run(-DataS);
		if(DEBUG){
			SmartDashboard::PutString("Auto Debug", "I am in A6 Function");
			SmartDashboard::PutNumber("ShooterPower", DataS);
			//SmartDashboard::PutNumber("LeftPower", DataL);
			//SmartDashboard::PutNumber("RightPower", DataR);
			//SmartDashboard::PutString("Code 1", &a1);
			//SmartDashboard::PutString("Code 2", &a2);
			//SmartDashboard::PutNumber("Distance", info_data1); //Measured by the ultrasound
			//SmartDashboard::PutNumber("Target RPMs", info_data2); //RPMs calculated by the arduino function
		}
		if(start_shooting){ //(a1 == 'I' && a2 == 'N' && start_shooting){
			if(DEBUG){
				SmartDashboard::PutNumber("ShooterPower", DataS);
				//SmartDashboard::PutString("Code 1", &a1);
				//SmartDashboard::PutString("Code 2", &a2);
			}
			//shooter::indexer_run();
			//shooter::agitator_run();
			start_shooting = false;
		}
		Wait(.001); // Delays the cycle for 1 ms
	}
	//shooter::indexer_stop();
	//shooter::agitator_stop();
	arduino_i2c::Send('S','T','0','0','0','0');
	gear::close();
}

void autonomous::auto51(RobotBase *rb){
	static char a1,a2;
	float DataS, DataR, DataL;
	static int info_data1, info_data2;
	bool start_shooting = true;
	static union {
		float Float;
		uint8_t Byte[4];
	}Transmit_data;
	//Transmit_data.Float = SmartDashboard::GetNumber("Desired RPMs",0);
	//arduino_i2c::Send('T','S',Transmit_data.Byte[0], Transmit_data.Byte[1], Transmit_data.Byte[2], Transmit_data.Byte[3]); // Send auto mode and desired RPMs for tuning
	//Wait(.0001);
	arduino_i2c::Send('T','S',Transmit_data.Byte[0], Transmit_data.Byte[1], Transmit_data.Byte[2], Transmit_data.Byte[3]);
	while (rb->IsEnabled() && rb->IsAutonomous()) {
		arduino_i2c::ReadI2C(&a1, &a2, &DataS, &DataR, &DataL, &info_data1, &info_data2); // Get Power values
		//shooter::run(-DataS);
		if(DEBUG){
			SmartDashboard::PutString("Auto Debug", "I am in A50 Function");
			SmartDashboard::PutNumber("ShooterPower", DataS);
			SmartDashboard::PutNumber("LeftPower", DataL);
			SmartDashboard::PutNumber("RightPower", DataR);
			SmartDashboard::PutString("Code 1", &a1);
			SmartDashboard::PutNumber("Distance", info_data1); //Measured by the ultrasound
			SmartDashboard::PutNumber("Target RPMs", info_data2); //RPMs calculated by the arduino function
		}
		if(a1 == 'I' && a2 == 'N' && start_shooting){
			if(DEBUG){
				SmartDashboard::PutString("Auto Debug", "I am in A50 Indexer");
				SmartDashboard::PutNumber("ShooterPower", DataS);
				SmartDashboard::PutNumber("LeftPower", DataL);
				SmartDashboard::PutNumber("RightPower", DataR);
				SmartDashboard::PutString("Code 1", &a1);
				//SmartDashboard::PutString("Code 2", &a2);
			}
			//shooter::indexer_run();
			//shooter::agitator_run();
			start_shooting = false;
		}
		Wait(.001); // Delays the cycle for 1 ms
	}
	//shooter::indexer_stop();
	//shooter::agitator_stop();
	arduino_i2c::Send('S','T','0','0','0','0');
}

void autonomous::auto10(RobotBase *rb) {
	arduino_i2c::Send_ST_Arduino();
	//gear::close();
	DriveStraight(rb, 'A','A'); //rb is robot base, '1' is the AA command for the arduino
	Wait(WAIT_OPEN_GEAR);
	gear::open();
	Wait(WAIT_DROPOFF_GEAR);
	DriveBack();
}

void autonomous::auto2(RobotBase *rb) { // Left Side auto. Go straight, turn right, go straight, release gear, drive back
	arduino_i2c::Send_ST_Arduino();
	gear::close();
	DriveStraight(rb, 'A','2');
	drivetrain::retract_versa();
	autonomous::Rotate(rb, 'A','3');
	DriveStraight(rb, 'A','4');
	gear::open();
	Wait(WAIT_DROPOFF_GEAR);
	DriveBack();
}

void autonomous::auto8(RobotBase *rb) { // Go straight only on middle gear peg release and drive back
	arduino_i2c::Send_ST_Arduino();
	gear::close();
	DriveStraight(rb, 'A','8');
	gear::open();
	Wait(WAIT_DROPOFF_GEAR);
	drivetrain::retract_versa();
	DriveBack();
}

void autonomous::DriveStraight(RobotBase *rb, char mode1, char mode2){
	static char a1;
	static char a2;
	static float DataS, DataR, DataL;
	static int info_data1, info_data2;

	while((a1 != 'O' || a2 != 'O') && rb->IsEnabled() && rb->IsAutonomous())
			arduino_i2c::ReadI2C(&a1, &a2, &DataS, &DataR, &DataL, &info_data1, &info_data2); // Wait until we get OO
	arduino_i2c::Send(mode1, mode2,'0','0', '0', '0'); // Send A 'mode'
	//std::cout << mode1, mode2 << std::endl;
	while (rb->IsEnabled() && rb->IsAutonomous()) {
			arduino_i2c::ReadI2C(&a1, &a2, &DataS, &DataR, &DataL, &info_data1, &info_data2); // Get Drivetrain Power values
			Wait(.005);
			if(DEBUG){
				SmartDashboard::PutString("Auto Debug", "I am DriveStraight");
				SmartDashboard::PutNumber("LeftPower", DataL);
				SmartDashboard::PutNumber("RightPower", DataR);
				SmartDashboard::PutString("Code 1", &a1);
				SmartDashboard::PutString("Code 2", &a2);
				SmartDashboard::PutNumber("Info Data 1", info_data1);
				SmartDashboard::PutNumber("Info Data 2", info_data2);
			}
			if (a1 == 'T' && a2 == 'R'){ // If reached target
				drivetrain::drive_auto(0.0, 0.0);
				//drivetrain::drive_lr(0.0, 0.0, -1); // Apply a slight negative value to stop the robot
				arduino_i2c::Send_ST_Arduino(); // Send ST
				//Wait(.02);
				break;
			}
			if (a1 == 'E' && a2 == 'N') { // If received encoder values
				drivetrain::drive_auto((double) DataL,(double) DataR);
				//drivetrain::drive_lr((double) DataL,(double) DataR, -1.0); // Drive with raw values
			} else {
				drivetrain::drive_auto(0.0, 0.0);
				//drivetrain::drive_lr(0, 0, -1); // Don't do anything
			}
	}
	drivetrain::drive_auto(0.0, 0.0);
	//drivetrain::drive_lr(0.0, 0.0, -1); //Stop moving
}

void autonomous::Rotate(RobotBase *rb, char mode1, char mode2) {
	static char a1, a2;
	static float DataS, DataR, DataL;
	static int info_data1, info_data2;
	arduino_i2c::Send_ST_Arduino();
	drivetrain::drop_versa();
	while ((a1 != 'O' || a2 != 'O') && rb->IsEnabled() && rb->IsAutonomous())
				arduino_i2c::ReadI2C(&a1, & a2, &DataS, &DataR, &DataL, &info_data1, &info_data2); // Wait until we get OO

	arduino_i2c::Send(mode1, mode2, '0','0','0','0');
	while (rb->IsEnabled() && rb->IsAutonomous()) {
		arduino_i2c::ReadI2C(&a1, & a2, &DataS, &DataR, &DataL, &info_data1, &info_data2); // Get Drivetrain Power values
		Wait(.001);
		SmartDashboard::PutNumber("LeftPower", DataL);
		SmartDashboard::PutNumber("RightPower", DataR);
		SmartDashboard::PutString("Code 1", &a1);
		if (a1 == 'R' && a2 == 'R')
			break;
		if (a1 == 'G' && a2 == 'Y') {
			drivetrain::drive_lr(DataL, DataR, -1.0);
		} else {
			drivetrain::drive_lr(0.0, 0.0, -1);
		}
	}
	arduino_i2c::Send_ST_Arduino();
	drivetrain::drive_lr(0.0, 0.0, -1.0);
}

void autonomous::DriveBack(){
	drivetrain::drive_lr(0.25, 0.25, -1);
	Wait(0.3);
	drivetrain::drive_lr(0.40, 0.40, -1);
	Wait(0.2);
	drivetrain::drive_lr(0.60, 0.60, -1);
	Wait(0.2);
	drivetrain::drive_lr(0.75, 0.75, -1);
	Wait(0.2);
	drivetrain::drive_lr(0, 0, -1);
}

void autonomous::DriveBack2(){
	drivetrain::drive_lr(0.2, 0.2, -1);
	Wait(0.4);
	drivetrain::drive_lr(0.35, 0.35, -1);
	Wait(0.2);
	drivetrain::drive_lr(0.45, 0.45, -1);
	Wait(0.5);
	drivetrain::drive_lr(0, 0, -1);
}

void autonomous::auto50(RobotBase *rb){
	static char a1,a2;
	float DataS, DataR, DataL;
	static int info_data1, info_data2;
	bool start_shooting = true;
	static union {
		float Float;
		uint8_t Byte[4];
	}Transmit_data;
	Transmit_data.Float = SmartDashboard::GetNumber("Desired RPMs",0);
	arduino_i2c::Send('T','S',Transmit_data.Byte[0], Transmit_data.Byte[1], Transmit_data.Byte[2], Transmit_data.Byte[3]); // Send auto mode and desired RPMs for tuning
	Wait(.0001);
	while (rb->IsEnabled() && rb->IsAutonomous()) {
		arduino_i2c::ReadI2C(&a1, &a2, &DataS, &DataR, &DataL, &info_data1, &info_data2); // Get Power values
		//shooter::run(-DataS);
		if(DEBUG){
			SmartDashboard::PutString("Auto Debug", "I am in A50 Function");
			SmartDashboard::PutNumber("ShooterPower", DataS);
			SmartDashboard::PutNumber("LeftPower", DataL);
			SmartDashboard::PutNumber("RightPower", DataR);
			SmartDashboard::PutString("Code 1", &a1);
			SmartDashboard::PutNumber("Distance", info_data1); //Measured by the ultrasound
			SmartDashboard::PutNumber("Target RPMs", info_data2); //RPMs calculated by the arduino function
		}
		if(a1 == 'I' && a2 == 'N' && start_shooting){
			if(DEBUG){
				SmartDashboard::PutString("Auto Debug", "I am in A50 Indexer");
				SmartDashboard::PutNumber("ShooterPower", DataS);
				SmartDashboard::PutNumber("LeftPower", DataL);
				SmartDashboard::PutNumber("RightPower", DataR);
				SmartDashboard::PutString("Code 1", &a1);
				//SmartDashboard::PutString("Code 2", &a2);
			}
			//shooter::indexer_run();
			//shooter::agitator_run();
			start_shooting = false;
		}
		Wait(.001); // Delays the cycle for 1 ms
	}
	//shooter::indexer_stop();
	//shooter::agitator_stop();
	arduino_i2c::Send('S','T','0','0','0','0');
}
