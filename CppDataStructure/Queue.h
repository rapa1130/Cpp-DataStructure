#pragma once
#include<iostream>
#include<algorithm>
template<typename T>
class Queue
{
public:
	Queue(int capacity = 10)
		:capacity(capacity),front(0),rear(0)
	{
		queue = new T[capacity];
	}
	void PushBack(const T& data)
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
	void PopFront()
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
	T operator[](int index) const
	{
		return queue[(front + index + 1) % capacity];
	}
	T& operator[](int index)
	{
		return queue[(front + index + 1) % capacity];
	}
	int Count() const
	{
		if (front <= rear)
		{
			return rear - front;
		}
		else
		{
			return rear + capacity - front;
		}
	}
	int Capacity() const
	{
		return capacity;
	}

	void Reset()
	{
		front = rear;
	}

	void Delete(int index)
	{
		int deletePos = (front + index + 1) % capacity;
		int start = (front + 1) % capacity;
		int queueIndex = deletePos;
		while (queueIndex != start)
		{
			int nextIndex = (queueIndex == 0 ? capacity - 1 : queueIndex - 1);
			queue[queueIndex] = queue[nextIndex];
			queueIndex = nextIndex;
		}
		PopFront();
	}

	void Insert(int index,const T& data)
	{
		PushBack(data);
		int insertPos = (front + index + 1) % capacity;
		int start = (front + 1) % capacity;
		int queueIndex = rear;
		while (queueIndex != insertPos)
		{
			int nextIndex = (queueIndex == 0 ? capacity - 1 : queueIndex - 1);
			queue[queueIndex] = queue[nextIndex];
			queueIndex = nextIndex;
		}
		queue[insertPos] = data;
	}

	void Merge_Interchangibly(const Queue<T>& first,const Queue<T>& second)
	{
		int firstStart = (first.front + 1) % first.capacity;
		int secondStart = (second.front + 1) % second.capacity;

		int firstEnd = (first.rear + 1) % first.capacity;
		int secondEnd = (second.rear + 1) % second.capacity;

		int firstIndex = firstStart;
		int secondIndex = secondStart;
		
		Reset();
		while (firstIndex < firstEnd && secondIndex < secondEnd)
		{
			if (Count() % 2 == 0)
			{
				PushBack(first.queue[firstIndex++]);
			}
			else
			{
				PushBack(second.queue[secondIndex++]);
			}
		}
		for (; firstIndex < firstEnd; firstIndex++)
		{
			PushBack(first.queue[firstIndex]);
		}
		for (; secondIndex < secondEnd; secondIndex++)
		{
			PushBack(second.queue[secondIndex]);
		}
	}

	std::pair<Queue<T>, Queue<T>> Split_Interchangibly() const
	{
		Queue<T> first;
		Queue<T> second;

		int start= (front + 1) % capacity;
		int end = (rear + 1) % capacity;

		for (int index = start; index != end; index = (index + 1) % capacity)
		{
			if ((index - start) % 2 == 0)
			{
				first.PushBack(queue[index]);
			}
			else
			{
				second.PushBack(queue[index]);
			}
		}
		return pair<Queue<T>, Queue<T>>(first, second);
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



	~Queue() {
		if (queue != nullptr)
		{
			delete[] queue;
		}
	}
protected:
	T* queue;
	int front;
	int rear;
	int capacity;
};