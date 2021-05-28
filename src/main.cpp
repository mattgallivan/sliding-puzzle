#include "puzzle.h"

#include <iostream>

#include <cstdlib>
#include <ctime>

int main() {
  // Seed for randomness.
  srand((unsigned int) time(NULL));

  Puzzle puzzle(3);
  puzzle.print();
  std::cout << std::boolalpha;
  std::cout << "Is solvable?\t" << puzzle.is_solvable() << std::endl;
  return 0;
}
