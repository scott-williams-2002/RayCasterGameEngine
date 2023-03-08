// Button Class by Scott Williams

#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

// button class for use in main game loop
class Button
{
    public:
        Button();
        Button(float width, float height, float xPosition, float yPosition);
        void setImage(string fileName);
        void setButtonColor(sf::Color myColor);
        void addToWindow(sf::RenderWindow &window);
        bool mouseContact(sf::RenderWindow &window);
        bool isClicked(sf::RenderWindow &window, sf::Event event);
    private:
        sf::RectangleShape buttonContainer;
        sf::Texture texture;
        float xPos;
        float yPos;
        float buttonWidth;
        float buttonHeight;
};




#endif