#include<iostream>
#include"Queue.h"
using namespace std;
int main() {
	Queue<int> q;
	q.Push(1); cout<<"count : "<<q.Count()<<"  |  " << q;
	q.Push(2); cout << "count : " << q.Count() << "  |  " << q;
	q.Push(3); cout << "count : " << q.Count() << "  |  " << q;
	q.Push(4); cout << "count : " << q.Count() << "  |  " << q;
	q.Push(5); cout << "count : " << q.Count() << "  |  " << q;
	q.Push(6); cout << "count : " << q.Count() << "  |  " << q;
	q.Push(7); cout << "count : " << q.Count() << "  |  " << q;
	q.Push(8); cout << "count : " << q.Count() << "  |  " << q;
	q.Push(9); cout << "count : " << q.Count() << "  |  " << q;
	q.Push(10); cout << "count : " << q.Count() << "  |  " << q;

	q.Pop();
	q.Pop();
	q.Pop();
	q.Pop();
	q.Pop();
	q.Pop();
	q.Pop();
	q.Pop();

	q.Push(1); cout << "count : " << q.Count() << "  |  " << q;
	q.Push(2); cout << "count : " << q.Count() << "  |  " << q;
	q.Push(3); cout << "count : " << q.Count() << "  |  " << q;
	q.Push(4); cout << "count : " << q.Count() << "  |  " << q;
	q.Push(5); cout << "count : " << q.Count() << "  |  " << q;
	q.Push(6); cout << "count : " << q.Count() << "  |  " << q;
	q.Push(7); cout << "count : " << q.Count() << "  |  " << q;
	q.Push(8); cout << "count : " << q.Count() << "  |  " << q;
	q.Push(9); cout << "count : " << q.Count() << "  |  " << q;
	q.Push(10); cout << "count : " << q.Count() << "  |  " << q;
	
}