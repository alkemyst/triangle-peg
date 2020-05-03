#include <iostream>
#include <vector>

#include "Triangle.h"
#include "Move.h"

int main(int argc, char* argv[]) {
  Triangle myTriangle(4);
  myTriangle.remove(2);
  myTriangle.print();
  std::cout << std::endl;
  std::cout << std::endl;

  MoveVector moveVector;
  std::vector<MoveVector> winningMoves;
  Triangle::exploreGame(myTriangle, moveVector, winningMoves);

  for (auto it : winningMoves) {
    std::cerr << "Winning in " << it.scoreMoves() << std::endl;
    Triangle::listMoves(it);
    std::cerr << std::endl;
  }

  return 0;
};
