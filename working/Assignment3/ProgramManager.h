/*
Gabe Davidson
2338642
gadavidson@chapman.edu
CPSC 350-3
Assignment 3

Header file for the ProgramManager class.
ProgramManager is considered the functional base of the simulation which generates and outputs the simulation, as well accesses
information and compares information in order to edit and manipulate the GridOfLife objects and advance the simulation.

Sources:

*/

#ifndef PROGRAMMANAGER_H
#define PROGRAMMANAGER_H

#include "GridOfLife.h"
#include "BoundaryModeManager.h"
#include <iostream>

using namespace std;

class ProgramManager{
  public:
    ProgramManager();
    ~ProgramManager();

    void doInitialPrompts();
    void getGridFromFile(string inFile);
    void writeGridToFile(ofstream& writer);
    void run();
  private:
    GridOfLife* activeGenGrid; // create pointer objects to initialize later
    GridOfLife* nextGenGrid;
    GridOfLife* pastGenGrid;
    BoundaryModeManager modeManager;

    int numGeneration;
    bool pauseBetweenGens;
    bool enterBetweenGens;
    string outfile;
};

#endif
