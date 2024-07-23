#ifndef TESTING_CPP
#define TESTING_CPP

#include "Game.h"

using namespace sf;




int main() {
	RenderWindow window(VideoMode(1920, 1080), "SFML Practice 2", Style::Fullscreen);
	window.setFramerateLimit(60);

	Game::Character gameChar("Sprites/Ship/Main Ship/Main Ship - Bases/PNGs/Main Ship - Base - Full health.png", 100.f, Vector2f(500.f, 500.f), 0.5f);

	Game::Character lol;

	while (window.isOpen()) {
		sf::Event anEvent;

		while (window.pollEvent(anEvent)) {
			switch (anEvent.type) {

			case Event::EventType::Closed:
				window.close();
				break;


			}

			if (sf::Keyboard::isKeyPressed(Keyboard::Escape)) {
				anEvent.type = Event::Closed;
			}
			

		}


		window.clear(Color(46, 34, 47));
		gameChar.drawTo(window);
		lol.drawTo(window);
		window.display();
	}
}












#endif 