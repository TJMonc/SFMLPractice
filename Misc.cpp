
//TODO: Implement hitbox and change entire program(minus constructor) to accomodate it.
#include "Misc.h"



Vector2f operator*(float mult, Vector2f vector) {

	return Vector2f(mult * vector.x, mult * vector.y);
}

Vector2f operator/(float mult, Vector2f vector) {

	return Vector2f(mult / vector.x, mult / vector.y);
}

Vector2f operator*(Vector2f vect1, Vector2f vect2) {
	return Vector2f(vect1.x * vect2.x, vect1.y * vect2.y);
}

Vector2f operator/(Vector2f vect1, Vector2f vect2) {
	return Vector2f(vect1.x / vect2.x, vect1.y / vect2.y);

}
std::unique_ptr<std::ifstream>  openReadFile(const std::string filePath) {
	std::unique_ptr<std::ifstream> file = std::make_unique<std::ifstream>(filePath, std::ios::in);
	std::string fileLine;
	try {
		if (!file->is_open()) {
			throw FileError(filePath);
		}
	}
	catch (FileError& e) {
		std::cerr << e.what();
		throw FileError(filePath);
	}

	return file;
}

template <typename T> void write3dVectToFile(const std::string filePath, const std::vector<std::vector<T>>& aVector, const int aDivide) {
	std::ofstream ofile(filePath, std::ios::app);
	for (int i = 0; i < aVector.size(); i++) {
		if (i % aDivide == 0) {
			ofile << "\n";
		}
		for (int j = 0; j < aVector[i].size(); j++) {
			ofile << aVector[i][j];
			if (!(j == aVector[i].size() - 1)) {
				ofile << ",";
			}
		}
		ofile << "\n";

	}
	ofile.close();
}

//Gen Function def.
void Game::loadSprite(sf::Texture& texture, std::string path) {	//Condense the sprite checking and loading into one function.

	if (!texture.loadFromFile(path)) {
		std::cerr << "Could not load " + path << std::endl;
		throw FileError(path);
	}
}

void Game::loadSound(sf::Sound& sound, sf::SoundBuffer& soundBuffer, std::string path) {

	if (!soundBuffer.loadFromFile(path)) {
		std::cerr << "Could not load " + path << std::endl;
		throw FileError(path);
	}
	sound.setBuffer(soundBuffer);
	sound.play();
}

void Game::loadSound(Clock& clock, Time& time, sf::Sound& sound, sf::SoundBuffer& soundBuffer, std::string path) {
	if (clock.getElapsedTime().asMilliseconds() > time.asMilliseconds()) {
		if (!soundBuffer.loadFromFile(path)) {
			std::cerr << "Could not load " + path << std::endl;
			throw FileError(path);
		}
		sound.setBuffer(soundBuffer);
		clock.restart();
		sound.play();
	}
}

bool Game::isOutOfBoundsX(Transformable& shape, RenderWindow& window) {
	if (shape.getPosition().x < 0 || shape.getPosition().x > window.getSize().x) {
		return true;
	}
	else {
		return false;
	}
}

bool Game::isOutOfBoundsY(Transformable& shape, RenderWindow& window) {
	if (shape.getPosition().y < 0 || shape.getPosition().y > window.getSize().y) {
		return true;
	}
	else {
		return false;
	}
}

Vector2f Game::getVectors(const Shape& player, const Vector2f playerCenter) {
	float actualAngle = -1.f * (90.f - player.getRotation());
	float actualAngleRad = actualAngle * (float)M_PI / 180.f;

	float yComp = sinf(actualAngleRad);
	float xComp = cosf(actualAngleRad);



	return Vector2f(xComp, yComp);



}
Vector2f Game::getVectors(const Vector2f playerCenter, const Vector2f otherCenter) {
	float xVect = playerCenter.x - otherCenter.x;
	float yVect = playerCenter.y - otherCenter.y;



	float Mag = std::pow(pow(xVect, 2) + std::pow(yVect, 2), 0.5f);

	return Vector2f(xVect / Mag, yVect / Mag);
}

void Game::loadFont(Text& text, Font& font, std::string path) {
	if (!font.loadFromFile(path)) {
		throw FileError(path);
	}
	text.setFont(font);
}


void Game::loadSave(int& aHighScore, int& aEnemyDestroy, std::string fileName) {
	std::ifstream saveFile(fileName);
	std::string fileLine;


	std::string hs = "HighScore:";
	std::string ed = "EnemiesDestroyed:";

	if (!saveFile.is_open()) {
		throw FileError(fileName);
	}

	while (std::getline(saveFile, fileLine)) {
		if (fileLine.find(hs) != std::string::npos) {
			std::unique_ptr<std::string> scoreContainer(new std::string);

			for (size_t i = hs.size(); i < fileLine.size(); i++) {
				*scoreContainer += fileLine[i];
			}

			aHighScore = std::stoi(*scoreContainer);
			scoreContainer.release();

		}
		else if (fileLine.find(ed) != std::string::npos) {
			std::unique_ptr<std::string> scoreContainer(new std::string);

			for (size_t i = ed.size(); i < fileLine.size(); i++) {
				*scoreContainer += fileLine[i];
			}

			aEnemyDestroy = std::stoi(*scoreContainer);
			scoreContainer.release();

		}

		if (saveFile.eof()) {
			break;
		}

	}


	saveFile.close();
}

void Game::saveGame(const int aHighScore, const int aEnemyDestroy, std::string fileName) {
	std::remove(fileName.c_str());

	std::ofstream newSave(fileName);
	if (!newSave.is_open()) {
		throw FileError(fileName);
	}

	newSave
		<< "HighScore:" + std::to_string(aHighScore) << std::endl
		<< "EnemiesDestroyed:" + std::to_string(aEnemyDestroy) << std::endl;

	newSave.close();

}

void Game::loadMusic(sf::Music& aMusic, float aVolume, std::string aPath) {
	if (!aMusic.openFromFile(aPath)) {

		throw FileError(aPath);
	}

	aMusic.setVolume(aVolume);

	aMusic.play();
}

std::string Game::FontPaths::blackLivesFont = "Fonts/aBlackLives.ttf";
std::string Game::FontPaths::BrowoodFont = "Fonts/Browood-Regular.ttf";

std::string Game::SpritePaths::playerShip = "Sprites/Ship/Main Ship/Main Ship - Bases/PNGs/Main Ship - Base - Full health.png";
std::string Game::SpritePaths::asteroid = "Sprites/Environment/Asteroids/PNGs/Asteroid 01 - Explode.png";
std::string Game::SpritePaths::engine = "Sprites/Ship/Main Ship/Main Ship - Engine Effects/PNGs/Main Ship - Engines - Base Engine - Spritesheet.png";

std::string Game::SoundPaths::playerHit = "Music/explosion3.wav";
std::string Game::SoundPaths::playerDead = "Music/explosion2.wav";
std::string Game::SoundPaths::asteroidDestroyed = "Music/explosion3.wav";
std::string Game::SoundPaths::bulletShot = "Music/projectile.wav";

std::string Game::MusicPaths::revolution = "Music/Revolution.mp3";
std::string Game::MusicPaths::badTime = "Music/Threat.mp3";
std::string Game::MusicPaths::encounter = "Music/Encounter.mp3";
std::string Game::MusicPaths::reverbEnsemble = "Music/Ensemble.mp3";
