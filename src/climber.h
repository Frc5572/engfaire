/*
 * climber.h
 *
 *  Created on: Feb 8, 2017
 *      Author: rosbots
 */

#ifndef SRC_CLIMBER_H_
#define SRC_CLIMBER_H_

namespace climber {
	void init();
	void prime(); //Pushes the piston out
	void piston_stop(); //Seitches the solenoid off
	void piston_reset(); //Pushes the piston back
	void climb(double a); // This is the climber motor
}

#endif /* SRC_CLIMBER_H_ */
