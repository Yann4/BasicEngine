#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "graphics.h"

class GameObject
{
	private:
		Point position;
		Shape shape;
		Point size;
		Colour colour;
		
	public:
		GameObject();
		GameObject(Shape shape, Point pos, float width, float height, Colour colour);
		void Update();
		void Draw(Graphics& graphics);
};
#endif
