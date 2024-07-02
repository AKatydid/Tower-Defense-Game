#include "entity/map.h"

bool Map::load(const std::string& path) 
{
	std::ifstream file(path);

	if (!file.good()) return false;

	int ind_x = -1, ind_y = -1;
	std::string str_line;
	while (std::getline(file, str_line)) 
	{
		str_line = trim_str(str_line);
		if (str_line.empty())
			continue;
		ind_x = -1, ind_y++;
		m_tile_map.emplace_back();	// add a new line for tile_map matrix

		std::string str_tile;
		std::stringstream str_stream(str_line);
		while (std::getline(str_stream, str_tile, ','))
		{
			ind_x++;
			m_tile_map[ind_y].emplace_back();
			Tile& tile = m_tile_map[ind_y].back();	// get the last one tile data
			load_tile_from_string(tile, str_tile);
		}
	}
	generate_map_cache();
	return true;
}

std::string Map::trim_str(const std::string& str)
{
	size_t begin_idx = str.find_first_not_of(" \t");
	if (begin_idx == std::string::npos)
		return "";
	size_t end_idx = str.find_last_not_of(" \t");
	size_t idx_range = end_idx - begin_idx + 1;

	return str.substr(begin_idx, idx_range);
}


void Map::load_tile_from_string(Tile& tile, const std::string& str) 
{
	std::string str_value;
	std::vector<int> values;
	std::stringstream str_stream(trim_str(str));

	while (std::getline(str_stream, str_value, '\\'))
	{
		int value;
		try
		{
			value = std::stoi(str_value);
		}
		catch (const std::invalid_argument&)
		{
			value = -1;
		}
		values.push_back(value);
	}

	// correctness check
	tile.terrian = (values.size() < 1 || values[0] < 0) ? 0 : values[0];
	tile.decoration = (values.size() < 2) ? -1 : values[1];
	tile.direction = (Tile::Direction)((values.size() < 3 || values[2] < 0) ? 0 : values[2]);
	tile.special_flag = (values.size() <= 3) ? -1 : values[3];
}

void Map::generate_map_cache() 
{
	for (int y = 0; y < get_height(); y++)
	{
		for (int x = 0; x < get_width(); x++)
		{
			const Tile& tile = m_tile_map[y][x];
			if (tile.special_flag < 0)
				continue;

			// House
			if (tile.special_flag == 0)
			{
				m_ind_home.x = x;
				m_ind_home.y = y;
			}
			// save the path of Monster_Brush_Point to House
			else 
			{
				m_spwaner_route_pool[tile.special_flag] = Route(m_tile_map, { x, y });
			}
		}
	}
}

size_t Map::get_width() const
{
	return m_tile_map.empty() ? 0 : m_tile_map[0].size();
}

size_t Map::get_height() const
{
	return m_tile_map.size();
}

const SDL_Point& Map::get_idx_home() const
{
	return m_ind_home;
}

const TileMap& Map::get_tile_map() const
{
	return m_tile_map;
}

const SpawnerRoutePool& Map::get_idx_spawner_pool() const 
{
	return m_spwaner_route_pool;
}

void Map::place_tower(const SDL_Point& idx_tile)
{
	m_tile_map[idx_tile.y][idx_tile.x].has_tower = true;
}