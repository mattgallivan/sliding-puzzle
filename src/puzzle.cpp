/* Copyright (c) 2021 Matthew Gallivan <gallivan.matt@gmail.com>
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 */

#include "puzzle.h"

#include <array>
#include <iostream>

Puzzle::Puzzle(size_t size) {
  width = size;
  height = size;

  // Randomly place the tiles on the board.
  std::vector<size_t> tiles;
  for (size_t i = 0; i < width * height; ++i)
    tiles.push_back(i);
  for (size_t i = 0; i < width * height; ++i) {
    size_t index = rand() % tiles.size();
    board.push_back(tiles[index]);
    tiles.erase(tiles.begin() + index);
  }
}

bool Puzzle::operator==(const Puzzle& puzzle) const {
  return board == puzzle.board;
}

bool Puzzle::operator!=(const Puzzle& puzzle) const {
  return board != puzzle.board;
}

bool Puzzle::operator<(const Puzzle& puzzle) const {
  if (width < puzzle.width || height < puzzle.height)
    return true;
  for (size_t i = 0; i < width * height; ++i) {
    if (board[i] < puzzle.board[i])
      return true;
    else if (board[i] > puzzle.board[i])
      return false;
  }
  return false;
}

std::vector<Action> Puzzle::actions() const {
  size_t index = index_of(BLANK);
  size_t row = index / width;
  size_t col = index % width;

  std::vector<Action> actions;
  if (col > 0)
    actions.push_back(LEFT);
  if (col < width - 1)
    actions.push_back(RIGHT);
  if (row > 0)
    actions.push_back(UP);
  if (row < height - 1)
    actions.push_back(DOWN);
  return actions;
}

bool Puzzle::is_solvable() const {
  // Solvability: https://mathworld.wolfram.com/15Puzzle.html
  size_t parity = 0;
  size_t blank_row = 0;
  for (size_t i = 0; i < width * height; ++i) {
    size_t tile = board[i];
    // We note the blank's row for the last calculation.
    if (tile == BLANK) {
      blank_row = height - (i / width) - 1;
      continue;
    }
    if (tile == 1)
      continue; // Nothing is less than 1.
    for (size_t j = i + 1; j < width * height; ++j) {
      size_t next = board[j];
      if (next == BLANK)
        continue;
      if (next < tile)
        parity++;
    }
  }
  return (parity + blank_row) % 2 == 0;
}

bool Puzzle::is_solved() const {
  if (board[0] != 1)
    return false;
  for (size_t i = 1; i < width * height; ++i) {
    if (board[i] == BLANK)
      continue;
    if (board[i] != i + 1)
      return false;
  }
  return true;
}

void Puzzle::print() const {
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

void Puzzle::move(Action action) {
  size_t index = index_of(BLANK);
  size_t row = index / width;
  size_t col = index % width;
  switch (action) {
  case LEFT:
    if (col == 0)
      return;
    swap(row, col, row, col - 1);
    break;
  case RIGHT:
    if (col == width - 1)
      return;
    swap(row, col, row, col + 1);
    break;
  case UP:
    if (row == 0)
      return;
    swap(row, col, row - 1, col);
    break;
  case DOWN:
    if (row == height - 1)
      return;
    swap(row, col, row + 1, col);
    break;
  };
}

size_t Puzzle::index_of(size_t tile) const {
  for (size_t i = 0; i < width * height; ++i) {
    if (board[i] == tile)
      return i;
  }
  return SIZE_MAX;
}

void Puzzle::swap(size_t ra, size_t ca, size_t rb, size_t cb) {
  size_t idxa = width * ra + ca;
  size_t idxb = width * rb + cb;
  size_t tmp = board[idxa];
  board[idxa] = board[idxb];
  board[idxb] = tmp;
}

size_t PuzzleHash::operator()(const Puzzle& puzzle) const {
  size_t hash = 0;
  for (size_t i = 0; i < puzzle.width * puzzle.height; ++i) {
    hash += i * puzzle.board[i];
  }
  return hash;
}
