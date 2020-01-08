#include <stdio.h>
char board[10][10];
char num_rows=6;
char num_cols=7;

void initBoard();
void drawBoard();

void addMove(char c);

int main()
{
	char column=99; //random init to enter the while
	initBoard();
	printf("Connect 4 - AI\n");
	//end game choice=0
	while(column!=0){
		drawBoard();
		printf("Insert your move: [columns from 1 to 7]\n");
		scanf("%d", &column);
		addMove(column);
		//printf("%c\n", column);



	}

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
