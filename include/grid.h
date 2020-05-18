#ifndef GRID_H
#define GRID_H
#include <SFML/Graphics.hpp>
#include <list>
#include "utility.h"

// grid class
class Grid {
    public:
        int                             scale;
        Point                           windowSize;
    public:
        Grid                            (sf::RenderWindow*,
                                         int,
                                         float,
                                         float);
    public:
        void init                       (void);
        void update                     (void);
        void render                     (void);
        void unWalkable                 (float,
                                         float);
        void hoverNode                  (void);
        void selectNode                 (void);
        std::list<Node*> getNeighbors   (Node*);
        bool checkIfExists              (std::list<Node*>,
                                         Node*);
        float getDistance               (Node*, Node*);
        void findPath                   (void);
        void retracePath                (void);
    private:
        sf::Vector2i                    mousePos;
        Node*                           nodeStart;
        Node*                           nodeEnd;
        sf::RenderWindow*               renderWin;
        sf::Mouse                       mouse;
        std::list<Node*>                nodes;
        std::list<Node*>                openNodes;
        std::list<Node*>                closedNodes;
        std::list<Node*>                path;
};

#endif
