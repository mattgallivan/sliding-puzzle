/* Copyright (c) 2021 Matthew Gallivan <gallivan.matt@gmail.com>
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 */

#include "puzzle.h"

#include <iostream>

#include <cstdlib>
#include <ctime>

int main() {
  // Seed for randomness.
  srand((unsigned int)time(NULL));

  size_t size = 3;
  Puzzle puzzle(size);
  while (!puzzle.is_solvable()) {
    puzzle = Puzzle(size);
  }
  puzzle.print();

  std::cout << std::boolalpha << std::endl;
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

  std::cout << std::endl;
  puzzle.print();

  return 0;
}
