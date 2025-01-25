#include <iostream>
#include <limits>

using namespace std;

const int BOARD_SIZE = 3;

struct Player {
    string name;
    char symbol;
};

void displayTable(const char table[BOARD_SIZE][BOARD_SIZE]) {
    cout << "\n";
    for(int i = 0; i < BOARD_SIZE; i++) {
        cout << " ";
        for(int j = 0; j < BOARD_SIZE; j++) {
            cout << table[i][j];
            if(j < BOARD_SIZE - 1) cout << " |";
        }
        cout << "\n";
        if(i < BOARD_SIZE - 1) {
            cout << "-----------\n";
        }
    }
    cout << "\n";
}

bool placeMark(char board[BOARD_SIZE][BOARD_SIZE], int position, char symbol) {
    int row = (position - 1) / BOARD_SIZE;
    int col = (position - 1) % BOARD_SIZE;
    
    if(position < 1 || position > 9 || board[row][col] == 'X' || board[row][col] == 'O') {
        return false;
    }
    
    board[row][col] = symbol;
    return true;
}

bool checkWin(const char board[BOARD_SIZE][BOARD_SIZE], char symbol) {
    // Check rows and columns
    for(int i = 0; i < BOARD_SIZE; i++) {
        if((board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) ||
           (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)) {
            return true;
        }
    }
    
    // Check diagonals
    return (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) ||
           (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol);
}

bool getValidInput(int& input) {
    while(true) {
        cin >> input;
        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number: ";
        } else {
            return true;
        }
    }
}

void initializePlayer(Player& player, int playerNumber) {
    cout << "Enter name for Player " << playerNumber << ": ";
    cin >> player.name;
    
    while(true) {
        cout << "Choose symbol (X/O) for " << player.name << ": ";
        char sym;
        cin >> sym;
        sym = toupper(sym);
        
        if(sym == 'X' || sym == 'O') {
            player.symbol = sym;
            break;
        }
        cout << "Invalid symbol! Please choose X or O.\n";
    }
}

int main() {
    Player players[2];
    bool playAgain = true;
    
    cout << "============== Welcome to Tic Tac Toe! ==============\n";
    
    // Initialize players
    initializePlayer(players[0], 1);
    players[1].symbol = (players[0].symbol == 'X') ? 'O' : 'X';
    cout << "Enter name for Player 2: ";
    cin >> players[1].name;

    while(playAgain) {
        char board[BOARD_SIZE][BOARD_SIZE] = {{'1', '2', '3'}, 
                                             {'4', '5', '6'}, 
                                             {'7', '8', '9'}};
        int moves = 0;
        bool gameWon = false;

        while(moves < 9 && !gameWon) {
            displayTable(board);
            Player& currentPlayer = players[moves % 2];
            
            int position;
            cout << currentPlayer.name << "'s turn (" << currentPlayer.symbol 
                 << "). Enter position (1-9): ";
            
            while(true) {
                if(!getValidInput(position)) continue;
                if(placeMark(board, position, currentPlayer.symbol)) break;
                cout << "Invalid position! Try again: ";
            }

            if(checkWin(board, currentPlayer.symbol)) {
                displayTable(board);
                cout << "Congratulations " << currentPlayer.name 
                     << "! You won!\n";
                gameWon = true;
            }
            moves++;
        }

        if(!gameWon) {
            displayTable(board);
            cout << "It's a draw!\n";
        }

        char choice;
        cout << "Play again? (Y/N): ";
        cin >> choice;
        playAgain = (toupper(choice) == 'Y');
    }

    cout << "Thanks for playing!\n";
    return 0;
}
