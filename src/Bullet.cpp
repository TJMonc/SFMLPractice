
#include "Bullet.h"


Game::Bullet::Bullet(Ship* aSource, RenderWindow* aWindow) {
	setSource(aSource);
	this->shape.setSize(Vector2f(10.f, 10.f));
	this->shape.setPosition(aSource->getCenter());
	this->shape.setFillColor(Color::Red);
	this->setWindow(aWindow);


}

void Game::Bullet::setSource(Ship* aSource) {
	this->source = aSource;
}

Transformable& Game::Bullet::getShape() {

	return this->shape;
}


void Game::Bullet::setWindow(RenderWindow* aWindow) {
	this->window = aWindow;
	Vector2f bulletScale = Vector2f(window->getSize()) / Vector2f RES_1080;
	shape.scale(bulletScale);
}

void Game::Bullet::move(Character& aSource, float mFactor) {
	if (this->moveClock.getElapsedTime().asMilliseconds() > this->moveTime.asMilliseconds()) {
		if (!this->shot) {

			this->xDirection = getVectors(aSource.getHitBox(), aSource.getCenter()).x * mFactor;
			this->yDirection = getVectors(aSource.getHitBox(), aSource.getCenter()).y * mFactor;
			Vector2f realMove = Vector2f(window->getSize()) / Vector2f(RES_1080_X / xDirection, RES_1080_Y / yDirection);

			this->shape.move(realMove);

			this->shot = true;
		}
		else {
			Vector2f realMove = Vector2f(window->getSize()) / Vector2f(RES_1080_X / xDirection, RES_1080_Y / yDirection);

			this->shape.move(realMove);

		}
	}



}

bool Game::Bullet::collision(Character& aShape) {
	if (aShape.getSprite().getGlobalBounds().intersects(shape.getGlobalBounds()) && aShape.getInitialized()) {

		return true;
	}
	else {
		return false;
	}
}

void Game::Bullet::drawTo(RenderWindow& window) {
	window.draw(shape);
}