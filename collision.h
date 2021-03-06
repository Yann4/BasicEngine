#ifndef COLLISION_H_
#define COLLISION_H_

#include "dataTypes.h"

#include <vector>
struct CollisionObject
{
	Point position;
	Shape shape;
	Point size;
	float rotation;
	
	CollisionObject(){};
	CollisionObject(Point pos, Shape shape, Point size, float rotation):
	position(pos), shape(shape), size(size), rotation(rotation){};
};
	
class Collision
{	
	public:
		Collision();
		Point checkCollision(CollisionObject a, CollisionObject b);
		
	private:
		Point circle_circleCollision(CollisionObject& a, CollisionObject& b);
		Point circle_rectCollision(CollisionObject& circle, CollisionObject& rect);
		Point circle_triCollision(CollisionObject& circle, CollisionObject& tri);
		Point rect_rectCollision(CollisionObject& a, CollisionObject& b);
		Point rect_triCollision(CollisionObject& rect, CollisionObject& tri);
		Point tri_triCollision(CollisionObject& a, CollisionObject& b);
		
		std::vector<Point> pointsOfShape(CollisionObject& a);
		Point rotatePoint(Point toRotate, double theta, Point pivot);
		double pythSq(Point a, Point b);
		Point normal(Point vector);
		float dotprod(Point a, Point b);
		Point normalise(Point vector);
		float max(Point p);
		float min(Point p);
};
#endif
