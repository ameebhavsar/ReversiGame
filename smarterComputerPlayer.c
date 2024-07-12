//
// Author: Amee Bhavsar
//
#include <stdbool.h>
#include <stdio.h>

#include "lab8part2.h"
#include "liblab8part2.h"

// Timer
#include <sys/resource.h>
#include <sys/time.h>

struct rusage usage;  // a structure to hold "resource usage" (including time)
struct timeval start, end;  // will hold the start and end times

int miniMax(char board[][26], int depth, bool maxPlayer) {
return 1;
/*  int bestScore = -1000;
  int score = 0;
  
  // Terminating condition
  if(depth == 0){
    return bestScore;
  }

  if(maxPlayer){

    return 0;
  }

return 0;*/

  }

int* aiMove(char board[][26], const char colour, const int n, int depth){
  int bestScore = -1000;
  int score = 0;
  int bestRow = 0, bestCol = 0;



// Find an available move
  // Iterate through every square
  for (int rows = 0; rows < n; rows++) {
    for (int cols = 0; cols < n; cols++) {
      // Check if square is unoccupied
      if (board[rows][cols] == 'U') {
        // Iterate through every direction, to check legality 
        for (int i = -1; i <= 1; i++) {
          for (int j = -1; j <= 1; j++) {
            if (!(i == 0 && j == 0)) {
              if (checkLegalInDirection(board, n, rows, cols, colour, i, j)) {


                // Possible move found, place AI move
                board[rows][cols] = colour;
                score = miniMax(board, depth, true);
                board[rows][cols] = 'U';
                if(score> bestScore){
                  bestScore = score;
                  bestRow = rows;
                  bestCol = cols;
                  }



              }
            }
          }
        }
      }
    }
  }
int moveToMake[2] = {bestRow, bestCol};
  

return moveToMake;


}

int makeMove(const char board[][26], int n, char turn, int *row, int *col) {

  getrusage(RUSAGE_SELF, &usage);
  start = usage.ru_utime;
  double timeStart = start.tv_sec + start.tv_usec / 1000000.0;  // in seconds

  // computer strategy
  int* moveToMake[2] = aiMove(board, turn, n, 3);

  getrusage(RUSAGE_SELF, &usage);
  end = usage.ru_utime;
  double timeEnd = end.tv_sec + end.tv_usec / 1000000.0;  // in seconds
  double totalTime = timeEnd - timeStart;
  // totalTime now holds the time (in seconds) it takes to run your code

  // If n =8 and time !<= 1 sec --> return as an invalid move --> otherwise
  // proceed

  return 0;
}

// Part 1 functions
bool gameOver(char computer, char player, char board[][26], int n,
              bool invalidPlay) {
  int compP = 0, playP = 0;

  if (invalidPlay) {
    printf("%c player wins.", computer);
  }

  else {
    // Iterate through each square
    for (int rows = 0; rows < n; rows++) {
      for (int cols = 0; cols < n; cols++) {
        if (board[rows][cols] == computer) {
          compP++;
        } else if (board[rows][cols] == player) {
          playP++;
        }
      }
    }

    if (compP < playP) {
      printf("%c player wins.", player);
    } else if (compP > playP) {
      printf("%c player wins.", computer);
    } else {
      printf("Draw!");
    }
  }

  return true;
}

void printBoard(char board[][26],
                int n) {  // Print board as it is @ time of use

  char colchr = 'a', rowchr = 'a';
  printf("  ");

  // Print scale of columns
  for (int i = 0; i < n; i++) {
    printf("%c", colchr);
    colchr++;
  }
  printf("\n");

  for (int rows = 0; rows < n; rows++) {
    printf("%c ", rowchr);
    rowchr++;
    for (int cols = 0; cols < n; cols++) {
      printf("%c", board[rows][cols]);
    }
    printf("\n");
  }
}

bool positionInBounds(
    int n, int row,
    int col) {  // Check if (row, col) input is within the board's dimensions
  bool isIt = true;
  if (row < n && col < n && row >= 0 && col >= 0) {
    isIt = true;
  } else {
    isIt = false;
  }
  return isIt;
}

