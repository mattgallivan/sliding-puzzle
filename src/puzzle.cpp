#include "puzzle.h"

#include <iostream>
#include <vector>

Puzzle::Puzzle(size_t size) {
  width = size;
  height = size;
  board = new size_t[width * height];

  // Randomly place the tiles on the board.
  std::vector<size_t> tiles;
  for (size_t i = 0; i < width * height; ++i)
    tiles.push_back(i);
  for (size_t i = 0; i < width * height; ++i) {
    size_t index = rand() % tiles.size();
    board[i] = tiles[index];
    tiles.erase(tiles.begin() + index);
  }
}

Puzzle::~Puzzle() { delete[] board; }

bool Puzzle::is_solvable() {
  // Solvability: https://mathworld.wolfram.com/15Puzzle.html
  size_t parity = 0;
  size_t blank_row = 0;
  for (size_t i = 0; i < width * height; ++i) {
    size_t tile = board[i];
    // We note the blank's row for the last calculation.
    if (tile == 0) {
      blank_row = height - (i / width) - 1;
      continue;
    }
    if (tile == 1)
      continue; // Nothing is less than 1.
    for (size_t j = i + 1; j < width * height; ++j) {
      size_t next = board[j];
      if (next == 0)
        continue; // Ignore the blank.
      if (next < tile)
        parity++;
    }
  }
  return (parity + blank_row) % 2 == 0;
}

void Puzzle::print() {
  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      std::cout << board[y * width + x];
      if (x != width - 1)
        std::cout << "\t";
      else
        std::cout << "\n";
    }
  }
}
