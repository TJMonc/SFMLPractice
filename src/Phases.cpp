#include "Phases.h"

Game::Phases::Phases(Game* aGame) {
	game = aGame;
}

void Game::Phases::phaseStartAndEnd() {
	if (!game->miscInfo->phaseStart) {
		if (game->miscInfo->survivedPhases < 3) {
			game->miscInfo->macroPhase = 1;
		}
		else if (game->miscInfo->survivedPhases < 15) {
			game->miscInfo->macroPhase = 2;
		}
		else if (game->miscInfo->survivedPhases < 30) {
			game->miscInfo->macroPhase = 3;
		}
		else {
			game->miscInfo->macroPhase = 4;
		}
		switch (game->miscInfo->macroPhase) {
		case 1:
			game->miscInfo->phase = rand() % 2 + 1;
			break;
		case 2:
			game->miscInfo->phase = rand() % 4 + 1;
			break;
		case 3:
			game->miscInfo->phase = rand() % 5 + 1;
			break;
		case 4:
			game->miscInfo->phase = rand() % 5 + 1;
			break;
		}
		game->miscInfo->phaseStart = true;
	}
	if (game->miscInfo->phaseStart && game->miscInfo->phaseClock.getElapsedTime().asSeconds() > game->miscInfo->phaseTime.asSeconds()) {
		game->miscInfo->phaseClock.restart();
		game->player->player.heal(10.f);
		game->miscInfo->survivedPhases++;
		for (int i = 0; i < game->enemies->enemies.size(); i++) {
			game->enemies->enemies[i]->damage(100.f);
		}
		game->miscInfo->phaseStart = false;
		if (game->miscInfo->survivedPhases > game->miscInfo->highScore) {
			game->miscInfo->highScore = game->miscInfo->survivedPhases;
		}
	}
}

void Game::Phases::Phase1() {
	auto newEnemy = std::make_unique<Character>(game->enemies->enemy);

	if (game->miscInfo->macroPhase == 1) {
		game->enemies->enemyTime = milliseconds(500);
	}
	else if (game->miscInfo->macroPhase == 2) {
		game->enemies->enemyTime = milliseconds(300);
	}
	else {
		game->enemies->enemyTime = milliseconds(100);
	}
	if (game->enemies->enemyClock.getElapsedTime().asMilliseconds() > game->enemies->enemyTime.asMilliseconds()) {

		game->enemies->enemyClock.restart();

		float xPos = rand() % game->window->getSize().x - newEnemy->getSprite().getGlobalBounds().getSize().x + 1.f;
		float yPos = 0.f;

		newEnemy->setPosition(xPos, yPos);
		game->enemies->enemies.push_back(std::make_unique<Character>(*newEnemy));
	}

	for (int i = 0; i < game->enemies->enemies.size(); i++) {
		if (game->miscInfo->macroPhase == 1) {
			game->enemies->enemies[i]->move(0, 30.f);
		}
		else if (game->miscInfo->macroPhase == 2) {
			game->enemies->enemies[i]->move(0, 45.f);
		}
		else {
			game->enemies->enemies[i]->move(15.f, 45.f);
		}
		if (isOutOfBoundsX(game->enemies->enemies[i]->getSprite(), *game->window) || isOutOfBoundsY(game->enemies->enemies[i]->getSprite(), *game->window)) {
			game->enemies->enemies.erase(game->enemies->enemies.begin() + i);
		}
	}
	return;
}

