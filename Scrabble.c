/*	This is to certify that this project is my/our own work, based on my/our personal efforts in studying and applying
the concepts learned. We have constructed the functions and their respective algorithms and corresponding codes
either individually or with my group mate. The program was run, tested, and debugged by my/our own efforts. I/We
further certify that I/we have not copied in part or whole or otherwise plagiarized the work of other students/groups
and/or persons.

	Arczen Angelo Gulla Baluyot					Lester Paolo Diaz
	DLSU ID 12126861						DLSU ID 12128570 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LETTERS 7

/*

Description: A Scrabble-influenced game
Programmed by: Arczen Baluyot and Paolo Diaz S-14
Last modified: 12/5/22
Version: 1.15
[Acknowledgements: NA ]

*/

typedef char Str9[10];


struct Player{
	char name[50];
	int score;
	Str9 longestWord;
	int highscore;
	int numGames;
	float averageScore;
	int letterNum;
	int vowelNum;
    char letters[MAX_LETTERS];
}player[4];

/*
This function displays the options
@param num is the number of which the player chooses.
@return the num.
*/

int options(int num){
	
	printf("===============================\n");
	printf("	  1. Play\n");
	printf("	  2. Instructions\n");
	printf("	  3. Quit\n");
	printf("===============================\n");
	printf("Choose an option: ");
	scanf("%d", &num);

	return num;
}

/*
This function initializes the Scrabble Board
Precondition: The Board is 11x11
*/
void initBoard(char B[11][11]){
	
	int i, j;
	for(i=0; i<11; i++){
		for(j=0; j<11; j++){
			B[i][j]= ' ';

		}
	}
}

/*
This function prints the Scrabble Board
Precondition: The Board is 11x11
@param B[11][11] is the dimension of the board
*/
void printBoard(char B[11][11]){
	int i,j;
	int k = 1;

	printf("	  1	  2	  3	  4	  5	  6	  7	  8	  9	  10	  11 \n"); // print the column number
    printf("   	_________________________________________________________________________________________");
    for(i = 0; i < 11; i++)
    {
        printf("\n");
        printf("   %d  	|", k);
        for(j = 0; j < 11; j++)
        {
            printf("%c	|", B[i][j]);
        }
        k++;
        printf("\n");
        printf("	|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|");

    }
    printf("\n");
    printf("\n");
}

/*
This function asks how many players will play
Precondition: Game can only be played by 2-4 players.
@param num is the number of players going to play

*/
void NumPlayers(int *num){

	int condition = 1;

	while(condition == 1) {

		printf("How many players would like to play? ");
		scanf("%d", num);

		if(*num < 2){
			printf("Minimum number of players are 2\n");
		}
		else if(*num > 4){
			printf("Maximum number of players are 4\n");
		}
		else
			condition--;
	}

}

/*
This function records data of the players
@param num is the number of players going to play
*/
void Players(int num){

	FILE *fp;
	struct Player temp;
	int i = 0, j;
	int valid = 0;

	do {
		printf("Player %d Name: ", ++i);
		scanf("%s", player[--i].name);

		// check if unique name
		if(i > 0) {
			for(j = 0; j < i; j++) {
				if(strcmp(player[i].name, player[j].name) != 0) {
					valid = 0;
				}
			}
		}

		if(valid == 0) {
			
			fp = fopen("SaveFile.txt", "r");
			
			while(fscanf(fp, "%s%s%d%d%f", temp.name, temp.longestWord, &temp.highscore, &temp.numGames, &temp.averageScore) == 5) {
				
				if(strcmp(temp.name, player[i].name) == 0) { // returning player
				
					strcpy(player[i].longestWord, temp.longestWord);
					player[i].highscore = temp.highscore;
					player[i].numGames = temp.numGames;
					player[i].averageScore = temp.averageScore;
					printf("Welcome back %s!\n", player[i].name);
					
				}
				else { // new player
				
					strcpy(player[i].longestWord, " ");
					strcat(player[i].longestWord, "\0");
					player[i].highscore = 0;
					player[i].numGames = 0;
					player[i].averageScore = 0;
					printf("Welcome new player!\n");
				}
			}
			i++;
			valid = 1;
			fclose(fp);
		}

	} while(i < num);


	printf("\nPLAYERS\n");

	for(i=0;i<num;i++)
    {
        printf("%s\n", player[i].name);
    }
}

/*
This function initializes Uppercase Letters
@param word is the word inputted by the player
*/
void uppercase(Str9 word){
	int i;

	for(i = 0; i < strlen(word); i++){
		if(word[i] >= 97 &&word[i] <= 122)
			word[i] -= 32;
	}
}

