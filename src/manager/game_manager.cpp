#include "manager/game_manager.h"

GameManager::GameManager() {
	init_assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL Init Fail.");
	init_assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"SDL_Image Init Fail.");
	init_assert(Mix_Init(MIX_INIT_MP3), u8"SDL_Mixer Init Fail.");
	init_assert(!TTF_Init(), u8"SDL_TTF Init Fail.");
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	// load game data
	ConfigManager* config = ConfigManager::instance();
	init_assert(config->map.load("./asset/data/map.csv"), "Load Map data fail.");
	init_assert(config->load_level_config("asset/data/level.json"), u8"Load Level Data Fail.");
	init_assert(config->load_game_config("asset/data/config.json"), u8"Load Game Config Data Fail.");

	// init window
	m_window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	init_assert(m_window, u8"Window create Fail.");

	// init drawer
	m_render = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	init_assert(m_render, u8"Render create Fail.");

	// load resource
	init_assert(ResourcesManager::instance()->load_from_file(m_render), u8"Load Fail.");
	init_assert(generate_tile_map_texture(), u8"Map Load Fail.");

	m_terminal = false;
}

GameManager::~GameManager() 
{
	SDL_DestroyRenderer(m_render);
	SDL_DestroyWindow(m_window);

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int GameManager::run(int argc, char** argv) {
	Uint64 last_counter = SDL_GetPerformanceCounter();
	const Uint64 counter_freq = SDL_GetPerformanceFrequency();

	while (!m_terminal)
	{
		while (SDL_PollEvent(&m_event))
			on_input();

		Uint64 current_counter = SDL_GetPerformanceCounter();
		double delay = (double)(current_counter - last_counter) / counter_freq;
		last_counter = current_counter;
		if (delay * 1000 < 1000.0 / 60)
			SDL_Delay((Uint32)(1000.0 / 60 - delay * 1000));

		on_update(delay);

		SDL_SetRenderDrawColor(m_render, 0, 0, 0, 255);
		SDL_RenderClear(m_render);

		on_render();

		SDL_RenderPresent(m_render);
	}

	return 0;
}

void GameManager::on_input() {
	if (m_event.type == SDL_QUIT)
	{
		m_terminal = true;
	}
}

void GameManager::on_update(double delay) {
	static ConfigManager* configInstance =  ConfigManager::instance();

	// [TEST] check render effect
	if (!configInstance->is_game_over)
	{
		WaveManager::instance()->on_update(delay);
		EnemyManager::instance()->on_update(delay);
	}
}

void GameManager::on_render()
{
	ConfigManager* instance = ConfigManager::instance();
	static SDL_Rect& rect_dst = instance->rect_tile_map;
	SDL_RenderCopy(m_render, m_tex_tile_map, nullptr, &rect_dst);

	// [TEST] render enemy
	EnemyManager::instance()->on_render(m_render);
}

bool GameManager::generate_tile_map_texture()
{
	const Map& map = ConfigManager::instance()->map;
	const TileMap& tile_map = map.get_tile_map();
	SDL_Rect& rect_tile_map = ConfigManager::instance()->rect_tile_map;
	SDL_Texture* tex_tile_set = ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_Tileset)->second;

	int width_tex_tile_set, height_tex_tile_set;
	SDL_QueryTexture(tex_tile_set, nullptr, nullptr, &width_tex_tile_set, &height_tex_tile_set);
	int num_tile_single_line = (int)std::ceil((double)width_tex_tile_set / SIZE_TILE);

	// Create tile map texture
	int width_tex_tile_map, height_tex_tile_map;
	width_tex_tile_map = (int)map.get_width() * SIZE_TILE;
	height_tex_tile_map = (int)map.get_height() * SIZE_TILE;
	m_tex_tile_map = SDL_CreateTexture(m_render, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_TARGET, width_tex_tile_map, height_tex_tile_map);
	if (!m_tex_tile_map) return false;

	ConfigManager* config = ConfigManager::instance();
	rect_tile_map.x = (config->basic_template.window_width - width_tex_tile_map) / 2;
	rect_tile_map.y = (config->basic_template.window_height - height_tex_tile_map) / 2;
	rect_tile_map.w = width_tex_tile_map;
	rect_tile_map.h = height_tex_tile_map;

	// [SDL_BLENDMODE_BLEND]: Enable Mixing Mode
	SDL_SetTextureBlendMode(m_tex_tile_map, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(m_render, m_tex_tile_map);

	// render every tile
	for (int y = 0; y < map.get_height(); y++)
	{
		for (int x = 0; x < map.get_width(); x++)
		{
			SDL_Rect rect_src;
			const Tile& tile = tile_map[y][x];

			const SDL_Rect& rect_dst =
			{
				x * SIZE_TILE, y * SIZE_TILE,
				SIZE_TILE, SIZE_TILE
			};

			rect_src =
			{
				(tile.terrian % num_tile_single_line) * SIZE_TILE,
				(tile.terrian / num_tile_single_line) * SIZE_TILE,
				SIZE_TILE, SIZE_TILE
			};
			SDL_RenderCopy(m_render, tex_tile_set, &rect_src, &rect_dst);

			if (tile.decoration >= 0)
			{
				rect_src =
				{
					(tile.decoration % num_tile_single_line) * SIZE_TILE,
					(tile.decoration / num_tile_single_line) * SIZE_TILE,
					SIZE_TILE, SIZE_TILE
				};
				SDL_RenderCopy(m_render, tex_tile_set, &rect_src, &rect_dst);
			}
		}
	}

	const SDL_Point& idx_home = map.get_idx_home();
	const SDL_Rect rect_dst ={
		idx_home.x * SIZE_TILE, idx_home.y * SIZE_TILE,
		SIZE_TILE, SIZE_TILE
	};

	SDL_RenderCopy(m_render, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_Home)->second, nullptr, &rect_dst);

	SDL_SetRenderTarget(m_render, nullptr);

	return true;
}


void GameManager::init_assert(bool flag, const char* err_msg) {
	if (flag) return;

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"Game Init fail!", err_msg, m_window);
	exit(-1);
}
