/* Copyright (c) 2021 Matthew Gallivan <gallivan.matt@gmail.com>
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 */

#ifndef PUZZLE_H
#define PUZZLE_H

#include <map>
#include <vector>

#include <stddef.h>

const size_t BLANK = 0; // The representation of the empty tile.

enum Action { LEFT, RIGHT, UP, DOWN, NUM_ACTIONS };
static std::map<Action, std::string> action_strings = {
    {LEFT, "LEFT"},
    {RIGHT, "RIGHT"},
    {UP, "UP"},
    {DOWN, "DOWN"},
};

class Puzzle {
public:
  size_t width, height;
  std::vector<size_t> board;

  Puzzle(size_t size);

  bool operator==(const Puzzle& puzzle) const;
  bool operator!=(const Puzzle& puzzle) const;
  bool operator<(const Puzzle& puzzle) const;

  std::vector<Action> actions() const;
  bool is_solvable() const;
  bool is_solved() const;
  void print() const;

  void move(Action action);

private:
  size_t index_of(size_t tile) const;
  void swap(size_t ra, size_t ca, size_t rb, size_t cb);
};

#endif /* PUZZLE_H */
