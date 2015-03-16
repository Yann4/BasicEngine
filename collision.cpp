#include "collision.h"

Collision::Collision()
{
}

Point Collision::checkCollision(CollisionObject a, CollisionObject b)
{
	if(a.shape == RECTANGLE)
	{
		if(b.shape == RECTANGLE)
		{
			return rect_rectCollision(a, b);
		}else if(b.shape == TRIANGLE)
		{
			return rect_triCollision(a, b);
		}else if(b.shape == CIRCLE)
		{
			return rect_circleCollision(a, b);
		}
	}else if(a.shape == CIRCLE)
	{
		if(b.shape == RECTANGLE)
		{
			return circle_rectCollision(a, b);
		}else if(b.shape == TRIANGLE)
		{
			return circle_triCollision(a, b);
		}else if(b.shape == CIRCLE)
		{
			return circle_circleCollision(a, b);
		}
	}else if(a.shape == TRIANGLE)
	{
		if(b.shape == RECTANGLE)
		{
			return tri_rectCollision(a, b);
		}else if(b.shape == TRIANGLE)
		{
			return tri_triCollision(a, b);
		}else if(b.shape == CIRCLE)
		{
			return tri_circleCollision(a, b);
		}
	}
	
	return Point(-1000, -1000);
}

Point Collision::circle_circleCollision(CollisionObject& a, CollisionObject& b)
{
	double distSq = pythSq(a.position, b.position);
	
	//No collision
	if(distSq > ((a.size.x+b.size.x)*(a.size.x+b.size.x)))
	{
		return Point(0, 0);
	}else
	{
		//Location of collision
		float xColl = ((a.position.x * b.size.x) + (b.position.x * a.size.x)) / (a.size.x + b.size.x);
		float yColl = ((a.position.y * b.size.x) + (b.position.y * a.size.x)) / (a.size.x + b.size.x);
		
		double grad = (a.position.x - xColl) / (a.position.y - yColl);
		
	}
}

double Collision::pythSq(Point a, Point b)
{
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}
