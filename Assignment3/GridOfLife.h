/*
Gabe Davidson
2338642
gadavidson@chapman.edu
CPSC 350-3
Assignment 3

Header file for the GridOfLife class.
GridOfLife holds the 2D array (grounds on which the simulation takes place) and is able to access, generate, edit, and return
data on the cells within the array, as well as compare and copy 2D arrays from other GridOfLife objects.
Sources:
  - #1 -> https://stackoverflow.com/a/936702 -> dynamic allocation of 2D array
*/

#ifndef GRIDOFLIFE_H
#define GRIDOFLIFE_H

#include "Cell.h"
#include <iostream>

class GridOfLife{
  public:
    GridOfLife();
    GridOfLife(int w, int h, float d);
    ~GridOfLife();

    void generateRandomAssignment();
    int checkNeighborsAround(int x, int y);
    void editGrid(int index_w, int index_h);
    void printGrid();
    Cell** getGrid(); // #1
    int getWidth();
    int getHeight();
    void populateEmptyGrid();
    bool cellIsOccupied(int x, int y);
    bool checkEquality(GridOfLife* _grid);
    void passGrid(GridOfLife* _grid);
    bool gridIsEmpty();
  private:
    int width;
    int height;
    Cell ** grid;
    float populationDensity;
};

#endif
