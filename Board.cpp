#include "Board.h"
#include "Tile.cpp"
#include <array>
#include <iostream>
#include <random>
#include <vector>

void PrintBoardLine(int rows);

// Default constructor
Board::Board()
{
  revealed_count = 0;
  has_won = false;
  has_lost = false;
  mine_count = 10;
  board_width = 8;
  board_height = 8;
  board = new Tile[board_width * board_height];
  place_mines();   // Place the mines on the board
  update_counts(); // Set the counts for the tiles for nearby mines
}

// Constructor with the user given values
Board::Board(int width, int heigth, int m_count)
{
  revealed_count = 0;
  has_won = false;
  has_lost = false;
  mine_count = m_count;
  board_width = width;
  board_height = heigth;
  board = new Tile[board_width * board_height];
  place_mines();   // Place the mines on the board
  update_counts(); // Set the counts for the tiles for nearby mines
}

// Destructor
Board::~Board() { delete[] board; }

void Board::place_mines()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distribution(
      0, ((board_width * board_height) - 1));

  std::vector<int> minePool;
  int mineTileIndex{0};
  const int mine{9};

  // Place mines
  for (int i{0}; i < mine_count; ++i)
  {
    bool is_unique;
    // Randomize a number and check if it has been already randomized, then
    // store it into a vector
    do
    {
      is_unique = true;
      mineTileIndex = distribution(gen);

      for (int j : minePool)
      {
        if (j == mineTileIndex)
        {
          is_unique = false;
          break;
        }
      }
    } while (!is_unique);

    minePool.push_back(mineTileIndex);

    // Place the mine on the field
    board[mineTileIndex].set_value(mine);
  }
}

void Board::update_counts()
{
  std::array<int, 8> nearbyTiles{
      -board_width - 1, -board_width, -board_width + 1, -1, 1,
      board_width - 1, board_width, board_width + 1};
  int possibleMineIndex{0}, nrby{0}, row{0}, col{0};
  // Iterate through every tile on the board
  for (int i{0}; i < (board_width * board_height); i++)
  {
    // If the tile's value is a 0, check nearby mines
    if (board[i].get_value() == 0)
    {
      for (int j{0}; j < 8; j++)
      {
        // Add numbers the nearby tiles indexes to the current tile index in the
        // row
        nrby = nearbyTiles.at(j);
        possibleMineIndex = i + nrby;
        row = i / board_width;
        col = i % board_width;
        if (possibleMineIndex > ((board_width * board_height) - 1) ||
            possibleMineIndex < 0)
        { // If the row goes out of bounds, move to
          // the next possible mine tile
          continue;
        }
        // If a tile is on the edge of the board, there are special cases
        // where a mine could be detected from the other side of the board.
        // This if statement is for preventing that from happening.
        if (col == 0 && (nrby == nearbyTiles.at(0) || nrby == -1 ||
                         nrby == nearbyTiles.at(5)))
        {
          continue;
        }
        else if (col == board_width - 1 &&
                 (nrby == nearbyTiles.at(2) || nrby == 1 ||
                  nrby == nearbyTiles.at(7)))
        {
          continue;
        }

        // If the there is a mine on a nearby tile, add +1 to the tile number.
        if (board[possibleMineIndex].get_value() == 9)
        {
          board[i].set_value(board[i].get_value() + 1);
        }
      }
    }
  }
}

bool Board::get_has_lost() const { return has_lost; }
bool Board::get_has_won() const { return has_won; }

void Board::display_revealed()
{
  // Reveal all tiles
  for (int i{0}; i < (board_width * board_height); i++)
  {
    board[i].set_revealed();
  }
  print();
}

bool Board::is_within_board(int row, int col) const
{
  if (row > board_height - 1 || col > board_width - 1 || row < 0 || col < 0)
  {
    return false;
  }
  return true;
}

void Board::reveal(int row, int col)
{
  int tileIndex;
  // Calculate the index of the tile with given row and col
  tileIndex = (row * board_width) + col;
  // If tile has been already revealed, return
  if (board[tileIndex].get_revealed_status() || !is_within_board(row, col))
  {
    return;
  }
  // Set the tile's revealed state to true
  board[tileIndex].set_revealed();
  revealed_count++; // Increment the revealed count by one
  // If the value of the revealed tile was a mine set has_lost as true
  if (board[tileIndex].get_value() == 9)
  {
    has_lost = true;
    // Then see if all possible tiles are revealed
  }
  else if (revealed_count == board_width * board_height - mine_count)
  {
    has_won = true; // If true, then set has_won as true
  }
}

// Function to style the board with
void PrintBoardLine(int rows)
{
  std::cout << "  ";
  for (int i{0}; i < rows; i++)
  {
    std::cout << '|' << "---";
  }
  std::cout << '|' << std::endl;
}

// Print it all out
void Board::print()
{
  int lineBreak{0}, count{0};
  std::cout << "  ";
  for (int i{0}; i < board_width; i++)
  {
    std::cout << "  " << count << ' ';
    count++;
  }
  count = 0;
  std::cout << std::endl;
  PrintBoardLine(board_width);
  std::cout << count << ' ';
  count++;
  for (int i{0}; i < (board_width * board_height); i++)
  {
    lineBreak++;
    if (lineBreak == board_width + 1)
    {
      std::cout << "|\n";
      PrintBoardLine(board_width);
      std::cout << count << ' ';
      count++;
      lineBreak = 1;
    }
    std::cout << "| ";
    board[i].display();
    std::cout << ' ';
  }
  count = 0;
  lineBreak = 0;
  std::cout << "|\n";
  PrintBoardLine(board_width);
}