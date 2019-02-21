#include "DrawManager.h"


bool DrawManager::draw() {
    _window.clear();
    _window.draw(_dataStorage.getTextData()[0]);
    _window.display();

    return true;

}

DrawManager::DrawManager(DataStorage &dataStorage, sf::RenderWindow &window) : _dataStorage(dataStorage),
                                                                               _window(window) {
    _dataStorage.getFontData().emplace_back();
    _dataStorage.getFontData()[0].loadFromFile("tnr.ttf");

    _dataStorage.getTextData().emplace_back("", _dataStorage.getFontData()[0], 14);
}
