#include "qtree.h"

Quadtree::Quadtree(): nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr)
{
}

Quadtree::Quadtree(AABB boundary): nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr), boundary(boundary)
{
}

Quadtree::~Quadtree()
{
    delete nw;
    delete sw;
    delete ne;
    delete se;
}

void Quadtree::subdivide()
{
    Point qSize = Point(boundary.halfSize.x/2, boundary.halfSize.y/2);
    Point qCentre = Point(boundary.centre.x - qSize.x, boundary.centre.y - qSize.y);
    nw = new Quadtree(AABB(qCentre, qSize));
    
    qCentre = Point(boundary.centre.x + qSize.x, boundary.centre.y - qSize.y);
    ne = new Quadtree(AABB(qCentre, qSize));
    
    qCentre = Point(boundary.centre.x - qSize.x, boundary.centre.y + qSize.y);
    sw = new Quadtree(AABB(qCentre, qSize));
    
    qCentre = Point(boundary.centre.x + qSize.x, boundary.centre.y + qSize.y);
    se = new Quadtree(AABB(qCentre, qSize));
}

bool Quadtree::insert(Data d)
{
    if(!boundary.contains(d.pos))
    {
        return false;
    }
    
    if(objects.size() < capacity)
    {
        objects.push_back(d);
        return true;
    }
    
    if(nw == nullptr)
    {
        subdivide();
    }
    
    if(nw->insert(d))
    {
        return true;
    }
    if(ne->insert(d))
    {
        return true;
    }
    if(sw->insert(d))
    {
        return true;
    }
    if(se->insert(d))
    {
        return true;
    }
    
    return false;
    
}

std::vector< Data > Quadtree::queryRange(AABB range)
{
    std::vector< Data > pInRange = std::vector< Data >();
    
    if(!boundary.intersects(range))
    {
        return pInRange;
    }
    
    for(auto&& object : objects)
    {
        if(range.contains(object.pos))
        {
            pInRange.push_back(object);
        }
    }
    
    if(nw == nullptr)
    {
        return pInRange;
    }
    
    std::vector< Data > temp = nw->queryRange(range);
    pInRange.insert(pInRange.end(), temp.begin(), temp.end());
    
    temp = ne->queryRange(range);
    pInRange.insert(pInRange.end(), temp.begin(), temp.end());
    
    temp = sw->queryRange(range);
    pInRange.insert(pInRange.end(), temp.begin(), temp.end());
    
    temp = se->queryRange(range);
    pInRange.insert(pInRange.end(), temp.begin(), temp.end());
    
    return pInRange;
}
