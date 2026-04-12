/*
	注意a+1和k-2
*/
#include <iostream>
using namespace std;
int invert(int a[], int k)
{
	int t;
	if (k > 1)
	{
		t = a[0];
		a[0] = a[k - 1];
		a[k - 1] = t;
		invert(a + 1, k - 2);
	}
}
int main()
{
	int a[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	invert(a, 9);
	return 0;
}