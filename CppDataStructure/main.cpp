#include<iostream>
#include"ChainList.h"

int main() 
{
	ChainList x, y;
	x.PushFront(8);
	x.PushFront(7);
	x.PushFront(1);

	y.PushFront(100);
	y.PushFront(9);
	y.PushFront(4);
	y.PushFront(3);
	y.PushFront(2);

	ChainList merged;

	cout << "x:" << x;
	cout << "y:" << y;
	cout << "merged:" << merged;

	merged = x.ArrangeMerge(y);
	
	cout << "x:" << x;
	cout << "y:" << y;
	cout << "merged:" << merged;
	cout << "merged Length : " << merged.Length() << endl;
}