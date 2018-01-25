#ifndef SRC_AUTONOMOUS_H_
#define SRC_AUTONOMOUS_H_

#include <RobotBase.h>

namespace autonomous {
	void auto1(RobotBase *rb); // Move forward
	void auto2(RobotBase *rb); // Turn
	void auto3(RobotBase *rb); // Delivers the gear on central peg and shoots
	void auto4(RobotBase *rb); // Delivers the gear on left peg and shoots
	void auto5(RobotBase *rb); // Delivers the gear on right side
	void auto6(RobotBase *rb); // Left side delivers gear and shoots
	void auto7(RobotBase *rb); // Moves forward only 110 inches
	void auto8(RobotBase *rb); // Move Forward
	void auto10(RobotBase *rb); //Left side delivery and shooting
	void auto50(RobotBase *rb); //This is used only for shooter testing to tune the PID
	void auto51(RobotBase *rb); //This is used only for shooter testing to tune the PID
	void DriveStraight(RobotBase *rb, char mode1, char mode2); //Move on a straight line
	void Rotate(RobotBase *rb, char mode1, char mode2); //Rotate the robot
	void DriveBack(); // Move robot back after releasing the gear
	void DriveBack2(); // Move robot back after releasing the gear in drive and shoot
}

#endif /* SRC_AUTONOMOUS_H_*/
