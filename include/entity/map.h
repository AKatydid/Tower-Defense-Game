#ifndef _MAP_H_
#define _MAP_H_

#include "entity/tile.h"

#include <SDL2/SDL.h>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

class Map
{
public:
	Map() = default;
	~Map() = default;

	// load map data
	bool load(const std::string& path);

private:
	// string trim utils
	std::string trim_str(const std::string& str);

	void load_tile_from_string(Tile& tile, const std::string& str);

	void generate_map_cache();

	size_t Map::get_width() const;
	size_t Map::get_height() const;

private:
	TileMap m_tile_map;
	SDL_Point m_ind_home = { 0, 0 };

};

#endif // !_MAP_H_
