#ifndef _move_h_
#define _move_h_

#include <vector>

class Move {
public:
  int fromSpot;
  int toSpot;
  int captureSpot;
};

class MoveVector : public std::vector<Move> {
public:
  int scoreMoves() const;
};

#endif
