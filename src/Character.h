
#ifndef HEADER_H
#define HEADER_H

#define _USE_MATH_DEFINES
#include "Misc.h"

using namespace sf;
namespace Game {


class Character {
protected:
	RenderWindow* window;
	Sprite sprite;
	Texture texture;
	sf::IntRect textRect;	//Needed for animation2 function
	sf::RectangleShape hitBox;
	float health = 100.f;
	float maxHealth = 100.f;

	float xMovement, yMovement = 0.f;
	float xPosition, yPosition = 0.f;

	bool isDead = true;

	float hitBoxMult;

	bool regBool;

	Clock aniClock;
	Time aniTime = milliseconds(15);

	Clock inClock;
	Time inTime = seconds(0.5f);

	Sound sound;
	SoundBuffer soundBuffer;
	Clock soundClock;
	Time soundTime;

	bool isInitialized = false;
	
public:
	Character();

	Character(const std::string aPath, float aHealth, Vector2f aPosition, float hitBoxFactor, bool init);

	void loadTexture(std::string path);
	void setWindow(RenderWindow* window);

	void drawTo(RenderWindow& aWindow);

	void setPosition(float aXPosition, float aYPosition);
	void setHealth(float aHealth);
	void setMaxHealth(float aHealth);
	void damage(float subtraction);
	void heal(float addition);
	void setTextRect(IntRect aTextRect);
	void setIsDead(bool aIsDead);
	void setRegBool(bool aRegBool);


	void move(float aXMovement, float aYMovement);
	void move(Vector2f movement);
	void move();
	void xMove(float aXMove);
	void yMove(float aYMove);



	Vector2f getMovement();
	Vector2f getPosition();
	Vector2f getCenter();
	float getHealth();
	bool& getIsDead();
	float getRotation();
	IntRect* getTextRect();
	bool& getRegBool();
	Vector2f getSize();
	RectangleShape& getHitBox();
	Vector2f getHitBoxSize() {

		return hitBox.getSize();
	}


	Sprite& getSprite();


	void animate1(int& counter, int max, std::string genPath, std::string extension, bool& isAnimating);

	void animate2(Vector2i xLimits, Vector2i yLimits, Vector2i components, bool& isAnimating);

	void animate2(Sprite& aSprite, Vector2i xLimits, Vector2i yLimits, Vector2i components, bool& isAnimating);

	bool collision(Character& shape);

	void loadSound(std::string path);

	void loadSound(int milliseconds, std::string path);

	void setInitialize(bool aInit);
	bool getInitialized();
};







}
#endif