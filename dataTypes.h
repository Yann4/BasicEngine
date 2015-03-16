#ifndef _DATATYPES_H_
#define _DATATYPES_H_

struct Point
{
	float x, y;
	Point(float x = 0, float y = 0):x(x), y(y){};
};

enum Shape
{
	RECTANGLE, CIRCLE, TRIANGLE, UNDEFINED
};

#endif
