#include <stdio.h>


typedef struct node{
	int index;
	double val;
	double max;
	double min;
	int max_last_index;
	int max_last_type;//�����ϸ������������С�����ǲ���   0 ��С�� 1 ���� 2 ���  �������Լ�Ϊ3����һ�������ֵ�ȳ����Լ��󻹴�
	int min_last_index;
	int min_last_type;//�����ϸ������������С�����ǲ���   0 ��С�� 1 ���� 2 ���	�������Լ�Ϊ3����һ������Сֵ�ȳ����Լ���С��
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
/* ��һ�����������У�ȡ���˻������Ӵ���ֵ������ -2.5��4��0��3��0.5��8��-1��
 * ��ȡ�������˻������Ӵ�Ϊ3��0.5��8��Ҳ����˵�����������У�
 * 3 0.5 8��3�����ĳ˻�30.58=12�����ģ������������ġ�                                                                     */
/************************************************************************/

/************************************************************************/
/* ��̬�滮���ķ���һ��forѭ���㶨������ʱ�临�Ӷ�ΪO(n)��                                                                     */
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
/* 1������һ������ΪN���������飬ֻ�����ó˷��������ó������������⣨N-1������������г˻�����һ�飬��д���㷨��ʱ�临�Ӷȡ�
���������ǿ��԰����п��ܵģ�N-1������������ҳ������ֱ�������ǵĳ˻������Ƚϴ�С�������ܹ���N����N-1����������ϣ�
�ܵ�ʱ�临�Ӷ�ΪO��N2������Ȼ�ⲻ����õĽⷨ��                                                                     */
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