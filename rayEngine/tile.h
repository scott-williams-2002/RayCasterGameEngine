#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include <vector>



class Tile
{
    protected:
        sf:: RectangleShape square;
        sf:: Texture texture;
        sf:: Color color;
        sf:: Vector2f location;
        int width;
    public:
        Tile();
        Tile(int tileWidth);
        void setLocation(sf::Vector2f tileLocation);
        void setColor(sf::Color tileColor);
        sf::Vector2f getLocation();
        sf::RectangleShape getShape();
        
};

#endif