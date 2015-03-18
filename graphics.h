#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include<SDL2/SDL.h>
#include <stack>

#include "dataTypes.h"

struct Colour
{
	int r, g, b, a;
	
	Colour():r(255), g(255), b(255), a(255){};
	Colour(int r, int g, int b, int a=255):r(r), g(g), b(b), a(a){};

	void red(){r = 255; g = 0; b = 0; a = 255;};
	void green(){r = 0; g = 255; b = 0; a = 255;};
	void blue(){r = 0; g = 0; b = 255; a = 255;};
	void light_blue(){r = 70; g = 177; b = 249; a = 255;};
	void yellow(){r = 231; g = 255; b = 0; a = 255;};
	void pink(){r = 255; g = 0; b = 255; a = 255;};
	void white(){r = 255; g = 255; b = 255; a = 255;}
	void black(){r = 0; g = 0; b = 0; a = 255;}
};

struct GraphicsObject
{
	Shape shape;
	Point position;
	Point size;
	Colour colour;
	float rotation;
	GraphicsObject(Shape sh = UNDEFINED, Point pos = Point(), Point size = Point(), Colour col = Colour(), float rotation = 0.0):
	shape(sh), position(pos), size(size), colour(col), rotation(rotation){};
};

class Graphics
{
	private:
		int screen_width;
		int screen_height;
	
		SDL_Window* window;
		SDL_Renderer *renderer;
		
		Colour clear_colour;

		std::stack<GraphicsObject> to_draw;
	public:
		Graphics();
		Graphics(int s_width, int s_height, Colour colour = Colour(0, 0, 255, 255));
		~Graphics();

		void init_window();
		void drawObject(GraphicsObject ob);
		void Draw();

	private:
		void drawRectangle(Point pos, Point size, float rotation);
		void drawTriangle(Point pos, Point size, float rotation);
		void drawCircle(Point centre, float radius);
		
		Point rotatePoint(Point toRotate, double theta, Point rotateAbout);
};

#endif
