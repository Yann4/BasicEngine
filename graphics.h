#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include<SDL2/SDL.h>
#include <stack>
#include <iostream>
struct Point
{
	float x, y;
	Point(float x = 0, float y = 0):x(x), y(y){};
};

struct Colour
{
	int r, g, b, a;
	
	Colour():r(255), g(255), b(255), a(255){};
	Colour(int r, int g, int b, int a=255):r(r), g(g), b(b), a(a){};
};

enum Shape
{
	RECTANGLE, CIRCLE, TRIANGLE, OTHER, UNDEFINED
};

struct Object
{
	Shape shape;
	Point position;
	Point size;
	Colour colour;
	Object(Shape sh = UNDEFINED, Point pos = Point(), Point size = Point(), Colour col = Colour()):
	shape(sh), position(pos), size(size), colour(col){};
};

class Graphics
{
	private:
		int screen_width;
		int screen_height;
	
		SDL_Window* window;
		SDL_Renderer *renderer;
		
		Colour clear_colour;

		std::stack<Object> to_draw;
	public:
		Graphics();
		~Graphics();
		void init_window();
		void drawObject(Object ob);
		void Draw();

	private:
		void drawRect(SDL_Rect rect);
		void drawTriangle(Point pos, Point size);
		void drawCircle(Point centre, float radius);
};

#endif
