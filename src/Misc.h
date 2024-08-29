#ifndef MISC_H
#define MISC_H

#define _USE_MATH_DEFINES
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <memory>
#include <thread>
#include <vector>
#include <array>
#include <unordered_map>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>


#define RES_1080 (1920, 1080)
#define RES_1080_X (1920)
#define RES_1080_Y (1080)

#define RES_768 (1366, 768)
#define RES_768_X (1366)
#define RES_768_Y (768)

using namespace sf;


class FileError :public std::exception {
private:
	std::string* filePath = nullptr;
public:
	FileError(std::string aMessage) {
		this->filePath = new std::string(aMessage + " could not be loaded");
	}
	const char* what() {

		return filePath->c_str();
	}

	~FileError() {
		if (filePath != nullptr) {
			delete filePath;
		}
	}
};


Vector2f operator*(float mult, Vector2f vector);
Vector2f operator/(float mult, Vector2f vector);

Vector2f operator*(Vector2f vect1, Vector2f vect2);
Vector2f operator/(Vector2f vect1, Vector2f vect2);

std::unique_ptr<std::ifstream> openReadFile(const std::string filePath);

template <typename T> void write3dVectToFile(const std::string filePath, const std::vector<std::vector<T>>& aVector, const int aDivide);

namespace Game {

	//File Paths
	struct FontPaths {
		static std::string blackLivesFont;
		static std::string BrowoodFont;

	};

	struct SpritePaths {
		static std::string playerShip;
		static std::string asteroid;
		static std::string engine;
	};

	struct SoundPaths {
		static std::string playerHit;
		static std::string playerDead;
		static std::string asteroidDestroyed;
		static std::string bulletShot;

	};

	struct MusicPaths {
		static std::string revolution;
		static std::string badTime;
		static std::string encounter;
		static std::string reverbEnsemble;
	};

	//Gen functions

	bool isOutOfBoundsY(Transformable& shape, RenderWindow& window);	//Checks if a transformable object is outside the screen on the y axis
	bool isOutOfBoundsX(Transformable& shape, RenderWindow& window);	//Checks Checks if a transformable object is outside the screen on the x axis
	void loadSprite(sf::Texture& texture, std::string path);	//Loads a sprite based on a texture and directory path
	Vector2f getVectors(const Shape& player, const Vector2f playerCenter); // Gets unit x and y vector according to the cos/sin of the angle a shape is pointing.
	Vector2f getVectors(const Vector2f playerCenter, const Vector2f otherCenter); // Get unit vector between two objects

	void loadSound(sf::Sound& sound, sf::SoundBuffer& soundBuffer, std::string path); // Loads sound buffer
	void loadSound(Clock& clock, Time& time, sf::Sound& sound, sf::SoundBuffer& soundBuffer, std::string path);

	void loadFont(Text& text, Font& font, std::string path);

	void loadSave(int& aHighScore, int& aEnemyDestroy, std::string fileName);

	void saveGame(const int aHighScore, const int aEnemyDestroy, std::string fileName);

	void loadMusic(sf::Music& aMusic, float aVolume, std::string aPath);

}

#endif