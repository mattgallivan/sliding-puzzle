/* Copyright (c) 2021 Matthew Gallivan <gallivan.matt@gmail.com>
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 */

#ifndef SEARCH_H
#define SEARCH_H

#include "puzzle.h"

#include <vector>

class AStar {
public:
  std::vector<Action> solve(Puzzle puzzle, size_t (*heuristic)(Puzzle));
};

class IDAStar {
public:
  std::vector<Action> solve(Puzzle puzzle, size_t (*heuristic)(Puzzle));
};

class LRTAStar {
public:
  std::vector<Action> solve(Puzzle puzzle, size_t (*heuristic)(Puzzle));
};

#endif /* SEARCH_H */
