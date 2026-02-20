#include<iostream>
#include"Circular List.h"

using namespace std;
int main()
{
	CircularList<int> list1;
	list1.PushBack(99);
	list1.PushBack(3);
	list1.PushBack(5);
	list1.PushBack(7);
	list1.PushBack(9);

	int* arr = list1.ToArray();
	int len = list1.Length();
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}


}