#ifndef ADDED_FUNCTIONS_CPP
#define ADDED_FUNCTIONS_CPP
#include "addedFunctions.h"
#include <SFML/Graphics.hpp>
#include <cmath>
//#include "rayEngine/speedStruct.h"
//#include "rayEngine/Sliders/SliderSFML.h"



using namespace std;

// rewrites the map.chron file with current map information
void rewriteFile(vector<vector<int>> map, int width, int height, string fileName)
{
    std::ofstream ofs (fileName);
    ofs << width << endl;
    ofs << height << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ofs << map.at(i).at(j);
            ofs << " ";
        }
        ofs << "" << endl;
        
    }
    ofs.close();
}

// gets the header width and height from the map.chron file
vector<int> getWidthHeight(ifstream &fileIn, string fileName)
{
    fileIn.open(fileName);

    int mapWidth, mapHeight;
    fileIn >> mapWidth;
    fileIn >> mapHeight;
    vector<int> returnedVal; 
    returnedVal.push_back(mapWidth); 
    returnedVal.push_back(mapHeight);
    return returnedVal;
}

// gets the map info from the map.chron file and returns a 2d int vector
vector<vector<int>> readFile(ifstream &fileIn, int mapWidth, int mapHeight)
{
    // .chron format is width, height, then 2d map 
    
    
    vector<vector<int>> vList;
    

    for (int i = 0; i < mapHeight; i++)
    {
        vector<int> row;
        for (int j = 0; j < mapWidth; j++)
        {
            int tempInt;
            fileIn >> tempInt;
            row.push_back(tempInt);
        }
        vList.push_back(row);
    }
    fileIn.close();
    return vList;
}

bool mouseIsUp(sf::Vector2f oldMousePosition, sf::Vector2f newMousePosition)
{
    if(newMousePosition.y < oldMousePosition.y){return true;}
    else{return false;}
}
bool mouseIsLeft(sf::Vector2f oldMousePosition, sf::Vector2f newMousePosition)
{
    if(newMousePosition.x < oldMousePosition.x){return true;}
    else{return false;}
}

void drawGun(sf::RenderWindow &window)
{
  sf::ConvexShape gun;
  gun.setPointCount(4);
  gun.setPoint(0, sf::Vector2f(350 + 800,800)); // bottom left
  gun.setPoint(1, sf::Vector2f(450 + 800,800)); // bottom right
  gun.setPoint(2, sf::Vector2f(410 + 800,500)); // top right
  gun.setPoint(3, sf::Vector2f(390 + 800, 500)); // top left
  gun.setFillColor(sf::Color(182,114,51));
  window.draw(gun);

  // depth effect slope is 30 rise over 4 run
  sf::ConvexShape bottomSight;
  bottomSight.setPointCount(4);
  bottomSight.setPoint(0, sf::Vector2f(390 + 800,750)); // bottom left
  bottomSight.setPoint(1, sf::Vector2f(410 + 800,750)); // bottom right
  bottomSight.setPoint(2, sf::Vector2f(406 + 800,720)); // top right
  bottomSight.setPoint(3, sf::Vector2f(394 + 800, 720)); // top left
  bottomSight.setFillColor(sf::Color(52,53,46));
  window.draw(bottomSight);

  sf::ConvexShape topSight;
  topSight.setPointCount(4);
  topSight.setPoint(0, sf::Vector2f(398 + 800,500)); // top left
  topSight.setPoint(1, sf::Vector2f(403 + 800,500)); // top right
  topSight.setPoint(2, sf::Vector2f(405 + 800,515)); // bottom right
  topSight.setPoint(3, sf::Vector2f(395 + 800, 515)); // bottom left
  topSight.setFillColor(sf::Color(52,53,46));
  window.draw(topSight);
}

void drawCrossHair(sf::RenderWindow &window)
{
  sf::Texture cHTexture;
  cHTexture.loadFromFile("rayEngine/ray_assets/crosshair55.png");
  sf::Sprite crossHair;
  crossHair.setTexture(cHTexture);
  crossHair.setScale(sf::Vector2f(2,2));
  crossHair.setPosition(sf::Vector2f(400 + 800,400));
  crossHair.setColor(sf::Color(255,0,0));
  window.draw(crossHair);

}

