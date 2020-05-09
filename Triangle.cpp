#include <iostream>
#include <set>
#include <vector>
#include <cmath>

#include "Coordinate.h"
#include "Triangle.h"
#include "Move.h"

unsigned int Triangle::nSides = 4;
unsigned int Triangle::nSpots = nSides*(nSides+1)/2;;
AvailableMoveSet Triangle::availableMoves[maxSpots];

void Triangle::setupGame(int pSides) {
  nSides=pSides;
  nSpots=nSides*(nSides+1)/2;

  for (int iSpot=1; iSpot<=nSpots; ++iSpot) {
    AvailableMoveSet& thisMoves = availableMoves[iSpot];

    Coordinate thisSpot(iSpot);
    // Check for all possible directions of movement
    for (int dir=0; dir<6; ++dir) {
      Coordinate nextSpot = thisSpot;

      // At a distance 2
      nextSpot.move(dir, 2);
      // if the landing spot is still inside the triangle
      if (nextSpot.isInside(nSides)) {
	Coordinate captureSpot = thisSpot;
	captureSpot.move(dir, 1);

	Move newMove;
	newMove.fromSpot = thisSpot.Spot;
	newMove.captureSpot = captureSpot.Spot;
	newMove.toSpot = nextSpot.Spot;
	
	thisMoves.push_back(newMove);
      }

    }
  }
}

// For now I am just moving things around
void Triangle::executeMove(const Move& aMove) {
  remove(aMove.fromSpot);
  remove(aMove.captureSpot);
  add(aMove.toSpot);
}

bool Triangle::isEmpty(const int& iSpot) const {
  return !(stones[iSpot-1]);
}

bool Triangle::isFull(const int& iSpot) const {
  return stones[iSpot-1];
}

void Triangle::remove(const int& iSpot) {
  stones[iSpot-1]=0;
  nMarbles--;
  emptySpots++;
}

void Triangle::add(const int& iSpot) {
  stones[iSpot-1]=1;
  nMarbles++;
  emptySpots--;
}

void Triangle::print() const {
  int pos=1;
  std::string sign="";
  for (int row=0; row < nSides; ++row) {
    for (int spa=row+1; spa<nSides; spa++) std::cout << " ";
    for (int col=0; col<row+1; col++) {
      if (isEmpty(pos)) sign = " ◯"; // u25ef
      else sign = " ⬤"; // u2b24
      // Coordinate test(pos+1);
      // sign = std::to_string(test.isInside(nSides));
      std::cout << sign;
      pos++;
    }
    std::cout<<std::endl;
  }
  std::cout << getNMarbles() << " marbles" << std::endl;
}

MoveVector Triangle::findLegalMoves() const {
  MoveVector result;
  int thisSpot, dir;
  for (thisSpot=1; thisSpot<=nSpots; ++thisSpot) {

    // If there is a marble in our spot
    if (isFull(thisSpot)) {
      AvailableMoveSet& thisMoves = availableMoves[thisSpot];

      for (const auto& itMove : thisMoves) {
	if (isEmpty(itMove.toSpot) && isFull(itMove.captureSpot)) {
	  result.push_back(itMove); // TODO: use just pointers
	}
      }
    }
  }
  return result;
}

void Triangle::listMoves(const MoveVector& moveVector) {
  for (const auto it : moveVector) {
    std::cout << "From " << it.fromSpot << " to " << it.toSpot << std::endl;
  }
}

bool Triangle::exploreGame(const Triangle& prevTriangle,
			   MoveVector moveVector,
			   std::vector<MoveVector>& bestMoves) {
  auto moves = prevTriangle.findLegalMoves();
  // Game over. did we win?
  if (moves.size()==0) {
    // We only record when win occurs
    if (prevTriangle.getNMarbles()==1) {
      bestMoves.push_back(moveVector);
    }
  } else {
    // Did we already find a solution better than this one?
    // if not we carry on the search
    // Since there are possible moves, then we can carry on recursively
    for (auto& aMove : moves) {
      Triangle nextTriangle = prevTriangle;
      nextTriangle.executeMove(aMove);
      MoveVector nextMoveVector = moveVector;
      nextMoveVector.push_back(aMove);
      exploreGame(nextTriangle, nextMoveVector, bestMoves);
    }
  }
  return true;
}

bool Triangle::exploreGameOptimal(const Triangle& prevTriangle,
				  MoveVector& moveVector,
				  MoveVector& bestMoves,
				  int& currentBestScore) {
  auto moves = prevTriangle.findLegalMoves();
  // Game over. did we win?
  if (moves.size()==0) {
    // We only record when win occurs
    if (prevTriangle.getNMarbles()==1) {
      bestMoves = moveVector;
      currentBestScore = moveVector.scoreMoves();
      std::cerr << "current best score is " << currentBestScore << std::endl;
    }
  } else {
    // Did we already find a solution better than this one?
    // if not we carry on the search
    if (currentBestScore-1 > moveVector.scoreMoves() ) {
      // Since there are possible moves, then we can carry on recursively
      for (auto& aMove : moves) {
	Triangle nextTriangle = prevTriangle;
	nextTriangle.executeMove(aMove);
	moveVector.push_back(aMove);
	exploreGameOptimal(nextTriangle, moveVector, bestMoves, currentBestScore);
	moveVector.pop_back();
      }
    }
  }
  return true;
}