/*
This function randomizes the letters
@param num is the number of players
@param letterQuantity is the number of letters
*/
void checkLetter(int num, int letterQuantity[27]) {
    int i;
	int number, index;
    int lower = 65, upper = 90;
    srand(time(NULL));


	for(i = 0; i < num; i++) {

		while(player[i].letterNum < 7) {
			if(player[i].vowelNum < 2) {
				number = (rand() % (upper - lower + 1)) + lower;
				if(number == 'A' || number == 'E' || number == 'I' || number == 'O' || number == 'U') {
					index = number-65;
					if(letterQuantity[index] > 0) {
						player[i].letters[player[i].letterNum] = number;
						player[i].letterNum++;
						letterQuantity[index]--;
						player[i].vowelNum++;
					}
				}
			}
			else {
				number = (rand() % (upper - lower + 1)) + lower;
				if(number != 'A' && number != 'E' && number != 'I' && number != 'O' && number != 'U') {
					index = number-65;
					if(letterQuantity[index] > 0) {
						player[i].letters[player[i].letterNum] = number;
						player[i].letterNum++;
						letterQuantity[index]--;
					}
				}
			}
		}
	}
}

/*
This function checks the word if its valid from the randomized letter
@param word the inputted word the player
@param turn determines whose turn is it
@return 0 if count is equal to the length of word
@return 1 if otherwise
*/
int checkWord(Str9 word, int turn) {
    int i, j;
    int count = 0;
    char temp[MAX_LETTERS];


    strcpy(temp, player[turn].letters);
    for(i = 0; i < strlen(word); i++) {
        for(j = 0; j < strlen(temp); j++) {
            if(word[i] == temp[j]) {
                temp[j] = ' ';
                count++;
                break;
            }
        }
    }

    if(count == (int)strlen(word))
        return 0;

    return 1;
}

/*
This function checks the word if its valid
@param word the inputted word the player
@param turn determines whose turn is it
@return 0 if count is equal to the length of word
@return 1 if otherwise
*/
void fixTile(Str9 word, int turn) {
    int i, j, count = 0;

    for(i = 0; i < strlen(word); i++) { //remove letters
        for(j = 0; j < strlen(player[turn].letters); j++) {
            if(word[i] == player[turn].letters[j]) {
				if(player[turn].letters[j] == 'A' || player[turn].letters[j] == 'E' ||
				   player[turn].letters[j] == 'I' || player[turn].letters[j] == 'O' || player[turn].letters[j] == 'U') {
					player[turn].vowelNum--;
				}
                player[turn].letters[j] = ' ';
                player[turn].letterNum--;
            }
        }
    }

    for(i = 0; player[turn].letters[i] != '\0'; i++) {
        if(player[turn].letters[i] == ' ') {
            count++;
        }
        else if(player[turn].letters[i] != ' ') {
            if(i != 0) { // not first index
                if(count > 0) { // there are spaces before this letter
                    player[turn].letters[i-count] = player[turn].letters[i];
                    player[turn].letters[i] = ' ';
                }
            }
        }
    }
}

/*
This function assigns value to the letters
@param word the inputted word the player
@return total
*/
int pointsystem(Str9 word){
	int i = 0;
	int total = 0;
	char letter;

	for(i = 0; i < strlen(word); i++){

		letter = word[i];

		if(letter == 'A' || letter == 'E' || letter == 'I' || letter == 'L' || letter == 'N'
		|| letter == 'O' || letter == 'R' || letter == 'S' || letter == 'T' || letter == 'U')
			total += 1;
		else if(letter == 'D' || letter == 'G')
			total += 2;
		else if(letter == 'B' || letter == 'C' || letter == 'M' || letter == 'P')
			total += 3;
		else if(letter == 'D' || letter == 'H' || letter == 'V' || letter == 'W' || letter == 'Y')
			total += 4;
		else if(letter == 'K')
			total += 5;
		else if(letter == 'J' || letter == 'X')
			total += 8;
		else if(letter == 'Q' || letter == 'Z')
			total += 10;
	}

	return total;
}

/*
This function assigns value to the letters
@param word the inputted word the player
@return total
*/
int wordcheck(Str9 word){
	FILE *fp;
	Str9 file;
	fp = fopen("Dictionary-MP.txt", "r");
	int j = 0;

	while(fscanf(fp, "%s", file) == 1) {
		if(strcmp(file, word) == 0) {
			j = 1;
		}
	}

	return j;
}

