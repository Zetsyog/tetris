#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

#define FRAME_VALUES 10

class FPSCounter {
  public:
	FPSCounter(float interval);
	void update();
    int getAverage();

  private:
	float interval;
	int frames;
	int last_time;
	int current;
};

#endif
