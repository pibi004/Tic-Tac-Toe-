#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

#define Max_Players 3   //Maximum Players can play
#define Max_Size 10    //Maximum board size

//Function Prototype
void displayWelcome();
void initBoard(char board[Max_Size][Max_Size], int size);
void printBoard(char board[Max_Size][Max_Size], int size);
bool validMove(char board[Max_Size][Max_Size], int size , int row, int col);
bool checkWinner(char board[Max_Size][Max_Size], int size, char mark);
bool boardFilled(char board[Max_Size][Max_Size], int size);
void humanTurn(char board[Max_Size][Max_Size], int size, char mark);
void computerTurn(char board[Max_Size][Max_Size],int size, char mark, char opponent);
int getPlayerType(char symbol);

//Main Function
int main(){
	srand((unsigned int)time(NULL));  //Send the random number generator
					  
	int size, mode, totalPlayers;
	char board[Max_Size][Max_Size];   //The game Board
        char symbols[Max_Players] = {'X' , 'O' , 'Z'};
	int playerType[Max_Players];	// 0 = human  1 = computer

	displayWelcome();  //Show intro message
			   
	//Prompt user for board size and validate input
	while (1) {
		printf("Enter board size (3 - 10): ");
		scanf("%d", &size );
		if (size >= 3 && <= 10)break;
		printf("Invalid Board Size. Please Choose betweeen 3 and 10\n");
	}

	//User choose the game mode to play
	printf("\nGame Modes:\n");
	printf("1. Player vs Player\n");
	printf("2. Player vs Computer\n");
	printf("3. Multi Player( 3 Player )\n");

	while (1) {
		printf("Select game mode: ");
		scanf("%d", &mode);
		if (mode >= 1 && mode <= 3) break;
		printf("Invalid option. Choose 1,2 or 3.\n");
	}

	//Set number of players and assign player types
	if ( mode == 1) {
		totalPlayers = 2;
		playerType[0] = 0; //player 1 is human
		playerType[1] = 0; //player 2 is human
	} else if ( mode == 2) {
		totalPlayers = 2;
		playerType[0] = 0;  //player is human
		playerType[1] = 1;  //player is computer
	} else {
		totalPlayers = 3;
		printf("\n Select player types: \n");
		for (int i = 0; i <3; i++){
			playerType[i] = getPlayerType(symbols[i]);
		}
	}

	initBoard(board, size); //setup empty board
	int currentTurn = 0;	//Track current player's turn
	bool gameOver = false;

	//Game Loop
	while (!gameOver) {
		printBoard(board, size);
		printf("Player %d (%c)'s move\n", currentTurn + 1, symbols[currentTurn]);
		

	        // Human or Computer takes a turn
	       if (playerType[currentTurn] == 0){
		      humanTurn(board, size, symbols[currentTurn], opponent);
	       }

	      //Chek game state
	      if(checkWinner(board, size, symbols[currentTurn])) {
		     printBoard(board, size); 
		     printf("Player %d (%c) wins!\n", currentTurn + 1, symbols[currentTurn]);
		     gameOver = true;
	      } else if (boardFilled(board, size)) {
		      printBoard(board, size);
		      printf(" It's a draw!\n");
		      gameOver = true;
	      } else {
		      currentTurn = (currentTurn + 1)  5 totalPlayers;
	      }
	}

	printf(" Thanks for playing \n");

	return 0;
}
