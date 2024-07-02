#ifndef _MAP_H_
#define _MAP_H_

#include "entity/tile.h"
#include "entity/route.h"

#include <SDL2/SDL.h>

#include <string>
#include <fstream>
#include <sstream>


class Map
{
public:
	Map() = default;
	~Map() = default;

	// load map data
	bool load(const std::string& path);

	size_t Map::get_width() const;
	size_t Map::get_height() const;
	const TileMap& get_tile_map() const;
	const SpawnerRoutePool& get_idx_spawner_pool() const;
	void place_tower(const SDL_Point& idn_tile);

private:
	TileMap m_tile_map;
	SDL_Point m_ind_home = { 0, 0 };
	SpawnerRoutePool m_spwaner_route_pool;

private:
	// string trim utils
	std::string trim_str(const std::string& str);

	// load tile data
	void load_tile_from_string(Tile& tile, const std::string& str);

	// cache home pos and ...
	void generate_map_cache();
};

#endif // !_MAP_H_
