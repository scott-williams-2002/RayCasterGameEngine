#ifndef RAY_ENGINE_CPP
#define RAY_ENGINE_CPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include "tile.h"
#include "tile.cpp"
#include "tileList.h"
#include "tileList.cpp"
#include "addedFunctions.h"
#include "addedFunctions.cpp"
#include <string>



using namespace std;

void tempWindow()
{
    sf::RenderWindow window(sf::VideoMode(100,100), "test window");
    sf::Event event;

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){window.close();}
        }
    }


}



int rayEngine()
{
    string fileName = "rayEngine/ray_assets/map.chron";
    ifstream fileIn;
    vector<int> mapDimensions = getWidthHeight(fileIn, fileName);
    int mapWidth = mapDimensions.at(0);
    int mapHeight = mapDimensions.at(1);

    float squareWidth = 800 / mapWidth;

    vector<vector<int>> vList = readFile(fileIn ,mapWidth, mapHeight);

    TileList tileList(mapWidth, mapHeight);
    tileList.addAllTiles(vList);
    
    

    






        

    
    
    sf::Mouse mouse;
    bool isPressed = false;
    bool eClick = false;
    bool addGun = false;

    sf::Vector2f oldMousePosition;
    oldMousePosition.x = 0.0;
    oldMousePosition.y = 0.0;
    
    sf::Vector2i mouseMapPosition;
    mouseMapPosition.x = 0;
    mouseMapPosition.y = 0;
    
    
    
    sf::RenderWindow window(sf::VideoMode(mapWidth * squareWidth, mapHeight * squareWidth), "RC");
    window.setFramerateLimit(60);
    sf::Event event;

    while(window.isOpen())
    {
        window.clear();
        while( window.pollEvent(event) )
        {
            if(event.type == sf::Event::Closed){window.close();}

            // bool to keep track of mouse being pressed or not
            if(event.type == sf::Event::MouseButtonPressed)
            {
                isPressed = true;
            }
            else{isPressed = false;}

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){eClick = true;}
            else{eClick = false;}

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)){addGun = true;}

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            {
                vList = clearWithWalls(vList, mapWidth, mapHeight);
                tileList.addAllTiles(vList);
            }
        }

        if(isPressed)
        {
            
            mouseMapPosition.x = mouse.getPosition(window).x / squareWidth;
            mouseMapPosition.y = mouse.getPosition(window).y / squareWidth;

            int whichColor = colorWindow();
            vList.at(mouseMapPosition.y).at(mouseMapPosition.x) = whichColor;
            tileList.addAllTiles(vList);

            isPressed = false;
            

           


            /*
            if(mouseIsLeft(oldMousePosition, sf::Vector2f(mouse.getPosition().x, mouse.getPosition().y)))
            {
                Tile thisTile;
                thisTile.setColor(sf::Color(0,0,255));
                
                tileList.addTile(mouseMapPosition.x - 1, mouseMapPosition.y, thisTile);
            }
            */
           
            
        }

        if(eClick)
        {
            rCaster(24,24, vList, addGun);
        }
        oldMousePosition = sf::Vector2f(mouse.getPosition().x, mouse.getPosition().y);
        
        
        tileList.drawAll(window);
        window.display();
        rewriteFile(vList,mapWidth, mapHeight, fileName);
    }
    
    return 0;

    // copy the entire contents of the tile list into a new written file
}

#endif