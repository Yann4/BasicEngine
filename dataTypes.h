#ifndef DATATYPES_H_
#define DATATYPES_H_

struct Point
{
	float x = 0.0f;
	float y = 0.0f;
	Point(){};
	Point(float x, float y):x(x), y(y){};
};

enum Shape
{
	RECTANGLE, CIRCLE, TRIANGLE, UNDEFINED
};

struct AABB
{
    Point centre;
    Point halfSize;
    
    AABB(Point centre = {}, Point halfSize = {}): centre(centre), halfSize(halfSize){};
    
    bool contains(Point a) const
    {
        if(a.x < centre.x + halfSize.x && a.x > centre.x - halfSize.x)
        {
            if(a.y < centre.y + halfSize.y && a.y > centre.y - halfSize.y)
            {
                return true;
            }
        }
        return false;
    }
    
    bool intersects(const AABB& other) const
    {
        //this right > that left                                          this left <s that right
        if(centre.x + halfSize.x > other.centre.x - other.halfSize.x || centre.x - halfSize.x < other.centre.x + other.halfSize.x)
        {
            // This bottom > that top
            if(centre.y + halfSize.y > other.centre.y - other.halfSize.y || centre.y - halfSize.y < other.centre.y + other.halfSize.y)
            {
                return true;
            }
        }
        return false;
    }
};

#endif
