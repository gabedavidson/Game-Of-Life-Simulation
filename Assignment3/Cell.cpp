/*
Gabe Davidson
2338642
gadavidson@chapman.edu
CPSC 350-3
Assignment 3

Implementation file for the Cell class.
Cell is a placeholder and it knows whether it is active or inactive and can change it's status

Sources:
  - none
*/

#include <iostream>
#include "Cell.h"

using namespace std;

Cell::Cell(){
  activeStatus = false;
  x_coord = -1;
  y_coord = -1;
}

Cell::Cell(int x, int y, bool s){
  activeStatus = s;
  x_coord = x;
  y_coord = y;
}

Cell::~Cell(){
  //
}

bool Cell::isActiveCell(){
  return activeStatus;
}

void Cell::changeStatus(){
  if (activeStatus){
    activeStatus = false;
  }
  else {
    activeStatus = true;
  }
}