void drawMiniMap(sf::RenderWindow &window, int width, int height, vector<vector<int>> map, sf::Vector2f playerPos, float rotation)
{
	sf::RectangleShape temp;
	temp.setSize(sf::Vector2f(10, 10));
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int coord = map.at(i).at(j);
			temp.setPosition(sf::Vector2f(10*j, 10*i));
			if(coord == 0)
			{
				temp.setFillColor(sf::Color(150,150,150));
			}
			if(coord == 1)
			{
				temp.setFillColor(sf::Color(255,0,0));
			}
			if(coord == 2)
			{
				temp.setFillColor(sf::Color(0,255,0));
			}
			if(coord == 3)
			{
				temp.setFillColor(sf::Color(0,0,255));
			}
			if(coord == 4)
			{
				temp.setFillColor(sf::Color(0,0,255));
			}
			window.draw(temp);
		}
	}
	sf::Texture shipTexture;
	shipTexture.loadFromFile("rayEngine/ray_assets/ship.png");
	sf::Sprite ship;
	ship.setTexture(shipTexture);
	ship.setPosition(playerPos);
	window.draw(ship);

}

void setSpeed(sf::RenderWindow &window)
{
	return;
}


void rCaster(int mapWidth, int mapHeight, vector<vector<int>> map, bool addGun)
{
  int w = 800; //640 480
  int h = 800;
  double posX = 22, posY = 12;  //x and y start position
  double dirX = -1, dirY = 0; //initial direction vector
  double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
  
  // sky stuff for loading sky in top half
  sf::Texture sky;
  sky.loadFromFile("rayEngine/ray_assets/sky.png");
  sf::RectangleShape skyBox;
  skyBox.setSize(sf::Vector2f(800,400));
  skyBox.setTexture(&sky);
  skyBox.setPosition(sf::Vector2f(800,0));
  

  int worldMap[mapWidth][mapHeight];
  for(int i = 0; i < mapWidth; i++)
  {
      for(int j = 0; j < mapHeight; j++)
      {
          worldMap[i][j] = map.at(i).at(j);
      }
  }


  // button bool events
    bool isUp,isDown,isLeft,isRight;
    isUp = false;
    isDown = false;
    isLeft = false;
    isRight = false;

  sf::RenderWindow window( sf::VideoMode(1600, h), "RayCasterTest" );
  window.setFramerateLimit(60);
  sf::Event event;

  double moveSpeed = 0.1; //the constant value is in squares/second
  double rotSpeed = 0.04;
  while(window.isOpen() )
  {
    window.clear(sf::Color(150,150,150));
	drawMiniMap(window, mapWidth, mapHeight, map, sf::Vector2f(posY*10, posX*10), 1 );
	setSpeed(window);
    window.draw(skyBox);
    while( window.pollEvent(event) ) {

            if(event.type == sf::Event::Closed){window.close();}

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){window.close();}

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){isUp = true;}
            else{isUp = false;}

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){isDown = true;}
            else{isDown = false;}

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){isLeft = true;}
            else{isLeft = false;}

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){isRight = true;} 
            else{isRight = false;}

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){moveSpeed = 0.5;}
            else{moveSpeed = 0.1;}
    }
        
    for(int x = 0; x < w; x++)
    {
      //calculate ray position and direction
      double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
      double rayDirX = dirX + planeX * cameraX;
      double rayDirY = dirY + planeY * cameraX;
      //which box of the map we're in
      int mapX = int(posX);
      int mapY = int(posY);

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;


      double deltaDistX = abs(1 / rayDirX);
      double deltaDistY = abs(1 / rayDirY);

      double perpWallDist;



      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY; 

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }
      //perform DDA
      while(hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if(worldMap[mapX][mapY] > 0) hit = 1;
      }

      if(side == 0) perpWallDist = (sideDistX - deltaDistX);
      else { perpWallDist = (sideDistY - deltaDistY)};

      //Calculate height of line to draw on screen
      int lineHeight = (int)(h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if(drawEnd >= h) drawEnd = h - 1;

      //choose wall color
      sf::Color color;
      switch(worldMap[mapX][mapY])
      {
        case 1:  color.r = 255; color.g = 0; color.b = 0;    break; //red
        case 2:  color.r = 0; color.g = 255; color.b = 0;    break; //green
        case 3:  color.r = 0; color.g = 0; color.b = 255;    break; //blue
        case 4:  color.r = 255; color.g = 255; color.b = 255;    break; //white
        default: color.r = 255; color.g = 255; color.b = 0;    break; //yellow
      }

      //give x and y sides different brightness
      if(side == 1) 
      {
        color.r = color.r /2;
        color.g = color.g / 2;
        color.b = color.b / 2;
      }

      //draw the pixels of the stripe as a vertical line

      sf::RectangleShape rect;
      rect.setPosition(sf::Vector2f(x+800, drawStart));
      rect.setSize(sf::Vector2f(1, drawEnd - drawStart));
      rect.setFillColor(color);
      window.draw(rect);
      
      

      

    }
    

    //speed modifiers
     //the constant value is in radians/second
    
    //move forward if no wall in front of you
    if(isUp)
    {
      if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == 0) posX += dirX * moveSpeed;
      if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
    }
    //move backwards if no wall behind you
    if(isDown)
    {
      if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == 0) posX -= dirX * moveSpeed;
      if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == 0) posY -= dirY * moveSpeed;
    }
    //rotate to the right
    if(isRight)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
      dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
      planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }
    //rotate to the left
    if(isLeft)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
      dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
      planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    }


    //drawCrossHair(window);
    //drawGun(window);

    // next step draw fire and enemy. then health.then add to itch for people to try
    

    
    

    if(addGun)
    {
        drawGun(window);
        drawCrossHair(window);
    }

    window.display();
  }
}

