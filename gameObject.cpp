#include "GameObject.h"

GameObject::GameObject()
{
	position = Point();
	shape = UNDEFINED;
}

GameObject::GameObject(Shape shape, Point pos, float width, float height)
{
	GameObject::shape = shape;
	GameObject::position = pos;
	GameObject::size = Point(width, height);
}

void GameObject::Update()
{
}

void GameObject::Draw()
{
}
