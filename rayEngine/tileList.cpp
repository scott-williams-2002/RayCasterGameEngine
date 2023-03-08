#ifndef TILE_LIST_CPP
#define TILE_LIST_CPP

#include "tileList.h"
using namespace std;

TileList::TileList()
{
    mapWidth = 0;
    mapHeight = 0;
}
TileList::TileList(int width, int height)
{
    mapWidth = width;
    mapHeight = height;
}
int TileList::width()
{
    return mapWidth;
}
int TileList::height()
{
    return mapHeight;
}

void TileList::addAllTiles(vector<vector<int>> map)
{
    if(list.size() > 0){list.clear();}

    for(int i = 0; i < mapHeight; i++)
    {
        vector<Tile> tempList;
        for (int j = 0; j < mapWidth; j++)
        {
            Tile thisTile(100);
            thisTile.setLocation(sf::Vector2f(j * 33.33, i * 33.33));
            
            if(map.at(i).at(j) == 1){thisTile.setColor(sf::Color(255,0,0));} // red
            else if(map.at(i).at(j) == 2){thisTile.setColor(sf::Color(0,255,0));} // green
            else if(map.at(i).at(j) == 3){thisTile.setColor(sf::Color(0,0,255));} // blue
            else if(map.at(i).at(j) == 4){thisTile.setColor(sf::Color(255,255,255));} // white
            else {thisTile.setColor(sf::Color(150,150,150));}

            tempList.push_back(thisTile);
            
        }
        list.push_back(tempList);
    }
}

void TileList::editTile(int height, int width, Tile thisTile)
{
    list.at(height).at(width) = thisTile;
}

void TileList::drawAll(sf::RenderWindow &window)
{
    for(int i = 0; i < mapHeight; i++)
    {
        for(int j = 0; j < mapWidth; j++)
        {
            window.draw(list.at(i).at(j).getShape());
        }
    }
}
#endif