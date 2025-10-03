#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define Max_Players 3   //Maximum Players can play

//Function Prototype
void displayWelcome();
void initBoard(char **board, int size);
void printBoard(char **board, int size);
int validMove(char **board, int size , int row, int col);
int checkWinner(char **board, int size, char mark);
int boardFilled(char **board, int size);
void humanTurn(char **board ,int size, char mark);
void computerTurn(char **board,int size, char mark, char opponent);
int getPlayerType(char symbol);

//Main Function
int main(){
	srand((unsigned int)time(NULL));  //Send the random number generator
					  
	int size, mode, totalPlayers;
        char symbols[Max_Players] = {'X' , 'O' , 'Z'};
	int playerType[Max_Players];	// 0 = human  1 = computer

	displayWelcome();  //Show intro message
			   
	//Prompt user for board size and validate input
	while (1) {
		printf("Enter board size (3 - 10): ");
		scanf("%d", &size);
		if (size >= 3 && size <= 10)break;
		printf("Invalid Board Size. Please Choose betweeen 3 and 10\n");
	}

	//Allocate memory dynamically for the board
	char **board = ( char **)malloc(size * sizeof(char *));
	for (int i = 0; i < size; i++){
		board[i] = (char *)malloc(size * sizeof(char));
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
	int gameOver = 0;

	//Game Loop
	while (!gameOver) {
		printBoard(board, size);
		printf("Player %d (%c)'s move\n", currentTurn + 1, symbols[currentTurn]);
		

	        // Human or Computer takes a turn
	       if (playerType[currentTurn] == 0){
		      humanTurn(board, size, symbols[currentTurn]);
	       }else{
		       char opponent = symbols[(currentTurn + 1) % totalPlayers];
		       computerTurn(board, size, symbols[currentTurn], opponent);
	       }

	      //Chek game state
	      if(checkWinner(board, size, symbols[currentTurn])) {
		     printBoard(board, size); 
		     printf("Player %d (%c) wins!\n", currentTurn + 1, symbols[currentTurn]);
		     gameOver = 1;
	      } else if (boardFilled(board, size)) {
		      printBoard(board, size);
		      printf(" It's a draw!\n");
		      gameOver = 1;
	      } else {
		      currentTurn = (currentTurn + 1)  % totalPlayers;
	      }
	}

	//Free allocated memory
	for (int i = 0; i < size; i++){
		free(board[i]);
	}
	free(board);

	return 0;
}

//Function Definition

//Show welcome message
void displayWelcome(){
	printf("..Welcome to Tic-Tac-Toe..\n");
	printf("Rules:\n");
	printf("-2  or 3 players can play.\n");
	printf("-Fill a row, column or a diaganal to win.\n");
	printf("-Board size range 3 to 10\n");
}

//Initialize empty board
void initBoard(char **board, int size){
	for(int i =0; i < size; i++)
		for(int j = 0; j < size; j++)
			board[i][j] = '-';
}

//Print board with grid lines
void printBoard(char **board, int size){
	printf("\n  ");
	for (int c = 0; c < size; c++)printf(" %2d ", c +1); //colum
	printf("\n");

	for (int r = 0 ; r < size; r++){ //row
		printf(" %2d ", r + 1);
		for (int c = 0; c < size; c++){
			printf(" %c ", board[c][r]);
			if( c < size - 1)printf("|");//vertical line
		}
		printf("\n");

		if(r < size -1){
			printf("  ");
			for (int c = 0; c < size; c++){
				printf("---");               //horizontal line
				if ( c < size - 1) printf("+");  //bind the grid
			}
			printf("\n");
		}
	}
	printf("/n");
}

//Validat move
int vallidMove(char **board, int size, int row, int col){
	//Check if row is inside the board
	if(row < 0 || row >= size)
		return 0;
	//Check if column inside the board
	if( col < 0 || col >= size)
		return 0;
	if(board[row][col] != '-')
		return 0;
	return 1;
}

//Check for winner
int checkWinner(char **board, int size, char mark){
	//Check Rows
	for (int r = 0; r < size; r++){
		int ok = 1;
		for(int c = 0; c < size; c++){
			if (board[r][c] != mark){
				ok = 0;
				break;
			}
		}
		if (ok) return 1;
	}

	//Check Colomns
	for (int c = 0; c < size; c++){
		int ok = 1;
		for(int r = 0; r < size; r++){
			if (board[r][c] != mark){
				ok = 0;
			}
		}
		if (ok) return 1;
	}

	//Check main diagnol
	int ok = 1;
	for (int i = 0; i < size; i++){
		if (board[i][i] != mark){
			ok = 0;
			break;
		}
	}
	if (ok) return 1;

	//Check anti diagnol
	ok = 1;
	for ( int i = 0; i < size; i++){
		if (board[i][size -1 -i] != mark){
			ok = 0;
			break;
		}
	}
	if (ok) return 1;

	return 0;
}

//Check if board is full
int boardFilled(char **board, int size){
	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
			if (board[r][c] == '-') return 0;
	return 1;
}

//Human turn
void humanTurn(char **board, int size, char mark){
	int r,c;
	while(1) {
		printf("Enter row and column: ");
		scanf("%d %d", &r, &c);
		r--; c--;   //Adjust to 0-based

		if (validMove(board, size, r, c)){
			board[r][c] = mark;
			break;
		} else {
			printf("Invalid Move, Try Again..\n");
		}
	}
}

//Computer turn
void computerTurn(char **board, int size, char mark, char opponent){
	int r, c;

	// 1.Try to win
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if (validMove(board, size, i, j)){
				board[i][j] = mark;
				if(checkWinner(board, size, mark)){
					printf("Computer plays at (%d,%d) to WIN\n", i + 1, j + 1);
					return;
				}
				board[i][j] = '-';
			}
		}
	}

	//2.Try to block opponent
	for(int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if (validMove(board, size, i , j)) {
				board[i][j] = opponent;
				if (checkWinner(board, size, opponent)) {
					board[i][j] = mark;
					printf("Computer blocks at (%d,%d)\n", i + 1, j +1);
					return;
				}
				board[i][j] = '-';
			}
		}
	}

	// 3.Else Random
	do {
		r = rand() % size;
		c = rand() % size;
	} while(!validMove(board, size, r, c));

	board[r][c] = mark;
	printf("Computer chooses random (%d,%d)\n", r + 1, c + 1);
}

//Ask player type
int getPlayerType(char symbol){
	int type;
	while(1){
		printf("Player %c - 0 = Human, 1 = Computer): ", symbol);
		scanf("%d", &type);
		if (type == 0 || type == 1) return type;
		printf("Invalid..! Enter 0 or 1.\n");
	}
}