// check if some input (row , col) is a legal move = inside bounds and has the
// stupid opp colour and our colour
bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol) {
  // Variables
  char opp;
  int count = 0;
  bool legality = false, exit = false;

  // Define the opposing colour
  if (colour == 'B') {
    opp = 'W';
  } else {
    opp = 'B';
  }

  for (int i = 1; exit == false && legality == false; i++) {
    // If the next letter in that direction is outside the board
    if (positionInBounds(n, row + (deltaRow * i), col + (deltaCol * i)) ==
        false) {
      exit = true;
    }

    // Otherwise
    else {
      // Check if the next letter in that direction is the opposing colour
      if (board[row + (deltaRow * i)][col + (deltaCol * i)] == opp) {
        count++;
      }

      // Letter is not the opposing colour, so, letter is U or our colour
      else {
        // Letter is our colour but not the first letter in that direction
        if (count != 0 &&
            board[row + (deltaRow * i)][col + (deltaCol * i)] == colour) {
          legality = true;
        }
        // Letter is U
        else {
          exit = true;
        }
      }
    }
  }

  return legality;
}

bool hasAvailableMoves(
    char board[][26], int n,
    char colour) {  // finds a (row, col) at which we can place = U --> legaldir

  bool hasMove = false;
  // Iterate through
  for (int rows = 0; rows < n; rows++) {
    for (int cols = 0; cols < n; cols++) {
      // Check if square is unoccupied
      if (board[rows][cols] == 'U') {
        // bool foundOne = false;  // did NOT find square

        // Iterate through every direction
        for (int i = -1; i <= 1; i++) {
          for (int j = -1; j <= 1; j++) {
            if (!(i == 0 && j == 0)) {
              if (checkLegalInDirection(board, n, rows, cols, colour, i, j)) {
                hasMove = true;
                // foundOne = true;
              }
            }
          }
        }
      }
    }
  }
  return hasMove;
}

bool inputValidation(char board[][26], int n, char colour, int row,
                     int col) {  // Checks player input shit

  bool validation = true;
  if (positionInBounds(n, row, col) == false) {  // Play is out of bounds
    validation = false;
  }

  else {  // Play is in bounds
    bool foundOne = false;
    // Iterate through every direction to find the direction
    for (int i = -1; i <= 1 && foundOne == false; i++) {
      for (int j = -1; j <= 1 && foundOne == false; j++) {
        if (!(i == 0 && j == 0)) {
          if (checkLegalInDirection(board, n, row, col, colour, i, j)) {
            foundOne = true;
          }
        }
      }
    }

    if (foundOne ==
        false) {  // In bounds play, but not a legal move in terms of gameplay
      validation = false;
    }
  }
  return validation;
}

void flipTile(char board[][26], int n, char colour, int row,
              int col) {  // Flips ALL tiles at input (row, col)

  // Iterate through every direction to find the direction to go in
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (!(i == 0 && j == 0)) {
        if (checkLegalInDirection(board, n, row, col, colour, i, j)) {
          // Place player colour on the empty spot
          board[row][col] = colour;

          // Flip the preceeding tiles until you hit your own tile in that
          // direciton
          for (int tile = 1;
               board[row + (i * tile)][col + (j * tile)] != colour; tile++) {
            board[row + (i * tile)][col + (j * tile)] = colour;
          }
        }
      }
    }
  }
}

void boardConfiguration(char board[][26]) {  // Midgame functionality

  // (2) Board Configuration
  char colourC = '\0', rowC = '\0', columnC = '\0';
  int indR = 0, indC = 0;
  // Prompt
  printf("Enter board configuration:\n");
  scanf(" %c%c%c", &colourC, &rowC, &columnC);

  while (!(colourC == '!' && rowC == '!' &&
           columnC == '!')) {  // Iterate as long as input is not '!!!'
    indR = rowC - 'a';
    indC = columnC - 'a';

    if (colourC == 'B') {
      board[indR][indC] = 'B';
    } else {
      board[indR][indC] = 'W';
    }

    scanf(" %c%c%c", &colourC, &rowC, &columnC);
  }
}

