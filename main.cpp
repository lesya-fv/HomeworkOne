#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "EventManager.h"
#include "DrawManager.h"
#include "DataStorage.h"

const uint WINDOW_WIDTH = 800;
const uint WINDOW_HEIGHT = 600;
const std::string WINDOW_NAME = "Coding IDE";

const std::string FILE_NAME = "futex.c";


int main(){
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);

    DataStorage dataStorage(FILE_NAME);

    EventManager eventManager(dataStorage, window);
    DrawManager drawManager(dataStorage, window);

    bool end = false;

    while (not end) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            end = not eventManager.manage(event);
        }

        drawManager.draw();
    }

    return 0;
}

