#ifndef BULLET_H
#define BULLET_H

#include "Ship.h"

namespace Game {
	class Bullet {
	private:
		RectangleShape shape;
		Ship* source;
		RenderWindow* window;

		float xDirection = 0.f;
		float yDirection = 0.f;

		bool shot = false;

		Clock moveClock;
		Time moveTime = milliseconds(30);


	public:
		Bullet(Ship* aSource, RenderWindow* aWindow);

		void setWindow(RenderWindow* aWindow);
		void move(Character& aSource, float mFactor);

		void setSource(Ship* aSource);

		Transformable& getShape();



		bool collision(Character& aShape);

		void drawTo(RenderWindow& window);



	};


}
#endif