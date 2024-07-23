#include "Game.h"

int main() {
	srand((int)std::time(NULL));

	Game::Game* game = new Game::Game;

	game->update();

	delete game;
}