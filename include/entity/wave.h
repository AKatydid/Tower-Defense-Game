#ifndef _WAVE_H_
#define _WAVE_H_

#include "entity/enemy/enemy_type.h"
#include <vector>

struct Wave
{
	struct SpawnEvent
	{
		double interval = 0;	// event interval
		int spawn_point = 1;	// Brush Point
		EnemyType enemy_type = EnemyType::Slim;
	};

	double rawards = 0;	
	double interval = 0;
	std::vector<SpawnEvent> spawn_event_list;
};

#endif // !_WAVE_H_
