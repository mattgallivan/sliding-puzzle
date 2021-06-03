/* Copyright (c) 2021 Matthew Gallivan <gallivan.matt@gmail.com>
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 */

#include "search.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <unordered_map>

static size_t uadd(size_t a, size_t b) { return a + b > a ? a + b : SIZE_MAX; }

static size_t manhattan_distance(Puzzle puzzle) {
  size_t distance = 0;
  for (size_t i = 0; i < puzzle.width * puzzle.height; ++i) {
    size_t tile = puzzle.board[i];
    size_t position = i + 1;
    if (tile == BLANK)
      continue;
    if (tile == position)
      continue;
    // NOTE: Two cases here to prevent underflow.
    if (tile > position)
      distance += tile - position;
    if (tile < position)
      distance += position - tile;
  }
  return distance;
}

std::vector<Action> AStar::solve(Puzzle puzzle) {
  Puzzle start = puzzle;

  // The initial heuristic of the start state.
  size_t start_h = manhattan_distance(start);

  // The open list is a frontier of states to expanded ordered from lowest to
  // highest by their f-score.
  typedef std::pair<size_t, Puzzle> FPuzzle;
  std::priority_queue<FPuzzle, std::vector<FPuzzle>, std::greater<>> open;
  open.push(std::make_pair(start_h, start));

  // The g-scores represent the minimum travel cost to a state.
  std::unordered_map<Puzzle, size_t, PuzzleHash> g;
  g[start] = 0;

  // The f-scores represent the minimum total cost to a state.
  std::unordered_map<Puzzle, size_t, PuzzleHash> f;
  f[start] = start_h;

  // The states leading to other states, used to rebuild the path.
  std::unordered_map<Puzzle, std::pair<Puzzle, Action>, PuzzleHash> parents;

  while (!open.empty()) {
    auto current = open.top().second;
    open.pop();

    if (current.is_solved()) {
      std::vector<Action> actions;
      Puzzle state = current;
      while (state != start) {
        actions.push_back(parents.at(state).second);
        state = parents.at(state).first;
      }
      std::reverse(actions.begin(), actions.end());
      return actions;
    }

    for (Action action : current.actions()) {
      Puzzle neighbour = current;
      neighbour.move(action);

      if (g.find(neighbour) == g.end())
        g[neighbour] = SIZE_MAX;

      size_t cost = uadd(g[current], 1); // NOTE: Move cost is always 1.
      if (cost < g[neighbour]) {
        g[neighbour] = cost;
        f[neighbour] = uadd(cost, manhattan_distance(neighbour));
        open.push(std::make_pair(f[neighbour], neighbour));
        parents.insert_or_assign(neighbour, std::make_pair(current, action));
      }
    }
  }

  std::cout << "Done?" << std::endl;

  return {};
}