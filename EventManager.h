#ifndef HOMEWORK1_EVENTMANGER_H
#define HOMEWORK1_EVENTMANGER_H

#include <SFML/Graphics.hpp>
#include "DataStorage.h"


class EventManager {
public:
    EventManager(DataStorage &, sf::RenderWindow &);

    bool manage(const sf::Event &);

private:
    sf::RenderWindow &_window;
    DataStorage &_dataStorage;
};


#endif
