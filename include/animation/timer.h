#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	void restart()
	{
		pass_time = 0;
		shotted = false;
	}

	void set_wait_time(double val){ wait_time = val; }

	void set_one_shot(bool flag){ one_shot = false; }

	void set_on_timeout(std::function<void()> on_timeout){ this->on_timeout = on_timeout; }

	void pause(){ paused = true; }

	void resume(){ paused = false; }

	void on_update(double delay)
	{
		if (paused) return;

		pass_time += delay;
		if (pass_time >= wait_time)
		{
			bool can_shot = (!one_shot || (one_shot && !shotted));
			shotted = true;
			if (can_shot && on_timeout)
				on_timeout();

			pass_time -= wait_time;
		}
	}

private:
	double pass_time = 0;
	double wait_time = 0;
	bool paused = false;
	bool shotted = false;	// event trigger flag
	bool one_shot = false;	// true meas only trig once
	std::function<void()> on_timeout;	// timeout callback function

};

#endif // !_TIMER_H_
