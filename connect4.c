#include <stdio.h>
#include <stdbool.h>

#define ROWS 6
#define COLS 7
#define WINDOW_LENGTH 4

//Function's prototype declaration
void initBoard(char board[][COLS]);
void drawBoard(char board[][COLS]);
void addMove(int c, bool player, char board[][COLS]);
int minimax(int depth, char board[][COLS], bool maxPlayer, int alpha, int beta);
int window_eval(char window[]);
int static_eval(char board[][COLS]);
char checkWin(char board[][COLS]);
bool is_valid_move(int c, char board[][COLS]);
int max(int x, int y);
int min(int x, int y);
void copy_matrix(char board[][COLS], char child_board[][COLS]);

char ai_best_move; //Global variable that receives the best column for AI player by minimax function

int main()
{	
	char board[ROWS][COLS];
	int column;
	char winner = 0;
	initBoard(board);
	drawBoard(board);
	printf("Connect 4 - AI\n");
	printf("You are playing as 'X', AI is playing as 'O'\n\n");
	while(!winner){
		
		printf("Insert your move [columns from 1 to 7]\n");
		scanf("%d", &column);

		if(is_valid_move(column-1, board)){
			addMove(column-1, false, board);
			minimax(5, board, true, -1000000, 1000000);
			addMove(ai_best_move, true, board);
		}
		else{
			printf("Column selected is invalid, chose another one.\n");
		}
		winner = checkWin(board);
		drawBoard(board);
	}
	printf("The winner is Player %d\n", winner);
	return 0;
}

//Function that initialize the board with '_'
void initBoard(char board[][COLS]){
	for(int r=0;r<ROWS;r++){
		for(int c=0;c<COLS;c++){
			board[r][c]='_';
        }
    }
}

//Function to draw the board, adding '|' separator for a better reading
void drawBoard(char board[][COLS]){
	printf("-----------------------------");
	printf("\n");

	for(int c=0;c<COLS;c++){
		printf("| %d ",c+1);
	}
	printf("|\n");
	printf("-----------------------------");
	printf("\n");
	for(int r=0;r<ROWS;r++){
		for(int c=0;c<COLS;c++){
			printf("| %c ",board[r][c]);
        }
        printf("|\n");
	}
	printf("-----------------------------");
	printf("\n");
}

//Function that add a piece on the board given the column and the player
void addMove(int c, bool player, char board[][COLS]){
	for(int r=ROWS-1;r>=0;r--){
		if(board[r][c]=='_'){
			if(player){
				board[r][c]='O';
				break;
			}
			else{
				board[r][c]='X';
				break;
			}
		}
	}
}

//Check if there is a winner
char checkWin(char board[][COLS]){
	char winner=0; // 0 indicates no winner yet
	//Check vertically
	for(int r=ROWS-1;r>=ROWS-3;r--){
		for(int c=0;c<COLS;c++){
			if(board[r][c]=='X' && board[r-1][c]=='X' && board[r-2][c]=='X' && board[r-3][c]=='X'){
				return 1;
			}
			else if(board[r][c]=='O' && board[r-1][c]=='O' && board[r-2][c]=='O' && board[r-3][c]=='O'){
				return 2;
			}
		}
	}

	//Check horizontally
	for(int r=ROWS-1;r>=0;r--){
		for(int c=0;c<4;c++){
			if(board[r][c]=='X' && board[r][c+1]=='X' && board[r][c+2]=='X' && board[r][c+3]=='X'){
				return 1;
			}
			else if(board[r][c]=='O' && board[r][c+1]=='O' && board[r][c+2]=='O' && board[r][c+3]=='O'){
				return 2;
			}
		}
	}

	//Check positively sloped diagonals
	for(int r=ROWS-1;r>=ROWS-3;r--){
		for(int c=0;c<4;c++){
			if(board[r][c]=='X' && board[r-1][c+1]=='X' && board[r-2][c+2]=='X' && board[r-3][c+3]=='X'){
				return 1;
			}
			else if(board[r][c]=='O' && board[r-1][c+1]=='O' && board[r-2][c+2]=='O' && board[r-3][c+3]=='O'){
				return 2;
			}
		}
	}

	//Check negatively sloped diagonals
	for(int r=ROWS-1;r>=ROWS-3;r--){
		for(int c=3;c<7;c++){
			if(board[r][c]=='X' && board[r-1][c-1]=='X' && board[r-2][c-2]=='X' && board[r-3][c-3]=='X'){
				winner=1;
			}
			else if(board[r][c]=='O' && board[r-1][c-1]=='O' && board[r-2][c-2]=='O' && board[r-3][c-3]=='O'){
				winner=2;
			}
		}
	}
	return winner;
}

