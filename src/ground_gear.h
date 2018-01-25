
#ifndef GROUND_GEAR_H_
#define GROUND_GEAR_H_

namespace ground_gear {
	void init();
	void update();
	void up();
	void down();
	void roll(bool);
	void stop();
	void rollpower(double m);
}

#endif