/*
This function prints the word vertically on the board
@param word
@param board[11][11]
@param row
@param column
*/
void vert(char board[11][11], Str9 word, int row, int column){

	int i;

	for(i=0; i<strlen(word); i++){
		board[row][column] = word[i];
		row++;
		}
	}


/*
This function prints the word horizontally on the board
@param word
@param board[11][11]
@param row
@param column
*/
void horz(char board[11][11], Str9 word, int row, int column){

	int i;
	for(i=0; i<strlen(word); i++){
		board[row][column] = word[i];
		column++;
		}
	}

/*
This function prints the scores of the players
@param num
*/
void scorecheck(int num){

	int i;
	printf("========================== POINTS =========================\n");
	for(i=0; i<num; i++){
		printf("%s has %d points\n", player[i].name, player[i].score);
	}

}

/*
This function validates if the word can be printed on the board
@param row
@param column
@param L
@param across
@param word
@param board[11][11]
@param tcondition
@return 0
*/
int checkBoard(int row, int column, int L, int across, Str9 word, char board[11][11], int tcondition){

	int i;
	int val, count1 = 0, count2 = 0;

	// check sufficient space
	// - for vertical
	if(across == 1) {
		val = 11 - row;
		if(strlen(word) <= val) {
			if(tcondition == 0)
				return 0;
			else {
				for(i = row; i < 11; i++) {
					if(board[i][column] != ' ')
						count1++;
				}

				if(count1 > 0) { // 
					for(i = row; i < 11; i++) {
						if(board[i][column] != ' ') { 
							if(board[i][column] == word[i - row]) { 
								count2++;
							}
						}
					}
					if(count2 == 0) {
						printf("Invalid Word Placement\n");
						return 1;
					}
					else
						return 0;
				}
				else {
					printf("Invalid Word Placement\n");
					return 1;
				}
			}
		}
		else {
			printf("Insufficient Space for Word \n");
			return 1;
		}
	}
	// - for horizontal
	if(across == 2) {
		val = 11 - column;
		if(strlen(word) <= val) {
			if(tcondition == 0)
				return 0;
			else {
				for(i = column; i < 11; i++) {
					if(board[row][i] != ' ')
						count1++;
				}

				if(count1 > 0) { 
					for(i = column; i < 11; i++) {
						if(board[row][i] != ' ') { 
							if(board[row][i] == word[i - column]) { 
								count2++;
							}
						}
					}
					if(count2 == 0){
						printf("Invalid Word Placement\n");
						return 1;
					}
					else
						return 0;
				}
				else {
					printf("Invalid Word Placement\n");
					return 1;
				}
			}
		}
		else {
			printf("Insufficient Space for Word \n");
			return 1;
		}
	}


	return 0;
}
/*
This function updates the player data
@param turn
@param word
*/
void updatePlayerData(int turn, Str9 word) {
	// update longest word
	if(strlen(player[turn].longestWord) < strlen(word)) {
		strcpy(player[turn].longestWord, word);
	}
	// update highscore
	if(player[turn].highscore < player[turn].score) {
		player[turn].highscore = player[turn].score;
	}
}
/*
This function saves the data of the players
@param num
*/
void saveFile(int num) {
	FILE *fp;
	int i;
	struct Player temp;

	for(i = 0; i < num; i++) {
		if(player[i].numGames == 1) { // new player
			fp = fopen("SaveFile.txt", "a");
			fprintf(fp, "\n%s\t%s\t%d\t%d\t%f", player[i].name, player[i].longestWord, player[i].highscore, player[i].numGames, player[i].averageScore);
			fclose(fp);
		}
		else {
			fp = fopen("SaveFile.txt", "r+");
			while(fscanf(fp, "%s%s%d%d%f", temp.name, temp.longestWord, &temp.highscore, &temp.numGames, &temp.averageScore) == 5) {
				if(strcmp(temp.name, player[i].name) == 0) { // fix
					fprintf(fp, "\n%s\t%s\t%d\t%d\t%f", player[i].name, player[i].longestWord, player[i].highscore, player[i].numGames, player[i].averageScore);
					fclose(fp);
				}
			}
		}
	}
}