//Minimax functioning with alpha beta pruning
int minimax(int depth, char board[][COLS], bool maxPlayer, int alpha, int beta) {
	char winner = checkWin(board);
	if((depth == 0) || (winner!=0)){
		
		if(depth==0){
			return static_eval(board);
			
		}
		else if(winner!=0){
			if(winner==2){
				return(1000000);
			}
			else if(winner==1){
				return(-1000000);
			}
		}
   	}
   	//AI's turn ---> maximize score
   	if(maxPlayer) {
   		int bestValue = -10000;
   		char bestMove = 1; // random init
    	for (int col = 0; col < COLS ; col++){
	      	char child_board[ROWS][COLS];
	      	copy_matrix(board, child_board);
	      	addMove(col, maxPlayer, child_board);
	      
	        int val = minimax(depth - 1, child_board, false, alpha, beta);
	        if(val>bestValue){
	        	bestValue=val;
	        	bestMove=col;
	        }
	        alpha = max(alpha, bestValue);
	        if (beta <= alpha){
	            break;
	        }
      	}
    //Return to the global variable the best column found so far
    ai_best_move=bestMove;
    return bestValue;
    //Player's turn ---> minimize score
 	} else {
		int bestValue = 10000;
		char bestMove = 1; // random init
    	for (int col = 0; col < COLS; col++){
	      	char child_board[ROWS][COLS];
	      	copy_matrix(board, child_board);
	      	addMove(col, maxPlayer, child_board);

	        int val = minimax(depth - 1, child_board, true, alpha, beta);
	        bestValue = min(val, bestValue);
	        beta = min(beta, bestValue);
	        if (beta <= alpha){
	            break;
	        }
        }
      return bestValue;
   }
}

//Evaluate 4 elements at the time
int window_eval(char window[]){
    int score = 0;
    char pieces = 0;
    char opponent_pieces = 0;
    char empty = 0;

    for(int i=0;i<WINDOW_LENGTH;i++){
	    if(window[i] == 'O')
	    	pieces++;
	    else if(window[i] == '_')
	    	empty++;
	    else if(window[i] == 'X')
	    	opponent_pieces++;
	}
	//Score proportional to the number of pieces
	if(pieces==4)
		score+=100;
	else if(pieces==3 && empty==1)
		score+=5;
	else if(pieces==2 && empty==2)
		score+=2;

	else if(opponent_pieces==3 && empty==1)
		score-=4;

    return score;
}

//Heuristic for evaluating the game positions
int static_eval(char board[][COLS]){
    int score = 0;
    int center_pieces = 0;
    // Score center column
    for(int r=0;r<ROWS;r++){
    	if(board[r][COLS/2]=='O'){
    		score+=3;
    	}
    }

    // Score Horizontal
    for(int r=ROWS-1;r>=0;r--){
    	char row_array[COLS];
    	//Extract one row at the time
    	for(int c=0;c<COLS;c++){
    		row_array[c] = board[r][c];
    	}
    	//Compare 4 elements of each row at the time
		for(int c=0;c<4;c++){
			char window[WINDOW_LENGTH];
			for(int t=0; t<WINDOW_LENGTH;t++){
				window[t] = row_array[t+c];
			}
			score += window_eval(window);
		}
	}

	// Score Vertical
    for(int c=0;c<COLS;c++){
    	char col_array[ROWS];
    	//Extract one column at the time
    	for(int r=0;r<ROWS;r++){
    		col_array[r] = board[r][c];
    	}
    	//Compare 4 elements of each column at the time
		for(int r=ROWS-1;r>=3;r--){
			char window[WINDOW_LENGTH];
			for(int t=0; t<WINDOW_LENGTH;t++){
				window[t] = col_array[t+r];
			}
			score += window_eval(window);
		}
	}
    // Score positively sloped diagonals
    for(int r=ROWS-1;r>=3;r--){
    	char diagp_array[WINDOW_LENGTH];
    	//Extract one row at the time
    	for(int c=0;c<4;c++){
    		//Compare 4 elements of each diagonal at the time
    		for(int i=0; i<WINDOW_LENGTH; i++){
    			diagp_array[i] = board[r-i][c+i];
    		}
    		score += window_eval(diagp_array);
    	}
	}
	// Score negatively sloped diagonals
    for(int r=ROWS-1;r>=3;r--){
    	char diagn_array[WINDOW_LENGTH];
    	//Extract one row at the time
    	for(int c=3;c<7;c++){
    		//Compare 4 elements of each diagonal at the time
			for(int i=0; i<WINDOW_LENGTH; i++){
    			diagn_array[i] = board[r-i][c+i];
    		}
    		score += window_eval(diagn_array);
    	}
	}
    return score;
}

//Check if there is any free space in the selected column
bool is_valid_move(int c, char board[][COLS]){
	bool flag=false;
	for(int r=ROWS-1; r>=0; r--){
		if(board[r][c]=='_'){
			flag = true;
			break;
		}
	}
	return flag;
}

// Useful functions
int max(int x, int y){
	if(x>=y){
		return x;
	}else{
		return y;
	}
}

int min(int x, int y){
	if(x<y){
		return x;
	}else{
		return y;
	}
}

void copy_matrix(char board[][COLS], char child_board[][COLS]){
	for(int r=0;r<ROWS;r++){
		for(int c=0;c<COLS;c++){
			child_board[r][c]= board[r][c];
        }
    }
}
