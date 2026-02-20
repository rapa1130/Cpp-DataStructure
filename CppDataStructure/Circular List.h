#pragma once
#include<iostream>
using namespace std;


template<typename T>
class CircularList
{
public:
	class ChainNode;
	CircularList(ChainNode* last = nullptr) :last(last) {} 
	
	void PushFront(const T& data)
	{
		if (last)
		{
			last->link = new ChainNode(data, last->link);
		}
		else
		{
			last->link = last = new ChainNode(data, nullptr);
		}
	}

	void PushBack(const T& data)
	{
		if (last)
		{
			last = last->link = new ChainNode(data, last->link);
		}
		else
		{
			last->link = last = new ChainNode(data, nullptr);
		}
	}

	friend ostream& operator<<(ostream& os, const CircularList<T>& list)
	{
		if (list.last)
		{
			ChainNode* first = list.last->link;
			ChainNode* now = first;
			do
			{
				os << now->data << " ";
				now = now->link;
			} while (now != first);
		}
		os << endl;
		return os;
	}


	void PopFront()
	{
		ChainNode* first = last->link;
		if (last == first)
		{
			last = nullptr;
		}
		else
		{
			last->link = first->link;
		}
		delete first;
	}

	void Insert(const T& data, int index)
	{
		if (last)
		{
			ChainNode* first = last->link;
			ChainNode* prev = last;
			ChainNode* now = first;
			int nowIndex = 0;
			while (nowIndex < index)
			{
				prev = now;
				now = now->link;
				nowIndex++;
			}
			prev->link = new ChainNode(data, now);
		}
		else
		{
			PushFront(data);
		}
	}

	int Length() const
	{
		if (last)
		{
			int len = 1;
			for (ChainNode* now = last->link; now != last; now = now->link)
			{
				len++;
			}
			return len;
		}
		else
		{
			return 0;
		}

	}

	void Delete(int index)
	{
		if (last == nullptr)
		{
			throw "List is Empty";
		}
		
		ChainNode* now = last->link;
		ChainNode* prev = last;
		
		for (int nowIndex = 0; nowIndex < index; nowIndex++)
		{
			prev = now;
			now = now->link;
		}

		if (now == prev)
		{
			delete now;
			last = nullptr;
			return;
		}

		prev->link = now->link;
		if (now == last) last = prev;
		delete now;
	}

	void DeleteAll()
	{
		if (last)
		{
			ChainNode* first = last->link;
			ChainNode* now = first;
			do
			{
				ChainNode* next = now->link;
				delete now;
				now = next;
			} while (now != first);
			last = nullptr;
		}
	}

	void Merge(CircularList& right)
	{
		if (right.last == nullptr) return;
		if (last == nullptr)
		{
			last = right.last;
			right.last = nullptr;
		}

		ChainNode* leftFirst = last->link;
		ChainNode* rightFirst = right.last->link;

		ChainNode* leftNow = leftFirst;
		ChainNode* rightPrev = right.last;
		ChainNode* rightNow = rightFirst;
		do
		{
			ChainNode* leftNext = leftNow->link;
			ChainNode* rightNext = rightNow->link;
			if (rightNow != rightFirst) rightPrev->link = leftNow;
			leftNow->link = rightNow;

			rightPrev = rightNow;
			leftNow = leftNext;
			rightNow = rightNext;
		} while (leftNow != leftFirst && rightNow != rightFirst);

		if (rightNow != rightFirst) last = right.last;
		else rightPrev->link = leftNow;
		right.last = nullptr;
	}

	T min() const
	{
		if (last) {
			ChainNode* first = last->link;
			T nowMin = first->data;
			ChainNode* now = first;
			do
			{
				if (nowMin > now->data) nowMin = now->data;
				now = now->link;
			} while (now != first);
			return nowMin;
		}
		else
		{
			return T();
		}
	}


	T* ToArray()
	{
		if (last)
		{

			ChainNode* first = last->link;
			ChainNode* now = first;
			int len = Length();
			T* arr = new T[len];
			int nowIndex = 0;
			do
			{
				arr[nowIndex++] = now->data;
				now = now->link;
			} while (now != first);
			return arr;
		}
		else
		{
			return nullptr;
		}
	}

private:
	class ChainNode
	{
	public:
		T data;
		ChainNode* link;
		ChainNode(const T& data, ChainNode* link = nullptr) :data(data), link(link) {}
		friend class ChainIterator;
		friend ostream& operator<<(ostream& os, const CircularList<T>& list);
	};
	ChainNode* last;
};