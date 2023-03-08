#include <SFML/Graphics.hpp>
#include "Button/button.h"
#include "Button/button.cpp"
#include "rayEngine/rayEngine.cpp"


/*
This is the src code for the Chronicle game engine by Scott Williams. 
This engine is still a work in progress but some heavy refactoring... and a new 
graphics library (currently SFML) is most likely needed to actually create a properly working 
engine. When working properly, this engine allows the user to edit a map using some simple button
clicks. The map has individual cells blocks which can be used to create walls or mazes. After editing
the user can press "e" on their keyboard to initiate the raycaster. The raycaster simulates
a 3D representation of the map using rays projected from the players position to calculate the 
distance to each wall or cell block in order to properly draw each slice of the object in pseudo-3d. Additionally
by pressing "g" then "e" in the map editor, the engine will be put in FPS mode where the player can walk around the 3d 
representation of the map with a rifle. Currently there is no shooting capability but that is coming soon. 
*/

void aboutUs()
{
    sf::RenderWindow window(sf::VideoMode(500,500), "About Us");
    sf::Event event;

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){window.close();}
        }

        sf::RectangleShape rect;
        sf::Texture texture;
        //texture.loadFromFile("assets/about_us.png");
        rect.setSize(sf::Vector2f(500,500));
        rect.setFillColor(sf::Color(200, 20, 50));
        rect.setPosition(sf::Vector2f(0,0));
        //rect.setTexture(&texture);
        window.draw(rect);
        window.display();
    }
    
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200,800), "test");
    sf::Event event;
    

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){window.close();}
        }
        //window.clear(sf::Color(0,0,0));

        sf::RectangleShape background;
        sf::Texture fireBack;
        fireBack.loadFromFile("assets/fire_back.png");
        background.setPosition(sf::Vector2f(0,0));
        background.setSize(sf::Vector2f(1200,800));
        background.setTexture(&fireBack);
        window.draw(background);
        

        


        Button logo(1200,150,0,0);
        logo.setImage("assets/chronicle_logo.png");
        logo.addToWindow(window);

        Button newRC(1200,200,0,160);
        newRC.setImage("assets/rc5.png");
        newRC.addToWindow(window);
        

        


        if(newRC.isClicked(window, event))
        {
            
            rayEngine();
        }

        if(logo.isClicked(window, event))
        {
            aboutUs();
        }
        



        window.display();
    }
}