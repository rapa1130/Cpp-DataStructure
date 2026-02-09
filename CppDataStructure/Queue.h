#pragma once
#include<iostream>

template<typename T>
class Queue
{
public:
	Queue(int capacity = 10)
		:capacity(capacity),front(0),rear(0)
	{
		queue = new T[capacity];
	}
	void Push(const T& data)
	{
		if (front == (rear + 1) % capacity){
			T* newQueue = new T[capacity * 2];
			int start = (front + 1) % capacity;
			if (start < 2)
			{
				std::copy(queue + start, queue + rear + 1, newQueue);
			}
			else
			{
				std::copy(queue + start, queue + capacity, newQueue);
				std::copy(queue, queue + rear + 1, newQueue + (capacity - start));
			}
			rear = capacity - 2;
			capacity *= 2;
			front = capacity - 1;
			delete[] queue;
			queue = newQueue;
		}
		rear = (rear + 1) % capacity;
		queue[rear] = data;
		
	}
	void Pop()
	{
		if (IsEmpty()) throw "can't pop less than 0 size of queue";
		front = (front + 1) % capacity;
	}
	bool IsEmpty() const
	{
		return front == rear;
	}
	T Front() const
	{
		if (IsEmpty()) throw "None of element in queue";
		return queue[(front + 1) % capacity];
	}
	T Rear() const
	{
		if (IsEmpty()) throw "None of element in queue";
		return queue[rear];
	}
	int Count() const
	{
		if (front < rear)
		{
			return rear - front;
		}
		else
		{
			return rear + capacity - front - 1;
		}
	}
	int Capacity() const
	{
		return capacity;
	}
	friend std::ostream& operator<<(std::ostream& os, const Queue<T>& queue)
	{
		int i = (queue.front + 1) % queue.capacity;
		int last = (queue.rear + 1) % queue.capacity;
		for (; i != last; i = ((i + 1) % queue.capacity))
		{
			os << queue.queue[i] << " ";
		}
		os << std::endl;
		return os;
	}
private:
	T* queue;
	int front;
	int rear;
	int capacity;
};