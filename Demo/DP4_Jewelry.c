#include <stdio.h>
#include <stdlib.h>
/************************************************************************/
/* Problem Statement
You have been given a list of jewelry items that must be split amongst two people: Frank and Bob. Frank likes very expensive jewelry. Bob doesn't care how expensive the jewelry is, as long as he gets a lot of jewelry. Based on these criteria you have devised the following policy:
1) Each piece of jewelry given to Frank must be valued greater than or equal to each piece of jewelry given to Bob. In other words, Frank's least expensive piece of jewelry must be valued greater than or equal to Bob's most expensive piece of jewelry.
2) The total value of the jewelry given to Frank must exactly equal the total value of the jewelry given to Bob.
3) There can be pieces of jewelry given to neither Bob nor Frank.
4) Frank and Bob must each get at least 1 piece of jewelry.
Given the value of each piece, you will determine the number of different ways you can allocate the jewelry to Bob and Frank following the above policy. For example:
values = {1,2,5,3,4,5}
Valid allocations are:
Bob       		Frank
1,2		         3
1,3        		 4
1,4		         5  (first 5)
1,4         		 5  (second 5)
2,3 		         5  (first 5)
2,3         		 5  (second 5)
5  (first 5)		 5  (second 5)
5  (second 5)	 5  (first 5)
1,2,3,4       		5,5
Note that each '5' is a different piece of jewelry and needs to be accounted for separately. There are 9 legal ways of allocating the jewelry to Bob and Frank given the policy, so your method would return 9.

Definition

Class:	Jewelry
Method:	howMany
Parameters:	int[]
Returns:	long
Method signature:	long howMany(int[] values)
(be sure your method is public)


Constraints
-	values will contain between 2 and 30 elements inclusive.
-	Each element of values will be between 1 and 1000 inclusive.

Examples
0)	

{1,2,5,3,4,5}
Returns: 9
From above.
1)	

{1000,1000,1000,1000,1000,
1000,1000,1000,1000,1000,
1000,1000,1000,1000,1000,
1000,1000,1000,1000,1000,
1000,1000,1000,1000,1000,
1000,1000,1000,1000,1000}
Returns: 18252025766940
2)	

{1,2,3,4,5}
Returns: 4
Valid allocations:
Bob               Frank
1,2                 3
2,3                 5
1,3                 4
1,4                 5
3)	

{7,7,8,9,10,11,1,2,2,3,4,5,6}
Returns: 607
4)	

{123,217,661,678,796,964,54,111,417,526,917,923}
Returns: 0                                                                     */
/************************************************************************/













/************************************************************************/
/* At first glance, this problem appears to be a straightforward variation on the knapsack theme. As lars announced in his trademark fashion, "It's TRIVIAL!" 
You would expect a crowd as well-versed in dynamic programming as this one to breeze through the problem. Ah, but there was a twist! 
The treatment of equal elements gave folks fits.

Without equal elements, the problem could be solved as follows:

sort the elements in increasing order
count = 0
for each i from 1 .. # of elements do
// assume element i is Bob's highest valued item
waysBelow = ways to make sums using elements below i
waysAbove = ways to make sums using elements above i
for each sum s from element i upto max do
count += waysBelow[s - element i] * waysAbove[s]
return count
Given K elements 1..K, you can calculate the number of ways to make various sums of those values using a typical knapsack algorithm:
initialize array ways[0..Max] to all zeros
ways[0] = 1
for each i from 1 upto K do
for each sum s from max downto element i do
ways[s] += ways[s - element i]
At the end of these loops, ways[s] contains the number of ways to choose elements that sum to s.
Equal elements complicate the picture because we can no longer guarantee that Bob's elements are all to the left of Frank's elements in the sorted list.
However, the only exceptions occur when Bob and Frank take elements of equal value. In each such case, we need to consider all the different ways that Bob and 
Frank can exchange their equal elements. Fortunately, the changes to the overall algorithm are relatively minor.

We now need to process the elements group by group instead of element by element, where each group contains equal elements. Suppose there are G equal elements in a group. 
For each size g between 1 and G, we calculate how many distributions there are in which Bob gets g items from this group. 
Then we multiply by Choose(G,g) to account for the different ways to pick g elements out of the group. Altogether, the final algorithm looks like

sort the elements in increasing order
count = 0
for each group of equal elements do
i = first index of group
G = size of group
waysBelow = ways to make sums using elements below i
for each g from 1 to G do
waysAbove = ways to make sums using elements above i+g-1
for each sum s from g * element i upto max do
count += Choose(G,g) * waysBelow[s - g * element i] * waysAbove[s]
return count                                                                     */
/************************************************************************/
int main()
{
	int jewelry[100] = {};
	int status[100] = {}; //	标志每一个是不是已经被分给谁了, 0:没分,1:已经分了
	int Franks[];
	int Bobs[];
	int FrankSum;	// > 0， 初始化0
	int BobSum;		// >0， 初始化0
	int FrankMin;	// > 0 >=BobMax, 初始化0
	int BobMax;		// > 0， 初始化0
	int n = sizeof(jewelry)/sizeof(int);			// 珠宝个数
	system("pause");
	return 0;
}