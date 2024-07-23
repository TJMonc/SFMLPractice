#include "Game.h"



Game::Game::Game(){

	window->setFramerateLimit(60);
	initPlayer();
	initEnemy();
	initMusic();
	initDisplay();
	loadSave(miscInfo->highScore, miscInfo->highEnemiesDestroyed, "SaveState/SaveState.txt");

	
}


void Game::Game::initPlayer() {

	player->player.addSprite(SpritePaths::engine, IntRect(96, 48, 48, 48));
	player->hitCounter = 1;
	player->player.setWindow(window.get());

	return;
}

void Game::Game::initEnemy() {
	enemies->enemy.setTextRect(enemies->enemyRect);
	enemies->enemy.setWindow(window.get());
	return;
}

void Game::Game::initMusic() {
	music->music.setLoop(true);
	music->music.setRelativeToListener(false);

	return;
}


void Game::Game::initDisplay() {
	loadFont(display->uiText, display->uiFont, FontPaths::blackLivesFont);
	display->uiText.setCharacterSize(window->getSize().x / 40.f);
	display->uiText.setPosition(0, window->getSize().y - display->uiText.getCharacterSize() * 2.5f);

	display->redRect.setSize(Vector2f(window->getSize().x, window->getSize().y / 36));
	display->redRect.setPosition(0.f, 0.f);
	display->greenRect.setPosition(display->redRect.getPosition());
	display->redRect.setFillColor(Color::Red);
	display->greenRect.setFillColor(Color::Green);

	loadFont(display->loseText, display->loseFont, FontPaths::blackLivesFont);
	display->loseText.setCharacterSize(window->getSize().x / 26.f);;
	display->loseText.setPosition(0, float(window->getSize().y / 2.f - display->loseText.getCharacterSize()));

	return;
}

inline void Game::Game::displayBaseHUD() {
	display->uiText.setString("Survived Phases: " + std::to_string(miscInfo->survivedPhases) + "\n Enemies Destroyed: " + std::to_string(miscInfo->enemiesDestroyed));
	display->greenRect.setSize(Vector2f(display->redRect.getSize().x * (player->player.getHealth() / 100), display->redRect.getSize().y));
}
inline void Game::Game::resetOnLose() {
	if (!miscInfo->lose && player->player.getHealth() <= 0) {
		miscInfo->lose = true;
		music->music1 = false;
		music->music2 = false;
		music->music3 = false;
		miscInfo->survivedPhases = 0;
		miscInfo->loseClock.restart();
	}
	if (miscInfo->lose) {
		display->loseText.setString("YOU LOSE\nHigh Score: " +
		std::to_string(miscInfo->highScore) + "   Enemies Destroyed: " + std::to_string(miscInfo->highEnemiesDestroyed));

		saveGame(miscInfo->highScore, miscInfo->highEnemiesDestroyed, "SaveState/SaveState.txt");

		enemies->enemies.reset();

		if (!bullets->bullets.empty()) {
			for (size_t i = 0; i < bullets->bullets.size(); i++) {
				bullets->bullets.erase(bullets->bullets.begin() + i);
			}
		}
		if (miscInfo->loseClock.getElapsedTime().asSeconds() > miscInfo->loseTime.asSeconds()) {
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				player->player.setHealth(100);
				miscInfo->lose = false;
				miscInfo->phaseStart = false;
				miscInfo->survivedPhases = 0;
				miscInfo->enemiesDestroyed = 0;
				miscInfo->phaseClock.restart();
			}
		}
		window->clear();
		window->draw(display->loseText);
	}
}
inline void Game::Game::playerMovement() {
	if (player->player.moveLeft(*window)) {
		for (size_t i = 0; i < player->player.getAddSprites().size(); i++) {
			player->player.animate2(player->player.getAddSprites().at(i), Vector2i(0, 144), Vector2i(48, 48), Vector2i(48, 0), player->player.getIsDead());
		}
	}
	if (player->player.moveRight(*window)) {
		for (size_t i = 0; i < player->player.getAddSprites().size(); i++) {
			player->player.animate2(player->player.getAddSprites().at(i), Vector2i(0, 144), Vector2i(48, 48), Vector2i(48, 0), player->player.getIsDead());
		}
	}
	if (player->player.moveUp(*window)) {

		for (size_t i = 0; i < player->player.getAddSprites().size(); i++) {
			player->player.animate2(player->player.getAddSprites().at(i), Vector2i(0, 144), Vector2i(0, 48), Vector2i(48, 48), player->player.getIsDead());
		}
	}
	if (player->player.moveDown(*window)) {
		for (size_t i = 0; i < player->player.getAddSprites().size(); i++) {
			player->player.animate2(player->player.getAddSprites().at(i), Vector2i(0, 144), Vector2i(0, 48), Vector2i(48, 0), player->player.getIsDead());
		}
	}
}

