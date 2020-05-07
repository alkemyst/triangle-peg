#ifndef _coordinate_h_
#define _coordinate_h_

class Coordinate {
public:
  Coordinate() {};
  Coordinate(int pSpot) { setSpot(pSpot); };
  int getSpot() const { return Spot; };
  int getA() { return A; };
  int getB() { return B; };
  int getC() { return C; };

  void setSpot(const int& pSpot);
  void setAB(const int& pA, const int& pB);
  void setAC(const int& pA, const int& pC);
  void setBC(const int& pB, const int& pC);
  bool isInside(const int& pSide);
  bool move(const int& direction, const int& step);
  bool move(const int& direction) { return move(direction, 1); };
  friend bool operator==(const Coordinate& lhs, const Coordinate& rhs);
  int Spot;
  
private:
  int A;
  int B;
  int C;
};

#endif
