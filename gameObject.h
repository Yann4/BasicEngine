#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "graphics.h"
#include "dataTypes.h"

class GameObject
{
	private:
		GraphicsObject go;
	public:
		GameObject();
		GameObject(Shape shape, Point pos, float width, float height, Colour colour);

		void Update();
		void Draw(Graphics& graphics);
		inline Point Position(){return go.position;};
};
#endif
