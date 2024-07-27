#ifndef HEADER_CPP
#define HEADER_CPP

#include "Character.h"

//Character superclass method def.
Game::Character::Character() {
	loadTexture(SpritePaths::asteroid);
	setPosition(0.f, 0.f);
	setRegBool(false);
	setIsDead(false);
	setMaxHealth(100.f);
	setHealth(100.f);
	setInitialize(false);


	this->hitBoxMult = 0.5f;
	this->hitBox.setSize(this->getSize() * hitBoxMult);
	this->hitBox.setOrigin(hitBox.getSize() / 2.f);

	
}

Game::Character::Character(const std::string aPath, float aHealth, Vector2f aPosition, float hitBoxFactor, bool init) {

	loadTexture(aPath);
	setPosition(aPosition.x, aPosition.y);
	setHealth(aHealth);
	setMaxHealth(aHealth);
	setRegBool(false);
	setIsDead(false);
	setInitialize(init);
	this->hitBoxMult = hitBoxFactor;
	this->hitBox.setSize(this->getSize() * hitBoxMult);
	this->hitBox.setOrigin(hitBox.getSize() / 2.f);

}

void Game::Character::loadTexture(std::string path) {

	loadSprite(this->texture, path);
	this->sprite.setTexture(texture);
	this->sprite.setOrigin(this->getSize() / 2.f);



}

void Game::Character::setWindow(RenderWindow* aWindow) {
	this->window = aWindow;
	this->sprite.scale(Vector2f(window->getSize()) / Vector2f RES_1080);
}

void Game::Character::drawTo(RenderWindow& aWindow) {
	if (isInitialized) {
		aWindow.draw(this->sprite);
	}
	
}

void Game::Character::setPosition(float aXPosition, float aYPosition) {
	this->xPosition = aXPosition;
	this->yPosition = aYPosition;

	this->sprite.setPosition(xPosition, yPosition);
	this->hitBox.setPosition(this->sprite.getPosition());
}

void Game::Character::setHealth(float aHealth) {
	if (isInitialized) {
		if (aHealth < 0) {
			aHealth = 0;
		}
		this->health = aHealth;
	}
}

void Game::Character::setMaxHealth(float aHealth) {
	if (isInitialized) {
		this->maxHealth = aHealth;
	}
}


void Game::Character::damage(float subtraction) {
	if (isInitialized) {

		if (this->inClock.getElapsedTime().asSeconds() > this->inTime.asSeconds()) {

			if ((this->health - subtraction) > 0.f) {
				this->health -= subtraction;
			}
			else {
				this->health = 0;

			}
			this->isDead = false;
			inClock.restart();
		}
	}
}

void Game::Character::heal(float addition) {
	if (isInitialized) {

		if ((this->health + addition) < this->maxHealth) {
			this->health += addition;
		}
		else {
			this->health = 100;
		}
	}
}


void Game::Character::setTextRect(IntRect aTextRect) {
	if (aTextRect.left < 0 || aTextRect.top < 0) {
		throw("No");
	}
	else {
		this->sprite.setTextureRect(aTextRect);
		this->sprite.setOrigin(getSize() / 2.f);
		this->hitBox.setSize(this->getSize() * hitBoxMult);
		this->hitBox.setOrigin(this->hitBox.getSize() / 2.f);
		this->hitBox.setPosition(this->sprite.getPosition());


	}

}

void Game::Character::setIsDead(bool aIsDead) {
	this->isDead = aIsDead;
}

void Game::Character::setRegBool(bool aRegBool) {
	if (isInitialized) {

		this->regBool = aRegBool;
	}
}



void Game::Character::move(float aXMovement, float aYMovement) {
	this->xMovement = aXMovement;
	this->yMovement = aYMovement;
	if (isInitialized) {
		Vector2f realMove = Vector2f(window->getSize()) / Vector2f(RES_1080_X, RES_1080_Y);
		realMove = realMove * Vector2f{xMovement, yMovement};
		this->sprite.move(realMove * 0.5f);
		this->hitBox.setPosition(this->sprite.getPosition());

		return;
	}
}

void Game::Character::move(Vector2f movement) {
	this->move(movement.x, movement.y);
}

void Game::Character::move() {
	if (isInitialized) {
		Vector2f realMove = Vector2f(window->getSize()) / Vector2f(RES_1080_X, RES_1080_Y);
		realMove = realMove * Vector2f(xMovement, yMovement);
		this->sprite.move(realMove * 0.5f);
		this->hitBox.setPosition(this->sprite.getPosition());
	}
}

void Game::Character::xMove(float aXMove) {
	if (isInitialized) {

		this->xMovement = aXMove;

		this->move(this->xMovement, this->yMovement);
	}
}

void Game::Character::yMove(float aYMove) {
	if (isInitialized) {

		this->yMovement = aYMove;
		this->move(xMovement, yMovement);
	}
}

