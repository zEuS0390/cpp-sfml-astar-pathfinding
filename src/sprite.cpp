#include "sprite.h"
#include <SFML/Graphics.hpp>

sprite::node::node (float scale,
                    sf::Vector2f pos)
:   RectangleShape(sf::Vector2f(scale, scale)),
    pos(pos) {
    init();
}

void sprite::node::init (void) {
    setFillColor(sf::Color::Yellow);
    setPosition(pos);
    return;
}
