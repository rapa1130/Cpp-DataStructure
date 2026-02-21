#include<iostream>
#include"Circular FakeHaed.h"

using namespace std;
int main()
{
	CircularList<int> list1;
	CircularList<int> list2;

	list1.PushFront(7);
	list1.PushFront(2);

	list2.PushFront(6);
	list2.PushFront(5);
	list2.PushFront(4);
	list2.PushFront(3);
	list2.PushFront(1);


	list2.ArrangeMerge(list1);
	//list1.ArrangeMerge(list2);
	cout << "list1 : "<<list1;
	cout << "list2 : "<<list2;
}