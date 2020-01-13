#include <stdio.h>
#include <stdbool.h>


#define ROWS 6
#define COLS 7

char board[ROWS][COLS];

void initBoard();
void drawBoard();

void addMove(char c, char player);
int minimax(int depth, char child_board[][COLS], bool maxPlayer, int alpha, int beta);
int static_eval(char child_board[][COLS]);

void addAIMove(char c, char child_board[][COLS], bool maxPlayer);
char checkWin();

int main()
{
	char column;
	char end = 0;
	bool maxPlayer=true;
	initBoard();
	printf("Connect 4 - AI\n");
	while(!end){
		
		printf("Insert your move: [columns from 1 to 7]\n");
		scanf("%d", &column);
		addMove(column);
		addAIMove();
		end = checkWin();
		drawBoard();

	}

	printf("The winner is Player %d\n", end);
	return 0;
}

void initBoard(){
	for(int r=0;r<ROWS;r++){
		for(int c=0;c<COLS;c++){
			board[r][c]='_';
        }
    }
}

void drawBoard(){

	for(int r=0;r<ROWS;r++){
		for(int c=0;c<COLS;c++){
			printf("| %c ",board[r][c]);
        }
        printf("|\n");
	}
	printf("\n");
}

void addMove(char c, char player){
	for(int r=ROWS-1;r>=0;r--){
		if(board[r][c-1]=='_'){
			if(player==1){
				board[r][c-1]='X';
				break;
			}
			else{
				board[r][c-1]='O';
				break;
			}
		}
	}
}

char checkWin(){
	char winner=0; // 0 indicates no winner yet
	//check vertically
	for(int r=ROWS-1;r>=ROWS-3;r--){
		for(int c=0;c<COLS;c++){
			if(board[r][c]=='X' && board[r-1][c]=='X' && board[r-2][c]=='X' && board[r-3][c]=='X'){
				printf("wins vertically!\n");
				winner=1;
			}
			else if(board[r][c]=='O' && board[r-1][c]=='O' && board[r-2][c]=='O' && board[r-3][c]=='O'){
				printf("wins vertically!\n");
				winner=2;
			}
		}
	}

	//check horizontally
	for(int r=ROWS-1;r>=0;r--){
		for(int c=0;c<4;c++){
			if(board[r][c]=='X' && board[r][c+1]=='X' && board[r][c+2]=='X' && board[r][c+3]=='X'){
				printf("wins horizontally!\n");
				winner=1;
			}
			else if(board[r][c]=='O' && board[r][c+1]=='O' && board[r][c+2]=='O' && board[r][c+3]=='O'){
				printf("wins horizontally!\n");
				winner=2;
			}
		}
	}

	//check diagonals 1
	for(int r=ROWS-1;r>=ROWS-3;r--){
		for(int c=0;c<4;c++){
			if(board[r][c]=='X' && board[r-1][c+1]=='X' && board[r-2][c+2]=='X' && board[r-3][c+3]=='X'){
				printf("wins right diagonal!\n");
				winner=1;
			}
			else if(board[r][c]=='O' && board[r-1][c+1]=='O' && board[r-2][c+2]=='O' && board[r-3][c+3]=='O'){
				printf("wins right diagonal!\n");
				winner=2;
			}
		}
	}

	//check diagonals 2
	for(int r=ROWS-1;r>=ROWS-3;r--){
		for(int c=3;c<7;c++){
			if(board[r][c]=='X' && board[r-1][c-1]=='X' && board[r-2][c-2]=='X' && board[r-3][c-3]=='X'){
				printf("wins left diagonal!\n");
				winner=1;
			}
			else if(board[r][c]=='O' && board[r-1][c-1]=='O' && board[r-2][c-2]=='O' && board[r-3][c-3]=='O'){
				printf("wins left diagonal!\n");
				winner=2;
			}
		}
	}

	return winner;
}

void addAIMove(char c, char child_board[][COLS], bool maxPlayer){
	for(int r=ROWS-1;r>=0;r--){
		if(child_board[r][c-1]=='_'){
			if(maxPlayer){
			child_board[r][c-1]='O';
			break;
			}
			else{
				child_board[r][c-1]='X';
				break;
			}
		}
	}
}

//Minimax functioning with alpha beta pruning
int minimax(int depth, char child_board[][COLS], bool maxPlayer, int alpha, int beta) {

	if (depth == 3) {
		return static_eval(child_board);
   	}

   	if (maxPlayer) {
   		int bestValue = -10000;
    	for (int col = 0; col < COLS ; col++) {
    		//TODO try to implement malloc to dinamycally allocate child tmp matrix
	      	char child_board[ROWS][COLS];
	      	memcpy(&child_board, &board,ROWS*COLS*sizeof(char));
	      	addAIMove(col, child_board, maxPlayer);

	        int val = minimax(depth + 1, child_board, false, alpha, beta);
	        bestValue = max(bestValue, val);
	        alpha = max(alpha, bestValue);
	        if (beta <= alpha)
	            break;
      	}
    return bestValue;

 	} else {
		int bestValue = 10000;
    	for (int col = 0; col < COLS; col++) {

    		//TODO try to implement malloc to dinamycally allocate the child matrix
	      	char child_board[ROWS][COLS];
	      	memcpy(&child_board, &board,ROWS*COLS*sizeof(char));
	      	addAIMove(col, child_board, maxPlayer);

	        int val = minimax(depth + 1, child_board, true, alpha, beta);
	        bestValue = min(bestValue, val);
	        beta = min(beta, bestValue);
	        if (beta <= alpha)
	            break;
        }
      return bestValue;
   }
}

//Heuristic to evaluate the game positions
int static_eval(char child_board[][COLS]){
	int score=0;
	//check vertically
	for(int c=0;c<COLS;c++){
		for(int r=ROWS-1;r>=ROWS-3;r--){
			if(child_board[r][c]=='X' && board[r-1][c]=='X' && board[r-2][c]=='X' && board[r-3][c]=='_'){
				score-=100;
			}
			else if(board[r][c]=='O' && board[r-1][c]=='O' && board[r-2][c]=='O' && board[r-3][c]=='_'){
				printf("wins vertically!\n");
				score+=100;
			}
		}
	}

	//check horizontally
	for(int r=ROWS-1;r>=0;r--){
		for(int c=0;c<4;c++){
			if(board[r][c]=='X' && board[r][c+1]=='X' && board[r][c+2]=='X' && board[r][c+3]=='_'){
				score+=100;
			}
			else if(board[r][c]=='O' && board[r][c+1]=='O' && board[r][c+2]=='O' && board[r][c+3]=='_'){
				score-=100;
			}
		}
	}
return score;
}