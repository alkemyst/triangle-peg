#ifndef _move_h_
#define _move_h_

#include <vector>
#include "Coordinate.h"

class Move {
public:
  Coordinate fromSpot;
  Coordinate toSpot;
  Coordinate captureSpot;
  bool carryOn=false;
};

class MoveVector : public std::vector<Move> {
public:
  int scoreMoves() const;
};

#endif
