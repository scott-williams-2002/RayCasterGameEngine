#ifndef TILE_LIST_H
#define TILE_LIST_H
#include "tile.h"
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class TileList : Tile
{
    private:
        vector<vector<Tile>> list;
        int mapWidth;
        int mapHeight;
    public:
        TileList();
        TileList(int mapWidth, int mapHeight);
        int width();
        int height();
        void addAllTiles(vector<vector<int>> map);
        void editTile(int height, int width, Tile thisTile);
        
        void drawAll(sf::RenderWindow &window);

};

#endif