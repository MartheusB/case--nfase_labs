//Author: Matheus Bernardes dos Santos
//compile: gcc min_tiredness.c -o min_tiredness
//run: ./min_tiredness

#include <stdlib.h>
#include <stdio.h>
/*
	this data structure contains: 
		-the start position of a person
		-the current position that is updated
		-his(her) tiredness 
		-a iterator for the tiredness that accumulate
*/
typedef struct person PERSON;

struct person{
	int startX;
	int currentX;
	int tiredness;
	int increaser;
};

void set_variables(PERSON *friendOne,PERSON *friendTwo){
	friendOne->currentX = friendOne->startX;
	friendOne->tiredness = 0;
	friendOne->increaser = 1;

	friendTwo->tiredness = 0;
	friendTwo->currentX = friendTwo->startX;
	friendTwo->increaser = 1;
}

void min_calculate(PERSON *One,PERSON *Two){

	if(One->currentX == Two->currentX) return;

	if(One->tiredness <= Two->tiredness){
		if(One->startX > Two->startX) One->currentX--;
		else One->currentX++;
		One->tiredness += One->increaser;
		One->increaser++;
	} else {
		if(Two->startX > One->startX) Two->currentX--;
		else Two->currentX++;
		Two->tiredness += Two->increaser;
		Two->increaser++;
	}

	min_calculate(One,Two);
}

int main(){
	PERSON *friendOne = (PERSON *) malloc(sizeof(PERSON));
	PERSON *friendTwo = (PERSON *) malloc(sizeof(PERSON));

	scanf("%d",&friendOne->startX);
	scanf("%d",&friendTwo->startX);

	set_variables(friendOne,friendTwo);

	min_calculate(friendOne,friendTwo);

	printf("%d\n", friendOne->tiredness + friendTwo->tiredness);

	free(friendOne);
	free(friendTwo);
	return 0;
}