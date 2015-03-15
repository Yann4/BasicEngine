#ifndef _GAME_H_
#define _GAME_H_

#include "graphics.h"
#include "gameObject.h"

#include <chrono>
#include <vector>

class Game
{
	private:
		Graphics graphics;
		
		//60fps
		const double ms_per_frame = 1.0/60.0;
		
	public:
		Game();
		~Game();
		
		void mainLoop();
		
	private:
		void Update();
		void Draw();
		
		bool load();
		void unload();
};

#endif
