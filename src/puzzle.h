#ifndef PUZZLE_H
#define PUZZLE_H

#include <stddef.h>

enum Action { LEFT, RIGHT, UP, DOWN };

class Puzzle {
  size_t width, height;
  size_t* board;

public:
  Puzzle(size_t size);
  ~Puzzle();

  bool is_solvable() const;
  bool is_solved() const;
  void print() const;

  void move(Action action);

private:
  size_t index_of(size_t tile) const;

  void swap(size_t ra, size_t ca, size_t rb, size_t cb);
};

#endif /* PUZZLE_H */
