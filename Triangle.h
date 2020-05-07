#ifndef _triangle_h_
#define _triangle_h_

#include <set>
#include <vector>
#include <cstring>
#include "Move.h"


class Triangle {
public:
  static const int maxSpots = 7*4;
  static unsigned int nSides;
  static unsigned int nSpots;
  static void setSides(int nSides);
  
  int emptySpots;
  int nMarbles;
  int stones[maxSpots];
  
  Triangle() {
    emptySpots = 0;
    nMarbles = nSpots;
    for (int i=0; i<nSpots; ++i) stones[i]=1;
  };
  Triangle(const Triangle& tri) {
    //    memcpy(stones, tri.stones, nSpots);
    for (int i=0; i<nSpots; ++i) stones[i]=tri.stones[i];
    emptySpots=tri.emptySpots;
    nMarbles=tri.nMarbles;
  }

  bool isEmpty(const int& iSpot) const;
  bool isEmpty(const Coordinate& aCoord) const;
  bool isFull(const int& iSpot) const;
  bool isFull(const Coordinate& aCoord) const;
  void remove(const int& iSpot);
  void add(const int& iSpot);
  void remove(const Coordinate& aCoord);
  void add(const Coordinate& aCoord);
  MoveVector findLegalMoves() const;
  void print() const;
  int getNMarbles() const { return nMarbles; };

  static void listMoves(const MoveVector&);
  static bool exploreGame(const Triangle& prevTriangle,
			  MoveVector moveVector,
			  std::vector<MoveVector>& bestMoves);
  static bool exploreGameOptimal(const Triangle& prevTriangle,
				 MoveVector& moveVector,
				 MoveVector& bestMoves,
				 int& currentBestScore);
  void executeMove(const Move& aMove);
};

#endif
