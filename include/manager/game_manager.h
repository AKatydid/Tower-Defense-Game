#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "manager/manager.h"
#include "manager/config_manager.h"
#include "manager/resource_manager.h"
#include "entity/map.h"

#include "utils/config.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class GameManager : public Manager<GameManager> 
{
	friend class Manager<GameManager>;

public:
	// outer interface
	int run(int argc, char** argv);

protected:
	GameManager();
	~GameManager();

private:
	void init_assert(bool flag, const char* err_msg);

	void on_input();

	void on_update(double delay);

	void on_render();

	bool generate_tile_map_texture();

private:
	SDL_Window* m_window;
	SDL_Renderer* m_render;
	SDL_Event m_event;

	SDL_Texture* m_tex_tile_map;

	bool m_terminal;
};

#endif