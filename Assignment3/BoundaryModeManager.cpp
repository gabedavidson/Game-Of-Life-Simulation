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

// default constructor, classic mode
BoundaryModeManager::BoundaryModeManager(){
  mode = 'c';
}

// destructor
BoundaryModeManager::~BoundaryModeManager(){
  //
}

// gets the current mode represented as a char
char BoundaryModeManager::getMode(){
  return mode;
}

// change the mode
void BoundaryModeManager::changeMode(char m){
  mode = m;
}

// counts the number of neighbors present as mirrored neighbors
// this only accounts for mirrored neighbors -> used in conjunction with grid->checkNeighborsAround(...)
int BoundaryModeManager::checkMirrorNeighborsAround(int x, int y, GridOfLife* grid, int w, int h){
  int count = 0;

  // if is occupied and in corner
  if ((x == 0 && y == 0) || (x == 0 && y == h - 1) || (x == w - 1 && y == 0) || (x == w - 1 && y == h - 1)){
    if (grid->cellIsOccupied(x, y)){
      // cout << "is in corner" << endl;
      ++count;
    }
  }

  // if is occupied and against wall, reflects itself
  if (x == 0 || x == w - 1 || y == 0 || y == h - 1){
    if (grid->cellIsOccupied(x, y)){
      // cout << "reflects itself" << endl;
      ++count;
    }
  }

  if (y == 0){ // is along top wall
    if (grid->cellIsOccupied(x - 1, 0)){ // left of c
      ++count;
    }
    if (grid->cellIsOccupied(x + 1, 0)){ // right of c
      ++count;
    }
  }

  if (y == h - 1){ // is along bottom wall
    if (grid->cellIsOccupied(x - 1, 0)){ // left of c
      ++count;
    }
    if (grid->cellIsOccupied(x + 1, 0)){ // right of c
      ++count;
    }
  }

  if (x == 0){ // is along left wall
    if (grid->cellIsOccupied(0, x - 1)){ // below c
      ++count;
    }
    if (grid->cellIsOccupied(0, x + 1)){ // above c
      ++count;
    }
  }

  if (x == w - 1){ // is along right wall
    if (grid->cellIsOccupied(0, x - 1)){ // below c
      ++count;
    }
    if (grid->cellIsOccupied(0, x + 1)){ // above c
      ++count;
    }
  }

  return count;
}

// counts the number of neighbors present given a doughnut shaped grid
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
