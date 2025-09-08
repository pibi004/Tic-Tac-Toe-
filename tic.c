#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

//structure to hold the game information
typedf struct{
	char** board;           //2D array for the game board
	int size;               //Board size
	int current_player;     //current player( 0, 1, 2)
	int number_of_players;  //number of players(2 or 3)
	char symbols[3];        //player symbols( X, Y, Z)
	int player_types[3];    //0 or 1
	FILE* log_file;         //Pointer for logging file
}
GameState;

//Function to initialize the game
GameState* initialize_game(int size, int number_of_players){
	GameState* game = malloc(sizeof(GameState));
	if (!game){
		printf("Memory allocation failes\n");
		return NULL;
	}

	//Allocate memory for the board
	game->board = malloc(size * sizeof(char*));
	if (!game->board){
		printf("Memory allocation failed\n");
		free(game); //if program cannot continue it cleans up the memory
	        return NULL;
	}

	for (int i = 0; i < size; i++){
		game->board[i] = malloc(size * sizeof(char));
		if(!game->board[i]){
			printf("Memory allocation failed\n");
			//Free previous allocated memory
			for (int j = 0;j <i;j++){
				free(game->board);
			}
			free(game->board);
			free(game);
			return NULL;
		}

		//Initialize board space with spaces
		for(int j = 0; j < size ; j++){
			game->board[i][j] = ' ';
		}
	}

	game->size = size;
	game->current_player = 0;
	game->number_of_players = number_of_players;

	//Give player symbols
	game->symbols[0] = 'X';
	game->symbols[1] = 'O';
	game->symbols[2] = 'Z';

	//Open logging files
	game->log_file = fopen("game_log.txt", "w");
	if(!game->log_file){
		printf("Error\n");
	}else {
		fprintf(game->log_file, "Tic-Tac-Toe"\n);
		fprintf(game->log_file, "Board Size: %d x %d\n", size, size);
		fprintf(game->log_file, "Number Of Players: %d\n", number_of_players);
	}
	return game;
}

