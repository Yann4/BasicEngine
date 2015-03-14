#include<SDL2/SDL.h>
#include <iostream>

struct Colour
{
	int r, g, b, a;
	
	Colour():r(255), g(255), b(255), a(255){};
	Colour(int r, int g, int b, int a=255):r(r), g(g), b(b), a(a){};
};

class Graphics
{
	private:
		int screen_width;
		int screen_height;
	
		SDL_Window* window;
		SDL_Renderer *renderer;
		
		Colour clear_colour;
		
	public:
		Graphics();
		~Graphics();
		void init_window();
		void drawRect(SDL_Rect rect);
};
