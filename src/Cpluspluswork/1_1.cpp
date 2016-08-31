// 1_1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;

int main()
{
	int i=0,sum=0;
	do
	{
		i=i+1;
		sum=sum+i;
	}
	while (i<10);
	cout<<sum<<endl;
	return 0;
}

