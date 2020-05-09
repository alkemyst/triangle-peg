#include <vector>
#include "Move.h"


// TODO: add scoring as we add moves
int MoveVector::scoreMoves() const {
  int result=0;
  for(auto it = std::vector<Move>::begin(); it != std::vector<Move>::end(); ++it) {
    result++;
    // if this is not the first move we can count
    if ( it != std::vector<Move>::begin() ) {
      const auto& prevIt = std::prev(it);
      if (prevIt->toSpot == it->fromSpot) result--;
    }
  }
  return result;
}

