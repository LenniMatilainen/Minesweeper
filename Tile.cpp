#include "Tile.h"
#include <iostream>

// Default constructor
Tile::Tile()
{
  value = 0;
  revealed = false;
}

// Constuctor with updated count
Tile::Tile(int val, bool rev)
{
  value = val;
  revealed = rev;
}

int Tile::get_value() { return value; }
void Tile::set_value(int val) { value = val; }
bool Tile::get_revealed_status() { return revealed; }
// Displays either a value, mine or a hashtag depending on the revealed boolean
void Tile::display()
{
  if (revealed)
  {
    if (value == 9)
    {
      std::cout << 'M';
    }
    else
    {
      std::cout << value;
    }
  }
  else
  {
    std::cout << "#";
  }
}

void Tile::set_revealed() { revealed = true; }