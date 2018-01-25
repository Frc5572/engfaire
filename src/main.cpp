#include <WPILib.h>
#include "drivetrain.h"
#include "autonomous.h"
#include "arduino_i2c.h"
#include "shooter.h"
#include "climber.h"
#include "gear.h"
#include <string>
#include "controller.h"
#include <iostream>
#include "ports.h"
#include "intake.h"
#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <time.h>
#include <chrono>
#include <Timer.h>
#include "ground_gear.h"

using namespace std;

void start_manual() {
}

class Robot: public SampleRobot {
	FRC5572Controller driver;
	frc::Timer timer;
public:
	//class RobotDrive *myDrive;
	//class Victor *frontLeft, *middleLeft, *frontRight, *rearLeft, *middleRight, *rearRight;
	Robot() :
			driver(2) {

		drivetrain::setMotors<DRIVETRAIN_MOTOR_TYPE>( {DRIVETRAIN_MOTOR_LEFT_ID}, {DRIVETRAIN_MOTOR_RIGHT_ID}); //drive motor initialization

	}
	void RobotInit() {
		arduino_i2c::init();
		drivetrain::init(); //Drivetrain initialization
		intake::init();//Ball Intake initialization
		gear::init();//Gear initialization
		gear::stop();
		//shooter::init();//Shooter initialization
		climber::init();
		climber::piston_stop();
		gear::close();
		ground_gear::init();
		arduino_i2c::Send('S','T','O','P', '0','0');
		timer.Reset();
		timer.Start();

		SmartDashboard::PutNumber("Auto", 0);
		SmartDashboard::PutNumber("x",88);
		SmartDashboard::PutNumber("x2",84);
		SmartDashboard::PutNumber("Distance", 0.0);

		if(DEBUG) {
			SmartDashboard::PutString("OP B ","");
			SmartDashboard::PutNumber("Time Now", 0.0);
			SmartDashboard::PutString("Shooter Init ","");
			SmartDashboard::PutString("Code 1", "");
			SmartDashboard::PutString("Code 2", "");
			SmartDashboard::PutString("Auto Debug", "");
			SmartDashboard::PutString("I2C Init ","");
			SmartDashboard::PutNumber("Distance", 0.0);
			SmartDashboard::PutNumber("Target RPMs", 0.0);
			SmartDashboard::PutNumber("Actual RPMs",0.0);
			SmartDashboard::PutNumber("Desired RPMs",0);
			SmartDashboard::PutNumber("Start Time",0.0);
			SmartDashboard::PutNumber("Info Data 1",0.0);
			SmartDashboard::PutNumber("Info Data 2",0.0);
		}

	}

