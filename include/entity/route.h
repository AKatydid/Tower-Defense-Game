#ifndef _ROUTE_H_
#define _ROUTE_H_

#include "tile.h"

#include <SDL2/SDL.h>
#include <vector>
#include <unordered_map>

class Route
{
public:
	Route() = default;
	~Route() = default;

	// Init one path according to TileMap
	Route(const TileMap& map, const SDL_Point& idx_origin);

	const std::vector<SDL_Point>& get_idx_list() const;

private:
	// Save all nodes of one path of one monster
	std::vector<SDL_Point> idn_list;

private:
	bool check_duplicate_idx(const SDL_Point& target_idx);
};

// Indicate that monsters' route
typedef std::unordered_map<int, Route> SpawnerRoutePool;

#endif // !_ROUTE_H_
