#include "graphics.h"

Graphics::Graphics()
{
	screen_width = 640;
	screen_height = 480;
	
	window = NULL;
	surface = NULL;
}

Graphics::~Graphics()
{
	SDL_DestroyWindow( window );
	SDL_Quit(); //Shouldn't be here
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
		//Get window surface
		surface = SDL_GetWindowSurface( window );

		//Fill the surface white
		SDL_FillRect( surface, NULL, SDL_MapRGB( surface->format, 0xFF, 0xFF, 0xFF ) );
		
		//Update the surface
		SDL_UpdateWindowSurface( window );
	}
}
