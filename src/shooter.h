/*
 * shooter.h
 *
 *  Created on: Feb 8, 2017
 *      Author: rosbots
 */

#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_
#include <RobotBase.h>

namespace shooter{
	void init();
	void shoot(bool *is_indexer, double timenow);
	void stop();
	void force_stop();
	void run(float power);
	void agitator_run();
	void agitator_stop();
	void indexer_run();
	void indexer_stop();
}

#define INDEXER_POWER 	0.4 //Indexer power set to 40%
#define SHOOTER_INIT_POWER1 -.68
#define SHOOTER_INIT_POWER2 -.8

#endif /* SRC_SHOOTER_H_ */
