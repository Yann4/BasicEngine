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
		inline Shape getShape(){return go.shape;};
		inline Point getSize(){return go.size;};
		
		inline void moveBy(Point p){go.position.x += p.x; go.position.y += p.y;};
		inline void moveTo(Point p){go.position = p;};

		inline Point Position(){return go.position;};

};
#endif
