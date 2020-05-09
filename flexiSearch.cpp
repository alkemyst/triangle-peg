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

  Triangle::setupGame(side);
  
  Triangle myTriangle;
  myTriangle.print();
  myTriangle.remove(toRemove);
  myTriangle.print();
  
  std::cout << std::endl;
  std::cout << std::endl;

  MoveVector moveVector;
  std::vector<MoveVector> winningMoves;
  Triangle::exploreGame(myTriangle, moveVector, winningMoves);

  int bestScore = myTriangle.nSpots;
  MoveVector bestMoves;
  if (winningMoves.size()>0) {
    for (auto it : winningMoves) {
      int thisScore = it.scoreMoves();
      if (thisScore<bestScore) {
	bestScore = thisScore;
	bestMoves = it;
      }
    }

    std::cerr << "Best score in " << bestScore << std::endl;
    Triangle::listMoves(bestMoves);

    Triangle demo = myTriangle;
    for (auto it : bestMoves) {
      demo.print();
      std::cout << "From " << it.fromSpot << " to " << it.toSpot << std::endl;
      demo.executeMove(it);
    }
    demo.print();
  } else {
    std::cout << "No winning moves from here" << std::endl;
  }
  return 0;
};