int main(){
	int opt;
	int num;
	char board[11][11];
	int row = 6; // first row coordinate
	int column = 6; // first column coordinate
	int condition = 1;
	int i;
	int turn = 0; // end = 0;
	int across = 0;
	Str9 word;
	int total;
	int check = 0, check2 = 1;
	int condition1;
	int e;
	int L;
	int checkB;
	int tcondition = 0;

	int letterQuantity[27] = {9, 2, 2, 4, 12, 2, 3, 2, 9, 1, 1, 4, 2, 6, 8, 2, 1, 6, 4, 6, 4, 2, 2, 1, 2, 1, 2};

	opt = options(opt);

	while(opt>0){

	if(opt == 1){ // play

		NumPlayers(&num);
		Players(num);

		for(i = 0; i < num; i++) { // initialize
			player[i].score = 0;
			player[i].letterNum = 0;
			player[i].vowelNum = 0;
		}

		initBoard(board);
		printBoard(board);
		
		int error;
		while(condition){
		
			
			printf("========================== %s's Move =========================\n", player[turn].name);

			checkLetter(num, letterQuantity);
			printf("%s - ", player[turn].name);
			for(i = 0; i < 7; i++) {
				printf("| %c ", player[turn].letters[i]);
			}
			printf("\n");
			
			 //initialize error
			e = 0;
			//--------------------------------
			do { // while invalid word input
				
				printf("Word:");
				scanf("%s", word);
				
				L = strlen(word);
				uppercase(word);

				check = wordcheck(word); // 1 - valid | 0 - invalid
				check2 = checkWord(word, turn); // 0 - valid | 1 - invalid
				
				//MODIFIED CODE
				
			 //After placing two invalid words, player loses their turn
			 	
			if(check != 1 || check2 != 0){
				e++;
					if(e == 2){
						turn++;
						printf("========================== %s's Move =========================\n", player[turn].name);
						e=0;
				
				}
			}
			
			}while(check != 1 || check2 != 0);
		
			if(tcondition == 0) { // first move
				printf("(1) VERTICAL \n(2) HORIZONTAL\n(1/2): ");
				scanf("%d", &across);

				row--;
				column--;

				checkB = checkBoard(row, column, L, across, word, board, tcondition); // 1 - insufficient space | 0 - otherwise

				if (checkB == 1)
					condition1 = 0;
				else
					condition1 = 1;

				if(condition1 == 1) {
					total = pointsystem(word);
					fixTile(word, turn);


					if(across == 1){
						vert(board, word, row, column);
						printBoard(board);
					}
					if(across == 2){
						horz(board, word, row, column);
						printBoard(board);
					}

					printf("Points Earned: %d\n", total);
					player[turn].score += total;
					scorecheck(num);
					updatePlayerData(turn, word);
					condition1 = 0;
					turn++;
					tcondition++; // indicate end of first turn
				}
			}
			else if (tcondition == 1) {
				printf("Row: ");
				scanf("%d", &row);
				printf("Column: ");
				scanf("%d", &column);

				row--;
				column--;

				printf("(1) VERTICAL \n(2) HORIZONTAL\n(1/2): ");
				scanf("%d", &across);
				checkB = checkBoard(row, column, L, across, word, board, tcondition);

				if (checkB == 1)
					condition1 = 0;
				else
					condition1 = 1;

				if(condition1 == 1) {
					total = pointsystem(word);
					fixTile(word, turn);

					if(across == 1){
						vert(board, word, row, column);
						printBoard(board);
					}
					if(across == 2){
						horz(board, word, row, column);
						printBoard(board);
					}

					printf("Points Earned: %d\n", total);
					player[turn].score += total;
					scorecheck(num);
					updatePlayerData(turn, word);
					condition1 = 0;
					
					if(turn == num-1) {
						turn = 0;
					}
					
					else
						turn++;
				}
			}
			printf("Continue?: ");
			scanf("%d", &condition);

				if((player[turn].score == 88 || turn == 12)) { //WINNING CONDITION
					printf("CONGRATULATION!!/n %s WINS!!!", player[turn].name);
				}
		}
		

		for(i = 0; i < num; i++) {
			player[i].numGames++;
			player[i].averageScore = (player[i].averageScore + player[i].score) / player[i].numGames;
		}

		// fix | display end game results (name - longest word | highscore | chuchu)
		// save updated data to FILE
		saveFile(num);

}
	if(opt == 2){//

		printf("========================== INSTRUCTIONS =========================\n\n");
		printf("The game is allowed to be played at a minimum of 2\n");
		printf("players and at a maximum of 4 players.\n");
		printf("A player collects points by placing words on the game board.\n");
		printf("Each letter has a different point value, so the strategy becomes\n");
		printf("to play words with high scoring letter combinations.\n");
		printf("Players are asked where to place the word on a coordinate basis(x,y)\n");
		printf("and are asked how they would want it placed(VERTICALLY/HORIZONTALLY)\n");
		printf("\n========================== INSTRUCTIONS =========================\n");

		printf("Do you want to play\n (1) PLAY (3) QUIT\n");
		scanf("%d", &opt);

	}
	if(opt == 3){//quit
		return 0;
	}

}
}