	void OperatorControl() override {
		arduino_i2c::clear_i2c();
		arduino_i2c::init();
		bool climber_piston = true;
		bool key_b = false;
		bool agitator_on = false;
		bool is_gear_open = false;
		bool start_shooting = true;
		bool rolleron = false;
		timer.Reset();
		double start_time = timer.Get(); //Time in ms
		double stop_time = timer.Get();

		//bool is_indexer = false; //Indexer is not started until message says IN

		static char a1;
		static char a2;
		static int info_data1, info_data2;
		static float DataS, DataR, DataL;

		if(DEBUG) {
			SmartDashboard::PutString("OP B ","");
			SmartDashboard::PutNumber("Time Now", 0.0);
			SmartDashboard::PutString("Shooter Init ","");
			SmartDashboard::PutString("Code 1", "");
			SmartDashboard::PutString("Code 2", "");
			SmartDashboard::PutString("Auto Debug", "");
			SmartDashboard::PutString("I2C Init ","");
			SmartDashboard::PutNumber("Distance", 0.0);
			SmartDashboard::PutNumber("Target RPMs", 0.0);
			SmartDashboard::PutNumber("Actual RPMs",0.0);
			SmartDashboard::PutNumber("Desired RPMs",0);
			SmartDashboard::PutNumber("Start Time",0.0);
		}

		drivetrain::drop_versa();
		arduino_i2c::Send_ST_Arduino();

		while (IsOperatorControl() && IsEnabled()) {
			drivetrain::drive_lr(-driver.L().second, -driver.R().second, .75 + (driver.LT() * .25));
			ground_gear::update();
			if(driver.A()) {
				ground_gear::down();
				arduino_i2c::Send_SH_Arduino();
			} else if(driver.Y()) {
				ground_gear::up();
				arduino_i2c::Send_ST_Arduino();
			}

			ground_gear::roll(driver.X()); //original code

			if (driver.LB()) {
				gear::open();
				is_gear_open = true;
			} else if(is_gear_open && driver.LT()) {
				gear::close();
				is_gear_open = false;
			};

			/*
			// B Button operator controller used to shoot
			if(operat.B()) { // If b is pressed on operator controller shooting routine starts
				arduino_i2c::Send_SH_Arduino();
				Wait(0.050);
				start_shooting = true;
				while (IsEnabled() && IsOperatorControl() && operat.B()) {
					drivetrain::drive_lr(-driver.L().second, -driver.R().second, .75 + (driver.LT() * .25));
					key_b = true;
					if(start_shooting) {
						arduino_i2c::ReadI2C(&a1, &a2, &DataS, &DataR, &DataL, &info_data1, &info_data2); // Get data from Arduino
						//shooter::run(-DataS);
						SmartDashboard::PutNumber("Distance", info_data1);//Measured by the ultrasound
						Wait(0.050);
					}

					if(DEBUG) {
						SmartDashboard::PutString("Auto Debug", "I am in Shooting");
						SmartDashboard::PutNumber("ShooterPower", DataS);
						SmartDashboard::PutNumber("LeftPower", DataL);
						SmartDashboard::PutNumber("RightPower", DataR);
						SmartDashboard::PutString("Code 1", &a1);
						SmartDashboard::PutString("Code 2", &a2);
						SmartDashboard::PutNumber("Distance", info_data1); //Measured by the ultrasound
						SmartDashboard::PutNumber("Target RPMs", info_data2);//RPMs calculated by the arduino function
						SmartDashboard::PutNumber("Time Now", timer.Get());
					}
					if(a1 == 'I' && a2 == 'N' && start_shooting) {
						if(DEBUG) {
							SmartDashboard::PutString("Auto Debug", "I am in Shooting Indexer");
							SmartDashboard::PutString("Code 1", &a1);
							SmartDashboard::PutString("Code 2", &a2);
							SmartDashboard::PutNumber("Start Time", start_time);
						}
						//shooter::indexer_run();
						//shooter::agitator_run();
						start_time = timer.Get();
						agitator_on = true;
						start_shooting = false;
					}
					if(!start_shooting && agitator_on && timer.Get() > start_time + 1) {
						//shooter::agitator_stop();
						stop_time = timer.Get();
						agitator_on = false;
					}
					if(!start_shooting && !agitator_on && timer.Get() > stop_time + 0.500) {
						//shooter::agitator_run();
						start_time = timer.Get();
						agitator_on = true;
					}
					//Wait(.050); // Delays the cycle for 5 ms
				}
				arduino_i2c::Send('S','T','0','0','0','0');
			} else if(!operat.B() && key_b) {
				////shooter::stop();
				////shooter::indexer_stop();
				////shooter::agitator_stop();
				SmartDashboard::PutString("Auto Debug", "");
				key_b = false;
				agitator_on = false;
				arduino_i2c::Send_ST_Arduino();
			};
			*/

			//A Button on Driver Controller Retracts Versa
			if(driver.RB())
			drivetrain::retract_versa();
			else if(driver.B())//B Button on Driver Controller drops Versa
			drivetrain::drop_versa();

			// ************ Climber Sequence*************/
			if(driver.RT() && climber_piston) {
				climber::climb(1.0);
				Wait(.3);  //Time needs to probably increase for comp bot
				if(climber_piston) {
					climber::prime();
					climber_piston = false;
				}
			} else if (driver.RT()) {
				//climber::climb(1.0);
				;
			} else if(!driver.RT() && !climber_piston) {
				climber::piston_reset();
				climber_piston = true;
				climber::climb(0.0);
			}
			Wait(0.005); // Waits for motors response
		}

	}
	void Autonomous() override {

		arduino_i2c::Send_ST_Arduino();

		//drivetrain::retract_versa();
		gear::close();

		int m = (int)SmartDashboard::GetNumber("Auto",0);
		Wait(.4);
		switch(m) {
			case 1: //.. Auto 1 delivers gear on central peg of read side
			autonomous::auto1(this);
			break;
			case 2://.. Auto 2
			autonomous::auto2(this);
			break;
			case 3://.. Auto 3
			//drivetrain::retract_versa();
			autonomous::auto3(this);
			break;
			case 4://.. Auto 4 This is to deliver left side gear and shoot 10 balls
			autonomous::auto4(this);
			break;
			case 5://.. Auto 5
			autonomous::auto5(this);// Right side blue delivers gear and then loads balls
			break;
			case 6://.. Auto 6
			autonomous::auto6(this);// Left side delivers gear and shoots
			break;
			case 7:
			// Do not use
			break;
			case 8:
			// Do not use
			break;
			case 9://.. Auto 8 delivers gear on central peg of blue side
			autonomous::auto8(this);
			break;
			case 10://.. Auto 8 delivers gear on central peg of blue side
			autonomous::auto10(this);
			break;
			case 50://.. Auto 50 is used for testing to tune the shooter PID
			autonomous::auto50(this);
			break;
		}
		arduino_i2c::Send_ST_Arduino();
		drivetrain::drive_lr(0, 0, -1);
		//shooter::stop();
		drivetrain::drop_versa();
		gear::close();
	}

	void Test() override {

	}

	void Disabled() override {
		arduino_i2c::Send('S','T','O','P','0','0');
		drivetrain::drive_lr(0, 0, -1);
		//shooter::stop();
	}

};

START_ROBOT_CLASS(Robot)
