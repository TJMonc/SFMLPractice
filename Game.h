#ifndef GAME_H
#define GAME_H

#include "Bullet.h"

namespace Game{
	class Game {
	public:
		std::shared_ptr<RenderWindow> window = std::make_shared<RenderWindow>(VideoMode(1920, 1080), "SFML Practice 2", Style::Fullscreen);

		struct playerStruct {
			float scaleFactor = 0.5f;
			Ship player = Ship(SpritePaths::playerShip, 100.f, true, scaleFactor);
			IntRect engineRect = IntRect(0, 0, 48, 48);
			int hitCounter = 1;

		};

		struct enemyStruct {
			float scaleFactor = 0.3f;
			

			Character phantomEnemy = Character(SpritePaths::asteroid, 50.f, Vector2f(-1000, -1000), scaleFactor, true);
			Character enemy = Character(SpritePaths::asteroid, 50.f, Vector2f(0, 0), scaleFactor, false);
			CharacterContainer enemies;

			IntRect enemyRect = IntRect(0, 0, 96, 96);

			Clock enemyClock;
			Time enemyTime = milliseconds(300);


		};

		struct bulletStruct {
			std::vector<Bullet> bullets;
			
			Clock bulletClock;
			Time bulletTime = milliseconds(300);

			Sound bulletSound;
			SoundBuffer bulletSoundBuffer;
			Clock bulletSoundClock;
			Time bulletSoundTime = milliseconds(20);
		};

		struct musicStruct {
			Music music;
			bool music1 = false;
			bool music2 = false;
			bool music3 = false;


		};

		struct hudStruct {
			Text uiText;
			Font uiFont;

			//Health Bar
			RectangleShape redRect;
			RectangleShape greenRect;

			//Lose
			Text loseText;
			Font loseFont;

		};

		struct gameInfoStruct {

			int highScore = 0;
			int survivedPhases = 0;
			int enemiesDestroyed = 0;
			int highEnemiesDestroyed = 0;

			int phase = 0;
			int macroPhase = 0;
			Clock phaseClock;
			Time phaseTime = seconds(20);
			bool phaseStart = false;

			bool lose = false;
			Clock loseClock;
			Time loseTime = seconds(2);


		};


	public:
		std::shared_ptr<playerStruct> player = std::make_shared<playerStruct>();
		std::shared_ptr<enemyStruct> enemies = std::make_shared<enemyStruct>();
		std::shared_ptr<bulletStruct> bullets = std::make_shared<bulletStruct>();
		std::shared_ptr<musicStruct> music = std::make_shared<musicStruct>();
		std::shared_ptr<hudStruct> display = std::make_shared<hudStruct>();
		std::shared_ptr<gameInfoStruct> miscInfo = std::make_shared<gameInfoStruct>();



	public:
		Game();
	public:
		inline void initPlayer();
		inline void initEnemy();
		inline void initBullet();
		inline void initMusic();
		inline void initDisplay();

		inline void phaseStartAndEnd();

		//Fall
		inline void Phase1();

		//Drift
		inline void Phase2();

		//Side Bounce
		inline void Phase3();

		//Fall bounce
		inline void Phase4();

		//Shoot
		inline void Phase5();

		inline void displayBaseHUD();
		inline void resetOnLose();
		inline void playerMovement();
		inline void bulletSpawn();
		inline void collisionAndDamage();

		inline void updateScreen();

	public:


		void update();




	};


}




#endif
