#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "cell.h"

using namespace sf;
using namespace std;

namespace maze_gen {
  auto windowWidth = 401;
  auto windowHeight = 401;
  auto cellRatio = 0.05;
}

Cell pickRandomNeighbor(Cell cell, vector<vector<Cell>> grid) {
  int i = cell.getI();
  int j = cell.getJ();
  auto pool = vector<Cell>();
  if (i > 0 && grid[i - 1][j].notVisited) {
      pool.push_back(grid[i - 1][j]);
  }
  if (i < grid.size() - 1 && grid[i + 1][j].notVisited) {
      pool.push_back(grid[i + 1][j]);
  }
  if (j > 0 && grid[i][j - 1].notVisited) {
      pool.push_back(grid[i][j - 1]);
  }
  if (j < grid[i].size() - 1 && grid[i][j + 1].notVisited) {
      pool.push_back(grid[i][j + 1]);
  }

  if (!pool.empty()) {
    return pool[rand() % pool.size()];
  }
  return Cell();
}

void removeWalls(Cell &cell, Cell &neighbor) {
  if (cell.getI() > neighbor.getI()) {
    cell.removeWall("W");
    neighbor.removeWall("E");
  } else if (cell.getI() < neighbor.getI()) {
    cell.removeWall("E");
    neighbor.removeWall("W");
  } else if (neighbor.getJ() > cell.getJ()) {
    cell.removeWall("S");
    neighbor.removeWall("N");
  } else {
    cell.removeWall("N");
    neighbor.removeWall("S");
  }
}

void generate(vector<vector<Cell>> &grid) {
  srand(time(NULL));

  int start = floor(rand() % grid.size());
  grid[start][0].removeWall("N");

  int end = floor(rand() % grid.size());
  grid[end][grid.size() - 1].removeWall("S");

  auto stack = vector<Cell>();
  stack.push_back(grid[start][0]);
  int depth = 0;

  while (!stack.empty()) {
    Cell current = stack.back();
    if (current.exists()) {
      grid[current.getI()][current.getJ()].notVisited = false;
      Cell neighbor = pickRandomNeighbor(current, grid);
      if (neighbor.exists() && depth < 10) {
        depth++;
        stack.push_back(neighbor);
        removeWalls(
          grid[current.getI()][current.getJ()],
          grid[neighbor.getI()][neighbor.getJ()]
        );
      } else {
        depth = 0;
        stack.pop_back();
      }
    } else {
      stack.pop_back();
    }
  }
}

vector<vector<Cell>> createGrid() {
  int cellSize;
  if (maze_gen::windowWidth < maze_gen::windowHeight) {
    cellSize = int(floor(maze_gen::windowWidth * maze_gen::cellRatio));
  } else {
    cellSize = int(floor(maze_gen::windowHeight * maze_gen::cellRatio));
  }
  int gridRows = int(floor(maze_gen::windowHeight / cellSize));
  int gridCols = int(floor(maze_gen::windowWidth / cellSize));

  vector<vector<Cell>> grid = vector<vector<Cell>>();
  for (int i = 0; i < gridCols; i++) {
    grid.push_back(vector<Cell>());
    for (int j = 0; j < gridRows; j++) {
      grid[i].push_back(Cell(i, j, cellSize));
    }
  }

  return grid;
}

int main() {
  vector<vector<Cell>> grid = createGrid();
  generate(grid);

  RenderWindow window(
    sf::VideoMode(maze_gen::windowWidth, maze_gen::windowHeight),
    "Maze Generator"
  );

  window.setFramerateLimit(5);

  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed) {
        window.close();
      } else if (event.type == Event::MouseButtonPressed) {
        grid = createGrid();
        generate(grid);
      }
    }

    window.clear();
    for (vector<vector<Cell>>::iterator col = grid.begin(); col != grid.end(); col++) {
      for (vector<Cell>::iterator row = (*col).begin(); row != (*col).end(); row++) {
        VertexArray lines = (*row).getLines();
        window.draw(lines, Transform().translate(Vector2f(1, 1)));
      }
    }
    window.display();
  }

  return 0;
}

