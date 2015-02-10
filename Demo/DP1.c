#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int S[100];

void dpDeal( int S[], int max, int coins[], int n ) 
{
	int i, j;
	for(i=0; i<=max; i++){
		for(j=0; j<n; j++){
			if(coins[j] <= i&& S[i-coins[j]]+1 < S[i]){
				S[i] = S[i-coins[j]]+1;
			}
		}
	}

	for(i=0; i<=max; i++){
		printf("i=%d, the number of coins= %d\n", i, S[i]);
	}
}

int main11()
{
	int coins[3] = {1, 3, 5};
	int max = 11;
	int n = 3;

	int i;
	for(i=0; i<max; i++){
		S[i] = INT_MAX;
	}

	S[0] = 0;
	dpDeal(S,max, coins, n);

	system("pause");

	return 0;
}