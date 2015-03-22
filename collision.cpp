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
		return normalise(toMove);
	}
}

Point Collision::circle_rectCollision(CollisionObject& circle, CollisionObject& rect){}
Point Collision::circle_triCollision(CollisionObject& circle, CollisionObject& tri){}

Point Collision::rect_rectCollision(CollisionObject& a, CollisionObject& b)
{
	std::vector<Point> cornersA = pointsOfShape(a);
	std::vector<Point> cornersB = pointsOfShape(b);
	
	
	//Get side vectors
	//Rectangle A
	std::vector<Point> sidesA;
	Point s1, s2;
	s1 = cornersA.at(0);
	s2 = cornersA.at(1);
	sidesA.push_back(Point(s1.x - s2.x, s1.y - s2.y)); //Top side
	
	s2 = cornersA.at(2);
	sidesA.push_back(Point(s1.x - s2.x, s1.y - s2.y)); //Left side
	
	s1 = cornersA.at(3);
	sidesA.push_back(Point(s1.x - s2.x, s1.y - s2.y)); //Bottom side
	
	s2 = cornersA.at(1);
	sidesA.push_back(Point(s1.x - s2.x, s1.y - s2.y)); //Right side
	
	//Rectangle B
	std::vector<Point> sidesB;
	s1 = cornersB.at(0);
	s2 = cornersB.at(1);
	sidesB.push_back(Point(s1.x - s2.x, s1.y - s2.y)); //Top side
	
	s2 = cornersB.at(2);
	sidesB.push_back(Point(s1.x - s2.x, s1.y - s2.y)); //Left side
	
	s1 = cornersB.at(3);
	sidesB.push_back(Point(s1.x - s2.x, s1.y - s2.y)); //Bottom side
	
	s2 = cornersB.at(1);
	sidesB.push_back(Point(s1.x - s2.x, s1.y - s2.y)); //Right side
	

	//Get the perpendicular vectors for each side
	std::vector<Point> normalA;
	std::vector<Point> normalB;
	
	for(int i = 0; i < sidesA.size(); i++)
	{
		normalA.push_back(normal(sidesA.at(i)));
	}
	
	for(int i = 0; i < sidesB.size(); i++)
	{
		normalB.push_back(normal(sidesB.at(i)));
	}
	//Now need to project sides onto axes http://www.dyn4j.org/2010/01/sat/
	Point smallest;
	
	for(int i = 0; i < normalA.size(); i++)
	{
		Point axis = normalA.at(i);
		
		float minA = dotprod(axis, cornersA.at(0));
		float maxA = minA;
		
		for(int j = 1; j < cornersA.size(); j++)
		{
			float p = dotprod(axis, cornersA.at(j));
			if(p < minA)
			{
				minA = p;
			}else if(p > maxA)
			{
				maxA = p;
			}
		}
		
		float minB = dotprod(axis, cornersB.at(0));
		float maxB = minB;
		
		for(int j = 0; j < cornersB.size(); j++)
		{
			float p = dotprod(axis, cornersB.at(j));
			if(p < minB)
			{
				minB = p;
			}else if(p > maxB)
			{
				maxB = p;
			}
		}
		
		if(maxB 
	}
}

Point Collision::rect_triCollision(CollisionObject& rect, CollisionObject& tri){}
Point Collision::tri_triCollision(CollisionObject& a, CollisionObject& b){}


/************************* Helper functions ***************************/
std::vector<Point> Collision::pointsOfShape(CollisionObject& a)
{
	std::vector<Point> points = std::vector<Point>();
	
	if(a.shape == CIRCLE)
	{
		points.push_back(a.position);
	}else if(a.shape == RECTANGLE)
	{
		Point pa,pb,pc,pd;
		pa = a.position; //Top left
		pb = Point(a.position.x + a.size.x, a.position.y); //Top right
		pc = Point(a.position.x, a.position.y + a.size.y); //Bottom left
		pd = Point(a.position.x + a.size.x, a.position.y + a.size.y); //Bottom right
		
		if(a.rotation != 0)
		{
			Point centre = Point(a.position.x + (a.size.x/2), a.position.y + (a.size.y/2));
			pa = rotatePoint(pa, a.rotation, centre);
			pb = rotatePoint(pb, a.rotation, centre);
			pc = rotatePoint(pc, a.rotation, centre);
			pd = rotatePoint(pd, a.rotation, centre);
		}
		
		points.push_back(pa);
		points.push_back(pb);
		points.push_back(pc);
		points.push_back(pd);
	}else if(a.shape == TRIANGLE)
	{
		Point pa, pb, pc;
		
		pa = Point(a.position.x + (a.size.x/2), a.position.y); //Top point
		pb = Point(a.position.x, a.position.y + a.size.y); //Bottom left
		pc = Point(a.position.x + a.size.x, a.position.y + a.size.y); //Bottom right
		
		if(a.rotation != 0)
		{
			Point centre = Point(a.position.x + (a.size.x/2), a.position.y + (a.size.y/2));
			pa = rotatePoint(pa, a.rotation, centre);
			pb = rotatePoint(pb, a.rotation, centre);
			pc = rotatePoint(pc, a.rotation, centre);
		}
		
		points.push_back(pa);
		points.push_back(pb);
		points.push_back(pc);
	}
	return points;
}

Point Collision::rotatePoint(Point toRotate, double theta, Point pivot)
{
	toRotate.x -= pivot.x;
	toRotate.y -= pivot.y;
	
	float si = sin(theta);
	float co = cos(theta);
	
	float xnew = toRotate.x * co - toRotate.y * si;
	float ynew = toRotate.x * si + toRotate.y * co;
	
	toRotate.x = xnew + pivot.x;
	toRotate.y = ynew + pivot.y;
	
	return toRotate;
}

double Collision::pythSq(Point a, Point b)
{
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

Point Collision::normal(Point vector)
{
	return Point(-vector.y, vector.x);
}


float Collision::dotprod(Point a, Point b)
{
	return (a.x * b.x) + (a.y * b.y);
}

Point Collision::normalise(Point vector)
{
	double mag = sqrt((vector.x*vector.x) + (vector.y*vector.y));
	return Point(vector.x/mag, vector.y/mag);
}

float Collision::max(Point p)
{
	return p.x > p.y ? p.x : p.y;
}

float Collision::min(Point p)
{
	return p.x < p.y ? p.x : p.y;
}
