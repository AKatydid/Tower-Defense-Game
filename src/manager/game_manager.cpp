#include "manager/game_manager.h"

GameManager::GameManager() {
	init_assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL Init Fail !!!");
	init_assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"SDL_Image Init Fail !!!");
	init_assert(Mix_Init(MIX_INIT_MP3), u8"SDL_Mixer Init Fail !!!");
	init_assert(!TTF_Init(), u8"SDL_TTF Init Fail !!!");
	
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	m_window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	init_assert(m_window, u8"Window create Fail !!!");

	m_render = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	init_assert(m_render, u8"Render create Fail !!!");

	m_terminal = false;
}

GameManager::~GameManager() {
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
	
}

void GameManager::on_render() {

}

void GameManager::init_assert(bool flag, const char* err_msg) {
	if (flag) return;

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"Game Init fail!", err_msg, m_window);
	exit(-1);
}
