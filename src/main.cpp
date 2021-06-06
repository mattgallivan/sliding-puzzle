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
  // srand((unsigned int)time(NULL));

  size_t size = 4;

  for (size_t i = 0; i < 10; ++i) {
    srand(i);

    std::cout << "Starting..." << std::endl;

    Puzzle puzzle(size);
    while (!puzzle.is_solvable()) {
      puzzle = Puzzle(size);
    }

    std::cout << std::endl;
    puzzle.print();

    IDAStar search;
    std::vector<Action> actions = search.solve(puzzle);
    for (auto action : actions) {
      puzzle.move(action);
    }

    if (actions.size() == 0) {
      std::cout << std::endl << "\t...Failed!" << std::endl << std::endl;
      return 1;
    } else {
      std::cout << std::endl
                << "\t...Solved in " << actions.size() << " moves!" << std::endl
                << std::endl;
      puzzle.print();
      std::cout << std::endl;
    }
  }

  return 0;
}
