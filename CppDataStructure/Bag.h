#pragma once
#include<iostream>
#include<algorithm>
using namespace std;
template<typename T>
class Bag
{
public:
	Bag(int capacity = 10);
	virtual ~Bag();
	virtual void Push(const T& data);
	virtual void Pop();
	virtual bool IsEmpty() const;
	virtual T& Element() const;
	friend ostream& operator<<(ostream& os, const Bag<T>& bag);
protected:
	T* array;
	int top;
	int capacity;
};

template<typename T>
ostream& operator<<(ostream& os, const Bag<T>& bag)
{
	for (int i = 0; i <= bag.top; i++)
	{
		os << bag.array[i] << " ";
	}
	os << std::endl;
}


template<typename T>
Bag<T>::Bag(int capacity)
	:top(-1), capacity(capacity)
{
	array = new T[capacity];
}

template<typename T>
void Bag<T>::Push(const T& data)
{
	if (top + 1 == capacity)
	{
		capacity *= 2;
		T* temp = new T[capacity];
		copy(array, array + top + 1, temp);
		delete[] array;
		array = temp;
	}
	array[++top] = data;
}

template<typename T>
void Bag<T>::Pop()
{
	if (IsEmpty()) throw "Cannot pop Empty Bag";
	int deletePos = (top + 1) / 2;
	copy(array + deletePos + 1, array + top + 1, array + deletePos);
	array[top--].~T();
}

template<typename T>
bool Bag<T>::IsEmpty() const
{
	return top == -1;
}

template<typename T>
T& Bag<T>::Element() const
{
	if (IsEmpty()) throw "Cannot get an Element From Empty Bag";
	return array[0];
}

template<typename T>
Bag<T>::~Bag()
{
	if (array != nullptr)
	{
		delete[] array;
	}
}