inline void Game::Game::bulletSpawn() {
	if (Keyboard::isKeyPressed(Keyboard::Enter) && bullets->bulletClock.getElapsedTime().asMilliseconds() > bullets->bulletTime.asMilliseconds() && !miscInfo->lose) {
		bullets->bulletClock.restart();

		bullets->bullets.push_back(Bullet(&player->player, window.get()));
		loadSound(bullets->bulletSoundClock, bullets->bulletSoundTime, bullets->bulletSound, bullets->bulletSoundBuffer, SoundPaths::bulletShot);
	}
	for (size_t i = 0; i < bullets->bullets.size(); i++) {
		bullets->bullets[i].move(player->player, 15.f);
		if (isOutOfBoundsX(bullets->bullets[i].getShape(), *window) || isOutOfBoundsY(bullets->bullets[i].getShape(), *window)) {
			bullets->bullets.erase(bullets->bullets.begin() + i);
		}

	}
}


inline void Game::Game::phaseStartAndEnd() {
	if (!miscInfo->phaseStart) {
		if (miscInfo->survivedPhases < 3) {
			miscInfo->macroPhase = 1;
		}
		else if (miscInfo->survivedPhases < 15) {
			miscInfo->macroPhase = 2;
		}
		else if (miscInfo->survivedPhases < 30) {
			miscInfo->macroPhase = 3;
		}
		else {
			miscInfo->macroPhase = 4;
		}
		switch (miscInfo->macroPhase) {
		case 1:
			miscInfo->phase = rand() % 2 + 1;
			break;
		case 2:
			miscInfo->phase = rand() % 4 + 1;
			break;
		case 3:
			miscInfo->phase = rand() % 5 + 1;
			break;
		case 4:
			miscInfo->phase = rand() % 5 + 1;
			break;
		}
		miscInfo->phaseStart = true;
	}
	if (miscInfo->phaseStart && miscInfo->phaseClock.getElapsedTime().asSeconds() > miscInfo->phaseTime.asSeconds()) {
		miscInfo->phaseClock.restart();
		player->player.heal(10.f);
		miscInfo->survivedPhases++;
		for (size_t i = 0; i < enemies->enemies.size(); i++) {
			enemies->enemies[i].damage(100.f);
		}
		miscInfo->phaseStart = false;
		if (miscInfo->survivedPhases > miscInfo->highScore) {
			miscInfo->highScore = miscInfo->survivedPhases;
		}
	}
}

inline void Game::Game::Phase1() {
	auto newEnemy = std::make_unique<Character>(enemies->enemy);

	if (miscInfo->macroPhase == 1) {
		enemies->enemyTime = milliseconds(500);
	}
	else if (miscInfo->macroPhase == 2) {
		enemies->enemyTime = milliseconds(300);
	}
	else {
		enemies->enemyTime = milliseconds(100);
	}
	if (enemies->enemyClock.getElapsedTime().asMilliseconds() > enemies->enemyTime.asMilliseconds()) {

		enemies->enemyClock.restart();

		float xPos = rand() % window->getSize().x - newEnemy->getSprite().getGlobalBounds().getSize().x + 1.f;
		float yPos = 0.f;

		newEnemy->setPosition(xPos, yPos);
		enemies->enemies.initialize(Character(*newEnemy));
	}

	for (size_t i = 0; i < enemies->enemies.size(); i++) {
		if (miscInfo->macroPhase == 1) {
			enemies->enemies[i].move(0, 30.f);
		}
		else if (miscInfo->macroPhase == 2) {
			enemies->enemies[i].move(0, 45.f);
		}
		else {
			enemies->enemies[i].move(15.f, 45.f);
		}
		if (isOutOfBoundsX(enemies->enemies[i].getSprite(), *window) || isOutOfBoundsY(enemies->enemies[i].getSprite(), *window)) {
			enemies->enemies.deInitialize(i);
		}
	}
	return;
}

