#include <string>
#include <vector>
#include <iostream>
#include "cell.h"

using namespace sf;
using namespace std;

Cell::Cell(int i, int j, int size) {
  mI = i;
  mJ = j;
  mSize = size;
  notVisited = true;
  mColor = Color::White;
  mWalls = vector<string>();
  mWalls.insert(mWalls.begin(), {"N", "E", "S", "W"});
}

Cell::Cell() {
  mSize = -1;
}

int Cell::getI() {
  return mI;
}

int Cell::getJ() {
  return mJ;
}

bool Cell::exists() {
  if (mSize != -1) {
    return true;
  }
  return false;
}

void Cell::removeWall(string wall) {
  if (!mWalls.empty()) {
    vector<string>::iterator p;
    for (vector<string>::iterator it = mWalls.begin(); it != mWalls.end(); it++) {
      if (*it == wall) {
        p = it;
      }
    }
    if (*p == wall) {
      mWalls.erase(p);
    }
  }
}

vector<string> Cell::getWalls() {
  return mWalls;
}

VertexArray Cell::getLines() {
  int x = mI * mSize;
  int y = mJ * mSize;
  int numVertices = mWalls.size() * 2;
  VertexArray lines(Lines, numVertices);

  int i = 0;
  for (vector<string>::iterator it = mWalls.begin(); it != mWalls.end(); it++) {
    if (*it == "N") {
      lines[i].position = Vector2f(x, y);
      lines[i + 1].position = Vector2f(x + mSize, y);
      i += 2;
    } else if (*it == "E") {
      lines[i].position = Vector2f(x + mSize, y);
      lines[i + 1].position = Vector2f(x + mSize, y + mSize);
      i += 2;
    } else if (*it == "S") {
      lines[i].position = Vector2f(x, y + mSize);
      lines[i + 1].position = Vector2f(x + mSize, y + mSize);
      i += 2;
    } else {
      lines[i].position = Vector2f(x, y);
      lines[i + 1].position = Vector2f(x, y + mSize);
      i += 2;
    }
  }

  return lines;
}
