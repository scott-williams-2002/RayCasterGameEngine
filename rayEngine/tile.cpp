#ifndef TILE_CPP
#define TILE_CPP
#include "tile.h"
#include <iostream>



Tile::Tile()
{
    width = 0;
}
Tile::Tile(int tileWidth)
{
    width = tileWidth;
    square.setSize(sf::Vector2f(width,width));
}
void Tile::setLocation(sf::Vector2f tileLocation)
{
    location = tileLocation;
    square.setPosition(location);
   
}
void Tile::setColor(sf::Color tileColor)
{
    color = tileColor;
    square.setFillColor(color);
}
sf::Vector2f Tile::getLocation()
{
    return location;
}
sf::RectangleShape Tile::getShape()
{
    return square;
}



#endif