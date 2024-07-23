#ifndef SHIP_H

#define SHIP_H

#include "CharacterContainer.h"

namespace Game {
	class Ship : virtual public Character {
	private:
		std::vector<Sprite> addSprites;
		std::vector<Texture> addTextures;
		std::vector<IntRect> addTextRects;

		bool isPlayer = true;

	public:
		Ship();
		Ship(std::string aPath, float aHealth, bool aPlayer, float hitBoxFactor);
		Ship(std::string aPath, float aHealth, Vector2f aPosition, bool aPlayer, float hitBoxFactor);

		void addSprite(std::string path, IntRect aTextRect);
		void addSprite(std::string path);

		void setWindow(RenderWindow* aWindow);

		void setPosition(float aXPosition, float aYPosition);
		void setPlayer(bool aPlayer);

		std::vector<Sprite>& getAddSprites();
		std::vector<IntRect>& getAddTextRects();

		void setRotation(float angle);


		bool getPlayer();

		//Movement
		void move(float xMovement, float yMovement);

		bool moveRight(const RenderWindow& window);
		bool moveLeft(const RenderWindow& window);
		bool moveUp(const RenderWindow& window);
		bool moveDown(const RenderWindow& window);


		void drawTo(RenderWindow& window);


	};


}
#endif