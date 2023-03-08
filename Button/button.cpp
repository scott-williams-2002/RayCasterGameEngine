// Button Class by Scott Williams

#ifndef BUTTON_CPP
#define BUTTON_CPP

#include <SFML/Graphics.hpp>
#include <string>
#include "button.h"

using namespace std;
// default constructor sets the positions to 0
Button:: Button()
{
    xPos = 0;
    yPos = 0;
}

// parameterized constructor which sets button font and positions of rectange and text
Button:: Button(float width, float height, float xPosition, float yPosition)
{
    buttonWidth = width;
    buttonHeight = height;
    buttonContainer.setSize(sf::Vector2f(width, height));
    buttonContainer.setPosition(xPosition,yPosition);
}

void Button::setImage(string fileName)
{
    texture.loadFromFile(fileName);
    buttonContainer.setTexture(&texture);
}

// sets the button rectangle's fill color
void Button:: setButtonColor(sf::Color myColor)
{
    buttonContainer.setFillColor(myColor);
}

// adds the rectangle then the text on the button to the window (order is important)
void Button:: addToWindow(sf::RenderWindow &window)
{
    window.draw(buttonContainer);
}

// checks if user's mouse is on the button and returns boolean 
bool Button:: mouseContact(sf::RenderWindow &window)
{
    // gets the mouse's x and y positions from screen
    float mousePosX = sf::Mouse::getPosition(window).x;
    float mousePosY = sf::Mouse::getPosition(window).y;

    // basically, if the mouse is within the x range of the button...
    if (mousePosX > buttonContainer.getPosition().x && mousePosX < (buttonContainer.getPosition().x + buttonWidth))
    {
        // and if the mouse is within the y range of the button...
        if(mousePosY > buttonContainer.getPosition().y && mousePosY < (buttonContainer.getPosition().y + buttonHeight))
        {
            // then the mouse if on the button and return true
            return true;
        }
        else
        {
            // if not on button return false
            return false;
        }
    }

    return false;
}

// returns true if button is pressed 
bool Button::isClicked(sf::RenderWindow &window, sf::Event event)
{
    if(mouseContact(window) && event.type == sf::Event::MouseButtonPressed)
    {
        return true;
    }
    return false;
}


#endif