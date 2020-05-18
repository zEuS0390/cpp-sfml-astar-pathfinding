#ifndef SPRITE_H
#define SPRITE_H
#include <SFML/Graphics.hpp>

namespace sprite {
    class node : public sf::RectangleShape {
        public:
            sf::Vector2f    pos;
        public:
            node            (float,
                             sf::Vector2f);
        public:
            void init       (void);
    };
}

#endif
