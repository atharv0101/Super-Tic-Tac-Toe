#include <iostream>
using namespace std;

const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
const char EMPTY = ' ';
const char *COLOR_RESET = "\033[0m";
const char *COLOR_X = "\033[1;31m"; // Red
const char *COLOR_O = "\033[1;34m"; // Blue

// Function prototypes
void display(char board[9][9], char BigBox[9]);
char checkWin(char board[9]);
void updateBigBox(char BigBox[9], char smallBoards[9][9]);
bool isBoardFull(char board[9]);
void Input(char smallBoards[9][9], char& player, int& nextBoard, char BigBox[9]);
bool isBigBoardFull(char BigBox[9]);

// Display the Super Tic Tac Toe board
void display(char board[9][9], char BigBox[9]) {
    for (int i = 0; i < 9; i += 3) {
        for (int row = 0; row < 3; ++row) {
            for (int j = 0; j < 3; ++j) {
                int boardIndex = i + j;
                int startIndex = row * 3;

                // Check if the board is won
                if (BigBox[boardIndex] != EMPTY) {
                    char winner = BigBox[boardIndex];
                    for (int col = 0; col < 3; ++col) {
                        cout << (winner == PLAYER_X ? COLOR_X : COLOR_O) << " " << winner << " " << COLOR_RESET;
                        if (col < 2) cout << " "; // Add extra space between cells
                    }
                } else {
                    // Display the normal board cells
                    for (int col = 0; col < 3; ++col) {
                        char cell = board[boardIndex][startIndex + col];
                        if (cell == PLAYER_X) {
                            cout << COLOR_X << " " << cell << " " << COLOR_RESET;
                        } else if (cell == PLAYER_O) {
                            cout << COLOR_O << " " << cell << " " << COLOR_RESET;
                        } else {
                            cout << " " << "-" << " ";
                        }
                        if (col < 2) cout << " "; // Add extra space between cells
                    }
                }
                if (j < 2) cout << "     "; // Add horizontal space between small boards
            }
            cout << endl;
        }
        if (i < 6) cout << endl; // Add vertical space between rows of small boards
    }
    cout << "Big Board Status: ";
    for (int i = 0; i < 9; ++i) {
        if (BigBox[i] == PLAYER_X) {
            cout << COLOR_X << BigBox[i] << COLOR_RESET << " ";
        } else if (BigBox[i] == PLAYER_O) {
            cout << COLOR_O << BigBox[i] << COLOR_RESET << " ";
        } else {
            cout << BigBox[i] << " ";
        }
    }
    cout << endl;
}

// Check for a winner on a small board
char checkWin(char board[9]) {
    // Check rows
    for (int i = 0; i < 9; i += 3) {
        if (board[i] != EMPTY && board[i] == board[i + 1] && board[i + 1] == board[i + 2]) {
            return board[i];
        }
    }
    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (board[i] != EMPTY && board[i] == board[i + 3] && board[i + 3] == board[i + 6]) {
            return board[i];
        }
    }
    // Check diagonals
    if (board[0] != EMPTY && board[0] == board[4] && board[4] == board[8]) {
        return board[0];
    }
    if (board[2] != EMPTY && board[2] == board[4] && board[4] == board[6]) {
        return board[2];
    }
    return EMPTY;
}

// Check if a small board is full
bool isBoardFull(char board[9]) {
    for (int i = 0; i < 9; ++i) {
        if (board[i] == EMPTY) return false;
    }
    return true;
}

// Update the status of the BigBox based on the small boards
void updateBigBox(char BigBox[9], char smallBoards[9][9]) {
    for (int i = 0; i < 9; ++i) {
        if (BigBox[i] == EMPTY) {
            BigBox[i] = checkWin(smallBoards[i]);
        }
    }
}

// Check if the entire big board is full
bool isBigBoardFull(char BigBox[9]) {
    for (int i = 0; i < 9; ++i) {
        if (BigBox[i] == EMPTY) return false;
    }
    return true;
}

// Handle player input and update the board
void Input(char smallBoards[9][9], char& player, int& nextBoard, char BigBox[9]) {
    int boardChoice, cellChoice;
    int tries = 0;
    const int MAX_TRIES = 5;
    while (true) {
        if (nextBoard == -1) {
            cout << "Select the board number (1-9): ";
            cin >> boardChoice;
            boardChoice--; // Adjust for 0-based indexing
        } else {
            boardChoice = nextBoard;
            cout << "Playing in board " << boardChoice + 1 << endl; // Show the board being played
        }

        // Check if the selected board is valid
        if (boardChoice >= 0 && boardChoice < 9 && BigBox[boardChoice] == EMPTY) {
            cout << "Select the cell number (1-9) in board " << boardChoice + 1 << ": ";
            cin >> cellChoice;
            cellChoice--; // Adjust for 0-based indexing

            // Check if the selected cell is valid
            if (cellChoice >= 0 && cellChoice < 9 && smallBoards[boardChoice][cellChoice] == EMPTY) {
                smallBoards[boardChoice][cellChoice] = player;
                nextBoard = cellChoice;
                break;
            } else {
                cout << "Invalid cell choice, try again." << endl;
            }
        } else {
            cout << "Invalid board choice, try again." << endl;
        }

        // Prevent infinite loop by breaking after MAX_TRIES
        if (++tries >= MAX_TRIES) {
            cout << "Too many invalid attempts. Please restart the game." << endl;
            exit(1);
        }
    }
}

// Check if the game is over
bool checkGameOver(char BigBox[9], char smallBoards[9][9]) {
    // Check if the big board has a winner
    char winner = checkWin(BigBox);
    if (winner != EMPTY) {
        cout << "Player " << winner << " wins the game!" << endl;
        return true;
    }
    // Check if the big board is full
    else if (isBigBoardFull(BigBox)) {
        cout << "The game is a draw!" << endl;
        return true;
    } else {
        updateBigBox(BigBox, smallBoards);
        return false;
    }
}

int main() {
    cout << "Welcome to the SUPER TIC TAC TOE" << endl;
    cout << endl;

    char smallBoards[9][9];
    char BigBox[9] = { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY };

    // Initialize the boards
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            smallBoards[i][j] = EMPTY;
        }
    }

    char currentPlayer = PLAYER_X; // Initialize with 'X'
    bool gameOver = false;
    int nextBoard = -1; // Initially, the player can choose any board

    while (!gameOver) {
        display(smallBoards, BigBox);
        cout << "Player " << (currentPlayer == PLAYER_X ? "X" : "O") << "'s turn:" << endl;
        Input(smallBoards, currentPlayer, nextBoard, BigBox);
        updateBigBox(BigBox, smallBoards);
        gameOver = checkGameOver(BigBox, smallBoards);
        if (!gameOver) {
            currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X; // Switch players
            if (nextBoard != -1 && (isBoardFull(smallBoards[nextBoard]) || BigBox[nextBoard] != EMPTY)) {
                nextBoard = -1; // Allow player to choose any board if the target board is full or closed
            }
        }
    }

    return 0;
}
