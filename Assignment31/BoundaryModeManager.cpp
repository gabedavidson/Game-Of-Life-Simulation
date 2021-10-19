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

  if (x == w || x == 0 || y == h || y == 0){ // is in corner
    ++count;
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

  if (count > 0){
    ++count; // if count > 0 then c has mirrored neighbors, therefore must mirror itself
  }

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
