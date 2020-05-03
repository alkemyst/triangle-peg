#include <iostream>
#include <set>
#include <vector>
#include <cmath>

class Coordinate {
public:
  Coordinate() {};
  Coordinate(int pSpot) {
    setSpot(pSpot);
  };
  int getSpot() const { return Spot; };
  int getA() { return A; };
  int getB() { return B; };
  int getC() { return C; };

  void setSpot(const int& pSpot) {
    Spot = pSpot;
    A = ceil( (sqrt(1+8.*Spot)-1)/2. );
    B = Spot - (A-1)*A/2;
    C = A-B+1;    
  };
  void setAB(const int& pA, const int& pB) {
    A=pA;
    B=pB;
    C = pA-pB+1;    
    Spot = pB+pA*(pA-1)/2;
  };
  void setAC(const int& pA, const int& pC) {
    A = pA;
    C = pC;
    B = A-C+1;
    Spot = B+A*(A-1)/2;
  };
  void setBC(const int& pB, const int& pC) {
    B = pB;
    C = pC;
    A = B+C-1;
    Spot = B+A*(A-1)/2;
  };

  bool isInside(const int& pSide) {
    if (A<1) return false;
    if (B<1) return false;
    if (C<1) return false;
    if (A>pSide) return false;
    return true;
  };

  bool move(const int& direction, const int& step) {
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
  };
  
  bool move(const int& direction) {
    return move(direction, 1);
  };
  
private:
  int Spot;
  int A;
  int B;
  int C;
};

class Move {
public:
  Coordinate fromSpot;
  Coordinate toSpot;
  Coordinate overSpot;
  bool carryOn=false;
};

class Triangle {
public:
  int nSides;
  int nSpots;
  Triangle(int pSides) { nSides=pSides ; nSpots=nSides*(nSides+1)/2; }
  std::set<int> emptySpots;

  bool isEmpty(const int& iSpot);
  bool isEmpty(const Coordinate& aCoord);
  void remove(const int& iSpot);
  void add(const int& iSpot);
  std::vector<Move> findLegalMoves();
  void print();

  static void listMoves(const std::vector<Move>&);
  void executeMove(const Move& aMove);
};

// For now I am just moving things around
void Triangle::executeMove(const Move& aMove) {
  add(aMove.fromSpot.getSpot());
  remove(aMove.toSpot.getSpot());
}

bool Triangle::isEmpty(const int& iSpot) {
  if (emptySpots.find(iSpot) != emptySpots.end()) return true;
  else return false;
}

bool Triangle::isEmpty(const Coordinate& aCoord) {
  return isEmpty(aCoord.getSpot());
}


void Triangle::remove(const int& iSpot) {
  emptySpots.insert(iSpot);
}

void Triangle::add(const int& iSpot) {
  emptySpots.erase(iSpot);
}

void Triangle::print() {
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
}

std::vector<Move> Triangle::findLegalMoves() {
  std::vector<Move> result;
  for (int i=1; i<=nSpots; ++i) {
    Coordinate thisSpot(i);

    if (isEmpty(thisSpot)) {
      for (int dir=0; dir<6; ++dir) {
	Coordinate nextSpot = thisSpot;
	nextSpot.move(dir, 2);
	if (nextSpot.isInside(nSides)) {
	  Move newMove; newMove.fromSpot = thisSpot; newMove.toSpot = nextSpot; result.push_back(newMove);
	}
      }
    }
  }
  return result;
}

void Triangle::listMoves(const std::vector<Move>& moveVector) {
  for (auto it : moveVector) {
    std::cout << "From " << it.fromSpot.getSpot() << " to " << it.toSpot.getSpot() << std::endl;
  }
}

int main(int argc, char* argv[]) {
  Triangle myTriangle(5);
  myTriangle.remove(8);
  myTriangle.print();
  std::vector<Move> allMoves = myTriangle.findLegalMoves();

  for (auto it : allMoves) {
    std::cout << std::endl;
    // std::cout << "From " << it.fromSpot.getSpot() << " to " << it.toSpot.getSpot() << std::endl;
    Triangle newTriangle = myTriangle;
    newTriangle.executeMove(it);
    newTriangle.print();
  }


  // Triangle::listMoves(allMoves);
  return 0;
};
