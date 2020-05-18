#include "utility.h"

Node::Node (float scale,
            float x,
            float y)
:   gCost(0.0f),
    hCost(0.0f),
    isOpen(false),
    isTraversable(true),
    point{x, y},
    node(scale, sf::Vector2f(x, y)) {
}

float Node::getFCost (void) {
    return gCost + hCost;
}
