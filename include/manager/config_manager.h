#ifndef _CONFIG_MANAGER_H_
#define _CONFIG_MANAGER_H_

#include "entity/map.h"
#include "entity/wave.h"
#include "manager/manager.h"
#include "utils/config.h"

#include <SDL2/SDL.h>
#include <cJSON.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ConfigManager : public Manager<ConfigManager>
{
	friend class Manager<ConfigManager>;

public:
	struct BasicTemplate
	{
		std::string window_title = WINDOW_NAME;
		int window_width = WIDTH;
		int window_height = HEIGHT;
	};

	struct PlayerTemplate
	{
		double speed = 3;
		double normal_attack_interval = 0.5;
		double normal_attack_damage = 0;
		double skill_interval = 10;
		double skill_damage = 1;
	};

	struct TowerTemplate
	{
		double interval[10] = { 1 };
		double damage[10] = { 25 };
		double view_range[10] = { 5 };
		double cost[10] = { 50 };
		double upgrade_cost[9] = { 75 };
	};

	struct EnemyTemplate
	{
		double hp = 100;
		double speed = 1;
		double damage = 1;
		double reward_ratio = 0.5;
		double recover_interval = 10;
		double recover_range = 0;
		double recover_intensity = 25;
	};

public:
	Map map;
	std::vector<Wave> wave_list;

	int level_archer = 0;
	int level_axeman = 0;
	int level_gunner = 0;

	bool is_game_win = true;
	bool is_game_over = false;
	SDL_Rect rect_tile_map = { 0 };			// texture render rect

	BasicTemplate basic_template;

	PlayerTemplate player_template;

	TowerTemplate archer_template;
	TowerTemplate axeman_template;
	TowerTemplate gunner_template;

	EnemyTemplate slim_template;
	EnemyTemplate king_slim_template;
	EnemyTemplate skeleton_template;
	EnemyTemplate goblin_template;
	EnemyTemplate goblin_priest_template;

	const double num_initial_hp = 10;		// initial House HP
	const double num_initial_coin = 100;	// initial coin
	const double num_coin_per_prop = 10;	

public:
	// load level data from config file
	bool load_level_config(const std::string& path);

	// load game data from config file
	bool load_game_config(const std::string& path);

protected:
	ConfigManager() = default;
	~ConfigManager() = default;

private:
	void parse_basic_template(BasicTemplate& tpl, cJSON* json_root);

	void parse_player_template(PlayerTemplate& tpl, cJSON* json_root);

	void parse_number_array(double* ary, int max_len, cJSON* json_root);

	void parse_tower_template(TowerTemplate& tpl, cJSON* json_root);

	void parse_enemy_template(EnemyTemplate& tpl, cJSON* json_root);

};

#endif // !_CONFIG_MANAGER_H_
