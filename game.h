#ifndef _GAME_H_
#define _GAME_H_

#include "graphics.h"
#include "gameObject.h"

class Game
{
	private:
		Graphics graphics;
		
		GameObject tri;
		
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
