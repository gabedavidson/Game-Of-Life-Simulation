/*
Gabe Davidson
2338642
gadavidson@chapman.edu
CPSC 350-3
Assignment 3

Implementation file for the BoundaryModeManager class.
BoundaryModeManager knows which mode the simulation is running in and can find neighbors depending on the mode

Sources:
  - none
*/

#include "BoundaryModeManager.h"
#include <iostream>

using namespace std;

BoundaryModeManager::BoundaryModeManager(){
  mode = 'c';
}

BoundaryModeManager::~BoundaryModeManager(){
  //
}

char BoundaryModeManager::getMode(){
  return mode;
}

void BoundaryModeManager::changeMode(char m){
  mode = m;
}

// this only accounts for mirrored neighbors -> used in conjunction with grid->checkNeighborsAround(...)
int BoundaryModeManager::checkMirrorNeighborsAround(int x, int y, GridOfLife* grid, int w, int h){
  int count = 0;

  cout << "\ncoords: " << x << ", " << y << endl;
  grid->printGrid();

  // if is occupied and in corner
  if ((x == 0 && y == 0) || (x == 0 && y == h - 1) || (x == w - 1 && y == 0) || (x == w - 1 && y == h - 1)){
    if (grid->cellIsOccupied(x, y)){
      cout << "is in corner" << endl;
      ++count;
    }
  }

  // if is occupied and against wall, reflects itself
  if (x == 0 || x == w - 1 || y == 0 || y == h - 1){
    if (grid->cellIsOccupied(x, y)){
      cout << "reflects itself" << endl;
      ++count;
    }
  }

  if (y == 0){ // is along top wall
    if (grid->cellIsOccupied(x - 1, 0)){ // left of c
      cout << "top, left of cell" << endl;
      ++count;
    }
    if (grid->cellIsOccupied(x + 1, 0)){ // right of c
      cout << "top, right of cell" << endl;
      ++count;
    }
  }

  if (y == h - 1){ // is along bottom wall
    if (grid->cellIsOccupied(x - 1, h - 1)){ // left of c
      cout << "bottom, left of cell" << endl;
      ++count;
    }
    if (grid->cellIsOccupied(x + 1, h - 1)){ // right of c
      cout << "bottom, left of cell" << endl;
      ++count;
    }
  }

  if (x == 0){ // is along left wall
    cout << "left" << endl;
    if (grid->cellIsOccupied(0, y + 1)){
      cout << "occupied below" << endl;
    }
    else {
      cout << "not occupied below" << endl;
    }
    if (grid->cellIsOccupied(0, y + 1)){ // below c
      cout << "left, below of cell" << endl;
      ++count;
    }
    cout << 0 << ", " << y - 1 << endl;
    if (grid->cellIsOccupied(0, y - 1)){ // above c
      cout << "left, above of cell" << endl;
      ++count;
    }
  }

  if (x == w - 1){ // is along right wall
    if (grid->cellIsOccupied(w - 1, y + 1)){ // below c
      cout << "right, below of cell" << endl;
      ++count;
    }
    if (grid->cellIsOccupied(w - 1, y - 1)){ // above c
      cout << "right, above of cell" << endl;
      ++count;
    }
  }

  cout << "mirror neighbors: " << count << endl;

  return count;
}

// this only accounts for doughnut neighbors -> used in conjunction with grid->checkNeighborsAround(...)
int BoundaryModeManager::checkDoughnutNeighborsAround(int x, int y, GridOfLife* grid, int w, int h){
  int count = 0;

  if (y == 0){ // is along top wall
    for (int i = -1; i < 2; ++i){
      if (grid->cellIsOccupied(x + i, h - 1)){
        ++count;
      }
    }
  }

  if (y == h - 1){ // is along bottom wall
    for (int i = -1; i < 2; ++i){
      if (grid->cellIsOccupied(x + i, 0)){
        ++count;
      }
    }
  }

  if (y == 0){ // is along left wall
    for (int i = -1; i < 2; ++i){
      if (grid->cellIsOccupied(w - 1, y + i)){
        ++count;
      }
    }
  }

  if (y == 0){ // is along right wall
    for (int i = -1; i < 2; ++i){
      if (grid->cellIsOccupied(0, y + i)){
        ++count;
      }
    }
  }

  return count;
}
