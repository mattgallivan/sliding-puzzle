#include "puzzle.h"

#include <iostream>

#include <cstdlib>
#include <ctime>

int main() {
  // Seed for randomness.
  srand((unsigned int)time(NULL));

  Puzzle puzzle(2);
  puzzle.print();

  std::cout << std::boolalpha;
  std::cout << "Is solvable?\t" << puzzle.is_solvable() << std::endl;

  while (!puzzle.is_solved()) {
    Action action;
    switch (getc(stdin)) {
    case 'a':
      action = LEFT;
      break;
    case 'd':
      action = RIGHT;
      break;
    case 'w':
      action = UP;
      break;
    case 's':
      action = DOWN;
      break;
    default:
      continue;
    }
    puzzle.move(action);
    puzzle.print();
    std::cout << std::endl;
  }

  std::cout << std::endl << "Solved!" << std::endl;

  return 0;
}
