#ifndef PUZZLE_H
#define PUZZLE_H

#include <stddef.h>

class Puzzle {
  size_t width, height;
  size_t* board;

 public:
  Puzzle(size_t size);
  ~Puzzle();

  bool is_solvable();
  void print();
};

#endif /* PUZZLE_H */
