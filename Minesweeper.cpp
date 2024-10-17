#include "Board.cpp"
#include <iostream>

int main()
{
  int rows, columns, mine_count;
  int dugRow, dugCol;
  // Prompt the user for a "difficulty" to play (width, height, minecount etc)
  std::cout << "Enter a board size rows followed by columns: ";
  std::cin >> rows >> columns;
  std::cout << "Enter number of mines for custom difficulty: ";
  std::cin >> mine_count;
  std::cout << std::endl;
  // Create the Board based on those parameters
  Board game(rows, columns, mine_count);
  // Repeat until the user has either WON or LOST
  while (!game.get_has_lost() && !game.get_has_won())
  {
    // Display the board (remember the Tile's keep track of whether they have
    // been revealed or not)
    game.print();
    // Ask the user where they want to "reveal"
    std::cout << "Enter a row and column to dig: ";
    std::cin >> dugRow >> dugCol;
    // Reveal the board at that spot (new method reveal() )
    game.reveal(dugRow, dugCol);
  }

  // After the loop ends determine
  // if the user has won
  if (game.get_has_won())
  {
    // tell them
    std::cout << "\nYOU'VE WON!!!\nFinal Board: " << std::endl;
    // display the final board without revealing the mines
    game.print();
  }
  else
  { // otherwise
    // tell them they lost
    std::cout << "\nYOU'VE LOST!!!!!!!\nFinal Board: " << std::endl;
    // display the whole board in a revealed state
    game.display_revealed();
  }
}