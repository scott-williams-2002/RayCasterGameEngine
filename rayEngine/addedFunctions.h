#ifndef ADDED_FUNCTIONS_H
#define ADDED_FUNCTIONS_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

void rewriteFile(vector<vector<int>> map, int width, int height, string fileName);
vector<int> getWidthHeight(ifstream &fileIn, string fileName);
vector<vector<int>> readFile(ifstream &fileIn, int mapWidth, int mapHeight);
bool mouseIsUp(sf::Vector2f oldMousePosition, sf::Vector2f newMousePosition);
bool mouseIsLeft(sf::Vector2f oldMousePosition, sf::Vector2f newMousePosition);


void drawGun(sf::RenderWindow &window);
void drawCrossHair(sf::RenderWindow &window);
void rCaster(int mapWidth, int mapHeight, vector<vector<int>> map, bool addGun);
int colorWindow();
vector<vector<int>> clearWithWalls(vector<vector<int>> map, int width, int height);

#endif