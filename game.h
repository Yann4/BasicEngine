#ifndef GAME_H_
#define GAME_H_

#include "graphics.h"
#include "gameObject.h"
#include "qtree.h"

class Game
{
	private:
		Graphics graphics;
		const double ms_per_frame = 1.0/60.0; //60fps
		
		GameObject a, b;
		Quadtree qtree;

	public:
		Game();
		~Game();
		
		//Just need to call this from main
		void mainLoop();
		
	private:
		//These need filling in for each game
		void Update();
		void Draw();
		
		bool load();
		void unload();
};

#endif
