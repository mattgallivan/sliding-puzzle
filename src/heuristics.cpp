/* Copyright (c) 2021 Matthew Gallivan <gallivan.matt@gmail.com>
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 */

#include "heuristics.h"

size_t manhattan(Puzzle puzzle) {
  size_t distance = 0;
  for (size_t i = 0; i < puzzle.width * puzzle.height; ++i) {
    size_t tile = puzzle.board[i];
    if (tile == BLANK || tile == i + 1)
      continue;
    size_t curr_row = i / puzzle.width;
    size_t curr_col = i % puzzle.width;
    size_t expt_row = (tile - 1) / puzzle.width;
    size_t expt_col = (tile - 1) % puzzle.width;
    // NOTE: Ternary statements to check for underflow.
    distance += curr_row > expt_row ? curr_row - expt_row : expt_row - curr_row;
    distance += curr_col > expt_col ? curr_col - expt_col : expt_col - curr_col;
  }
  return distance;
}
