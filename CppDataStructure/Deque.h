#pragma once
#include"Queue.h"

template<typename T>
class Deque : public Queue<T>
{
public:
	Deque(int capacity = 10) :Queue<T>(capacity) {}
	void PushFront(const T& data)
	{
		
		if ((this->rear + 1) % this->capacity == this->front)
		{
			T* newQueue = new T[this->capacity * 2];
			int start = (this->front + 1) % this->capacity;
			if (start < 2)
			{
				std::copy(this->queue + start, this->queue + this->rear + 1, newQueue);
			}
			else
			{
				std::copy(this->queue + start, this->queue + this->capacity, newQueue);
				std::copy(this->queue, this->queue + this->rear + 1, newQueue + (this->capacity - start));
			}
			this->rear = this->capacity - 2;
			this->capacity *= 2;
			this->front = this->capacity - 1;
			delete[] this->queue;
			this->queue = newQueue;
		}
		this->queue[this->front] = data;
		if (this->front == 0)
		{
			this->front = this->capacity - 1;
		}
		else
		{
			this->front--;
		}
	}
	void PopBack()
	{
		if (this->IsEmpty()) throw "None of element in queue";
		(this->rear == 0) ? this->rear = this->capacity - 1 : this->rear--;
	}
};