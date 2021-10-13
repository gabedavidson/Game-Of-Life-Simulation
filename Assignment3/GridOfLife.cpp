/*
Gabe Davidson
2338642
gadavidson@chapman.edu
CPSC 350-3
Assignment 3

Implementation file for the GridOfLife class.
GridOfLife holds the 2D array (grounds on which the simulation takes place) and is able to access, generate, edit, and return
data on the cells within the array, as well as compare and copy 2D arrays from other GridOfLife objects.

Sources:
  - Help from Joshua Anderson with converting GridOfLife objects to pointers
  - #1 -> https://stackoverflow.com/a/2544425 -> float to int
  - #2 -> https://www.cplusplus.com/reference/cstdlib/rand/ -> generating random numbers
  - #3 -> https://stackoverflow.com/a/936702 -> dynamic allocation of 2D array
*/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include "GridOfLife.h"

using namespace std;

GridOfLife::GridOfLife(){
  width = 6;
  height = 6;
  grid = new Cell*[width]; // #3
  for (int i = 0; i < width; ++i){
    grid[i] = new Cell[height];
  }
  populationDensity = static_cast<int>(.5 * width * height); // #1
  this->populateEmptyGrid();
}

GridOfLife::GridOfLife(int w, int h, float d){
  width = w;
  height = h;
  grid = new Cell*[width]; // #3
  for (int i = 0; i < width; ++i){
    grid[i] = new Cell[height];
  }
  populationDensity = static_cast<int>(round(d * width * height)); // #1
  this->populateEmptyGrid();
}

GridOfLife::~GridOfLife(){
  for (int i = 0; i < width; ++i){
    delete[] grid[i];
  }
  delete[] grid;
}

void GridOfLife::populateEmptyGrid(){
  for (int i = 0; i < width; ++i){
    for (int j = 0; j < height; ++j){
      grid[i][j] = Cell(i, j, false);
    }
  }
}

void GridOfLife::generateRandomAssignment(){ // #2
  srand(time(0));

  int x;
  int y;

  for (int i = 0; i < populationDensity; ++i){
    x = rand() % (width);
    y = rand() % (height);
    if (!grid[x][y].isActiveCell()){
      grid[x][y].changeStatus();
    }
    else {
      --i;
    }
  }
}

int GridOfLife::checkNeighborsAround(int x, int y){
  int count = 0;

  if (cellIsOccupied(x, y + 1)){
    // cout << "found occupied cell at: " << x << " , " << y + 1 << endl;
    ++count;
  }
  if (cellIsOccupied(x + 1, y + 1)){
    // cout << "found occupied cell at: " << x + 1 << " , " << y + 1 << endl;
    ++count;
  }
  if (cellIsOccupied(x + 1, y)){
    // cout << "found occupied cell at: " << x + 1 << " , " << y << endl;
    ++count;
  }
  if (cellIsOccupied(x + 1, y - 1)){
    // cout << "found occupied cell at: " << x + 1 << " , " << y - 1 << endl;
    ++count;
  }
  if (cellIsOccupied(x, y - 1)){
    // cout << "found occupied cell at: " << x << " , " << y - 1 << endl;
    ++count;
  }
  if (cellIsOccupied(x - 1, y - 1)){
    // cout << "found occupied cell at: " << x - 1<< " , " << y - 1 << endl;
    ++count;
  }
  if (cellIsOccupied(x - 1, y)){
    // cout << "found occupied cell at: " << x - 1 << " , " << y << endl;
    ++count;
  }
  if (cellIsOccupied(x - 1, y + 1)){
    // cout << "found occupied cell at: " << x - 1 << " , " << y + 1 << endl;
    ++count;
  }

  return count;
}

bool GridOfLife::cellIsOccupied(int x, int y){
  if (x >= 0 && y >= 0 && x < width && y < height){
    if (grid[x][y].isActiveCell()){
      return true;
    }
  }
  return false;
}

int GridOfLife::getWidth(){
  return width;
}

int GridOfLife::getHeight(){
  return height;
}

bool GridOfLife::checkEquality(GridOfLife* _grid){
  for (int i = 0; i < width; ++i){
    for (int j = 0; j < height; ++j){
      if (_grid->cellIsOccupied(i, j) != cellIsOccupied(i, j)){
        return false;
      }
    }
  }
  return true;
}

// copies contents of _grid into grid
void GridOfLife::passGrid(GridOfLife* _grid){
  for (int i = 0; i < width; ++i){
    for (int j = 0; j < height; ++j){
      if (_grid->cellIsOccupied(i, j) != cellIsOccupied(i, j)){
        grid[i][j].changeStatus();
      }
    }
  }
}

void GridOfLife::editGrid(int index_w, int index_h){
  grid[index_w][index_h].changeStatus();
}

void GridOfLife::printGrid(){
  for (int i = 0; i < width; ++i){
    for (int j = 0; j < height; ++j){
      if (grid[i][j].isActiveCell()){
        cout << "X";
      }
      else {
        cout << "-";
      }
    }
    cout << "\n";
  }
}

Cell** GridOfLife::getGrid(){
  return grid;
}
