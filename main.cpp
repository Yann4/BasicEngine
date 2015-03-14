#include "graphics.h"
#include "gameObject.h"

void Update()
{
}

int main(int argc, char** argv)
{
	Graphics g = Graphics();
	g.init_window();

	GameObject go = GameObject(CIRCLE, Point(200, 200), 50.0, 50.0, Colour(255, 0, 0, 255));
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
		go.Draw(g);
		g.Draw();
		SDL_Delay(1000);
	}
	
}

