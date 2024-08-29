#include "Game.h"
#include <Windows.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {
	srand((int)std::time(NULL));

	Game::Game* game = new Game::Game;

	game->update();

	delete game;
}