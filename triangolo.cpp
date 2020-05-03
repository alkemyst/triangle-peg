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
  Coordinate captureSpot;
  bool carryOn=false;
};

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
  std::vector<Move> findLegalMoves() const;
  void print() const;
  int getNMarbles() const {
    return nSpots-emptySpots.size();
  };

  static void listMoves(const std::vector<Move>&);
  void executeMove(const Move& aMove);
};

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

std::vector<Move> Triangle::findLegalMoves() const {
  std::vector<Move> result;
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

void Triangle::listMoves(const std::vector<Move>& moveVector) {
  for (auto it : moveVector) {
    std::cout << "From " << it.fromSpot.getSpot() << " to " << it.toSpot.getSpot() << std::endl;
  }
}

bool exploreGame(const Triangle& prevTriangle, std::vector<Move> moveVector, std::vector<std::vector<Move>>& winningMoves) {
  auto moves = prevTriangle.findLegalMoves();
  // Game over. did we win?
  if (moves.size()==0) {
    // we won
    if (prevTriangle.getNMarbles()==1) {
      winningMoves.push_back(moveVector);
      std::cerr << "Winning" << std::endl;
      Triangle::listMoves(moveVector);
      prevTriangle.print();
      std::cerr << std::endl;
    } else {
      std::cerr << "Losing" << std::endl;
      Triangle::listMoves(moveVector);
      prevTriangle.print();
      std::cerr << std::endl;
    }
  } else {
    // We can carry on recursively
    for (auto& aMove : moves) {
      Triangle nextTriangle = prevTriangle;
      nextTriangle.executeMove(aMove);
      std::vector<Move> nextMoveVector = moveVector;
      nextMoveVector.push_back(aMove);
      exploreGame(nextTriangle, nextMoveVector, winningMoves);
    }
  }
  return true;
}

int main(int argc, char* argv[]) {
  Triangle myTriangle(4);
  myTriangle.remove(1);
  myTriangle.remove(2);
  myTriangle.remove(3);
  myTriangle.remove(4);
  //myTriangle.remove(5);
  //Triangle.remove(6);
  myTriangle.remove(7);
  myTriangle.remove(8);
  myTriangle.print();

  // std::vector<Move> allMoves = myTriangle.findLegalMoves();
  // for (auto it : allMoves) {
  //   std::cout << std::endl;
  //   std::cout << "From " << it.fromSpot.getSpot() << " to " << it.toSpot.getSpot() << " over " << it.captureSpot.getSpot() << std::endl;
  //   Triangle newTriangle = myTriangle;
  //   newTriangle.executeMove(it);
  //   newTriangle.print();
  // }

  std::vector<Move> moveVector;
  std::vector<std::vector<Move> > winningMoves;
  exploreGame(myTriangle, moveVector, winningMoves);
  // Triangle::listMoves(allMoves);
  return 0;
};
