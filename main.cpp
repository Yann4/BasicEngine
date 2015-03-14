#include "graphics.h"

void Update()
{
}

int main(int argc, char** argv)
{
	Graphics g = Graphics();
	g.init_window();
	
	SDL_Event event;
	bool quit = false;
	
	while(!quit)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		
		Update();
	}
	
}

