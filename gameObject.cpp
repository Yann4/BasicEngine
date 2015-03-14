#include "gameObject.h"

GameObject::GameObject()
{
	position = Point();
	shape = UNDEFINED;
	size = Point();
	colour = Colour();
}

GameObject::GameObject(Shape shape, Point pos, float width, float height, Colour colour)
{
	GameObject::shape = shape;
	GameObject::position = pos;
	GameObject::size = Point(width, height);
	GameObject::colour = colour;
}

void GameObject::Update()
{
}

void GameObject::Draw(Graphics& graphics)
{
	graphics.drawObject(Object(shape, position, size, colour));
}
