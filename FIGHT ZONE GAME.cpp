#include <iostream>
using namespace std;

const int ROWS = 10;
const int COLS = 10;
char board[ROWS][COLS];

int lives = 3;
int score = 0;
int playerHealth = 3;

// Function to print the game title
void printTitle() {
    cout << "=============================" << endl;
    cout << "        Fight Zone           " << endl;
    cout << "=============================" << endl;
}

// Initialize the game board
void initializeBoard() {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            board[i][j] = '-';

    board[9][5] = 'P';     // Player at bottom center
    board[0][3] = 'E';     // Enemy 1
    board[0][6] = 'E';     // Enemy 2
    board[1][4] = 'E';     // Enemy 3
}

// Print the board
void printBoard() {
    cout << "\n   F I G H T   Z O N E\n" << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

// Move player to the left
void movePlayerLeft() {
    for (int j = 0; j < COLS; j++) {
        if (board[9][j] == 'P') {
            if (j > 0 && board[9][j - 1] == '-') {
                board[9][j - 1] = 'P';
                board[9][j] = '-';
            }
            break;
        }
    }
}

// Move player to the right
void movePlayerRight() {
    for (int j = 0; j < COLS; j++) {
        if (board[9][j] == 'P') {
            if (j < COLS - 1 && board[9][j + 1] == '-') {
                board[9][j + 1] = 'P';
                board[9][j] = '-';
            }
            break;
        }
    }
}

// Fire a bullet
void fire() {
    for (int j = 0; j < COLS; j++) {
        if (board[9][j] == 'P') {
            if (board[8][j] == '-') {
                board[8][j] = '*';
            }
            break;
        }
    }
}

// Move the bullet upward
void moveFire() {
    for (int i = 1; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == '*') {
                if (board[i - 1][j] == 'E') {
                    board[i - 1][j] = '-';  // Enemy hit
                    score += 10;
                } else if (board[i - 1][j] == '-') {
                    board[i - 1][j] = '*';
                }
                board[i][j] = '-';
            }
        }
    }
}

// Move enemies in a direction
void moveEnemy(char object, string direction) {
    char tempBoard[ROWS][COLS];

    // Copy original board
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            tempBoard[i][j] = board[i][j];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (tempBoard[i][j] == object) {
                int newI = i, newJ = j;
                if (direction == "left" && j > 0 && board[i][j - 1] == '-')
                    newJ = j - 1;
                else if (direction == "right" && j < COLS - 1 && board[i][j + 1] == '-')
                    newJ = j + 1;
                else if (direction == "down" && i < ROWS - 1 && board[i + 1][j] == '-')
                    newI = i + 1;

                if (board[newI][newJ] == '-') {
                    board[newI][newJ] = object;
                    board[i][j] = '-';
                }
            }
        }
    }
}

// Main game loop
int main() {
    printTitle(); // Show the title at the beginning
    initializeBoard();
    char command;

    while (true) {
        printBoard();
        cout << "Lives: " << lives << " | Health: " << playerHealth << " | Score: " << score << endl;
        cout << "Command (a=left, d=right, f=fire, m=move bullet, e=enemy move, q=quit): ";
        cin >> command;

        if (command == 'a')
            movePlayerLeft();
        else if (command == 'd')
            movePlayerRight();
        else if (command == 'f')
            fire();
        else if (command == 'm')
            moveFire();
        else if (command == 'e')
            moveEnemy('E', "left"); // You can change direction here
        else if (command == 'q')
            break;

        // Game over check
        if (lives <= 0 || playerHealth <= 0) {
            cout << "\nGame Over!" << endl;
            break;
        }
    }

    return 0;
}