void Game::Phases::Phase2() {
	auto newEnemy = std::make_unique<Character>(game->enemies->enemy);

	float xPos = rand() % game->window->getSize().x;
	float yPos = 0.f;
	float xMovement;
	float yMovement;

	switch (game->miscInfo->macroPhase) {
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
	if (newEnemy->getPosition().x <= game->window->getSize().x / 2) {
		newEnemy->move(xMovement, yMovement);
	}
	else {
		newEnemy->move(-1 * xMovement, yMovement);
	}
	game->enemies->enemies.push_back(std::make_unique<Character>(*newEnemy));
	game->enemies->enemyClock.restart();


	for (int i = 0; i < game->enemies->enemies.size(); i++) {
		//float xMovement;
		//float yMovement;

		game->enemies->enemies[i]->move(game->enemies->enemies[i]->getMovement().x, game->enemies->enemies[i]->getMovement().y);

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
		//if (enemies[i]->getPosition().x <= window.getSize().x / 2) {
		//	if (enemies[i]->getMovement().x < 0) {
		//		enemies[i]->setRegBool(false);
		//	}
		//	else {
		//		enemies[i]->setRegBool(false);
		//	}
		//}
		//else if (enemies[i]->getPosition().x >= window.getSize().x / 2) {
		//	if (enemies[i]->getMovement().x > 0) {
		//		enemies[i]->setRegBool(false);
		//	}
		//	else {
		//		enemies[i]->setRegBool(false);
		//	}
		//}


		//if (enemies[i]->getPosition().x < window.getSize().x / 2) {
		//	if (!enemies[i]->getRegBool()) {
		//		enemies[i]->move(xMovement, yMovement);
		//	}
		//	else {
		//		enemies[i]->move(-1 * xMovement, yMovement);
		//	}

		//}
		//else if (enemies[i]->getPosition().x >= window.getSize().x / 2) {
		//	if (!enemies[i]->getRegBool()) {
		//		enemies[i]->move(-1 * xMovement, yMovement);
		//	}
		//	else {
		//		enemies[i]->move(xMovement, yMovement);
		//	}
		//}


		if (isOutOfBoundsX(game->enemies->enemies[i]->getSprite(), *game->window) || isOutOfBoundsY(game->enemies->enemies[i]->getSprite(), *game->window)) {
			game->enemies->enemies.erase(game->enemies->enemies.begin() + i);
		}
	}
}

void Game::Phases::Phase3() {
	auto newEnemy = std::make_unique<Character>(game->enemies->enemy);

	if (game->miscInfo->macroPhase == 1) {
		game->enemies->enemyTime = milliseconds(100);
	}
	else if (game->miscInfo->macroPhase == 2) {
		game->enemies->enemyTime = milliseconds(70);
	}
	else {
		game->enemies->enemyTime = milliseconds(50);
	}
	if (game->enemies->enemyClock.getElapsedTime().asMilliseconds() > game->enemies->enemyTime.asMilliseconds()) {
		game->enemies->enemyClock.restart();
		int randNum = rand() % 2;
		float xPos;
		float yPos = 1.f;

		switch (randNum) {
		case 0:
			xPos = 0.f;
			if (game->miscInfo->macroPhase >= 3) {
				xPos = rand() % game->window->getSize().x / 5.f;
			}
			break;
		case 1:
			xPos = rand() % (game->window->getSize().x) - newEnemy->getSize().x - 1.f;
			if (game->miscInfo->macroPhase >= 3) {
				xPos = rand() % game->window->getSize().x * 4.f / 5.f - newEnemy->getSize().x - 1.f;
			}
			break;
		}
		switch (game->miscInfo->macroPhase) {
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
			yPos = rand() % game->window->getSize().y / 10.f;
			break;
		case 4:
			yPos = rand() % game->window->getSize().y / 5.f;
		}
		game->enemies->enemy.setPosition(xPos, yPos);
		game->enemies->enemies.push_back(std::make_unique<Character>(*newEnemy));
	}
	for (int i = 0; i < game->enemies->enemies.size(); i++) {

		float xMovement = 50.f;
		float yMovement;

		if (game->miscInfo->macroPhase == 1) {
			yMovement = 10.f;
		}
		else if (game->miscInfo->macroPhase == 2) {
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
		if (game->enemies->enemies[i]->getPosition().x >= game->window->getSize().x - game->enemies->enemies[i]->getSize().x || game->enemies->enemies[i]->getPosition().x <= 0) {
			if (!game->enemies->enemies[i]->getRegBool()) {
				game->enemies->enemies[i]->setRegBool(true);
			}
			else {
				game->enemies->enemies[i]->setRegBool(false);
			}
		}
		if (game->enemies->enemies[i]->getPosition().x >= game->window->getSize().x / 2) {
			if (!game->enemies->enemies[i]->getRegBool()) {
				xMovement *= -1;
			}
		}
		else if (game->enemies->enemies[i]->getPosition().x <= game->window->getSize().x / 2) {
			if (!game->enemies->enemies[i]->getRegBool()) {
				xMovement *= -1;
			}
		}
		game->enemies->enemies[i]->move(xMovement, yMovement);
		if (isOutOfBoundsY(game->enemies->enemies[i]->getSprite(), *game->window)) {
			game->enemies->enemies.erase(game->enemies->enemies.begin() + i);
		}
	}
}

void Game::Phases::Phase4() {
	auto newEnemy = std::make_unique<Character>(game->enemies->enemy);

	if (game->miscInfo->macroPhase == 2) {
		game->enemies->enemyTime = milliseconds(300);
	}
	else if (game->miscInfo->macroPhase == 3) {
		game->enemies->enemyTime = milliseconds(200);
	}
	else {
		game->enemies->enemyTime = milliseconds(100);
	}
	if (game->enemies->enemyClock.getElapsedTime().asMilliseconds() > game->enemies->enemyTime.asMilliseconds()) {
		game->enemies->enemyClock.restart();
		float xPos = rand() % game->window->getSize().x;
		float yPos = rand() % game->window->getSize().y;

		game->enemies->enemy.setPosition(xPos, yPos);
		game->enemies->enemies.push_back(std::make_unique<Character>(*newEnemy));

	}

	for (int i = 0; i < game->enemies->enemies.size(); i++) {
		float yMovement = 30.f;
		float xMovement = 0.f;

		if (game->miscInfo->macroPhase <= 2) {
			yMovement = 30.f;
		}
		else if (game->miscInfo->macroPhase == 3) {
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

		if (game->enemies->enemies[i]->getPosition().y < 0 ||
			game->enemies->enemies[i]->getPosition().y + game->enemies->enemies[i]->getHitBoxSize().y > game->window->getSize().y) {

			if (!game->enemies->enemies[i]->getRegBool()) {
				game->enemies->enemies[i]->setRegBool(true);
			}
			else {
				game->enemies->enemies[i]->setRegBool(false);
				if (game->miscInfo->macroPhase <= 2) {
					game->enemies->enemies[i]->setRegBool(true);
				}
			}
		}

		if (game->enemies->enemies[i]->getRegBool()) {
			yMovement *= -1;
		}

		game->enemies->enemies[i]->move(xMovement, yMovement);

		if (isOutOfBoundsX(game->enemies->enemies[i]->getSprite(), *game->window) || isOutOfBoundsY(game->enemies->enemies[i]->getSprite(), *game->window)
			|| game->enemies->enemies.size() > 250) {
			game->enemies->enemies.erase(game->enemies->enemies.begin() + i);

		}
	}
}

void Game::Phases::Phase5() {
	auto newEnemy = std::make_unique<Character>(game->enemies->enemy);
		if (game->miscInfo->macroPhase == 1) {
			game->enemies->enemyTime = milliseconds(1000);

		}
		else if (game->miscInfo->macroPhase == 2) {
			game->enemies->enemyTime = milliseconds(1000);

		}
		else if (game->miscInfo->macroPhase == 3) {
			game->enemies->enemyTime = milliseconds(600);
		}
		else {
			game->enemies->enemyTime = milliseconds(300);

		}
	if (game->enemies->enemyClock.getElapsedTime().asMilliseconds() > game->enemies->enemyTime.asMilliseconds()) {
		game->enemies->enemyClock.restart();
		float xPos = rand() % game->window->getSize().x;
		float yPos = rand() % game->window->getSize().y;

		game->enemies->enemy.setPosition(xPos, yPos);
		game->enemies->enemies.push_back(std::make_unique<Character>(*newEnemy));
	}
	for (int i = 0; i < game->enemies->enemies.size(); i++) {

		if (!game->enemies->enemies[i]->getRegBool()) {
			game->enemies->enemies[i]->setRegBool(true);
			Vector2f movement = getVectors(game->player->player.getPosition(), game->enemies->enemies[i]->getCenter());
			game->enemies->enemies[i]->move(movement.x * 30.f, movement.y * 30.f);
		}
		else {
			game->enemies->enemies[i]->move();
		}
		if (isOutOfBoundsX(game->enemies->enemies[i]->getSprite(), *game->window) || isOutOfBoundsY(game->enemies->enemies[i]->getSprite(), *game->window)
			|| game->enemies->enemies.size() > 250) {
			game->enemies->enemies.erase(game->enemies->enemies.begin() + i);
		}
	}
}
