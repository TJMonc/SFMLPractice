#ifndef _HEADER_H_
#define _HEADER_H_

#include "Phases.h"


//TODO:Finish Music
int main(){
	srand(std::time(NULL));
	RenderWindow window(VideoMode(1920, 1080), "SFML Practice 2", Style::Fullscreen);
	window.setFramerateLimit(60);

	

	//Player
	Game::Ship player("Sprites/Ship/Main Ship/Main Ship - Bases/PNGs/Main Ship - Base - Full health.png", 100.f, true, 0.5f);
	player.addSprite("Sprites/Ship/Main Ship/Main Ship - Engine Effects/PNGs/Main Ship - Engines - Base Engine - Spritesheet.png", IntRect(96, 48, 48, 48));
	int hitCounter = 1;
	IntRect intRect = IntRect(0, 0, 48, 48);

	//Enemy
	Game::Character enemy("Sprites/Environment/Asteroids/PNGs/Asteroid 01 - Explode.png", 50.f, Vector2f(0, 0), 0.3f);
	enemy.setTextRect(IntRect(0, 0, 96, 96));
	std::vector<Game::Character> enemies;
	IntRect rect = IntRect(0, 0, 96, 96);
	Clock enemyClock;
	Time enemyTime = milliseconds(300.f);

	//Player Bullets
	std::vector<Game::Bullet> bullets;
	Clock bulletClock;
	Time bulletTime = milliseconds(300.f);
	Sound bulletSound;
	SoundBuffer bulletSoundBuffer;
	Clock bulletSoundClock;
	Time bulletSoundTime = milliseconds(20);

	//Phase
	int phase;
	int survivedPhases = 0;
	int macroPhase;
	Clock phaseClock;
	Time phaseTime = seconds(20);
	bool phaseStart = false;
	int enemiesDestroyed = 0;

	//Lose State
	bool lose = false;
	int highScore = 0;
	int highEnemiesDestroyed = 0;
	Game::loadSave(highScore, highEnemiesDestroyed, "SaveState/SaveState.txt");
	Text loseText;
	Font loseFont;
	Game::loadFont(loseText, loseFont, "Fonts/aBlackLives.ttf");
	loseText.setCharacterSize(75.f);
	loseText.setPosition(0, window.getSize().y / 2 - loseText.getCharacterSize());
	Clock loseClock;
	Time loseTime = seconds(2);
	
	//Music
	Music music;
	music.setLoop(true);
	music.setRelativeToListener(false);
	bool music1 = false;
	bool music2 = false;
	bool music3 = false;

	//UI
	Text uiText;
	Font uiFont;
	Game::loadFont(uiText, uiFont, "Fonts/aBlackLives.ttf");
	uiText.setCharacterSize(50.f);
	uiText.setPosition(0, window.getSize().y - uiText.getCharacterSize() * 2.5);

	//Health Bar
	RectangleShape redRect;
	RectangleShape greenRect;
	redRect.setSize(Vector2f(1000.f, 30.f));
	redRect.setPosition(0.f, 0.f);
	greenRect.setPosition(redRect.getPosition());
	redRect.setFillColor(Color::Red);
	greenRect.setFillColor(Color::Green);

	while (window.isOpen()) {
		sf::Event anEvent;
		while (window.pollEvent(anEvent)) {
			switch (anEvent.type) {
			case Event::EventType::Closed:
				Game::saveGame(highScore, highEnemiesDestroyed, "SaveState/SaveState.txt");
				window.close();
				break;
			}
			if (sf::Keyboard::isKeyPressed(Keyboard::Escape)) {
				anEvent.type = Event::Closed;
			}
		}

		uiText.setString("Survived Phases: " + std::to_string(survivedPhases) + "\n Enemies Destroyed: " + std::to_string(enemiesDestroyed));
		greenRect.setSize(Vector2f(redRect.getSize().x * (player.getHealth() / 100), redRect.getSize().y));

		if (!lose && player.getHealth() <= 0) {
			lose = true;
			music1 = false;
			music2 = false;
			music3 = false;
			survivedPhases = 0;
			loseClock.restart();
		}
		if (lose) {
			loseText.setString("YOU LOSE\n\High Score: " + std::to_string(highScore) + "   Enemies Destroyed: " + std::to_string(highEnemiesDestroyed));
			Game::saveGame(highScore, highEnemiesDestroyed, "SaveState/SaveState.txt");

			if (!enemies.empty()) {
				
				
				i = 0; i < enemies.size(); i++) {
					enemies.erase(enemies.begin() + i);
				}
			}
			if (!bullets.empty()) {
				for (size_t i = 0; i < bullets.size(); i++) {
					bullets.erase(bullets.begin() + i);
				}
			}
			if (loseClock.getElapsedTime().asSeconds() > loseTime.asSeconds()) {
				if (Keyboard::isKeyPressed(Keyboard::Enter)) {
					player.setHealth(100);
					lose = false;
					phaseStart = false;
					survivedPhases = 0;
					enemiesDestroyed = 0;
					phaseClock.restart();
				}
			}
			window.clear();
			window.draw(loseText);
		}
		//
	
		//Player Movement
		if (player.moveLeft(window)) {
			for (size_t i = 0; i < player.getAddSprites().size(); i++) {
				player.animate2(player.getAddSprites().at(i), Vector2i(0, 144), Vector2i(48, 48), Vector2i(48, 0), player.getIsDead());
			}
		}
		if (player.moveRight(window)) {		
			for (size_t i = 0; i < player.getAddSprites().size(); i++) {
				player.animate2(player.getAddSprites().at(i), Vector2i(0, 144), Vector2i(48, 48), Vector2i(48, 0), player.getIsDead());
			}
		}
		if (player.moveUp(window)) {

			for (size_t i = 0; i < player.getAddSprites().size(); i++) {
				player.animate2(player.getAddSprites().at(i), Vector2i(0, 144), Vector2i(0, 48), Vector2i(48, 48), player.getIsDead());
			}
		}
		if (player.moveDown(window)) {
			for (size_t i = 0; i < player.getAddSprites().size(); i++) {
				player.animate2(player.getAddSprites().at(i), Vector2i(0, 144), Vector2i(0, 48), Vector2i(48, 0), player.getIsDead());
			}
		}
		//
		//Phase Implementation
		if (!phaseStart) {
			if (survivedPhases < 3) {
				macroPhase = 1;
			}
			else if (survivedPhases < 15) {
				macroPhase = 2;
			}
			else if (survivedPhases < 30) {
				macroPhase = 3;
			}
			else {
				macroPhase = 4;
			}
			switch (macroPhase) {
			case 1:
				phase = rand() % 2 + 1;
				break;
			case 2:
				phase = rand() % 4 + 1;
				break;
			case 3:
				phase = rand() % 5 + 1;
				break;
			case 4:
				phase = rand() % 5 + 1;
				break;
			}
			phaseStart = true;
		}
		if (phaseStart && phaseClock.getElapsedTime().asSeconds() > phaseTime.asSeconds()) {
			phaseClock.restart();
			player.heal(10.f);
			survivedPhases++;
			for (size_t i = 0; i < enemies.size(); i++) {
				enemies[i].damage(100.f);
			}
			phaseStart = false;
			if (survivedPhases > highScore) {
				highScore = survivedPhases;
			}
		}
		if (phaseStart && !lose) { // REMEMBER
			switch (phase) {	//Fall
			case 1:
				if (macroPhase == 1) {
					enemyTime = milliseconds(500);
				}
				else if (macroPhase == 2) {
					enemyTime = milliseconds(300);
				}
				else {
					enemyTime = milliseconds(100);
				}
				if (enemyClock.getElapsedTime().asMilliseconds() > enemyTime.asMilliseconds()) {
					enemyClock.restart();
					float xPos = rand() % window.getSize().x - enemy.getSprite().getGlobalBounds().getSize().x + 1.f;
					float yPos = 0.f;
					enemy.setPosition(xPos, yPos);
					enemies.push_back(Game::Character(enemy));
				}

				for (size_t i = 0; i < enemies.size(); i++) {
					if (macroPhase == 1) {
						enemies[i].move(0, 30.f);
					}
					else if (macroPhase == 2) {
						enemies[i].move(0, 45.f);
					}
					else {
						enemies[i].move(15.f, 45.f);
					}
					if (Game::isOutOfBoundsX(enemies[i].getSprite(), window) || Game::isOutOfBoundsY(enemies[i].getSprite(), window)) {
						enemies.erase(enemies.begin() + i);
					}
				}
				break;
			case 2:	//Drift
				enemyTime = milliseconds(300);

				if (enemyClock.getElapsedTime().asMilliseconds() > enemyTime.asMilliseconds()) {
					auto newEnemy = std::make_unique<Game::Character>(enemy);
					float xPos = rand() % window.getSize().x;
					float yPos = 0.f;
					float xMovement;
					float yMovement;

					switch (macroPhase) {
					case 1:
						xMovement = 15.f;
						yMovement = 20.f;
						break;
					case 2:
						xMovement = 25.f;
						yMovement = 25.f;
						break;
					default:
						xMovement = 30.f;
						yMovement = 40.f;
					}
					newEnemy->setPosition(xPos, yPos);
					if (newEnemy->getPosition().x <= window.getSize().x / 2) {
						newEnemy->move(xMovement, yMovement);
					}
					else {
						newEnemy->move(-1 * xMovement, yMovement);
					}
					enemies.push_back(*newEnemy);				
					enemyClock.restart();
				}

				for (size_t i = 0; i < enemies.size(); i++) {
					//float xMovement;
					//float yMovement;

					enemies[i].move(enemies[i].getMovement().x, enemies[i].getMovement().y);

					//if (macroPhase == 1) {
					//	xMovement = 15.f;
					//	yMovement = 20.f;
					//}
					//else if (macroPhase == 2) {
					//	xMovement = 25.f;
					//	yMovement = 25.f;
					//}
					//else {
					//	xMovement = 30.f;
					//	yMovement = 40.f;

					//}
					//if (enemies[i].getPosition().x <= window.getSize().x / 2) {
					//	if (enemies[i].getMovement().x < 0) {
					//		enemies[i].setRegBool(false);
					//	}
					//	else {
					//		enemies[i].setRegBool(false);
					//	}
					//}
					//else if (enemies[i].getPosition().x >= window.getSize().x / 2) {
					//	if (enemies[i].getMovement().x > 0) {
					//		enemies[i].setRegBool(false);
					//	}
					//	else {
					//		enemies[i].setRegBool(false);
					//	}
					//}


					//if (enemies[i].getPosition().x < window.getSize().x / 2) {
					//	if (!enemies[i].getRegBool()) {
					//		enemies[i].move(xMovement, yMovement);
					//	}
					//	else {
					//		enemies[i].move(-1 * xMovement, yMovement);
					//	}

					//}
					//else if (enemies[i].getPosition().x >= window.getSize().x / 2) {
					//	if (!enemies[i].getRegBool()) {
					//		enemies[i].move(-1 * xMovement, yMovement);
					//	}
					//	else {
					//		enemies[i].move(xMovement, yMovement);
					//	}
					//}


					if (Game::isOutOfBoundsX(enemies[i].getSprite(), window) || Game::isOutOfBoundsY(enemies[i].getSprite(), window)) {
						enemies.erase(enemies.begin() + i);
					}
				}
				break;
			case 3:	//Side bounce
				if (macroPhase == 1) {
					enemyTime = milliseconds(100);
				}
				else if (macroPhase == 2) {
					enemyTime = milliseconds(70);
				}
				else {
					enemyTime = milliseconds(50);
				}
				if (enemyClock.getElapsedTime().asMilliseconds() > enemyTime.asMilliseconds()) {
					enemyClock.restart();
					int randNum = rand() % 2;
					float xPos;
					float yPos = 1.f;

					switch (randNum) {
					case 0:
						xPos = 0.f;
						if (macroPhase >= 3) {
							xPos = rand() % window.getSize().x / 5.f;
						}
						break;
					case 1:
						xPos = rand() % (window.getSize().x) - enemy.getSize().x - 1.f;
						if (macroPhase >= 3) {
							xPos = rand() % window.getSize().x * 4.f / 5.f - enemy.getSize().x - 1.f;
						}
						break;
					}
					switch (macroPhase) {
					case 2:
						randNum = rand() % 2;
						switch (randNum) {
						case 0:
							yPos = 20.f;
							break;
						case 1:
							yPos = 1.f;
						}
						break;
					case 3:
						yPos = rand() % window.getSize().y / 10.f;
						break;
					case 4:
						yPos = rand() % window.getSize().y / 5.f;
					}
					enemy.setPosition(xPos, yPos);
					enemies.push_back(Game::Character(enemy));
				}
				for (size_t i = 0; i < enemies.size(); i++) {
					float xMovement = 50.f;
					float yMovement;

					if (macroPhase == 1) {
						yMovement = 10.f;
					}
					else if (macroPhase == 2) {
						std::unique_ptr<int> randNum(new int(rand() % 2));

						switch (*randNum) {
						case 0:
							yMovement = 8.f;
							break;
						case 1:
							yMovement = 10.f;
						}
						*randNum = rand() % 2;
						switch (*randNum) {
						case 0:
							xMovement = 50.f;
							break;
						case 1:
							xMovement = 40.f;
							break;

						}
					}
					else {
						std::unique_ptr<int> randNum(new int(rand() % 5));
						switch (*randNum) {
						case 0:
							yMovement = 5.f;
							break;
						case 1:
							yMovement = 8.f;
							break;
						case 2:
							yMovement = 10.f;
							break;
						case 3:
							yMovement = 15.f;
							break;
						case 4:
							yMovement = 25.f;
						}

						*randNum = rand() % 5;
						switch (*randNum) {
						case 0:
							xMovement = 50.f;
							break;
						case 1:
							xMovement = 45.f;
							break;
						case 2:
							xMovement = 40.f;
							break;
						case 3:
							xMovement = 35.f;
							break;
						case 4:
							xMovement = 30.f;
						}
					
					}
					if (enemies[i].getPosition().x >= window.getSize().x - enemies[i].getSize().x || enemies[i].getPosition().x <= 0) {
						if (!enemies[i].getRegBool()) {
							enemies[i].setRegBool(true);
						}
						else {
							enemies[i].setRegBool(false);
						}
					}
					if (enemies[i].getPosition().x >= window.getSize().x / 2) {
						if (!enemies[i].getRegBool()) {
							xMovement *= -1;
						}
					}
					else if (enemies[i].getPosition().x <= window.getSize().x / 2) {
						if (!enemies[i].getRegBool()) {
							xMovement *= -1;
						}
					}
					enemies[i].move(xMovement, yMovement);
					if (Game::isOutOfBoundsY(enemies[i].getSprite(), window)) {
						enemies.erase(enemies.begin() + i);
					}
				}
				break;
			case 4://Fall bounce

				if (macroPhase == 2) {
					enemyTime = milliseconds(300);
				}
				else if (macroPhase == 3) {
					enemyTime = milliseconds(200);
				}
				else {
					enemyTime = milliseconds(100);
				}
				if (enemyClock.getElapsedTime().asMilliseconds() > enemyTime.asMilliseconds()) {
					enemyClock.restart();
					float xPos = rand() % window.getSize().x;
					float yPos = rand() % window.getSize().y;

					enemy.setPosition(xPos, yPos);
					enemies.push_back(Game::Character(enemy));

				}

				for (size_t i = 0; i < enemies.size(); i++) {
					float yMovement = 30.f;
					float xMovement = 0.f;

					if (macroPhase <= 2) {
						yMovement = 30.f;
					}
					else if (macroPhase == 3) {
						yMovement = 45.f;
					}
					else {
						int randNum = rand() % 2;
						yMovement = 50.f;
						switch (randNum) {
						case 0:
							xMovement = 15.f;
							break;
						case 1:
							xMovement = -15.f;
							break;
						}
					}

					if (enemies[i].getPosition().y < 0 || enemies[i].getPosition().y + enemies[i].getHitBoxSize().y > window.getSize().y) {
						if (!enemies[i].getRegBool()) {
							enemies[i].setRegBool(true);
						}
						else {
							enemies[i].setRegBool(false);
							if (macroPhase <= 2) {
								enemies[i].setRegBool(true);
							}
						}
					}

					if (enemies[i].getRegBool()) {
						yMovement *= -1;
					}

					enemies[i].move(xMovement, yMovement);

					if (Game::isOutOfBoundsX(enemies[i].getSprite(), window) || Game::isOutOfBoundsY(enemies[i].getSprite(), window) || enemies.size() > 250) {
						enemies.erase(enemies.begin() + i);

					}
				}
				break;

			case 5:	//Shoot phase
				if (macroPhase == 1) {
					enemyTime = milliseconds(1000);

				}
				else if (macroPhase == 2) {
					enemyTime = milliseconds(1000);

				}
				else if (macroPhase == 3) {
					enemyTime = milliseconds(600);
				}
				else {
					enemyTime = milliseconds(300);

				}
				if (enemyClock.getElapsedTime().asMilliseconds() > enemyTime.asMilliseconds()) {
					enemyClock.restart();
					float xPos = rand() % window.getSize().x;
					float yPos = rand() % window.getSize().y;

					enemy.setPosition(xPos, yPos);
					enemies.push_back(Game::Character(enemy));
				}
				for (size_t i = 0; i < enemies.size(); i++) {

					if (!enemies[i].getRegBool()) {
						enemies[i].setRegBool(true);
						Vector2f movement = Game::getVectors(player.getPosition(), enemies[i].getCenter());
						enemies[i].move(movement.x * 30.f, movement.y * 30.f);
					}
					else {
						enemies[i].move();
					}
					if (Game::isOutOfBoundsX(enemies[i].getSprite(), window) || Game::isOutOfBoundsY(enemies[i].getSprite(), window) || enemies.size() > 250) {
						enemies.erase(enemies.begin() + i);
					}
				}
				break;
			}

			//Bullet Spawn
			if (Keyboard::isKeyPressed(Keyboard::Enter) && bulletClock.getElapsedTime().asMilliseconds() > bulletTime.asMilliseconds() && !lose) {
				bulletClock.restart();

				bullets.push_back(Game::Bullet(&player));
				Game::loadSound(bulletSoundClock, bulletSoundTime, bulletSound, bulletSoundBuffer, "Music/projectile.wav");
			}
			for (size_t i = 0; i < bullets.size(); i++) {
				bullets[i].move(player, 15.f);
				if (Game::isOutOfBoundsX(bullets[i].getShape(), window) || Game::isOutOfBoundsY(bullets[i].getShape(), window)) {
					bullets.erase(bullets.begin() + i);
				}

			}

			//Collision + damage
			for (size_t i = 0; i < enemies.size(); i++) {
				for (size_t j = 0; j < bullets.size(); j++) {

					if (bullets[j].collision(enemies[i]) && enemies[i].getHealth() > 0) {
						bullets.erase(bullets.begin() + j);

						enemies[i].damage(100.f);
						enemy.loadSound(100, "Music/explosion3.wav");
						enemiesDestroyed++;
						if (enemiesDestroyed > highEnemiesDestroyed) {
							highEnemiesDestroyed++;
						}
						break;
					}
				}
			}
			for (size_t i = 0; i < enemies.size(); i++) {
				if (enemies[i].collision(player) && enemies[i].getHealth() > 0.f) {

					enemies[i].damage(100.f);
					player.damage(10.f);
					player.loadSound(1000, "Music/explosion3.wav");

					if (player.getHealth() <= 0) {
						player.loadSound(1000, "Music/explosion2.wav");
					}
				}
			}

			//Collision animation
			if (!player.getIsDead()) {
				player.animate1(hitCounter, 4, "Sprites/Ship/Main Ship/Main Ship - Design/Main Ship - Fighter Design", ".tga", player.getIsDead());
			}
			else {
				player.loadTexture("Sprites/Ship/Main Ship/Main Ship - Bases/PNGs/Main Ship - Base - Full health.png");
			}


			for (size_t i = 0; i < enemies.size(); i++) {
				if (enemies[i].getHealth() <= 0.f) {
					if (!enemies[i].getIsDead()) {
						enemies[i].animate2(enemies[i].getSprite(), Vector2i(0, 768), Vector2i(0, 0), Vector2i(95, 1), enemies[i].getIsDead());
					}
					else {
						enemies.erase(enemies.begin() + i);
					}
				}
			}
		}
			window.clear(Color(46, 34, 47));
			if (!lose) {
				for (size_t i = 0; i < bullets.size(); i++) {
					bullets[i].drawTo(window);
				}
				for (size_t i = 0; i < enemies.size(); i++) {
					enemies[i].drawTo(window);
				}

				player.drawTo(window);
				window.draw(uiText);
				window.draw(redRect);
				window.draw(greenRect);

				if (!music1) {
					music1 = true;
					Game::loadMusic(music, 75.f, "Music/Revolution.mp3");
				}
				else if (!music2 && music1 && survivedPhases > 5) {
					music2 = true;
					Game::loadMusic(music, 75.f, "Music/Threat.mp3");
				}
				else if (!music3 && music2 && survivedPhases > 15) {
					music3 = true;
					Game::loadMusic(music, 75.f, "Music/Encounter.mp3");
				}
				else if(music3 && music2 && music1 && survivedPhases >= 30){
					Game::loadMusic(music, 75.f, "Music/Ensemble.mp3");
				}
			}
			else {
				window.draw(loseText);
			}
			window.display();
	}
	return 0;
}
#endif
