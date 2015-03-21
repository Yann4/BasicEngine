#ifndef QUADTREE_H_
#define QUADTREE_H_

#include <vector>
#include <iostream>
#include <cstddef>

#include "dataTypes.h"
#include "gameObject.h"

struct Data
{
    Point pos;
    GameObject obj;
    
    Data(GameObject data = {}): obj(data)
    {
		UpdatePos();
	};
	
	void UpdatePos()
	{
		pos = obj.Position();
	}
};

class Quadtree
{
    private:
        //4 children
        Quadtree* nw;
        Quadtree* ne;
        Quadtree* sw;
        Quadtree* se;
        
        AABB boundary;
        
        std::vector< Data > objects;
        
        static constexpr int capacity = 4;       
    public:
        Quadtree();
        Quadtree(AABB boundary);
        
        ~Quadtree();
        
        bool insert(Data d);
        void subdivide();
        std::vector< Data > queryRange(AABB range);
};
#endif
