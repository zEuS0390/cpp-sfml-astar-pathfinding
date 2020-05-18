#ifndef UTILITY_H
#define UTILITY_H
#include <list>
#include "sprite.h"

// utility class
struct Point {
    float x, y;
};

// Node class
class Node {
    public:
        float               gCost;
        float               hCost;
        bool                isOpen;
        bool                isTraversable;
    public:
        Point               point;
    public:
        Node                (float,
                            float,
                            float);
    public:
        float getFCost      (void);
    public:
        Node*               parent;
        std::list<Node*>    neighbors;
        sprite::node        node;

};

#endif
