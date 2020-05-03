#include <cmath>
#include "Coordinate.h"

void Coordinate::setSpot(const int& pSpot) {
  Spot = pSpot;
  A = ceil( (sqrt(1+8.*Spot)-1)/2. );
  B = Spot - (A-1)*A/2;
  C = A-B+1;    
}

void Coordinate::setAB(const int& pA, const int& pB) {
  A=pA;
  B=pB;
  C = pA-pB+1;    
  Spot = pB+pA*(pA-1)/2;
}

void Coordinate::setAC(const int& pA, const int& pC) {
  A = pA;
  C = pC;
  B = A-C+1;
  Spot = B+A*(A-1)/2;
}

void Coordinate::setBC(const int& pB, const int& pC) {
  B = pB;
  C = pC;
  A = B+C-1;
  Spot = B+A*(A-1)/2;
}

bool Coordinate::isInside(const int& pSide) {
  if (A<1) return false;
  if (B<1) return false;
  if (C<1) return false;
  if (A>pSide) return false;
  return true;
}

bool Coordinate::move(const int& direction, const int& step) {
  if ((direction<0) || (direction>=6)) return false;
    
  // 0 - East
  if (direction==0) setAB(A, B+step);
  // 1 - NorthEast
  if (direction==1) setAB(A-step, B);
  // 2 - NorthWest
  if (direction==2) setAC(A-step, C);
  // 3 - West
  if (direction==3) setAB(A, B-step);
  // 4 - SouthWest
  if (direction==4) setAB(A+step, B);
  // 5 - SouthEast
  if (direction==5) setAC(A+step, C);    

  return true;
}
  
bool operator==(const Coordinate& lhs, const Coordinate& rhs){
  return (lhs.Spot == rhs.Spot);
}

