//Author: Matheus Bernardes dos Santos
//compile: gcc fibonaccica.c -o fibonaccica
//run: ./fibonaccica

#include <stdlib.h>
#include <stdio.h>

/*
	attempt 1: exchanging f(n+2) by f(n)
	f(2) = f(1) + f(0)

	Sample 1:
	(0) (1) (2)
	1   2   -1
	-1  2   1

	Sample 2:
	(0) (1) (2) (3) (4)
	35  28  21  14  7
	35  28  7   14  21
	35  14  7   28  21
	35  14  7   21  28
	7   14  35  21  28
	7   14  21  35  28

	Sample 3:
	(0) (1) (2) (3) (4)
	28  35  7   14  21
	28  35  7   14  21
	28  14  7   35  21
	28  14  7   21  35
	7   14  28  21  35
	7   14  21  28  35
	7   14  21  35  28

*/

int fib_sort(int *fib,int size){
	int i = size-1,aux,result = 0;

	while(i > 1) {
		if(fib[i] ==  fib[i-1] + fib[i-2]) i--;
		else {
			aux = fib[i];
			fib[i] = fib[i-2];
			fib[i-2] = aux;

			if(fib[i] != fib[i-1] + fib[i-2]){
				aux = fib[i];
				fib[i] = fib[i+1];
				fib[i+1] = aux;

				if(i+2 < size && fib[i+1] != fib[i] + fib[i-1]){
					fib[i+1] = fib[i] + fib[i-1];
				}
			}
		}
	}

	for(i = 0; i < size; i++){
		if(fib[i] == fib[i-1] + fib[i-2]) result = i;
	}

	return result;
}

int main(){
	int i,size,result;

	scanf("%d",&size);
	int *fib = (int *) malloc(sizeof(int)*size);
	
	for(i = 0;i < size;i++){
		scanf("%d",&fib[i]);
	}

	result = fib_sort(fib,size);

	printf("%d\n", result+1);

	free(fib);
	return 0;
}