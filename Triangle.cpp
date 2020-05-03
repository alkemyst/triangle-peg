#include <iostream>
#include <set>
#include <vector>
#include <cmath>

#include "Coordinate.h"
#include "Triangle.h"
#include "Move.h"

// For now I am just moving things around
void Triangle::executeMove(const Move& aMove) {
  remove(aMove.fromSpot);
  remove(aMove.captureSpot);
  add(aMove.toSpot);
}

bool Triangle::isEmpty(const int& iSpot) const {
  if (emptySpots.find(iSpot) != emptySpots.end()) return true;
  else return false;
}

bool Triangle::isEmpty(const Coordinate& aCoord) const {
  return isEmpty(aCoord.getSpot());
}

void Triangle::remove(const int& iSpot) {
  emptySpots.insert(iSpot);
}

void Triangle::remove(const Coordinate& aCoord) {
  remove(aCoord.getSpot());
}

void Triangle::add(const int& iSpot) {
  emptySpots.erase(iSpot);
}

void Triangle::add(const Coordinate& aCoord) {
  add(aCoord.getSpot());
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
  for (int i=1; i<=nSpots; ++i) {
    Coordinate thisSpot(i);

    // If there is a marble in our spot
    if (!isEmpty(thisSpot)) {
      // Check for all possible directions of movement
      for (int dir=0; dir<6; ++dir) {
	Coordinate nextSpot = thisSpot;
	// At a distance 2
	nextSpot.move(dir, 2);
	// if the landing spot is still inside the triangle
	if (nextSpot.isInside(nSides)) {
	  // If the landing spit is free
	  if (isEmpty(nextSpot)) {
	    // And if there is a marble to jump over
	    Coordinate captureSpot = thisSpot;
	    captureSpot.move(dir, 1);
	    if (!isEmpty(captureSpot)) {
	      // Then we have a capture move
	      Move newMove;
	      newMove.fromSpot = thisSpot;
	      newMove.toSpot = nextSpot;
	      newMove.captureSpot = captureSpot;
	      result.push_back(newMove);
	    }
	  }
	}
      }
    }
  }
  return result;
}

void Triangle::listMoves(const MoveVector& moveVector) {
  for (auto it : moveVector) {
    std::cout << "From " << it.fromSpot.getSpot() << " to " << it.toSpot.getSpot() << std::endl;
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
				  MoveVector moveVector,
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
    if (currentBestScore-1 > moveVector.scoreMoves()) {
      // Since there are possible moves, then we can carry on recursively
      for (auto& aMove : moves) {
	Triangle nextTriangle = prevTriangle;
	nextTriangle.executeMove(aMove);
	MoveVector nextMoveVector = moveVector;
	nextMoveVector.push_back(aMove);
	exploreGameOptimal(nextTriangle, nextMoveVector, bestMoves, currentBestScore);
      }
    }
  }
  return true;
}


