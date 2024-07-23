#ifndef CHARACTERCONTAINER_H
#define CHARACTERCONTAINER_H
#include "Character.h"

namespace Game {
	class CharacterContainer {
	private:
		Character* characters = nullptr;
		int my_size = 0;	//Is not the actual size of the container. Will return how many 
		int capacity = 0;
		int initIndex;

		bool allocate(const int aCapacity, const std::string path);
		bool allocate(const int aCapacity, const Character aCharacter);

	public:
		CharacterContainer();
		CharacterContainer(const int aCapacity, const std::string path);
		CharacterContainer(const int aCapacity, const Character aCharacter);
		~CharacterContainer();

		bool initialize(const Character aCharacter);
		bool initialize();
		bool deInitialize(const int index);
		bool reset();
		int size() const;

		inline Character& operator[](const int index) { return this->characters[index]; };
		inline const Character& operator[](const int index) const { return this->characters[index]; };



	};

}

#endif
