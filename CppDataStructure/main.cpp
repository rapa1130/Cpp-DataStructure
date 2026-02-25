#include<iostream>
#include"04_LinkedList/04_05_Linked_Stack_Queue/QueueByCircularLinked2.h"

using namespace std;
int main()
{
	Queue<int> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	cout<<"Len:"<<q.Count()<<endl;
	cout<<q;
}