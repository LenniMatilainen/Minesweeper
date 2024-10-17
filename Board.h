#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"

class Board
{
private:
  Tile *board;
  int board_width;
  int board_height;
  int mine_count;
  void place_mines();
  void update_counts();
  bool has_won;
  bool has_lost;
  int revealed_count;
  bool is_within_board(int row, int col) const;

public:
  Board();
  Board(int width, int heigth, int mine_count);
  ~Board();
  void print();
  void reveal(int row, int col);
  bool get_has_won() const;
  bool get_has_lost() const;
  void display_revealed();
};

#endif