/*
* 给一个不多于 5 位的正整数，要求：①求出它是几位数；②分别打印出每一位数字；③
* 按逆序打印出各位数字，例如原数为 321，应输出 123。 (15 分)
*/
#include<iostream>
using namespace std;

void output(int a[],int k);
void invert(int a[],int k);
void num(int n);

int main()
{
	int n=345;
	num(n);
	return 0;
}

void output(int a[],int k)
{
	for(int i = 0;i<k;i++)
	{
		cout<<a[i];
	}
}

void invert(int a[],int k)
{
	int t;
	if(k>1)
	{
		t = a[0];
		a[0] = a[k-1];
		a[k-1] = t;
		invert(a+1,k-2);
	}
}

void num(int n)
{
	int k = 0;
	int a[5];
	while(n)
	{
		a[k++]=n%10;
		n/=10;
	}
	cout<<"几位数："<<k<<endl;

    cout<<"逆序打印：";
	output(a,k);
    cout<<endl;
	invert(a,k);

    cout<<"原本数据：";
	output(a,k);
}