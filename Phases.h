#ifndef PHASES_H
#define PHASES_H

#include "Game.h"


namespace Game {


	
	struct Phases {
	private:
		Game* game;
	public:
		Phases(Game* aGame);
		
	public:
		void phaseStartAndEnd();
		//Fall
		void Phase1();

		//Drift
		void Phase2();

		//Side Bounce
		void Phase3();

		//Fall bounce
		void Phase4();

		//Shoot
		void Phase5();

	};
}


#endif