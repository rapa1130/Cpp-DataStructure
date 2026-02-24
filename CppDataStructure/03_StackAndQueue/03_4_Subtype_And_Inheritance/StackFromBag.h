#pragma once
#include"Bag.h"

template<typename T>
class Stack : public Bag<T>
{
public:
	Stack(int capacity = 10) :Bag(capacity) {}
	~Stack() {}
	T Top() const
	{
		return this->array[top];
	}
	virtual void Pop() override
	{
		if (IsEmpty()) throw "Cannot pop Empty Stack";
		this->array[top--].~T();
	}
};