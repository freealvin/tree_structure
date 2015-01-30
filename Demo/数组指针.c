#include <stdio.h>
#include <stdlib.h>

int  mai1n1()
{
	int a[4] = {1, 2,3,4};
	int *p1 = (int *)(&a+1);
	int *p2 = (int *)((int)a+1);
	printf("%x,%x\n", p1[-1], *p2);
	printf("%d\n", sizeof(int));
	printf("%x\n", a);
	printf("%x\n", ((int)a+1));

	system("pause");
	return 0;

}
int main4()
{
	int a[5] ={'a','b','c','d', 'e'};

	int (*p1)[3] = &a;
	int (*p2)[3] = a;
	printf("p1=%p\n", p1);
	printf("p2=%p\n", p2);

	printf("p1+1=%p\n", p1+1);
	printf("p2+1=%p\n", p2+1);

	printf("a[0]=%d\n", (*p1)[0]);
	printf("a=%d\n", (*p2));

	printf("sizeof(p1):%d\n", sizeof(*p1));
	printf("sizeof(p2):%d\n", sizeof(*p2));


	system("pause");
	return 0;
}

int main2()
{
	int a[5] ={'a','b','c','d', 'e'};
	printf("&a[0]=%p\n", &a[0]);
	printf("&a=%p\n", &a);
	printf("a=%p\n", a);

	printf("*a = %d\n", *a);
	printf("*(&a) = %d\n", *(&a));
	printf("*((int*)&a) = %d\n", *((int*)&a));


	system("pause");
	return 0;
}

int main3()
{
	int a[5] ={'a','b','c','d', 'e'};

	int (*p1)[3] = &a;
	int (*p2)[3] = a;
	printf("p1=%p\n", p1);
	printf("p2=%p\n", p2);

	printf("p1+1=%p\n", p1+1);
	printf("p2+1=%p\n", p2+1);

	printf("a[0]=%d\n", (*p1)[0]);
	printf("a=%d\n", (*p2));

	printf("sizeof(p1):%d\n", sizeof(*p1));
	printf("sizeof(p2):%d\n", sizeof(*p2));


	system("pause");
	return 0;
}

/**
*
output
&a[0]=0024FE90
&a=0024FE90
a=0024FE90
*a = 97
*(&a) = 2424464
*((int*)&a) = 97

a叫做数组名，是数组首元素的地址，也就是&a[0]的值
&a这才是一个真正的指针，是一个数组指针。是数组的地址

为什么会相同呢？
**/