/*
Gabe Davidson
2338642
gadavidson@chapman.edu
CPSC 350-3
Assignment 3

Implementation file for the ProgramManager class.
ProgramManager is considered the functional base of the simulation which generates and outputs the simulation, as well accesses
information and compares information in order to edit and manipulate the GridOfLife objects and advance the simulation.

Sources:
  - #1 -> https://www.softwaretestinghelp.com/cpp-sleep/ -> sleep functionality
*/

#include "ProgramManager.h"
#include "GridOfLife.h"
#include "BoundaryModeManager.h"

#include <chrono>
#include <thread>
#include <string>
#include <fstream>
#include <iostream>
#include <exception>

using namespace std;

ProgramManager::ProgramManager(){
  BoundaryModeManager modeManager;

  numGeneration = 1;
  pauseBetweenGens = false;
  enterBetweenGens = false;

  outfile = "";
} // default constructor

ProgramManager::~ProgramManager(){ // destructor
  delete activeGenGrid;
  delete nextGenGrid;
}

void ProgramManager::doInitialPrompts(){
  char res;
  string _res;

  // random configuration / flat file configuration
  cout << "Respond with the correlating number:\n1. Random configuration\n2. Specify flat file configuration" << endl;
  cin >> res;

  if (res == '1'){ // user has chosen to create random configuration
    cout << "You have chosen to make a random configuration.\n" << endl;

    int x;
    int y;
    float pDensity;

    cout << "What is the width of the environment? (grid): ";
    cin >> x;

    cout << "What is the height of the environment? (grid): ";
    cin >> y;

    cout << "What is the population density? (between 0 and 1): ";
    cin >> pDensity;

    activeGenGrid = new GridOfLife(y, x, pDensity); // initialize given width and height and population density
    nextGenGrid = new GridOfLife(y, x, pDensity); // initialize given width and height and population density

    activeGenGrid->generateRandomAssignment();
    cout << "Random configuration successfully created as:\n" << endl;
    activeGenGrid->printGrid();
    cout << endl;
  }
  else if (res == '2'){ // user chose to input initial configuration
    cout << "Please provide the input file name: ";
    cin >> _res;
    try{ // in case of mispelled filename
      getGridFromFile(_res);
    } catch(exception& err){
      cout << "Exception: " << err.what() << endl;
      cout << "Could not load file." << endl;
      exit(0);
    }
  }

  // boundary mode
  cout << "\nRespond with the correlating number:\nWhat boundary mode would you like to simulate?\n1. Clasic mode\n2. Doughnut mode\n3. Mirror mode" << endl;
  cin >> res;

  if (res == '1'){ // user chose classic mode
    cout << "Running simulation in classic mode." << endl;
  }
  else if (res == '2'){ // user chose doughnut mode
    modeManager.changeMode('d');
    cout << "Running simulation in doughnut mode." << endl;
  }
  else if (res == '3'){
    modeManager.changeMode('m'); // user chose mirror mode
    cout << "Running simulation in mirror mode." << endl;
  }

  // pauses / output
  cout << "Do you want to have brief pauses between generations or write to a file?" << endl;
  cout << "\nRespond with the correlating number:\n1. Brief pause\n2. Press 'enter'\n3. Write to file" << endl;
  cin >> res;

  if (res == '1'){ // user chose to have brief pauses between generations
    cout << "You have chosen to have brief pauses between generations." << endl;
    pauseBetweenGens = true;
  }
  else if (res == '2'){ // user chose to press enter between generations
    cout << "You have chosen to have press 'enter' between generations." << endl;
    enterBetweenGens = true;
  }
  else if (res == '3'){ // user chose to write simulation results to file
    cout << "You have chosen to write generations to a file." << endl;
    cout << "Enter name for the outfile: ";
    cin >> outfile;
  }

  cout << "\nPress enter to begin simulation" << endl;
  cin.get(); // grab trailing input
  cin.get();
}

void ProgramManager::getGridFromFile(string inFile){
  //
  ifstream reader;
  reader.open(inFile);

  string t;
  int w, h;
  int heightIndex = 0; // using this to index height

  getline(reader, t); // get width
  w = stoi(t);
  getline(reader, t); // get height
  h = stoi(t);

  activeGenGrid = new GridOfLife(w, h, -1.0); // initialize given width and height
  nextGenGrid = new GridOfLife(w, h, -1.0); // initialize given width and height

  while (!reader.eof()){
    getline(reader, t);
    for (int i = 0; i < t.length(); ++i){
      if (t.at(i) == 'X' || t.at(i) == 'x'){
        activeGenGrid->editGrid(heightIndex, i); // if 'x' or 'X', change inactive cell to active at coordinates
      }
    }
    ++heightIndex;
  }

  reader.close();

  cout << "Grid loaded successfully as: " << endl;
  activeGenGrid->printGrid();
}

