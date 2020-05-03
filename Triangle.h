#ifndef _triangle_h_
#define _triangle_h_

#include <set>
#include <vector>
#include "Move.h"

class Triangle {
public:
  int nSides;
  int nSpots;
  Triangle(int pSides) { nSides=pSides ; nSpots=nSides*(nSides+1)/2; }
  std::set<int> emptySpots;

  bool isEmpty(const int& iSpot) const;
  bool isEmpty(const Coordinate& aCoord) const;
  void remove(const int& iSpot);
  void add(const int& iSpot);
  void remove(const Coordinate& aCoord);
  void add(const Coordinate& aCoord);
  MoveVector findLegalMoves() const;
  void print() const;
  int getNMarbles() const {
    return nSpots-emptySpots.size();
  };

  static void listMoves(const MoveVector&);
  static bool exploreGame(const Triangle& prevTriangle,
			  MoveVector moveVector,
			  std::vector<MoveVector>& bestMoves);
  static bool exploreGameOptimal(const Triangle& prevTriangle,
				 MoveVector moveVector,
				 MoveVector& bestMoves,
				 int& currentBestScore);
  void executeMove(const Move& aMove);
};

#endif
