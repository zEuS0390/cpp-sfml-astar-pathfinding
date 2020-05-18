#include <algorithm>
#include <iostream>
#include <cmath>
#include <list>
#include "grid.h"

Grid::Grid (sf::RenderWindow* renderWin,
            int scale,
            float x,
            float y)
:   scale(scale),
    windowSize{x, y},
    nodeStart(NULL),
    nodeEnd(NULL),
    renderWin(renderWin) {
    init();
}

void Grid::init (void) {
    for (unsigned int x = 0; x < 640; x++) {
        for (unsigned int y = 0; y < 480; y++) {
            if (x%scale == 0 && y%scale == 0)
                nodes.push_back(new Node(scale, x, y));
        }
    }
    return;
}

void Grid::update (void) {
    mousePos = mouse.getPosition(*renderWin);
    selectNode();
    if (nodeStart != NULL &&
        nodeEnd != NULL) {
        findPath();
    }
    return;
}

void Grid::render (void) {
    for (auto iter = nodes.begin(); iter != nodes.end(); iter++) {
        Node* node = *iter;
        if (node == nodeStart) {
            node->node.setFillColor(sf::Color::Green);

            for (auto i = node->neighbors.begin();
                 i != node->neighbors.end(); i++) {
                (*i)->node.setFillColor(sf::Color::Blue);
            }

        } else if (node == nodeEnd) {
            node->node.setFillColor(sf::Color::Red);
        } else if (!node->isTraversable) {
            node->node.setFillColor(sf::Color(100, 150, 0));
        } else if (node->isOpen) {
            node->node.setFillColor(sf::Color::Blue);
        } else {
            node->node.setFillColor(sf::Color(255, 255, 200));
        }

        for (auto i = path.begin(); i != path.end(); i++) {
            if (*i != nodeEnd)
                (*i)->node.setFillColor(sf::Color::Black);
        }
        renderWin->draw(node->node);
        node->isOpen = false;
    }
    return;
}

void Grid::unWalkable (float x, float y) {
    for (auto iter = nodes.begin(); iter != nodes.end(); iter++) {
        Node* node = *iter;
        if (x == node->point.x &&
            y == node->point.y) {
            node->isTraversable = false;
        }
    }
    return;
}

void Grid::selectNode (void) {
    if (mouse.isButtonPressed(sf::Mouse::Left) ||
        mouse.isButtonPressed(sf::Mouse::Right) ||
        mouse.isButtonPressed(sf::Mouse::Middle) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        for (auto iter = nodes.begin(); iter != nodes.end(); iter++) {
            Node* node = *iter;
            if (mousePos.x > node->point.x &&
                mousePos.x < node->point.x+node->node.getGlobalBounds().width &&
                mousePos.y > node->point.y &&
                mousePos.y < node->point.y+node->node.getGlobalBounds().height) {
                if (mouse.isButtonPressed(sf::Mouse::Left)) {
                    if (node != nodeEnd &&
                        node->isTraversable) {
                        nodeStart = node;
                    }
                } else if (mouse.isButtonPressed(sf::Mouse::Right)) {
                    if (node != nodeStart  &&
                        node->isTraversable) {
                        nodeEnd = node;
                    }
                } else if (mouse.isButtonPressed(sf::Mouse::Middle)) {
                    if (node != nodeStart || node != nodeEnd) {
                        node->isTraversable = false;
                    }
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    if (!node->isTraversable) {
                        node->isTraversable = true;
                    }
                }
            }
        }
    }
    return;
}

std::list<Node*> Grid::getNeighbors (Node* node) {
    std::list<Node*> neighbors;
    for (auto iter = nodes.begin(); iter != nodes.end(); iter++) {
        Node* currNode = *iter;
        if (!checkIfExists(node->neighbors, currNode)) {
            if ((node->point.x-scale == currNode->point.x &&
                node->point.y == currNode->point.y) ||
                (node->point.x+scale == currNode->point.x &&
                node->point.y == currNode->point.y) ||
                (node->point.x == currNode->point.x &&
                 node->point.y-scale == currNode->point.y) ||
                (node->point.x == currNode->point.x &&
                 node->point.y+scale == currNode->point.y) ||
                (node->point.x-scale == currNode->point.x &&
                 node->point.y-scale == currNode->point.y) ||
                (node->point.x+scale == currNode->point.x &&
                 node->point.y-scale == currNode->point.y) ||
                (node->point.x-scale == currNode->point.x &&
                 node->point.y+scale == currNode->point.y) ||
                (node->point.x+scale == currNode->point.x &&
                 node->point.y+scale == currNode->point.y)) {
                neighbors.push_back(currNode);
            }
        }
    }
    return neighbors;
}

bool Grid::checkIfExists (std::list<Node*> nodes,
                          Node* node) {
    for (auto iter = nodes.begin(); iter != nodes.end(); iter++) {
        Node* currNode = *iter;
        if (currNode->point.x == node->point.x &&
            currNode->point.y == node->point.y) {
            return true;
        }
    }
    return false;
}

float Grid::getDistance (Node* node1, Node* node2) {
    return std::sqrt(std::pow(node1->point.x-node2->point.x, 2)+
                     std::pow(node1->point.y-node2->point.y, 2));
}

void Grid::findPath (void) {
    if (!checkIfExists(openNodes, nodeStart))
        openNodes.push_back(nodeStart);
    while (openNodes.size() > 0) {
        Node* currentNode = openNodes.front();
        for (auto iter = openNodes.begin(); iter != openNodes.end(); iter++) {
            if ((*iter)->getFCost() <= currentNode->getFCost() ||
                (*iter)->hCost <= currentNode->hCost) {
                currentNode = *iter;
            }
        }
        openNodes.remove(currentNode);
        closedNodes.push_back(currentNode);
        if (currentNode == nodeEnd) {
            break;
        }
        std::list<Node*> neighbors = getNeighbors(currentNode);
        for (auto iter = neighbors.begin();
            iter != neighbors.end();
            iter++) {
            Node* neighbor = *iter;
            if (!neighbor->isTraversable || checkIfExists(closedNodes, neighbor)) {
                continue;
            }
            float newMovementCostToNeighbor = currentNode->gCost + getDistance(currentNode, neighbor);
            if (newMovementCostToNeighbor < currentNode->gCost ||
                !checkIfExists(openNodes, neighbor)) {
                neighbor->gCost = newMovementCostToNeighbor;
                neighbor->hCost = getDistance(neighbor, nodeEnd);
                neighbor->parent = currentNode;
                if (!checkIfExists(openNodes, neighbor)) {
                    openNodes.push_back(neighbor);
                }
            }
        }
        for (auto iter = openNodes.begin();
             iter != openNodes.end(); iter++) {
            Node* node = *iter;
            node->isOpen = true;
        }
    }
    retracePath();
    openNodes.clear();
    closedNodes.clear();
    return;
}

void Grid::retracePath (void) {
    path.clear();
    Node* node = nodeEnd;
    while (node != nodeStart) {
        path.push_back(node);
        node = node->parent;
    }
    return;
}
