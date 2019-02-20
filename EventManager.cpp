#include "EventManager.h"

bool EventManager::manage(const sf::Event &event) {

    if (event.type == sf::Event::Closed) {
        _window.close();
        return false;
    } else if (event.type == sf::Event::KeyPressed) {
        std::string next_word;

        for (size_t i = 0; i < 10; ++i) {
            next_word += static_cast<char>(_dataStorage.getReader().get());
        }

        _dataStorage.getTextData()[0].setString(_dataStorage.getTextData()[0].getString() + next_word);

        if (_dataStorage.getTextData()[0].getGlobalBounds().height >= _window.getSize().y and
            next_word.find('\n') != std::string::npos) {
            _dataStorage.getTextData()[0].move(0, _window.getSize().y - _dataStorage.getTextData()[0].getPosition().y -
                                                  _dataStorage.getTextData()[0].getGlobalBounds().height -
                                                  static_cast<float>(_dataStorage.getTextData()[0].getCharacterSize()));
        }

        fflush(nullptr);
    }

    return true;
}

EventManager::EventManager(DataStorage &dataStorage, sf::RenderWindow &window) : _dataStorage(dataStorage),
                                                                                 _window(window) {}
