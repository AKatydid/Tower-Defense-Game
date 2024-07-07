#ifndef _TILE_H_
#define _TILE_H_

#include <vector>

struct Tile
{
	enum class Direction
	{
		None = 0,
		Up,
		Down,
		Left,
		Right
	};

	int terrian = 0;		// terrian texture index
	int decoration = -1;	// decoration index
	int special_flag = -1;	// mark special architectural
	bool has_tower = false;
	Direction direction = Direction::None;
};

// TileMap is an array with 2 dimension.
typedef std::vector<std::vector<Tile>> TileMap;

#endif // !_TILE_H_
