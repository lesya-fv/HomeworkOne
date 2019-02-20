#ifndef HOMEWORK1_DATASTORAGE_H
#define HOMEWORK1_DATASTORAGE_H

#include <fstream>
#include <SFML/Graphics.hpp>
#include <vector>


class DataStorage {
public:
    explicit DataStorage(std::string);

    std::vector<sf::Texture> &getTextureData();

    std::vector<sf::Text> &getTextData();

    std::vector<sf::Font> &getFontData();

    std::vector<sf::Sprite> &getSprite();

    std::ifstream &getReader();

    ~DataStorage();

private:
    std::vector<sf::Texture> _textures;
    std::vector<sf::Text> _texts;
    std::vector<sf::Font> _fonts;
    std::vector<sf::Sprite> _sprites;

    std::ifstream _reader;
};


#endif
