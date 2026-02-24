#pragma once

#include"Bag.h"
#include<iostream>

template<typename T>
class Queue : public Bag<T>
{
public:
	Queue(int capacity = 10)
		:Bag<T>(capacity), front(0)
	{
		this->top = 0;
	}
	~Queue() {}

	virtual void Push(const T& data) override
	{
		if ((this->top +1)% this->capacity == front)
		{
			T* temp = new T[this->capacity * 2];
			int start = (front + 1) % this->capacity;
			if (start < 2)
			{
				copy(this->array + start, this->array + this->top + 1, temp);
			}
			else
			{
				copy(this->array + start, this->array + this->capacity, temp);
				copy(this->array, this->array + this->top + 1, temp + this->capacity - 1);
			}
			front = 2 * this->capacity - 1;
			this->top = this->capacity - 2;
			this->capacity *= 2;
			delete[] this->array;
			this->array = temp;
		}
		this->top = (this->top + 1) % this->capacity;
		this->array[this->top] = data;
	}
	virtual void Pop() override
	{
		if (IsEmpty()) throw "Cannot Pop Empty Queue";
		front = (front + 1) % this->capacity;
	}
	virtual bool IsEmpty() const override
	{
		return front == this->top;
	}
	friend ostream& operator<<(ostream& os, const Queue<T>& queue)
	{
		int index = (queue.front + 1) % queue.capacity;
		int end = (queue.top + 1) % queue.capacity;
		while (index != end)
		{
			os << queue.array[index] << " ";
			index = (index + 1) % queue.capacity;
		}
		os << std::endl;
		return os;
	}
private:
	int front;
};
