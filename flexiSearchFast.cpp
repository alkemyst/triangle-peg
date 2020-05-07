#include <iostream>
#include <vector>
#include <cstdlib>

#include "Triangle.h"
#include "Move.h"

int main(int argc, char* argv[]) {
  if (argc!=3) {
    std::cerr << "Syntax: " << argv[0] << " side_size marble_to_remove" << std::endl;
    return -1;
  }

  int side = atoi(argv[1]);
  int toRemove = atoi(argv[2]);
  
  Triangle myTriangle;
  Triangle::setSides(side);
  myTriangle.remove(toRemove);
  
  myTriangle.print();
  std::cout << std::endl;
  std::cout << std::endl;

  MoveVector moveVector;
  MoveVector bestMoves;
  int bestScore = myTriangle.nSpots;
  Triangle::exploreGameOptimal(myTriangle, moveVector, bestMoves, bestScore);

  if (bestScore!=myTriangle.nSpots) {
    std::cerr << "Solved. Best score in " << bestScore << std::endl;
    Triangle::listMoves(bestMoves);
  } else {
    std::cerr << "Not_possible" << std::endl;    
  }
  
  return 0;
};
