#include<SDL2/SDL.h>
#include <iostream>

class Graphics
{
	private:
		int screen_width;
		int screen_height;
	
		SDL_Window* window;
		SDL_Surface* surface;
		
	public:
		Graphics();
		~Graphics();
		void init_window();
};
