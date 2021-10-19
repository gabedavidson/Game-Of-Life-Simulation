/*
Gabe Davidson
2338642
gadavidson@chapman.edu
CPSC 350-3
Assignment 3

Header file for the Cell class.
Cell is a placeholder and it knows whether it is active or inactive and can change it's status

Sources:
  - none
*/

#ifndef CELL_H
#define CELL_H

class Cell{
  public:
    Cell();
    Cell(int x, int y, bool s);
    ~Cell();

    bool isActiveCell();
    void changeStatus();
    void changeStatus(bool changeTo);
  private:
    bool activeStatus;
    int x_coord;
    int y_coord;
};

#endif