int colorWindow()
{
    sf::RenderWindow window(sf::VideoMode(200,120), "Choose a Color");
    sf::Event event;

    // 1, 2, 3, 4
    // r, g, b, w
    sf::RectangleShape redRect;
    redRect.setFillColor(sf::Color(255,0,0));
    redRect.setSize(sf::Vector2f(50,100));
    redRect.setPosition(sf::Vector2f(0,0));

    sf::RectangleShape greenRect;
    greenRect.setFillColor(sf::Color(0,255,0));
    greenRect.setSize(sf::Vector2f(50,100));
    greenRect.setPosition(sf::Vector2f(50,0));

    sf::RectangleShape blueRect;
    blueRect.setFillColor(sf::Color(0,0,255));
    blueRect.setSize(sf::Vector2f(50,100));
    blueRect.setPosition(sf::Vector2f(100,0));

    sf::RectangleShape whiteRect;
    whiteRect.setFillColor(sf::Color(255,255,255));
    whiteRect.setSize(sf::Vector2f(50,100));
    whiteRect.setPosition(sf::Vector2f(150,0));

    sf::RectangleShape blankSpace;
    blankSpace.setFillColor(sf::Color(150,150,150));
    blankSpace.setSize(sf::Vector2f(200,20));
    blankSpace.setPosition(sf::Vector2f(0,100));


    sf::Mouse mouse;


    while(window.isOpen())
    {
        int xPos = mouse.getPosition(window).x;
        int yPos = mouse.getPosition(window).y;

        while( window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){window.close();}
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){window.close();}

            if(xPos >= 0 && xPos < 50 && yPos <= 100 && event.type == sf::Event::MouseButtonPressed){return 1;}
            if(xPos >= 50 && xPos < 100 && yPos <= 100 && event.type == sf::Event::MouseButtonPressed){return 2;}
            if(xPos >= 100 && xPos < 150 && yPos <= 100 && event.type == sf::Event::MouseButtonPressed){return 3;}
            if(xPos >= 150 && xPos < 200 && yPos <= 100 && event.type == sf::Event::MouseButtonPressed){return 4;}

            if(yPos > 100 && event.type == sf::Event::MouseButtonPressed){return 0;}
            
            
            

            
        }

        window.draw(redRect);
        window.draw(greenRect);
        window.draw(blueRect);
        window.draw(whiteRect);
        window.draw(blankSpace);
        window.display();
        
    }

}

vector<vector<int>> clearWithWalls(vector<vector<int>> map, int width, int height)
{
    int wallColor = colorWindow();
    vector<vector<int>> newMap;

    vector<int> tempVec;
    for (int x = 0; x < width; x++){tempVec.push_back(wallColor);}
    newMap.push_back(tempVec);

    for(int i = 0; i < height -2; i++)
    {
        vector<int> temp;
        temp.push_back(wallColor);
        for (int j = 0; j < width - 2; j++)
        {
            temp.push_back(0);
        }
        temp.push_back(wallColor);
        newMap.push_back(temp);
    }

    newMap.push_back(tempVec);

    return newMap;
}

#endif