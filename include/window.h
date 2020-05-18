#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>
#include "grid.h"

// window class
class window {
    public:
        bool                isRunning;
    public:
        window              (unsigned int,
                             unsigned int);
    public:
        void init           (void);
        void events         (void);
        void updates        (void);
        void renders        (void);
        void loop           (void);
    private:
        sf::RenderWindow    renderWin;
        Grid                grid;
};

#endif
