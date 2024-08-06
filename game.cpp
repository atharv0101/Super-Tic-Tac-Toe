#include <iostream>
using namespace std;

void display(char A[10], char B[10], char C[10], char D[10], char E[10], char F[10], char G[10], char H[10], char I[10]) {
    for (int i = 0; i < 9; i += 3) {
        cout << A[i] << " |" << A[i + 1] << " |" << A[i + 2] << " ||" << B[i] << " |" << B[i + 1] << " |" << B[i + 2] << " ||" << C[i] << " |" << C[i + 1] << " |" << C[i + 2] << endl;
        cout << "--------||--------||--------" << endl;
    }
    cout<<"--------||--------||--------" <<endl;
    for (int i = 0; i < 9; i += 3) {
        cout << D[i] << " |" << D[i + 1] << " |" << D[i + 2] << " ||" << E[i] << " |" << E[i + 1] << " |" << E[i + 2] << " ||" << F[i] << " |" << F[i + 1] << " |" << F[i + 2] << endl;
        cout << "--------||--------||--------" << endl;
    }
    cout<<"--------||--------||--------" <<endl;
    for (int i = 0; i < 9; i += 3) {
        cout << G[i] << " |" << G[i + 1] << " |" << G[i + 2] << " ||" << H[i] << " |" << H[i + 1] << " |" << H[i + 2] << " ||" << I[i] << " |" << I[i + 1] << " |" << I[i + 2] << endl;
        if(i<=5){
            cout << "--------||--------||--------" << endl;
        }
    }
}

char checkWin(char board[10]) {
    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; i++) {
        if (board[i] != ' ' && board[i] == board[i + 3] && board[i + 3] == board[i + 6]) {
            return board[i]; // column win
        }
        if (board[i * 3] != ' ' && board[i * 3] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2]) {
            return board[i * 3]; // Row win
        }
    }
    if (board[4] != ' ' && board[0] == board[4] && board[4] == board[8]) {
        return board[4]; // Diagonal win
    }
    if (board[4] != ' ' && board[2] == board[4] && board[4] == board[6]) {
        return board[4]; // Diagonal win
    }
    return 'c'; // 'c' represents the game is ongoing
}

char CheckSmallBoardWin(char board[]) {
    return checkWin(board);
}

void CheckBigBoardWin(char BigBox[9]) {
    char winner = checkWin(BigBox);
    if (winner == 'X'){
        cout<<"Player X wins";
    }
    else if (winner == 'O'){
        cout<<"Player O wins";
    }
    else{
        cout<<"Continue the game"<<endl;
    }
}

void Input(char A[10], char B[10], char C[10], char D[10], char E[10], char F[10], char G[10], char H[10], char I[10], char player) {
    int box;
    int place;
    cout << "Select the Box:";
    cin >> box;
    cout << "Select the Place:";
    cin >> place;

    // Fix the switch cases to correctly set the values in the corresponding board.
    char* currentBoard;
    switch (box) {
    case 1:
        currentBoard = A;
        break;
    case 2:
        currentBoard = B;
        break;
    case 3:
        currentBoard = C;
        break;
    case 4:
        currentBoard = D;
        break;
    case 5:
        currentBoard = E;
        break;
    case 6:
        currentBoard = F;
        break;
    case 7:
        currentBoard = G;
        break;
    case 8:
        currentBoard = H;
        break;
    case 9:
        currentBoard = I;
        break;
    default:
        cout << "Invalid Entry. Enter Value between 1 to 9" << endl;
        return;
    }

    // Check if the place is already occupied
    if (currentBoard[place - 1] == ' ') {
        currentBoard[place - 1] = player;
    }
    else {
        cout << "Place is already occupied!" << endl;
        return;
    }
}

int main() {
    cout<<"Welcome to the SUPER TIC TAC TOE"<<endl;
    cout<<endl;
    char A[10], B[10], C[10], D[10], E[10], F[10], G[10], H[10], I[10];

    // Initialize the boards...
    for (int i = 0; i < 10; i++) {
        A[i] = ' ';
        B[i] = ' ';
        C[i] = ' ';
        D[i] = ' ';
        E[i] = ' ';
        F[i] = ' ';
        G[i] = ' ';
        H[i] = ' ';
        I[i] = ' ';
    }

    display(A, B, C, D, E, F, G, H, I);

    char currentPlayer = 'X'; // Initialize with 'X'

    while (true) {
        cout << "Player " << currentPlayer << "'s turn:" << endl;
        Input(A, B, C, D, E, F, G, H, I, currentPlayer);
        display(A, B, C, D, E, F, G, H, I);
        char result = CheckSmallBoardWin(A);

        if (result == 'X' || result == 'O') {
            cout << "Player " << result << " wins!" << endl;
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}