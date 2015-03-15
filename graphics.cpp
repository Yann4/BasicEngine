#include "graphics.h"

#include <iostream>

/******************* Initialisation/Tear down *************************/
Graphics::Graphics()
{
	screen_width = 640;
	screen_height = 480;
	
	clear_colour = Colour();
	
	window = NULL;
	renderer = NULL;
}

Graphics::Graphics(int s_width, int s_height, Colour colour)
{
	screen_width = s_width;
	screen_height = s_height;
	
	clear_colour = colour;
	
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

/************************** Public draw functions *********************/
void Graphics::drawObject(GraphicsObject ob)
{
	to_draw.push(ob);
}

void Graphics::Draw()
{
	//Clear screen to clear_colour
	SDL_SetRenderDrawColor(renderer, clear_colour.r, clear_colour.g, clear_colour.b, clear_colour.a);
	SDL_RenderClear(renderer);

	while(!to_draw.empty())
	{
		GraphicsObject o = to_draw.top();
		to_draw.pop();
		
		SDL_SetRenderDrawColor(renderer, o.colour.r, o.colour.g, o.colour.b, o.colour.a);
		switch(o.shape)
		{
			case RECTANGLE:
				drawRect(o.position, o.size, o.rotation);
				break;
			case TRIANGLE:
				drawTriangle(o.position, o.size, o.rotation);
				break;
			case CIRCLE:
				drawCircle(o.position, o.size.x);
				break;
			case UNDEFINED:
				std::cout << "GraphicsObject shape is undefined." << std::endl;
				break;
		}
		
		SDL_SetRenderDrawColor(renderer, clear_colour.r, clear_colour.g, clear_colour.b, clear_colour.a);
	}
	SDL_RenderPresent(renderer);
}

/************************* Drawing primatives *************************/
void Graphics::drawRect(Point pos, Point size, float rotation)
{
	Point a, b, c, d;
	
	a = Point(pos.x, pos.y); //Top left
	b = Point(pos.x + size.x, pos.y); //Top right
	c = Point(pos.x, pos.y + size.y); //Bottom left
	d = Point(pos.x + size.x, pos.y + size.y); //Bottom right
	
	if(rotation != 0.0f)
	{
		Point centre = Point(pos.x + (size.x/2), pos.y + (size.y/2));
		a = rotatePoint(a, rotation, centre);
		b = rotatePoint(b, rotation, centre);
		c = rotatePoint(c, rotation, centre);
		d = rotatePoint(d, rotation, centre);
	}
	
	SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);
	SDL_RenderDrawLine(renderer, d.x, d.y, c.x, c.y);
	SDL_RenderDrawLine(renderer, c.x, c.y, a.x, a.y);
	SDL_RenderDrawLine(renderer, d.x, d.y, b.x, b.y);
}

void Graphics::drawTriangle(Point pos, Point size, float rotation)
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

	if(rotation != 0.0f)
	{
		Point centre = Point(pos.x + (size.x/2), pos.y + (size.y/2));
		
		a = rotatePoint(a, rotation, centre);
		b = rotatePoint(b, rotation, centre);
		c = rotatePoint(c, rotation, centre);
	}
	
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

Point Graphics::rotatePoint(Point toRotate, double theta, Point pivot)
{
	toRotate.x -= pivot.x;
	toRotate.y -= pivot.y;
	
	float si = sin(theta);
	float co = cos(theta);
	
	float xnew = toRotate.x * co - toRotate.y * si;
	float ynew = toRotate.x * si + toRotate.y * co;
	
	toRotate.x = xnew + pivot.x;
	toRotate.y = ynew + pivot.y;
	
	return toRotate;
}