inline void Game::Game::Phase2() {

	enemies->enemyTime = milliseconds(300);
	if (miscInfo->macroPhase >= 3) {
		enemies->enemyTime = milliseconds(100);

	}

	if (enemies->enemyClock.getElapsedTime().asMilliseconds() > enemies->enemyTime.asMilliseconds()) {

		int xPos = rand() % window->getSize().x;
		float yPos = 0.f;
		float xMovement;
		float yMovement;

		switch (miscInfo->macroPhase) {
		case 1:
			xMovement = 15.f;
			yMovement = 20.f;
			break;
		case 2:
			xMovement = 25.f;
			yMovement = 25.f;
			break;
		default:
			xMovement = rand() % 70;
			yMovement = 50.f;
		}
		enemies->enemy.setPosition((float)xPos, yPos);
		if (enemies->enemy.getPosition().x <= window->getSize().x / 2.f) {
			enemies->enemy.move(xMovement, yMovement);
		}
		else {
			enemies->enemy.move(-1 * xMovement, yMovement);
		}


		enemies->enemies.initialize(Character(enemies->enemy));
		enemies->enemyClock.restart();
	}


	for (size_t i = 0; i < enemies->enemies.size(); i++) {
		//float xMovement;
		//float yMovement;

		enemies->enemies[i].move(enemies->enemies[i].getMovement().x, enemies->enemies[i].getMovement().y);

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
		//if (enemies[i].getPosition().x <= window->getSize().x / 2) {
		//	if (enemies[i].getMovement().x < 0) {
		//		enemies[i].setRegBool(false);
		//	}
		//	else {
		//		enemies[i].setRegBool(false);
		//	}
		//}
		//else if (enemies[i].getPosition().x >= window->getSize().x / 2) {
		//	if (enemies[i].getMovement().x > 0) {
		//		enemies[i].setRegBool(false);
		//	}
		//	else {
		//		enemies[i].setRegBool(false);
		//	}
		//}


		//if (enemies[i].getPosition().x < window->getSize().x / 2) {
		//	if (!enemies[i].getRegBool()) {
		//		enemies[i].move(xMovement, yMovement);
		//	}
		//	else {
		//		enemies[i].move(-1 * xMovement, yMovement);
		//	}

		//}
		//else if (enemies[i].getPosition().x >= window->getSize().x / 2) {
		//	if (!enemies[i].getRegBool()) {
		//		enemies[i].move(-1 * xMovement, yMovement);
		//	}
		//	else {
		//		enemies[i].move(xMovement, yMovement);
		//	}
		//}


		if (isOutOfBoundsX(enemies->enemies[i].getSprite(), *window) || isOutOfBoundsY(enemies->enemies[i].getSprite(), *window)) {
			enemies->enemies.deInitialize(i);
		}
	}
}

inline void Game::Game::Phase3() {

	enemies->enemyTime = milliseconds(100);
	if (enemies->enemyClock.getElapsedTime().asMilliseconds() > enemies->enemyTime.asMilliseconds()) {
		auto newEnemy = std::make_unique<Character>(enemies->enemy);

		enemies->enemyClock.restart();
		int randNum = rand() % 2;
		float xPos;
		float yPos = 1.f;

		switch (randNum) {
		case 0:
			xPos = 0.f;
			if (miscInfo->macroPhase > 3) {
				xPos = rand() % (window->getSize().x / 20);
			}
			break;
		case 1:
			xPos = (window->getSize().x) - newEnemy->getSize().x - 1.f;
			if (miscInfo->macroPhase > 3) {
				xPos = rand() % window->getSize().x * (19 / 20.f);
			}
			break;
		}

		switch (miscInfo->macroPhase) {
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
			yPos = rand() % window->getSize().y / 20.f;
			break;
		case 4:
			yPos = rand() % window->getSize().y / 20.f;
		}
		newEnemy->setPosition(xPos, yPos);
		enemies->enemies.initialize(Character(*newEnemy));
	}
	for (size_t i = 0; i < enemies->enemies.size(); i++) {

		float xMovement = 50.f;
		float yMovement;

		if (miscInfo->macroPhase == 1) {
			yMovement = 10.f;
		}
		else if (miscInfo->macroPhase == 2) {
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
				yMovement = 15.f;
			}

			*randNum = rand() % 5;
			switch (*randNum) {
			case 0:
				xMovement = 60.f;
				break;
			case 1:
				xMovement = 50.f;
				break;
			case 2:
				xMovement = 45.f;
				break;
			case 3:
				xMovement = 40.f;
				break;
			case 4:
				xMovement = 30.f;
			}

		}
		if (enemies->enemies[i].getPosition().x >= window->getSize().x - enemies->enemies[i].getSize().x || enemies->enemies[i].getPosition().x <= 0) {
			if (!enemies->enemies[i].getRegBool()) {
				enemies->enemies[i].setRegBool(true);
			}
			else {
				enemies->enemies[i].setRegBool(false);
			}
		}
		if (enemies->enemies[i].getPosition().x >= window->getSize().x / 2) {
			if (!enemies->enemies[i].getRegBool()) {
				xMovement *= -1;
			}
		}
		else if (enemies->enemies[i].getPosition().x <= window->getSize().x / 2) {
			if (!enemies->enemies[i].getRegBool()) {
				xMovement *= -1;
			}
		}

		enemies->enemies[i].move(xMovement, yMovement);
		if (isOutOfBoundsY(enemies->enemies[i].getSprite(), *window)) {
			enemies->enemies.deInitialize(i);
		}
	}
}

