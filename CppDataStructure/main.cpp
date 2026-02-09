#include<iostream>
#include"Queue.h"
#include"Deque.h"
#include<algorithm>
using namespace std;


int main() {
	Queue<int> q;
	
	for (int i = 1; i <= 10; i++)
	{
		q.PushBack(i);
	}
	for (int i = 1; i <= 5; i++)
	{
		q.PopFront();
	}
	for (int i = 11; i <= 20; i++)
	{
		q.PushBack(i);
	}
	q.Insert(8, 1);
	cout << q;
}

