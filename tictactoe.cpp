#include <bits/stdc++.h>

using namespace std;

// Global variables

// Board to play game on
int BOARD[3][3] =
{
    { 5, 5, 5 },
    { 5, 5, 5 },
    { 5, 5, 5 }
};

bool MARKED[3][3] =
{
    { false, false, false },
    { false, false, false },
    { false, false, false }
};

// Labels for players
int computerLabel, playerLabel;

// Whose turn is it
// 0 = Computer
// 1 = Player
int moveTurn;

// Game conditions
//  0 = Running
//  1 = Win
// -1 = Draw
int GAME;

// Functions
void gameBegin();
bool checkIfAlreadyMarked(int , int);
void firstMove();
void nextMove();
bool checkWin(int[3][3], int);
void showBoard(int[3][3]);
void copyBoard(int[3][3], int[3][3]);
void gameEnd();

// Begins game by assigning global variables
void gameBegin()
{
    system("cls");

    // Game initialized
    GAME = 0;

    // Ask player for symbols
    cout<<"Do you want X or O?\n0 = \'O\'\n1 = \'X\'\nPlease enter 0 or 1: ";
    cin>>playerLabel;
    if(playerLabel == 0)
        computerLabel = 1;
    else if(playerLabel == 1)
        computerLabel = 0;
    else
    {
        cout<<"That wasn't an option! Bye Bye!";
        exit(1);
    }
    // Randomly decide who moves first
    int whoMoves = rand() % 2; // Gives either 0 or 1
    if(whoMoves == 0)
    {
        moveTurn = 0; // Computer moves first
        cout<<"First move: computer!\n";
    }
    else
    {
        moveTurn = 1; // Player moves first
        cout<<"First move: player!\n";
    }
    // Call first move to get first move of the computer or player
    firstMove();
    showBoard(BOARD);

    // Call next move to run next eight moves
    for (int i=0;i<=8;i++)
    {
        nextMove();
        showBoard(BOARD);
        if ( i==8 )
        {
            cout<<"\n\n\nIts a draw";
            getchar();
            exit(0);
        }
    }
}

void showBoard(int BOARD[3][3])
{
    cout<<endl;
    cout<<"\t    0  |  1  |  2  "<<endl;
    cout<<"\t==================="<<endl;
    cout<<"\t||     |     |     "<<endl;
	cout<<"0\t||  "<< BOARD[0][0]<<"  |  "<<BOARD[0][1]<<"  |  "<<BOARD[0][2]<<endl;
	cout<<"\t||_____|_____|_____"<<endl;
	cout<<"\t||     |     |     "<<endl;
	cout<<"1\t||  "<< BOARD[1][0]<<"  |  "<<BOARD[1][1]<<"  |  "<<BOARD[1][2]<<endl;
	cout<<"\t||_____|_____|_____"<< endl;
	cout<<"\t||     |     |     "<< endl;
	cout<<"2\t||  "<< BOARD[2][0]<<"  |  "<<BOARD[2][1]<<"  |  "<<BOARD[2][2]<<endl;
	cout<<"\t||     |     |     "<<endl<<endl;
}

// Function to check if position (x,y) is marked on the board.
bool checkIfAlreadyMarked(int x, int y)
{
    if(MARKED[x][y] == true)
        return true;
    else
        return false;
}

// First Move to move on the board.
void firstMove()
{
    showBoard(BOARD);
    int posX, posY;

    // If Computer has to move first
    if (moveTurn == 0)
    {
        posX = rand() % 3;
        posY = rand() % 3;
        BOARD[posX][posY] = computerLabel;
        MARKED[posX][posY] = true;
        moveTurn = 1;
    }
    else
    {
        cout<<"Enter the i-coordinate(0-2): ";
        cin>>posX;
        cout<<"\nEnter the j-coordinate(0-2): ";
        cin>>posY;
        BOARD[posX][posY] = playerLabel;
        MARKED[posX][posY] = true;
        moveTurn = 0;
    }
}

