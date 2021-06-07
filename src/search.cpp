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

std::vector<Action> AStar::solve(Puzzle puzzle, size_t (*heuristic)(Puzzle)) {
  Puzzle start = puzzle;

  // The initial heuristic of the start state.
  size_t start_h = heuristic(start);

  // The open list is a frontier of states to expand ordered from lowest to
  // highest by their f-score.
  typedef std::pair<size_t, Puzzle> FPuzzle;
  std::priority_queue<FPuzzle, std::vector<FPuzzle>, std::greater<>> open;
  open.push(std::make_pair(start_h, start));

  // The g-scores represent the minimum travel cost to a state.
  std::map<Puzzle, size_t> g;
  g[start] = 0;

  // The f-scores represent the minimum total cost to a state.
  std::map<Puzzle, size_t> f;
  f[start] = start_h;

  // The states leading to other states, used to rebuild the path.
  std::map<Puzzle, std::pair<Puzzle, Action>> parents;

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
        f[neighbour] = uadd(cost, heuristic(neighbour));
        open.push(std::make_pair(f[neighbour], neighbour));
        parents.insert_or_assign(neighbour, std::make_pair(current, action));
      }
    }
  }

  return {};
}

static size_t ida_search(std::vector<Action>& actions,
                         std::vector<Puzzle>& states, size_t g, size_t bound,
                         size_t (*heuristic)(Puzzle)) {
  Puzzle state = states.back();
  if (state.is_solved())
    return 0;

  size_t f = uadd(g, heuristic(state));
  if (f > bound)
    return f;

  size_t minimum = SIZE_MAX;
  for (Action action : state.actions()) {
    Puzzle neighbour = state;
    neighbour.move(action);

    if (std::find(states.begin(), states.end(), neighbour) == states.end()) {
      actions.push_back(action);
      states.push_back(neighbour);
      // NOTE: Move cost is always 1.
      size_t t = ida_search(actions, states, uadd(g, 1), bound, heuristic);
      if (t == 0)
        return 0;
      if (t < minimum)
        minimum = t;
      states.pop_back();
      actions.pop_back();
    }
  }
  return minimum;
}

std::vector<Action> IDAStar::solve(Puzzle puzzle, size_t (*heuristic)(Puzzle)) {
  Puzzle start = puzzle;

  std::vector<Action> actions;
  std::vector<Puzzle> states;
  states.push_back(puzzle);

  size_t bound = heuristic(start);
  while (bound != 0 && bound != SIZE_MAX) {
    bound = ida_search(actions, states, 0, bound, heuristic);
  }

  return actions;
}

std::vector<Action> LRTAStar::solve(Puzzle puzzle, size_t (*heuristic)(Puzzle)) {
  std::map<Puzzle, size_t> h;
  std::vector<Action> actions;
  Puzzle state = puzzle;
  while (!state.is_solved()) {
    // Planning
    size_t min_f = SIZE_MAX;
    Puzzle next_state = state;
    Action next_action;
    for (Action action : state.actions()) {
      Puzzle neighbour = state;
      neighbour.move(action);
      if (h.find(neighbour) == h.end())
	h[neighbour] = heuristic(neighbour);
      // NOTE: Move cost is always 1.
      size_t f = 1 + h[neighbour];
      if (f < min_f) {
	next_state = neighbour;
	next_action = action;
	min_f = f;
      }
    }
    // Learning
    if (min_f > h[state])
      h[state] = min_f;
    // Acting
    state = next_state;
    actions.push_back(next_action);
  }
  return actions;
}
