//
// Created by Yang on 18/11/2017.
//

#ifndef TANKCRAFT_UTILITY_H
#define TANKCRAFT_UTILITY_H
#include <sstream>
namespace sf
{
    class Sprite;
    class Text;
}

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string toString(const T& value);

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);



#endif //TANKCRAFT_UTILITY_H
