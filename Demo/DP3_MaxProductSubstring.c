#include <stdio.h>


typedef struct node{
	int index;
	double val;
	double max;
	double min;
	int max_last_index;
	int max_last_type;//乘于上个结点的最大还是最小，还是不乘   0 最小， 1 自身， 2 最大，  不乘于自己为3（上一个的最大值比乘于自己后还大）
	int min_last_index;
	int min_last_type;//乘于上个结点的最大还是最小，还是不乘   0 最小， 1 自身， 2 最大，	不乘于自己为3（上一个的最小值比乘于自己后还小）
}node;

double max(double v1, double v2)
{
	return v1>=v2?v1:v2;
}

double min(double v1, double v2)
{
	return v1<=v2?v1:v2;
}

/************************************************************************/
/* 给一个浮点数序列，取最大乘积连续子串的值，例如 -2.5，4，0，3，0.5，8，-1，
 * 则取出的最大乘积连续子串为3，0.5，8。也就是说，上述数组中，
 * 3 0.5 8这3个数的乘积30.58=12是最大的，而且是连续的。                                                                     */
/************************************************************************/

/************************************************************************/
/* 动态规划求解的方法一个for循环搞定，所以时间复杂度为O(n)。                                                                     */
/************************************************************************/
double MaxProductSubstring1(double *a, int length)
{
	double maxEnd = a[0];
	double minEnd = a[0];
	double maxResult = a[0];

	int i;
	for (i = 1; i < length; ++i)
	{
		double end1 = maxEnd * a[i], end2 = minEnd * a[i];
		maxEnd = max(max(end1, end2), a[i]);
		minEnd = min(min(end1, end2), a[i]);
		maxResult = max(maxResult, maxEnd);
	}
	return maxResult;
}




node products[100];

void printMaxString(double *arr, int lastIndex)
{
	if(products[lastIndex].index ==products[lastIndex].max_last_index){
		printf("%.2lf \n", arr[lastIndex]);
	}
	else if(lastIndex>=0){
		switch(products[lastIndex].max_last_type){
			case 0 :
			case 1 :
			case 2 :
				printMaxString(arr, products[lastIndex].max_last_index);
				printf("%.2lf \n", arr[lastIndex]);
				break;
			case 3:
				printMaxString(arr, products[lastIndex].max_last_index);
				break;
			default:
				break;
		}
	}
}

/************************************************************************/
/* 1、给定一个长度为N的整数数组，只允许用乘法，不能用除法，计算任意（N-1）个数的组合中乘积最大的一组，并写出算法的时间复杂度。
分析：我们可以把所有可能的（N-1）个数的组合找出来，分别计算它们的乘积，并比较大小。由于总共有N个（N-1）个数的组合，
总的时间复杂度为O（N2），显然这不是最好的解法。                                                                     */
/************************************************************************/
double MaxProductSubstring(double *a, int n)
{
	int i;
	double maxEnd = a[0];
	double minEnd = a[0];
	double maxResult =a[0];
	double minResult =a[0];
	int maxIndex = 0;
	int minIndex = 0;

	for (i=0; i<n; i++)
	{
		products[i].index = i;
		products[i].val = a[i];
		products[i].max = a[i];
		products[i].min = a[i];
		products[i].max_last_index = i;
		products[i].min_last_index = i;
		products[i].max_last_type = 1;
		products[i].min_last_type = 1;
	}

	for(i=1; i<n; i++){
		products[i].max = max(max(a[i], max(a[i]*products[i-1].max, a[i]*products[i-1].min)),products[i-1].max) ;
		products[i].min = min(min(a[i], min(a[i]*products[i-1].max, a[i]*products[i-1].min)), products[i-1].min);

		if(a[i] >= a[i]*products[i-1].max&&a[i] >= a[i]*products[i-1].min&& a[i] >= products[i-1].max){
			products[i].max_last_type = 1;
			products[i].max_last_index = i;
		}else if(a[i]*products[i-1].min >= a[i]*products[i-1].max&& a[i]*products[i-1].min >= a[i] && a[i]*products[i-1].min >= products[i-1].max){
			products[i].max_last_type = 0;
			products[i].max_last_index = i-1;
		}else if(a[i]*products[i-1].max >= a[i]*products[i-1].min&& a[i]*products[i-1].max >= a[i] && a[i]*products[i-1].max >= products[i-1].max){
			products[i].max_last_type = 2;
			products[i].max_last_index = i-1;
		}else{
			products[i].max_last_type = 3;
			products[i].max_last_index =products[i-1].max_last_type==3? products[i-1].max_last_index:i-1;
		}


		if(a[i] <= a[i]*products[i-1].max&&a[i] <= a[i]*products[i-1].min&& a[i] <=products[i-1].min){
			products[i].min_last_type = 1;
			products[i].min_last_index = i;
		}else if(a[i]*products[i-1].min <= a[i]*products[i-1].max&& a[i]*products[i-1].min <= a[i] && a[i]*products[i-1].min <= products[i-1].min){
			products[i].min_last_type = 0;
			products[i].min_last_index = i-1;
		}else if(a[i]*products[i-1].max <= a[i]*products[i-1].min&& a[i]*products[i-1].max <= a[i] && a[i]*products[i-1].max <=products[i-1].min){
			products[i].min_last_type = 2;
			products[i].min_last_index = i-1;
		}else{
			products[i].min_last_type = 3;
			products[i].min_last_index = products[i-1].min_last_type==3?products[i-1].min_last_index: i-1;
		}

		if(maxResult < products[i].max){
			maxResult = products[i].max;
			maxIndex = i;
		}

		if(minResult > products[i].min){
			minResult = products[i].min;
			minIndex = i;
		}


	}

	printf("%lf\n", maxResult);
	printMaxString(a, maxIndex);

	return maxResult;


}

int main()
{

	double arr[11] = {-1, 2, 4, 0.8, 3, 10, -4, -6, 7, -0.5, -1.5};
	MaxProductSubstring(arr, 11);

	return 0;


}