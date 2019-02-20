#include "DataStorage.h"

std::vector<sf::Texture> &DataStorage::getTextureData() {
    return _textures;
}

std::vector<sf::Text> &DataStorage::getTextData() {
    return _texts;
}

std::vector<sf::Font> &DataStorage::getFontData() {
    return _fonts;
}

std::vector<sf::Sprite> &DataStorage::getSprite() {
    return _sprites;
}

DataStorage::DataStorage(std::string file_name) {
    _reader.open(file_name);
}

DataStorage::~DataStorage() {
    _reader.close();
}

std::ifstream &DataStorage::getReader() {
    return _reader;
}
