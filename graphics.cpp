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
	
	window = SDL_CreateWindow( "", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN );
	
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

void Graphics::drawObject(Object ob)
{
	to_draw.push(ob);
}

void Graphics::Draw()
{
	while(!to_draw.empty())
	{
		Object o = to_draw.top();
		to_draw.pop();
		
		SDL_SetRenderDrawColor(renderer, o.colour.r, o.colour.g, o.colour.b, o.colour.a);
		switch(o.shape)
		{
			case RECTANGLE:
				SDL_Rect rect;
				rect.x = o.position.x;
				rect.y = o.position.y;
				rect.w = o.size.x;
				rect.h = o.size.y;
				drawRect(rect);
				break;
			case TRIANGLE:
				drawTriangle(o.position, o.size);
				break;
			case CIRCLE:
				drawCircle(o.position, o.size.x);
				break;
		}
		
		SDL_SetRenderDrawColor(renderer, clear_colour.r, clear_colour.g, clear_colour.b, clear_colour.a);
	}
	SDL_RenderPresent(renderer);
}

void Graphics::drawRect(SDL_Rect rect)
{
	SDL_RenderDrawRect(renderer, &rect);
}

void Graphics::drawTriangle(Point pos, Point size)
{
	Point a, b, c;
	
	//Top point of triangle
	a.x = pos.x + (size.x / 2);
	a.y = pos.y;
	
	//Bottom left point
	b.x = pos.x;
	b.y = pos.y + size.y;
	
	//Bottom right point
	c.x = pos.x + size.x;
	c.y = pos.y + size.y;
	
	SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);
	SDL_RenderDrawLine(renderer, b.x, b.y, c.x, c.y);
	SDL_RenderDrawLine(renderer, c.x, c.y, a.x, a.y);
}

void Graphics::drawCircle(Point centre, float radius)
{
	Point onC;
	
	for(double theta = 0.0; theta < 360; theta++)
	{
		onC.x = centre.x + radius * cos(theta);
		onC.y = centre.y + radius * sin(theta);
		
		SDL_RenderDrawPoint(renderer, onC.x, onC.y);
	}
}
