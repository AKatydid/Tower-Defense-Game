#include "manager/enemy_manager.h"

EnemyManager::~EnemyManager()
{
	for (Enemy* enemy : enemy_list)
		delete enemy;
}

// ====================
//       public
// ====================

void EnemyManager::on_update(double delay)
{
	for (Enemy* enemy : enemy_list)
		enemy->on_update(delay);

	process_home_collision();
	process_bullet_collision();

	remove_invalid_enemy();
}

void EnemyManager::on_render(SDL_Renderer* renderer)
{

}

void EnemyManager::spawn_enemy(EnemyType type, int idx_spawn_point)
{
	static Vector2 position;
	static const SDL_Rect& rect_tile_map = ConfigManager::instance()->rect_tile_map;
	static const SpawnerRoutePool& spawner_route_pool
		= ConfigManager::instance()->map.get_idx_spawner_pool();

	const auto& itor = spawner_route_pool.find(idx_spawn_point);
	if (itor == spawner_route_pool.end())
		return;

	Enemy* enemy = nullptr;

	switch (type)
	{
	case EnemyType::Slim:
		enemy = new SlimEnemy();
		break;
	case EnemyType::KingSlim:
		enemy = new KingSlimeEnemy();
		break;
	case EnemyType::Skeleton:
		enemy = new SkeletonEnemy();
		break;
	case EnemyType::Goblin:
		enemy = new GoblinEnemy();
		break;
	case EnemyType::GoblinPriest:
		enemy = new GoblinPriestEnemy();
		break;
	default:
		enemy = new SlimEnemy();
		break;
	}

	enemy->set_on_skill_released(
		[&](Enemy* enemy_src)
		{
			double recover_raduis = enemy_src->get_recover_radius();
			if (recover_raduis < 0) return;

			const Vector2 pos_src = enemy_src->get_position();
			for (Enemy* enemy_dst : enemy_list)
			{
				const Vector2& pos_dst = enemy_dst->get_position();
				double distance = (pos_dst - pos_src).length();
				if (distance <= recover_raduis)
					enemy_dst->increase_hp(enemy_src->get_recover_intensity());
			}
		});

	const std::vector<SDL_Point>& idx_list = itor->second.get_idx_list();
	position.x = rect_tile_map.x + idx_list[0].x * SIZE_TILE + SIZE_TILE / 2;
	position.y = rect_tile_map.y + idx_list[0].y * SIZE_TILE + SIZE_TILE / 2;

	enemy->set_position(position);
	enemy->set_route(&itor->second);

	enemy_list.push_back(enemy);
}

bool EnemyManager::check_cleared()
{
	return false;
}

EnemyManager::EnemyList& EnemyManager::get_enemy_list()
{
	return enemy_list;
}

// ====================
//       private
// ====================
void EnemyManager::process_home_collision()
{
	static const SDL_Point& idx_home = ConfigManager::instance()->map.get_idx_home();
	static const SDL_Rect& rect_tile_map = ConfigManager::instance()->rect_tile_map;
	static const Vector2 position_home_tile =
	{
		(double)rect_tile_map.x + idx_home.x * SIZE_TILE,
		(double)rect_tile_map.y + idx_home.y * SIZE_TILE
	};

	for (Enemy* enemy : enemy_list)
	{
		if (enemy->can_remove()) continue;

		const Vector2& position = enemy->get_position();

		if (position.x >= position_home_tile.x
			&& position.y >= position_home_tile.y
			&& position.x <= position_home_tile.x + SIZE_TILE
			&& position.y <= position_home_tile.y + SIZE_TILE)
		{
			enemy->make_invalid();

			HomeManager::instance()->decrease_hp(enemy->get_damage());
		}
	}
}

void EnemyManager::process_bullet_collision()
{

}

void EnemyManager::remove_invalid_enemy()
{
	enemy_list.erase(
		std::remove_if(enemy_list.begin(), enemy_list.end(), [](const Enemy *enemy){
			bool need_del = enemy->can_remove();
			if (need_del) delete enemy;
			return need_del;
		})
		,enemy_list.end()
	);
}