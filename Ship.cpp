#include "Ship.h"

//Ship derived class method def.

Game::Ship::Ship() :Character() {

}
Game::Ship::Ship(std::string aPath, float aHealth, bool aPlayer, float hitBoxFactor) :	//Constructor
	Game::Character::Character(aPath, aHealth, Vector2f(500.f, 500.f), hitBoxFactor, true) {

	setPlayer(aPlayer);



}

Game::Ship::Ship(std::string aPath, float aHealth, Vector2f aPosition, bool aPlayer, float hitBoxFactor) :	//Constructor
	Game::Character::Character(aPath, aHealth, aPosition, hitBoxFactor, true) {

	setPlayer(aPlayer);



}

void Game::Ship::addSprite(std::string path, IntRect aTextRect) {	//All ships will have at least 1 additional sprite because the main ship and the thrusters are different textures.
	Sprite* newSprite = new Sprite;
	Texture* newText = new Texture;

	newSprite->setPosition(this->sprite.getPosition());

	loadSprite(*newText, path);
	newSprite->setTexture(*newText);
	newSprite->setTextureRect(aTextRect);
	newSprite->setOrigin(newSprite->getGlobalBounds().getSize() / 2.f);


	newSprite->setPosition(this->sprite.getPosition());
	newSprite->setRotation(this->sprite.getRotation());

	this->addTextures.push_back(*newText);
	this->addSprites.push_back(*newSprite);
	this->addTextRects.push_back(aTextRect);

	delete newSprite, newText;
}

void Game::Ship::addSprite(std::string path) {	//Adds a sprite, texture, and texture rect for member vectors.
	Sprite* newSprite = new Sprite;
	Texture* newText = new Texture;
	IntRect* newTextRect = new IntRect(0, 0, 0, 0);


	loadSprite(*newText, path);
	newSprite->setTexture(*newText);
	newSprite->setTextureRect(*newTextRect);

	newSprite->setOrigin(newSprite->getGlobalBounds().getSize() / 2.f);

	newSprite->setPosition(this->sprite.getPosition());
	newSprite->setRotation(this->sprite.getRotation());



	this->addTextures.push_back(*newText);
	this->addSprites.push_back(*newSprite);
	this->addTextRects.push_back(*newTextRect);


	delete newSprite, newText, newTextRect;
}

void Game::Ship::setPosition(float aXPosition, float aYPosition) {
	xPosition = aXPosition;
	yPosition = aYPosition;

	this->setPosition(xPosition, yPosition);

	for (size_t i = 0; i < this->addSprites.size(); i++) {
		this->addSprites[i].setPosition(this->sprite.getPosition());
	}

}

void Game::Ship::setWindow(RenderWindow* aWindow) {
	this->window = aWindow;
	Vector2f windowScale = Vector2f(window->getSize()) / Vector2f RES_1080;
	this->sprite.scale(windowScale);

	for (int i = 0; i < addSprites.size(); i++) {
		addSprites[i].scale(windowScale);
	}
}


void Game::Ship::setPlayer(bool aPlayer) {
	this->isPlayer = aPlayer;
}

std::vector<Sprite>& Game::Ship::getAddSprites() {	//Gets the member vector 'addSprites'

	return this->addSprites;
}

std::vector<IntRect>& Game::Ship::getAddTextRects() {

	return this->addTextRects;
}

void Game::Ship::setRotation(float angle) {

	this->sprite.setRotation(angle);
	this->hitBox.setRotation(angle);

	for (size_t i = 0; i < this->addSprites.size(); i++) {
		this->addSprites[i].setPosition(this->sprite.getPosition());
		this->addSprites[i].setRotation(this->sprite.getRotation());

	}

}

bool Game::Ship::getPlayer() {
	return this->isPlayer;
}

void Game::Ship::move(float axMovement, float ayMovement) {
	this->xMovement = axMovement;
	this->yMovement = ayMovement;
	Vector2f realMove = Vector2f(window->getSize()) / Vector2f(RES_1080_X / xMovement, RES_1080_Y / yMovement);

	
	this->sprite.move(realMove * 0.5f);


}

bool Game::Ship::moveRight(const RenderWindow& window) {
	if (window.getSize().x > this->sprite.getPosition().x + this->sprite.getGlobalBounds().getSize().x) {
		if (this->isPlayer) {
			if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
				this->move(15.f, 0.f);

				for (size_t i = 0; i < this->addSprites.size(); i++) {
					this->addSprites[i].setPosition(this->sprite.getPosition());
				}
				return true;


			}
			else {
				return false;
			}
		}
		else {
			this->move(15.f, 0.f);
			for (size_t i = 0; i < this->addSprites.size(); i++) {
				this->addSprites[i].setPosition(this->sprite.getPosition());
			}


		}
	}
	return false;
}
bool Game::Ship::moveLeft(const RenderWindow& window) {

	if (this->sprite.getGlobalBounds().getPosition().x > 0) {
		if (this->isPlayer) {

			if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
				this->move(-15.f, 0.f);
				for (size_t i = 0; i < this->addSprites.size(); i++) {
					this->addSprites[i].setPosition(this->sprite.getPosition());
				}

				return true;
			}
			else {


				return false;
			}
		}
		else {

			this->move(-15.f, 0.f);

			for (size_t i = 0; i < this->addSprites.size(); i++) {
				this->addSprites[i].setPosition(this->sprite.getPosition());
			}
		}

	}
	return true;

}
bool Game::Ship::moveUp(const RenderWindow& window) {
	if (this->sprite.getGlobalBounds().getPosition().y > 0) {
		if (this->isPlayer) {
			if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
				this->move(0.f, -15.f);

				for (size_t i = 0; i < this->addSprites.size(); i++) {
					this->addSprites[i].setPosition(this->sprite.getPosition());
				}

				return true;
			}
			else {
				return false;
			}
		}
		else {
			this->move(0.f, -15.f);

			for (size_t i = 0; i < this->addSprites.size(); i++) {
				this->addSprites[i].setPosition(this->sprite.getPosition());
			}

			return true;
		}

	}
	return false;
}
bool Game::Ship::moveDown(const RenderWindow& window) {

	if (window.getSize().y > this->sprite.getPosition().y + this->sprite.getGlobalBounds().getSize().y) {
		if (this->isPlayer) {

			if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
				this->move(0.f, 15.f);

				for (size_t i = 0; i < this->addSprites.size(); i++) {
					this->addSprites[i].setPosition(this->sprite.getPosition());
				}
				return true;

			}
			else {
				return false;
			}
		}

		else {

			this->move(0.f, 15.f);

			for (size_t i = 0; i < this->addSprites.size(); i++) {
				this->addSprites[i].setPosition(this->sprite.getPosition());
			}
			return true;
		}

	}

	return true;
}

void Game::Ship::drawTo(RenderWindow& window) {
	window.draw(this->sprite);
	for (size_t i = 0; i < this->addSprites.size(); i++) {
		window.draw(addSprites[i]);
	}
}