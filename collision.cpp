#include "collision.h"

#include <math.h>

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
			return circle_rectCollision(b, a);
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
			return rect_triCollision(b, a);
		}else if(b.shape == TRIANGLE)
		{
			return tri_triCollision(a, b);
		}else if(b.shape == CIRCLE)
		{
			return circle_triCollision(b, a);
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
		
		Point toMove = Point(a.position.x - xColl, a.position.y - yColl);
		double mag = sqrt((a.position.x - xColl)*(a.position.x - xColl) + (a.position.y - yColl)*(a.position.y - yColl));
		
		toMove.x /= mag;
		toMove.y /= mag;
		return toMove;
	}
}

Point Collision::circle_rectCollision(CollisionObject& circle, CollisionObject& rect){}
Point Collision::circle_triCollision(CollisionObject& circle, CollisionObject& tri){}
Point Collision::rect_rectCollision(CollisionObject& a, CollisionObject& b){}
Point Collision::rect_triCollision(CollisionObject& rect, CollisionObject& tri){}
Point Collision::tri_triCollision(CollisionObject& a, CollisionObject& b){}


double Collision::pythSq(Point a, Point b)
{
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}
