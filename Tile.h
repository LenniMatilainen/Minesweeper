#ifndef TILE_H
#define TILE_H

class Tile
{
private:
  int value;
  bool revealed;

public:
  Tile();
  Tile(int val, bool rev);
  void display();
  void set_revealed();
  int get_value();
  bool get_revealed_status();
  void set_value(int val);
};

#endif