void nextMove()
{
    int posX, posY;
    if (moveTurn == 1) // Player Moves
    {
        cout<<"\n\n--------------------------------\n";
        cout<<moveTurn;
        cout<<"\n\n--------------------------------\n";
        // Ask player for input
        cout<<"Enter the i-coordinate(0-2): ";
        cin>>posX;
        cout<<"\nEnter the j-coordinate(0-2): ";
        cin>>posY;
        BOARD[posX][posY] = playerLabel;
        MARKED[posX][posY] = true;
        moveTurn = 0;
        if (checkWin(BOARD, playerLabel))
        {
            cout<<"Player has moved and won!";
            gameEnd();
        }
    }
    else // Computer moves
    {
        cout<<"\n\n--------------------------------\n";
        cout<<moveTurn;
        cout<<"\n\n--------------------------------\n";
        bool moved = false;
        // ATTACK THE PLAYER
        // Check if it can win in the next move.
        // Find all the blank spaces then check if filling any of them
        // makes the computer win
        for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
            {
                if (!checkIfAlreadyMarked(i, j))
                {
                    int BOARD_COPY[3][3];
                    // Create a new copy of the array
                    copyBoard(BOARD, BOARD_COPY);
                    // Place the computer label
                    BOARD_COPY[i][j] = computerLabel;
                    // Check if it can win
                    if(checkWin(BOARD_COPY, computerLabel))
                    {
                        posX = i;
                        posY = j;
                        BOARD[posX][posY] = computerLabel;
                        //MARKED[posX][posY] = true;
                        //moved = true;
                        moveTurn = 1;
                        gameEnd();
                    }
                }
            }
        // DEFENSE
        // Stop the player from winning
        // Find all the blank spaces then check if by filling any spaces with
        // player's label allows the player to win or not. If yes, place the computer label at that position
        // Else place at most suitable position.
        for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
            {
                if (!checkIfAlreadyMarked(i, j))
                {
                    int BOARD_COPY[3][3];
                    // Create a new copy of the array
                    copyBoard(BOARD, BOARD_COPY);
                    // Place the player's label
                    BOARD_COPY[i][j] = playerLabel;
                    if(checkWin(BOARD_COPY, playerLabel))
                    {
                        posX = i;
                        posY = j;
                        BOARD[posX][posY] = computerLabel;
                        MARKED[posX][posY] = true;
                        moved = true;
                    }
                }
            }
        // Otherwise randomly place the the computer move anywhere
        // where there is free space.
        if (moved == false)
        {
            for (int i=0;i<8;i++)
            {
                posX = rand() % 3;
                posY = rand() % 3;
                if (!checkIfAlreadyMarked(posX, posY))
                {
                    BOARD[posX][posY] = computerLabel;
                    MARKED[posX][posY] = true;
                    moved = true;
                    break;
                }
            }
        }
        moveTurn = 1;
    }

}

void copyBoard(int src[3][3], int dest[3][3])
{
    for (int i=0;i<3;i++)
        for (int j=0;j<3;j++)
            dest[i][j] = src[i][j];
}

bool checkWin(int tempBoard[3][3], int label)
{
    // Check horizontal win
    for(int i=0; i<2; i++)
        if(tempBoard[i][0] == tempBoard[i][1] && tempBoard[i][1] == tempBoard[i][2] && tempBoard[i][0] == label)
            return true;

    // Check vertical win
    for(int j=0; j<2; j++)
        if(tempBoard[0][j] == tempBoard[1][j] && tempBoard[1][j] == tempBoard[2][j] && tempBoard[0][j] == label)
            return true;

    // Check diagonal win
    if(tempBoard[0][0] == tempBoard[1][1] && tempBoard[1][1] == tempBoard[2][2] && tempBoard[1][1] == label)
        return true;

    if(tempBoard[0][2] == tempBoard[1][1] && tempBoard[1][1] == tempBoard[2][0] && tempBoard[1][1] == label)
        return true;

    return false;
}

void gameEnd()
{
    cout<<"thank you! the game has ended!";
    cout<<"\n"<<moveTurn;
    if (moveTurn == 0)
         cout<<"\n\nPlayer has won the game!";
    else
        cout<<"\n\nComputer has won the game!";
    cout<<"\n\n=======================================\n";
    showBoard(BOARD);
    cout<<"\n\n=======================================\n";
    getchar();
    exit(0);
}


int main()
{
    srand(time(0)); // Flushes randoms time generation
    cout<<"Welcome to Tic Tac Toe! \n\nPress any key to continue";
    getchar();
    gameBegin();
    cout<<"Compilation Successful!";
    return 0;
}
