#include "entity/route.h"

Route::Route(const TileMap& map, const SDL_Point& idn_origin) {
	size_t width_map = map[0].size();
	size_t height_map = map.size();
	SDL_Point idn_next = idn_origin;

	while (true)
	{
		if (idn_next.x >= width_map || idn_next.y >= height_map)
			break;

		if (check_duplicate_idx(idn_next))
			break;
		else
			idn_list.push_back(idn_next);

		bool is_next_dir_exist = true;
		const Tile& tile = map[idn_next.y][idn_next.x];

		if (tile.special_flag == 0)
			break;
		switch (tile.direction)
		{
		case Tile::Direction::Up:
			idn_next.y--;
			break;
		case Tile::Direction::Down:
			idn_next.y++;
			break;
		case Tile::Direction::Left:
			idn_next.x--;
			break;
		case Tile::Direction::Right:
			idn_next.x++;
			break;
		default:
			is_next_dir_exist = false;
			break;
		}

		if (!is_next_dir_exist)
			break;
	}
}

const std::vector<SDL_Point>& Route::get_idx_list() const
{
	return idn_list;
}


bool Route::check_duplicate_idx(const SDL_Point& target_idn)
{
	for (const SDL_Point& idx : idn_list)
	{
		if (idx.x == target_idn.x && idx.y == target_idn.y)
			return true;
	}

	return false;
}
