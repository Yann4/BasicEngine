#include "gameObject.h"

GameObject::GameObject()
{
	go = GraphicsObject();
}

GameObject::GameObject(Shape shape, Point pos, float width, float height, Colour colour)
{
	go = GraphicsObject(shape, pos, Point(width, height), colour, 0.0);
}

void GameObject::Update()
{
	//Add update logic here
	go.position.x += 0.01;
}

//Shouldn't need changing too much, assuming the GraphicsObject is up to date at this point
void GameObject::Draw(Graphics& graphics)
{
	graphics.drawObject(go);
}
