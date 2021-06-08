/* Copyright (c) 2021 Matthew Gallivan <gallivan.matt@gmail.com>
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 */

#include "heuristics.h"
#include "puzzle.h"
#include "search.h"
#include "stats.h"

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>

int main() {
  // Seed for randomness.
  srand((unsigned int)time(NULL));

  size_t size = 5;

  for (size_t i = 0; i < 1; ++i) {
    Puzzle puzzle(size);
    while (!puzzle.is_solvable()) {
      puzzle = Puzzle(size);
    }
    puzzle.print();

    Statistics stats;
    auto alg = IDAStar(&stats);
    auto heuristic = manhattan;
    {
      // Print the header.
      std::cout << std::endl;
      std::cout << alg.name << std::endl;
      std::cout << "- - - - -" << std::endl;

      // Solve the puzzle and measure the time it takes.
      auto t1 = std::chrono::high_resolution_clock::now();
      std::vector<Action> actions = alg.solve(puzzle, heuristic);
      auto t2 = std::chrono::high_resolution_clock::now();
      auto ms_int =
          std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1)
              .count();

      Puzzle copy = puzzle;
      for (Action a : actions)
        copy.move(a);

      // Print the puzzle.
      copy.print();
      std::cout << std::endl;

      // Print the statistics.
      std::cout << "Max Memory (bytes): " << stats.mem_bytes << std::endl;
      std::cout << "Solution Length: " << actions.size() << std::endl;
      std::cout << "Expansions: " << stats.num_expansions << std::endl;
      std::cout << "Time Elapsed (milliseconds): " << ms_int << std::endl;
      std::cout << "- - - - -" << std::endl;
      std::cout << std::endl;
    }
  }

  return 0;
}
