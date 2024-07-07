#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

#include "manager/manager.h"
#include "manager/home_manager.h"

#include "entity/enemy/enemy.h"
#include "entity/enemy/enemy_type.h"
#include "entity/enemy/enemy_goblin.h"
#include "entity/enemy/enemy_goblin_priest.h"
#include "entity/enemy/enemy_skeleton.h"
#include "entity/enemy/enemy_slim.h"
#include "entity/enemy/enemy_slim_king.h"

#include <vector>
#include <SDL2/SDL.h>

class EnemyManager : public Manager<EnemyManager>
{
	friend class Manager<EnemyManager>;
public:
	typedef std::vector<Enemy*> EnemyList;

public:
	void on_update(double delay);

	void on_render(SDL_Renderer* renderer);

	/* spawn an enemy in a point */
	void spawn_enemy(EnemyType type, int idx_spawn_point);

	bool check_cleared();

	EnemyManager::EnemyList& get_enemy_list();

protected:
	EnemyManager() = default;

	~EnemyManager();

private:
	EnemyList enemy_list;

private:
	/* enemy destroy home */
	void process_home_collision();

	void process_bullet_collision();

	/* remove dead enemy from list */
	void remove_invalid_enemy();

};

#endif // !_ENEMY_MANAGER_H_