void computerPlay(char board[][26], int n, char currentPlay) {
  int Hrow = 0, Hcol = 0, Hscore = 0, score = 0;

  // Iterate through each square
  for (int rows = 0; rows < n; rows++) {
    for (int cols = 0; cols < n; cols++) {
      // Check if square is unoccupied
      if (board[rows][cols] == 'U') {  // If it is unoccupied:

        // Iterate through EVERY DIR direction
        for (int i = -1; i <= 1; i++) {
          for (int j = -1; j <= 1; j++) {
            if (!(i == 0 && j == 0)) {
              if (checkLegalInDirection(board, n, rows, cols, currentPlay, i,
                                        j)) {  // Check (rows, cols) is legal

                // Sum the preceeding tiles until you hit your own tile in that
                // ONE direciton
                for (int tile = 1;
                     board[rows + (i * tile)][cols + (j * tile)] != currentPlay;
                     tile++) {
                  score++;
                }
              }
            }
          }
        }

        if (score > Hscore) {  // If the most tiles are flipped --> make this
                               // the play for comp
          Hscore = score;
          Hrow = rows;
          Hcol = cols;
          score = 0;  // Reset score
        } else if (score <= Hscore) {
          score = 0;  // Reset score
        }
      }
    }
  }

  flipTile(board, n, currentPlay, Hrow, Hcol);
  printf("Computer places %c at %c%c.\n", currentPlay, Hrow + 'a', Hcol + 'a');
}

bool inputPlay(char currentPlay, char computer, char player, char board[][26],
               int n) {
  bool isGameOver = false;
  int aiRow = 0, aiCol = 0;
  char colour = '\0', row = '\0', column = '\0';

  if (currentPlay == computer) {  // computer play
    //computerPlay(board, n, computer);

    makeMove(board, n, computer, &aiRow, &aiCol);
    flipTile(board, n, computer, aiRow, aiCol);
    printBoard(board, n);
  }

  else {  // human play
    colour = player;
    // take input for a move

    //findSmarterMove(board, n, colour, &row, &column);
    //printf("Testing AI move (row, col): %c%c\n", row + 'a', column + 'a');
    printf("Enter move for colour %c (RowCol): \n", colour);
    scanf(" %c%c", &row, &column);

    if (inputValidation(board, n, colour, row - 'a', column - 'a')) {
      flipTile(board, n, colour, row - 'a', column - 'a');
      printBoard(board, n);

      isGameOver = false;
    }

    else if (inputValidation(board, n, colour, row - 'a', column - 'a') ==
             false) {
      printf("Invalid move.\n");
      isGameOver = gameOver(computer, player, board, n, true);
    }
  }
  return isGameOver;
}

// Main Function
int main(void) {
  bool isGameOver = false;
  char computer = '\0', player = '\0', currentPlay = '\0', idlePlayer = '\0';
  int n = 0;

  // (1) Input n (for nxn table) and assign computer's colour
  printf("Enter the board dimension:");
  scanf("%d", &n);
  printf("Computer plays (B/W): ");
  scanf(" %c", &computer);

  // Assign player colour and computer colour
  if (computer == 'B') {
    player = 'W';
  } else {
    player = 'B';
  }

  // Initialize the board with its starting positions
  char board[26][26];
  for (int rows = 0; rows < n; rows++) {
    for (int cols = 0; cols < n; cols++) {
      // Assigning initial board positions
      int b = n - 1;
      if ((rows == (b / 2) && cols == (b / 2)) ||
          (rows == ((b / 2) + 1) && cols == ((b / 2) + 1))) {
        board[rows][cols] = 'W';
      }

      else if ((rows == (b / 2) && cols == ((b / 2) + 1)) ||
               (rows == ((b / 2) + 1) && cols == (b / 2))) {
        board[rows][cols] = 'B';
      }

      else {
        board[rows][cols] = 'U';
      }
    }
  }

  // Print the initial board
  printBoard(board, n);

  // First play --> always black player
  isGameOver =
      inputPlay('B', computer, player, board, n);  // Pass currentPlay as B


// Main Game play, rounds
  for (int i = 1; isGameOver == false; i++) {
    // Odd number play --> White plays, Even number play --> Black plays
    if (i % 2 == 0) {  // Even number play --> Black plays
      currentPlay = 'B';
      idlePlayer = 'W';
    } else {  // Odd number play --> White plays
      currentPlay = 'W';
      idlePlayer = 'B';
    }

    // Check if current player has a play
    if (hasAvailableMoves(board, n, currentPlay)) {
      // Complete 1 round of play
      isGameOver = inputPlay(currentPlay, computer, player, board, n);
    } else if (hasAvailableMoves(board, n, idlePlayer)) {
      // If not, switch player until play exists
      printf("%c player has no valid move.\n", currentPlay);
      while (hasAvailableMoves(board, n, currentPlay == false)) {
        isGameOver = inputPlay(idlePlayer, computer, player, board, n);
      }
    } else {
      isGameOver = gameOver(computer, player, board, n, false);
    }
  }

  return 0;
}