void ProgramManager::writeGridToFile(ofstream& writer){
  writer << numGeneration <<"\n"; // write generation number

  for (int i = 0; i < activeGenGrid->getWidth(); ++i){
    for (int j = 0; j < activeGenGrid->getHeight(); ++j){
      if (nextGenGrid->cellIsOccupied(i, j)){ // if occupied/active
        writer << "X";
      }
      else { // if unoccupied/inactive
        writer << "-";
      }
    }
    writer << "\n";
  }
  writer << "\n\n";
}

void ProgramManager::run(){
  doInitialPrompts();

  bool inProgress = true;

  // initialize writer here so that it doesn't need to be opened/closed
  //  repeatedly as it writes to file within writeGridToFile method
  ofstream writer;
  writer.open(outfile);

  int numNeighbors = 0;

  while (inProgress){

    if (pauseBetweenGens || enterBetweenGens){
      cout << "\n" << numGeneration << endl;
      activeGenGrid->printGrid();
    }

    for (int i = 0; i < activeGenGrid->getWidth(); ++i){
      for (int j = 0; j < activeGenGrid->getHeight(); ++j){

        // find number of neighbors
        numNeighbors += activeGenGrid->checkNeighborsAround(i, j);
        // check if boundary mode is mirror
        if (modeManager.getMode() == 'm'){
          // find number of neighbors from mirrors
          numNeighbors += modeManager.checkMirrorNeighborsAround(i, j, activeGenGrid, activeGenGrid->getWidth(), activeGenGrid->getHeight());
        }
        // check if boundary mode is doughnut
        else if (modeManager.getMode() == 'd'){
          // find number of neighbors from doughnut
          numNeighbors += modeManager.checkDoughnutNeighborsAround(i, j, activeGenGrid, activeGenGrid->getWidth(), activeGenGrid->getHeight());
        }

        // if neighbors < 2 -> if active, becomes inactive
        if (numNeighbors < 2){
          if (activeGenGrid->cellIsOccupied(i, j)){
            nextGenGrid->editGrid(i, j); // change active to inactive
          }
        }

        // if neighbors == 2 -> nothing changes

        // if neighbors == 3 -> if inactive, becomes active.
        if (numNeighbors == 3){
          if (!activeGenGrid->cellIsOccupied(i, j)){
            nextGenGrid->editGrid(i, j); // change inactive to active
          }
        }

        // if neighbors > 3 -> if active, becomes inactive
        if (numNeighbors > 3){
          if (activeGenGrid->cellIsOccupied(i, j)){
            nextGenGrid->editGrid(i, j); // change active to inactive
          }
        }

        numNeighbors = 0;
      }
    }
    // if activeGen grid == nextGen grid -> grid is stable or empty
    if (activeGenGrid->checkEquality(nextGenGrid)){
      inProgress = false;
    }
    // if not stable or empty
    else {
      // copy nextGen grid onto activeGen grid
      activeGenGrid->passGrid(nextGenGrid);
      ++numGeneration;

      if (!pauseBetweenGens && !enterBetweenGens){
        writeGridToFile(writer);
      }
      else {
        if (pauseBetweenGens){
          // sleep for 1/5th of a second
          std::this_thread::sleep_for(std::chrono::milliseconds(200)); // #1
        }
        else if (enterBetweenGens){
          // waits for user to press enter before continuing
          std::cin.get();
        }
      }
    }
  }
  // outro and end
  if (activeGenGrid->gridIsEmpty()){
    cout << "\nEnvironment is empty" << endl;
  }
  else {
    cout << "\nEnvironment is stable" << endl;
  }
  if (!pauseBetweenGens && !enterBetweenGens){
    cout << "Simulation ended as:" << endl;
    activeGenGrid->printGrid();
    cout << "\nPlease see " << outfile << " for results.\n" << endl;
  }
  cout << "Press enter to end program" << endl;
  cin.get();
  cout << "Ending program." << endl;
  writer.close();
}
