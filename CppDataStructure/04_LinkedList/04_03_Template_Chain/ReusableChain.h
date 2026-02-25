#pragma once
#include<iostream>
using namespace std;

template<typename T>
class ChainList
{
	private:
	class ChainNode
	{
	public:
		T data;
		ChainNode* link;
		ChainNode(const T& data, ChainNode* link = nullptr) :data(data), link(link) {}
		friend class ChainIterator;
	};
	ChainNode* first;
	ChainNode* last;
	friend ostream& operator<<(ostream& os, const ChainList<T>& chain);
public:
	class ChainIterator;
	ChainList() :first(nullptr),last(nullptr) {}

	void PushFront(const T& data)
	{
		if (first)
		{
			first = new ChainNode(data, first);
		}
		else
		{
			first = last = new ChainNode(data, nullptr);
		}
	}

	void PushBack(const T& data) 
	{
		if (last)
		{
			last = last->link = new ChainNode(data, nullptr);
		}
		else
		{
			first = last = new ChainNode(data, nullptr);
		}
	}

	friend ostream& operator<<(ostream& os, const ChainList<T>& chain)
	{
		for (ChainNode* now = chain.first; now != nullptr; now = now->link)
		{
			os << now->data << " ";
		}
		os << endl;
		return os;
	}
	
	void Reverse()
	{
		ChainNode* prev = nullptr;
		ChainNode* now = first;
		while (now != nullptr)
		{
			ChainNode* next = now->link;
			now->link = prev;
			prev = now;
			now = next;
		}
		swap(first, last);
	}

	//concatenate
	void Concatenate(ChainList<T>& right)
	{
		if (first)
		{
			last->link = right.first;
			last = right.last;
		}
		else
		{
			first = right.first;
			last = right.last;
		}
		right.last = nullptr;
		right.first = nullptr;
	}

	void PopFront()
	{
		if (first)
		{
			if (first == last)
			{
				delete first;
				first = last = nullptr;
			}
			else
			{
				ChainNode* second = first->link;
				delete first;
				first = second;
			}
		}
		else
		{
			throw "Cannot PopFrot Because Chain is Empty";
		}
	}
	void PopBack()
	{
		if (first)
		{
			ChainNode* prev = nullptr;
			for (ChainNode* now = first; now != last; now = now->link)
			{
				prev = now;
			}
			
			if (first == last)
			{
				delete last;
				first = last = nullptr;
			}
			else
			{
				delete last;
				last = prev;
				prev->link = nullptr;
			}
		}
		else
		{
			throw "Cannot PopBack Because Chain is Empty";
		}
	}

	T Front() const
	{
		return first->data;
	}

	T Back() const
	{
		return last->data;
	}

	T Get(int index) const
	{
		ChainNode* now = first;
		for (int i = 0; i < index; i++)
		{
			now = now->link;
		}
		return now->data;
	}

	~ChainList()
	{
		for (ChainNode* now = first; now != nullptr;)
		{
			ChainNode* next = now->link;
			delete now;
			now = next;
		}
	}

	void Insert(int index,const T& data)
	{
		ChainNode* now = first;
		ChainNode* prev = nullptr;
		for (int i = 0; i < index; i++)
		{
			prev = now;
			now = now->link;
		}
		if (prev == nullptr)
		{
			if (first) first = new ChainNode(data, first);
			else first = last = new ChainNode(data, nullptr);
		}
		else
		{
			prev->link = new ChainNode(data, now);
		}
	}


	void Delete(int index)
	{
		if (first == nullptr)
		{
			throw "Cannot Delete Because Chain is Empty";
		}
		ChainNode* now = first;
		ChainNode* prev = nullptr;
		for (int i = 0; i < index; i++)
		{
			prev = now;
			now = now->link;
		}
		if (prev == nullptr)
		{
			if (first->link) first = first->link;
			else first = last = nullptr;
			delete now;
		}
		else if (now == last)
		{
			prev->link = nullptr;
			last = prev;
			delete now;
		}
		else
		{
			prev->link = now->link;
			delete now;
		}
	}

	ChainIterator begin() const
	{
		return ChainIterator(first);
	}

	ChainIterator begin() 
	{
		return ChainIterator(first);
	}
	ChainIterator end()
	{
		return ChainIterator(nullptr);
	}
	ChainIterator end() const
	{
		return ChainIterator(nullptr);
	}

	//�迭 ����
	int Count() const
	{
		int len = 0;
		for (ChainNode* now = first; now != nullptr; now = now->link)
		{
			len++;
		}
		return len;
	}

	T* ToArray()
	{
		int len = Count();
		T* arr = new T[len];
		std::copy(this->begin(), this->end(), arr);
		return arr;
	}

	class ChainIterator
	{
	public:
		ChainIterator(ChainNode* start = nullptr) :current(start) {}
		T& operator*() const
		{
			return current->data;
		}
		T* operator->() const
		{
			return &current->data;
		}
		ChainIterator& operator++()
		{
			current = current->link;
			return *this;
		}

		ChainIterator operator++(int)
		{
			ChainIterator ret = ChainIterator(current);
			current = current->link;
			return ret;
		}

		bool operator==(const ChainIterator& right) const
		{
			return current == right.current;
		}
		bool operator!=(const ChainIterator& right) const
		{
			return current != right.current;
		}
	private:
		ChainNode* current;
	};

	


};

template<class Iterator>
auto FindMin(Iterator begin,Iterator end)
{
	auto min = *begin;
	for (Iterator iter = begin; iter != end; iter++)
	{
		if (*iter < min)
		{
			min = *iter;
		}
	}
	return min;
}



template<typename T, class Iterator>
T* ToArray(Iterator begin, Iterator end)
{
	int len = GetLength(begin, end);
	T* arr = new T[len];
	copy(begin,end, arr);
	return arr;
}

template<class Iterator>
int GetLength(Iterator begin, Iterator end)
{
	int len = 0;
	for (Iterator iter = begin; iter != end; iter++)
	{
		len++;
	}
	return len;
}

