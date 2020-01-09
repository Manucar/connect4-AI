#include <stdio.h>
char board[10][10];
char num_rows=6;
char num_cols=7;

void initBoard();
void drawBoard();

void addMove(char c);
void addAIMove();
char checkWin();

int main()
{
	char column;
	char end = 0;
	initBoard();
	printf("Connect 4 - AI\n");
	//end game choice=0
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
	for(int r=0;r<num_rows;r++){
		for(int c=0;c<num_cols;c++){
			board[r][c]='_';
        }
    }
}

void drawBoard(){

	for(int r=0;r<num_rows;r++){
		for(int c=0;c<num_cols;c++){
			printf("| %c ",board[r][c]);
        }
        printf("|\n");
	}
	printf("\n");
}

void addMove(char c){
	for(int r=num_rows-1;r>=0;r--){
		if(board[r][c-1]=='_'){
			board[r][c-1]='X';
			break;
		}
	}
}

char checkWin(){
	char winner=0; // 0 indicates no winner yet
	//check vertically
	for(int r=num_rows-1;r>=num_rows-3;r--){
		for(int c=0;c<num_cols;c++){
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
	for(int r=num_rows-1;r>=0;r--){
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
	for(int r=num_rows-1;r>=num_rows-3;r--){
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
	for(int r=num_rows-1;r>=num_rows-3;r--){
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

void addAIMove(){

}
