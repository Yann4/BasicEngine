#include "graphics.h"
#include "gameObject.h"

#include <time.h>

void Update()
{
}

int main(int argc, char** argv)
{
	clock_t time;
	double ms_per_frame = 1.0/60.0;
	
	Graphics g = Graphics();
	g.init_window();

	GameObject go = GameObject(CIRCLE, Point(200, 200), 50.0, 50.0, Colour(255, 0, 0, 255));
	SDL_Event event;
	bool quit = false;
	time = clock();
	
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
		go.Draw(g);
		g.Draw();
		
		clock_t diff = clock() - time;
		if(diff < ms_per_frame)
		{
			SDL_Delay(ms_per_frame - diff);
		}
		time = clock();
	}
	
}

