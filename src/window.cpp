#include <SFML/Graphics.hpp>
#include <iostream>
#include "window.h"

// window constructor
window::window (unsigned int x,
                unsigned int y)
:   isRunning(true),
    renderWin(sf::VideoMode(x, y), "SFML Window"),
    grid(&renderWin, 24, x, y) {
    init();
}

// window initialization method
void window::init (void) {
    loop();
    return;
}

// events method
void window::events (void) {
    sf::Event event;
    while (renderWin.pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            isRunning = false;
            renderWin.close();
        }
    }
    return;
}

// updates method
void window::updates (void) {
    grid.update();
    return;
}

// renders method
void window::renders (void) {
    renderWin.clear();
    grid.render();
    renderWin.display();
    return;
}

// loop method
void window::loop (void) {
    while (isRunning) {
        updates();
        events();
        renders();
    }
    return;
}
