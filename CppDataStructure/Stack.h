#pragma once
#include<iostream>


template<typename T>
class Stack
{
public:
	Stack(int capacity = 10)
		:top(-1), capacity(capacity)
	{
		stack = new T[capacity];
	}
	bool IsEmpty() const
	{
		return top == -1;
	}
	T Top() const
	{
		return stack[top];
	}
	void Push(const T& data)
	{
		if (top == capacity - 1)
		{
			capacity *= 2;
			T* temp = new T[capacity];
			std::copy_n(stack, top + 1, temp);
			delete[] stack;
			stack = temp;
		}
		stack[++top] = data;
	}
	void Pop()
	{
		if (IsEmpty()) throw "Stack is Empty";

		stack[top--].~T();
	}

	friend std::ostream& operator<<(std::ostream& os, const Stack<T>& stack)
	{
		for (int i = 0; i <= stack.top; i++)
		{
			os << stack.stack[i] << " ";
		}
		os << std::endl;
		return os;
	}
	Stack SplitHalf()
	{
		int otherSize = top / 2;
		Stack otherHalf(otherSize+1);
		otherHalf.top = otherSize;
		for (int i = otherSize; i >= 0; i--)
		{
			otherHalf.stack[i] = Top();
			Pop();
		}
		return otherHalf;
	}

	Stack operator+=(const Stack& right)
	{
		for (int i = 0; i <= right.top; i++)
		{
			Push(right.stack[i]);
		}
		return *this;
	}
private:
	T* stack;
	int top;
	int capacity;
};