/* 
* Simple Mastermind Game
* An eight index board is randomly filled with four colors represented by B = "Black", W = "White", R = "Red", Y = "Yellow"
* The user has a fixed number of guesses to match the pattern
* User input = eight char string without spaces. Input is transformed to uppercase before being displayed on board
*/

#include <iostream>
#include <string>
#include <cstdlib> /* srand */
#include <ctime>

const int BOARD_SIZE = 8;

class mastermind {
  public:
    mastermind();
    void play();
  private:
    void printBoard(std::string board);
    bool compareBoards(std::string guess, std::string answer);
    std::string randomizeSolution();
    std::string updateBoard(std::string input);
    std::string board;
    std::string answerBoard;
};


int main(){
  mastermind game;
  game.play();
  return 0;
}

mastermind::mastermind() {
  board[0] = '0';
  board[1] = '1';
  board[2] = '2';
  board[3] = '3';
  board[4] = '4';
  board[5] = '5';
  board[6] = '6';
  board[7] = '7';
}

/*                                                                                                                           
 * Prints Mastermind board.                                                                                                 
 */
void mastermind::printBoard(std::string board) {
  std::cout << "+---+---+---+---+---+---+---+---+" << std::endl;
  std::cout << "| " << board[0]  << " | " << board[1] << " | " << board[2] << " | " << board[3] << " | " << board[4] << " | " << board[5] << " | " << board[6] << " | " << board[7] << " | " << std::endl;
  std::cout << "+---+---+---+---+---+---+---+---+" << std::endl;

}

/*                                                                                                                           
 * Randomly chooses a number from 0 - 3, assigns char at index to 'B' if 0, else 'W' if 1, else 'Y' if 2, else 'R' if 3                                                     
 */
std::string mastermind::randomizeSolution()
{
  srand(time(NULL));
  for (int i = 0; i < BOARD_SIZE; i++) {
    if (rand() % 4 == 0) {
      answerBoard[i] = 'B';
    } else if (rand() % 4 == 1) {
      answerBoard[i] = 'W';
    } else if (rand() % 4 == 2) {
      answerBoard[i] = 'Y';
    } else {
      answerBoard[i] = 'R';
    }
  }
  return answerBoard;
}

/*                                                                                                                           
 * Compare user input guess with answer                                                        
 */
bool mastermind::compareBoards(std::string guess, std::string answer) {
  bool matched = false;
  int count = 0;
  for (int i = 0; i < BOARD_SIZE; i++) {
    if (guess[i] == answer[i]) {
        count++;
    } else {
      matched = false;
    }
  }
  if (count == 8) {
    matched = true;
  }
  return matched;
}

/*                                                                                                                           
 * Outputs updated board with guesses from user that match                                                              
 */
std::string mastermind::updateBoard(std::string input)
{
  for (int i = 0; i<BOARD_SIZE; i++ ) {
    // if a match, add to attempt string
    if (input[i] == answerBoard[i]){
      board[i] = input[i];
    } 
  }
  return board;
}


void mastermind::play() {
    int tries = 4;
    bool matched = false;
    std::cout << "\n     Welcome to MASTERMIND!" << std::endl;
    // print empty board to start
    board = "????????";
    printBoard(board);

    std::string input = "";
    randomizeSolution();
    std::cout << "Solution: " << std::endl;
    printBoard(answerBoard);

    while (!matched) {
      std::cout << "Enter a guess: ";
      std::cin >> input;

      // convert input to uppercase
      std::transform(input.begin(), input.end(),input.begin(), ::toupper);

      //to do: input validation
      //if input is not one of the color options, get new input

      
      // compare input to answer. If correct color and position is guessed, then print to user
      matched = compareBoards(input, answerBoard);
      std::string updated_board = updateBoard(input);
      printBoard(updated_board);

      // Check if user has guessed the answer and how many guesses left
      if (matched) {
        std::cout << "You guessed it!" << std::endl;
      } else {
        std::cout << "Guess again. You have " << tries << " guesses left." << std::endl;
      }
      tries--;
    }
    if (tries == 0) {
      std::cout << "Out of guesses! The answer is: " << std::endl;
      printBoard(answerBoard);
    }
}
