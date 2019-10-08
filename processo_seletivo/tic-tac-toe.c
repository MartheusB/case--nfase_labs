//Author: Matheus Bernardes dos Santos
//compile: gcc tic-tac-toe.c -o tic-tac-toe
//run: ./tic-tac-toe

#include <stdlib.h>
#include <stdio.h>

typedef struct player PLAYER;

struct player{
	int num_plays;
	int num_matchs;
};
/*
	RESULTS keep the information of the game in general
		end_game -> if the table is full
		invalid_game -> if there is some invalid format of the table
		cross_win -> the player using cross is the winner
		cross_turn -> the next turn if for cross
		circle_win -> the player using circle is the winner
		circle_turn -> the next turn is for circle
*/
typedef struct results RESULTS;

struct results{
	int end_game;
	int invalid_game;
	int cross_win;
	int cross_turn;
	int circle_win;
	int circle_turn;
};
/*
	Read_line is a function that reads as many char's as it needs using 
	delimitators like ENTER and EOF
*/
char *Read_line(){
 	char c;
	char *string = NULL;
	int counter = 0;

 	do {
 		c = fgetc(stdin);
 		string = (char *) realloc(string,(counter+1)*sizeof(char));
 		string[counter++] = c;
 	} while ( c != 10 && c != EOF);
 	string[counter-1] = '\0';

 	return string;
}

void check_table(char **table,PLAYER *cross,PLAYER *circle,RESULTS *results){
	int i,j;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			if(table[i][j] == 'X') cross->num_plays++;
			else if(table[i][j] == 'O') circle->num_plays++;
		}
	}
	
	if(cross->num_plays + circle->num_plays == 9) results->end_game = 1;	   //it's full
	else if(cross->num_plays > circle->num_plays) results->circle_turn = 1;	   //circle turn
	else results->cross_turn = 1;											   //cross turn
}

void check_matchs(char **table,PLAYER *cross,PLAYER *circle,RESULTS *results){
	int i;

	for(i = 0;i < 3;i++){
		//percorre as linhas procurando um jogo completo de 'X' ou 'O'
		if((table[i][0] == 'X' && table[i][1] == 'X') && table[i][2] == 'X') cross->num_matchs++;
		else if(table[i][0] == 'O' && table[i][1] == 'O' && table[i][2] == 'O') circle->num_matchs++;
		//percorre as colunas procurando um jogo completo de 'X' ou 'O'
		if((table[0][i] == 'X' && table[1][i] == 'X') && table[2][i] == 'X') cross->num_matchs++;
		else if(table[0][i] == 'O' && table[1][i] == 'O' && table[2][i] == 'O') circle->num_matchs++;
	}
	//percorre a diagonal principal procurando um jogo completo de 'X' ou 'O'
	if((table[0][0] == 'X' && table[1][1] == 'X') && table[2][2] == 'X') cross->num_matchs++;
	else if(table[0][0] == 'O' && table[1][1] == 'O' && table[2][2] == 'O') circle->num_matchs++;
	//percorre a diagonal secundaria procurando um jogo completo de 'X' ou 'O'
	if((table[0][2] == 'X' && table[1][1] == 'X') && table[2][0] == 'X') cross->num_matchs++;
	else if(table[0][2] == 'O' && table[1][1] == 'O' && table[2][0] == 'O') circle->num_matchs++;

	if(abs(cross->num_plays - circle->num_plays) > 1) results->invalid_game = 1;
	if(cross->num_matchs > 0 && circle->num_matchs > 0) results->invalid_game = 1;
	else if(cross->num_matchs == 1 && circle->num_matchs == 0) results->cross_win = 1;
	else if(circle->num_matchs == 1 && cross->num_matchs == 0) results->circle_win = 1;
}

void update_results(RESULTS *results){
	if(results->invalid_game == 1) printf("inválido\n");
	else if(results->end_game == 1 && results->cross_win == 0 && results->circle_win == 0) printf("empate\n");
	else if(results->cross_turn == 1 && results->cross_win == 0 && results->circle_win == 0) printf("primeiro\n");
	else if(results->circle_turn == 1 && results->cross_win == 0 && results->circle_win == 0) printf("segundo\n");
	else if(results->cross_win == 1 && results->circle_win == 0) printf("primeiro_venceu\n");
	else printf("segundo_venceu\n");

}

int main() {
	int i,j;
	char **table = (char **) malloc(sizeof(char *)*3);
	RESULTS *results = (RESULTS *) malloc(sizeof(RESULTS));
	PLAYER *cross = (PLAYER *) malloc(sizeof(PLAYER));
	PLAYER *circle = (PLAYER *) malloc(sizeof(PLAYER));
	cross->num_plays = 0;
	cross->num_matchs = 0;
	circle->num_plays = 0;
	circle->num_matchs = 0;

	for (i = 0; i < 3; i++) {
		table[i] = Read_line();
	}

	check_table(table,cross,circle,results);

	check_matchs(table,cross,circle,results);

	update_results(results);	


	for(i = 0;i < 3;i++) free(table[i]);
	free(table);
	free(results);
	free(cross);
	free(circle);
	return 0;
}