Vector2f Game::Character::getMovement() {

	return Vector2f(this->xMovement, this->yMovement);
}

Vector2f Game::Character::getPosition() {
	this->xPosition = this->sprite.getPosition().x;
	this->yPosition = this->sprite.getPosition().y;
	return Vector2f(xPosition, yPosition);
}

Vector2f Game::Character::getCenter() {

	return Vector2f(this->sprite.getPosition().x, this->sprite.getPosition().y);
}

float Game::Character::getHealth() {

	return this->health;
}

Sprite& Game::Character::getSprite() {

	return this->sprite;
}

bool& Game::Character::getIsDead(){

	return this->isDead;
}

float Game::Character::getRotation(){

	return this->sprite.getRotation();
}

IntRect* Game::Character::getTextRect() {

	return &this->textRect;
}

bool& Game::Character::getRegBool() {

	return this->regBool;
}

Vector2f Game::Character::getSize() {

	return this->sprite.getGlobalBounds().getSize();
};

RectangleShape& Game::Character::getHitBox() {
	return this->hitBox;
}



void Game::Character::animate1(int& counter, int max, std::string genPath, std::string extension, bool& isAnimating) {
	if (isInitialized) {

		if (aniClock.getElapsedTime().asMilliseconds() > aniTime.asMilliseconds() || !isDead) {

			if (counter < max) {
				this->loadTexture(genPath + std::to_string(counter) + extension);
				counter++;
			}
			else {
				counter = 1;
				this->isDead = true;
				aniClock.restart();

			}
		}
	}
	
}

void Game::Character::animate2(Vector2i xLimits, Vector2i yLimits, Vector2i components, bool& isAnimating) {
	if (isInitialized) {

		sf::IntRect dimensions = sprite.getTextureRect();

		if (aniClock.getElapsedTime().asMilliseconds() > aniTime.asMilliseconds()) {

			if (dimensions.top == yLimits.x) {

				if (dimensions.left != xLimits.y) {
					dimensions.left += components.x;
				}
				else {
					dimensions.top += components.y;
					dimensions.left = xLimits.x;
					this->isDead = true;
					aniClock.restart();
				}

			}
			else if (dimensions.top <= yLimits.y) {

				if (dimensions.left != xLimits.y) {
					dimensions.left += components.x;
				}
				else {
					dimensions.top -= components.y;
					dimensions.left = xLimits.x;

				}

			}
			else {
				dimensions.left = xLimits.x;
				dimensions.top = yLimits.x;

			}


			aniClock.restart();

		}

		sprite.setTextureRect(dimensions);
		sprite.setOrigin(getSize() / 2.f);
		this->hitBox.setOrigin(this->hitBox.getSize() / 2.f);
		this->hitBox.setPosition(this->sprite.getPosition());

	}
}

void Game::Character::animate2(Sprite& aSprite, Vector2i xLimits, Vector2i yLimits, Vector2i components, bool& isAnimating) {
	if (isInitialized) {

		sf::IntRect dimensions = aSprite.getTextureRect();

		if (aniClock.getElapsedTime().asMilliseconds() > aniTime.asMilliseconds()) {

			if (dimensions.top == yLimits.x) {

				if (dimensions.left != xLimits.y) {
					dimensions.left += components.x;
				}
				else {
					dimensions.top += components.y;
					dimensions.left = xLimits.x;
					this->isDead = true;
					aniClock.restart();
				}

			}
			else if (dimensions.top <= yLimits.y) {

				if (dimensions.left != xLimits.y) {
					dimensions.left += components.x;
				}
				else {
					dimensions.top -= components.y;
					dimensions.left = xLimits.x;

				}

			}
			else {
				dimensions.left = xLimits.x;
				dimensions.top = yLimits.x;

			}


			aniClock.restart();
		}

		aSprite.setTextureRect(dimensions);
		aSprite.setOrigin(getSize() / 2.f);
		this->hitBox.setOrigin(this->hitBox.getSize() / 2.f);
		this->hitBox.setPosition(this->sprite.getPosition());
	}
}



bool Game::Character::collision(Character& shape) {
	if (isInitialized) {

		if (this->hitBox.getGlobalBounds().intersects(shape.getHitBox().getGlobalBounds()) &&
			this->inClock.getElapsedTime().asMilliseconds() > this->inTime.asMilliseconds()) {

			inClock.restart();

			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

void Game::Character::loadSound(std::string path) {

	Game::loadSound(this->sound, this->soundBuffer, path);

}

void Game::Character::loadSound(int aMilliseconds, std::string path) {

	this->soundTime = milliseconds(aMilliseconds);
	Game::loadSound(this->soundClock, this->soundTime, this->sound, this->soundBuffer, path);
}

void Game::Character::setInitialize(bool aInit) {
	this->isInitialized = aInit;
}
bool Game::Character::getInitialized() {
	return this->isInitialized;
}



#endif