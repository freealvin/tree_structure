#include <stdio.h>
#include <stdlib.h>

int len[100];
int last[100];


/*
 * O(n2)
*/

void dealLIS(int arr[], int n)
{
	int i, j;
	int max_len = 0;
	int last_index = 0;
	for(i=1; i<n; i++){
		for(j=0; j<i; j++){
			if(arr[j] <= arr[i] && len[i] < len[j] +1){
				len[i] = len[j] +1;
				last[i] = j;
			}if(arr[j] <= arr[i] && len[i] == len[j] +1){
				printf("\tarr[%d]= \t%d  \t len =\t %d  \tarr[%d] = \t%d\n", i, arr[i],len[i] ,j,arr[j]);
			}
		}
	}



	for(i=0; i<n; i++){
		printf("i=\t%d \tval=\t%d \tlen=\t%d last_index= \t %d\n", i, arr[i], len[i], last[i]);
		if(len[i] > max_len){
			max_len = len[i];
			last_index = i;
		}
	}

	

	while(last_index>=0){
		//last_index为自己时,输出并结束
		if(last_index!=last[last_index]){
			printf("%d \n", arr[last_index]);
			last_index = last[last_index];
		}else{
			printf("%d \n", arr[last_index]);
			break;
		}
	}
}

int main12()
{
	int arr[13] = {1,5,8,3,6,7};
	int i;
	for(i=0; i<5; i++){
		len[i] = 1;
		last[i] = i;
	}

	dealLIS(arr, 5);
	system("pause");
	return 0;
}