#include "graphics.h"

Graphics::Graphics()
{
	screen_width = 640;
	screen_height = 480;
	
	clear_colour = Colour();
	
	window = NULL;
	renderer = NULL;
}

Graphics::~Graphics()
{
	SDL_DestroyWindow( window );
	SDL_Quit(); //Shouldn't be here (I don't think)
}

void Graphics::init_window()
{
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		std::cout << "SDL could not initialize! SDL_Error: " <<  SDL_GetError() << std::endl;
	}
	
	window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN );
	
	if( window == NULL )
	{
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		
		SDL_SetRenderDrawColor(renderer, clear_colour.r, clear_colour.g, clear_colour.b, clear_colour.a);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}
}

void Graphics::drawRect(SDL_Rect rect)
{
	SDL_RenderDrawRect(rect);
}
