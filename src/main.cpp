/* Copyright (c) 2021 Matthew Gallivan <gallivan.matt@gmail.com>
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 */

#include "puzzle.h"
#include "search.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

int main() {
  // Seed for randomness.
  srand((unsigned int)time(NULL));

  size_t size = 3;
  Puzzle puzzle(size);
  while (!puzzle.is_solvable()) {
    puzzle = Puzzle(size);
  }

  puzzle.print();

  AStar search;
  std::vector<Action> actions = search.solve(puzzle);
  for (auto action : actions) {
    puzzle.move(action);
  }

  std::cout << std::endl << "Solved!" << std::endl << std::endl;

  puzzle.print();

  return 0;
}