inline void Game::Game::Phase4() {
	auto newEnemy = std::make_unique<Character>(enemies->enemy);

	if (miscInfo->macroPhase == 2) {
		enemies->enemyTime = milliseconds(300);
	}
	else if (miscInfo->macroPhase == 3) {
		enemies->enemyTime = milliseconds(200);
	}
	else {
		enemies->enemyTime = milliseconds(100);
	}
	if (enemies->enemyClock.getElapsedTime().asMilliseconds() > enemies->enemyTime.asMilliseconds()) {
		enemies->enemyClock.restart();
		int xPos = rand() % window->getSize().x;
		int yPos = rand() % window->getSize().y;

		newEnemy->setPosition((float)xPos, (float)yPos);
		enemies->enemies.initialize(Character(*newEnemy));

	}

	for (size_t i = 0; i < enemies->enemies.size(); i++) {
		float yMovement = 30.f;
		float xMovement = 0.f;

		if (miscInfo->macroPhase <= 2) {
			yMovement = 30.f;
		}
		else if (miscInfo->macroPhase == 3) {
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

		if (enemies->enemies[i].getPosition().y <= enemies->enemies[i].getHitBoxSize().y ||
			enemies->enemies[i].getPosition().y + enemies->enemies[i].getHitBoxSize().y > window->getSize().y) {

			if (!enemies->enemies[i].getRegBool()) {
				enemies->enemies[i].setRegBool(true);
			}
			else {
				enemies->enemies[i].setRegBool(false);
				if (miscInfo->macroPhase <= 2) {
					enemies->enemies[i].setRegBool(true);
				}
			}
		}

		if (enemies->enemies[i].getRegBool()) {
			yMovement *= -1;
		}

		enemies->enemies[i].move(xMovement, yMovement);

		if (isOutOfBoundsX(enemies->enemies[i].getSprite(), *window) || isOutOfBoundsY(enemies->enemies[i].getSprite(), *window)
			|| enemies->enemies.size() > 250) {
			enemies->enemies.deInitialize(i);

		}
	}
}

inline void Game::Game::Phase5() {
	auto newEnemy = std::make_unique<Character>(enemies->enemy);
	if (miscInfo->macroPhase == 1) {
		enemies->enemyTime = milliseconds(1000);

	}
	else if (miscInfo->macroPhase == 2) {
		enemies->enemyTime = milliseconds(1000);

	}
	else if (miscInfo->macroPhase == 3) {
		enemies->enemyTime = milliseconds(600);
	}
	else {
		enemies->enemyTime = milliseconds(300);

	}
	if (enemies->enemyClock.getElapsedTime().asMilliseconds() > enemies->enemyTime.asMilliseconds()) {
		enemies->enemyClock.restart();
		int xPos = rand() % window->getSize().x;
		int yPos = rand() % window->getSize().y;

		enemies->enemy.setPosition((float)xPos, (float)yPos);
		enemies->enemies.initialize(*newEnemy);
	}
	for (size_t i = 0; i < enemies->enemies.size(); i++) {

		if (!enemies->enemies[i].getRegBool()) {
			enemies->enemies[i].setRegBool(true);
			Vector2f movement = getVectors(player->player.getPosition(), enemies->enemies[i].getCenter());
			enemies->enemies[i].move(movement.x * 30.f, movement.y * 30.f);
		}
		else {
			enemies->enemies[i].move();
		}
		if (isOutOfBoundsX(enemies->enemies[i].getSprite(), *window) || isOutOfBoundsY(enemies->enemies[i].getSprite(), *window)
			|| enemies->enemies.size() > 250) {
			enemies->enemies.deInitialize(i);
		}
	}
}

void Game::Game::collisionAndDamage(){
	for (size_t i = 0; i < enemies->enemies.size(); i++) {
		for (size_t j = 0; j < bullets->bullets.size(); j++) {

			if (bullets->bullets[j].collision(enemies->enemies[i]) && enemies->enemies[i].getHealth() > 0) {
				bullets->bullets.erase(bullets->bullets.begin() + j);

				enemies->enemies[i].damage(100.f);
				enemies->phantomEnemy.loadSound(100, SoundPaths::asteroidDestroyed);
				miscInfo->enemiesDestroyed++;
				if (miscInfo->enemiesDestroyed > miscInfo->highEnemiesDestroyed) {
					miscInfo->highEnemiesDestroyed++;
				}
				break;
			}
		}
	}
	for (size_t i = 0; i < enemies->enemies.size(); i++) {
		if (enemies->enemies[i].collision(player->player) && enemies->enemies[i].getHealth() > 0.f) {

			enemies->enemies[i].damage(100.f);
			player->player.damage(10.f);
			player->player.loadSound(1000, SoundPaths::playerHit);

			if (player->player.getHealth() <= 0) {
				player->player.loadSound(1000, SoundPaths::playerDead);
			}
		}
	}

	//Collision animation
	if (!player->player.getIsDead()) {
		player->player.animate1(player->hitCounter, 4, "Sprites/Ship/Main Ship/Main Ship - Design/Main Ship - Fighter Design", ".tga", player->player.getIsDead());
	}
	else {
		player->player.loadTexture(SpritePaths::playerShip);
	}


	for (size_t i = 0; i < enemies->enemies.size(); i++) {
		if (enemies->enemies[i].getHealth() <= 0.f) {
			if (!enemies->enemies[i].getIsDead()) {
				enemies->enemies[i].animate2(Vector2i(0, 768), Vector2i(0, 0), Vector2i(95, 1), enemies->enemies[i].getIsDead());
			}
			else {
				enemies->enemies.deInitialize(i);
			}
		}
	}
}

inline void Game::Game::updateScreen() {
	window->clear(Color(46, 34, 47));

	if (!miscInfo->lose) {
		for (size_t i = 0; i < bullets->bullets.size(); i++) {
			bullets->bullets[i].drawTo(*window);

		}
		for (size_t i = 0; i < enemies->enemies.size(); i++) {
			enemies->enemies[i].drawTo(*window);

		}

		player->player.drawTo(*window);
		window->draw(display->uiText);
		window->draw(display->redRect);
		window->draw(display->greenRect);

		if (!music->music1) {
			music->music1 = true;
			loadMusic(music->music, 75.f, MusicPaths::revolution);
		}
		else if (!music->music2 && !music->music3 && music->music1 && miscInfo->survivedPhases > 5) {
			music->music2 = true;
			loadMusic(music->music, 75.f, MusicPaths::badTime);
		}
		else if (!music->music3 && music->music2 && miscInfo->survivedPhases > 15) {
			music->music3 = true;
			loadMusic(music->music, 75.f, MusicPaths::encounter);
		}
		else if (music->music3 && music->music2 && music->music1 && miscInfo->survivedPhases >= 30) {
			music->music2 = false;
			loadMusic(music->music, 75.f, MusicPaths::reverbEnsemble);
		}
	}
	else {
		window->draw(display->loseText);
	}
	window->display();

}

void Game::Game::update() {
	while (window->isOpen()) {
		sf::Event anEvent;
		while (window->pollEvent(anEvent)) {
			switch (anEvent.type) {
			case Event::EventType::Closed:
				saveGame(miscInfo->highScore, miscInfo->highEnemiesDestroyed, "SaveState/SaveState.txt");
				window->close();
				break;
			}
			if (sf::Keyboard::isKeyPressed(Keyboard::Escape)) {
				anEvent.type = Event::Closed;
			}
		}
		displayBaseHUD();
		resetOnLose();
		playerMovement();

		phaseStartAndEnd();


		if (miscInfo->phaseStart && !miscInfo->lose) {
			switch (miscInfo->phase) {
			case 1:
				Phase1();
				break;
			case 2:
				Phase2();
				break;
			case 3:
				Phase3();
				break;
			case 4:
				Phase4();
				break;
			case 5:
				Phase5();
				break;

			}
		}

		bulletSpawn();
		collisionAndDamage();


		updateScreen();
	}

}

