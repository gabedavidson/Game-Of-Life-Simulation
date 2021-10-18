/*
Gabe Davidson
2338642
gadavidson@chapman.edu
CPSC 350-3
Assignment 3

Header file for the BoundaryModeManager class.
BoundaryModeManager knows which mode the simulation is running in and can find neighbors depending on the mode

Sources:
  - none
*/

#ifndef BOUNDARYMODEMANAGER_H
#define BOUNDARYMODEMANAGER_H

#include "Cell.h"
#include "GridOfLife.h"

class BoundaryModeManager{
  public:
    BoundaryModeManager();
    ~BoundaryModeManager();

    void changeMode(char m);
    char getMode();
    int checkMirrorNeighborsAround(int x, int y, GridOfLife* grid, int w, int h);
    int checkDoughnutNeighborsAround(int x, int y, GridOfLife* grid, int w, int h);
  private:
    char mode;
};

#endif
