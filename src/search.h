/* Copyright (c) 2021 Matthew Gallivan <gallivan.matt@gmail.com>
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 */

#ifndef SEARCH_H
#define SEARCH_H

#include "puzzle.h"
#include "stats.h"

#include <vector>

struct AStar {
  std::string name = "A*";
  Statistics* stats = NULL;

  AStar(){};
  AStar(Statistics* stats) : stats(stats){};

  std::vector<Action> solve(Puzzle puzzle, size_t (*heuristic)(Puzzle));
};

struct IDAStar {
  std::string name = "IDA*";
  Statistics* stats = NULL;

  IDAStar(){};
  IDAStar(Statistics* stats) : stats(stats){};

  std::vector<Action> solve(Puzzle puzzle, size_t (*heuristic)(Puzzle));
};

struct LRTAStar {
  std::string name = "LRTA*";
  Statistics* stats = NULL;

  LRTAStar(){};
  LRTAStar(Statistics* stats) : stats(stats){};

  std::vector<Action> solve(Puzzle puzzle, size_t (*heuristic)(Puzzle));
};

#endif /* SEARCH_H */
