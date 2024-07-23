#include "CharacterContainer.h"


bool Game::CharacterContainer::allocate(const int aCapacity, const std::string path) {
	this->capacity = aCapacity;
	this->characters = (Character*)new Character[capacity];

	if (this->characters == nullptr) {
		return false;
	}

	for (int i = 0; i < this->capacity; i++) {
		this->characters[i] = Character(path, 100.f, Vector2f(-1000.f, -1000.f), 0.3f, false);
	}
	return true;
}

bool Game::CharacterContainer::allocate(const int aCapacity, const Character aCharacter) {
	this->capacity = aCapacity;
	this->characters = (Character*)new Character[this->capacity];

	if (this->characters == nullptr) {
		return false;
	}

	for (int i = 0; i < this->capacity; i++) {
		this->characters[i] = Character(aCharacter);
	}
	return true;
}

Game::CharacterContainer::CharacterContainer() {
	this->allocate(200, SpritePaths::asteroid);
}

Game::CharacterContainer::CharacterContainer(const int aCapacity, const std::string path) {
	this->allocate(aCapacity, path);
}

Game::CharacterContainer::CharacterContainer(const int aCapacity, const Character aCharacter) {
	this->allocate(aCapacity, aCharacter);
}

Game::CharacterContainer::~CharacterContainer() {
	delete[] this->characters;

	this->characters = nullptr;
	this->capacity = 0;
	this->initIndex = 0;
	this->my_size = 0;
}

bool Game::CharacterContainer::initialize() {
	if (my_size == 200) {

		return false;
	}
	if (initIndex == 199) {
		initIndex = 0;
	}

	if (!this->characters[this->initIndex].getInitialized()) {
		if (my_size != 0) {
			initIndex++;
		}
		my_size++;

		characters[this->initIndex].setInitialize(true);
		return true;
	}
	else {
		for (size_t i = 0; i < this->capacity; i++) {
			if (!this->characters[i].getInitialized()) {
				this->characters[i].setInitialize(true);
				return true;
			}
			else {
				continue;
			}
		}
	}

}

bool Game::CharacterContainer::initialize(const Character aCharacter) {

	if (initIndex == 199) {
		initIndex = 0;
	}
	if (my_size >= 200) {
		return false;
	}

	if (!this->characters[this->initIndex].getInitialized()) {
		if (my_size != 0) {
			initIndex++;
		}
		my_size++;

		characters[this->initIndex] = aCharacter;

		characters[this->initIndex].setInitialize(true);

		return true;
	}
	else {
		for (size_t i = 0; i < this->capacity; i++) {
			if (!this->characters[i].getInitialized()) {
				if (my_size != 0) {
					initIndex++;
				}
				my_size++;
				characters[i] = aCharacter;

				this->characters[i].setInitialize(true);

				return true;
			}
			else {
				continue;
			}
		}
	}
	return false;
}

bool Game::CharacterContainer::deInitialize(const int index) {
	characters[index].setInitialize(false);
	my_size--;
	return true;
}

bool Game::CharacterContainer::reset() {

	for (size_t i = 0; i < this->capacity; i++) {
		characters[i].setInitialize(false);
	}
	this->initIndex = 0;
	this->my_size = 0;

	return true;
}

int Game::CharacterContainer::size() const{
	return capacity;
}







