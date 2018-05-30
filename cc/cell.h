#ifndef MAZE_GEN_CELL_H
#define MAZE_GEN_CELL_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class Cell {
  private:
    int mI;
    int mJ;
    int mSize;
    vector<string> mWalls;
    sf::Color mColor;

  public:
    bool notVisited;

    Cell(int i, int j, int size);
    Cell();
    int getI();
    int getJ();
    bool exists();
    vector<string> getWalls();
    void removeWall(string wall);
    sf::VertexArray getLines();
};

#endif
