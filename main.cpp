#define SDL_MAIN_HANDLED

#include "manager/game_manager.h"

int main(int argc, char** argv) {
	return GameManager::instance()->run(argc, argv);
}