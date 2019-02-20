#ifndef HOMEWORK1_DRAWMANAGER_H
#define HOMEWORK1_DRAWMANAGER_H

#include "DataStorage.h"
#include <SFML/Graphics.hpp>


class DrawManager {
public:
    DrawManager(DataStorage &, sf::RenderWindow &);

    bool draw();
private:
    DataStorage &_dataStorage;
    sf::RenderWindow &_window;
};


#endif
