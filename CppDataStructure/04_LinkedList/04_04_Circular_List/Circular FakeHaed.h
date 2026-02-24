#pragma once
#include<iostream>
using namespace std;

template<typename T>
class CircularList
{
private:
	class ChainNode
	{
	public:
		ChainNode(const T& data, ChainNode* link = nullptr) :data(data), link(link) {}
		ChainNode() :link(nullptr) {}
		T data;
		ChainNode* link;
		friend ostream& operator<<(ostream& os, const CircularList<T>& list);
	};
	ChainNode* header;
public:
	CircularList(){
		header = new ChainNode();
		header->link = header;
	}
	void PushFront(const T& data)
	{
		header->link = new ChainNode(data, header->link);
	}
	void PopFront()
	{
		if (IsEmpty()) throw "List is Empty";
		ChainNode* toDel = header->link;
		header->link = toDel->link;
		delete toDel;
	}
	bool IsEmpty() const
	{
		return header == header->link;
	}
	void Delete(int index)
	{
		int nowIndex = 0;
		ChainNode* now = header->link;
		ChainNode* prev = header;
		while (nowIndex < index && now != header)
		{
			nowIndex++;
			prev = now;
			now = now->link;
		}
		prev->link = now->link;
		delete now;
	}
	friend ostream& operator<<(ostream& os, const CircularList<T>& list)
	{
		for (ChainNode* now = list.header->link; now != list.header; now = now->link)
		{
			os << now->data << " ";
		}
		os << endl;
		return os;
	}

	void DeleteAll()
	{
		for (ChainNode* now = header->link; now != header;)
		{
			ChainNode* next = now->link;
			delete now;
			now = next;
		}
		header->link = header;
	}

	void Insert(const T& data, int index)
	{
		int nowIndex = 0;
		ChainNode* now = header->link;
		ChainNode* prev = header;
		while (now != header)
		{
			if (nowIndex == index)
			{
				prev->link = new ChainNode(data, now);
			}

			nowIndex++;
			prev = now;
			now = now->link;
		}
	}

	void Merge(CircularList<T>& right)
	{
		ChainNode* leftNow = header->link;
		ChainNode* rightNow = right.header->link;
		ChainNode* rightPrev = right.header;
		while (leftNow != header && rightNow != right.header)
		{
			ChainNode* leftNext = leftNow->link;
			ChainNode* rightNext = rightNow->link;
			leftNow->link = rightNow;
			if (rightPrev != right.header) rightPrev->link = leftNow;

			rightPrev = rightNow;
			leftNow = leftNext;
			rightNow = rightNext;
		}

		if (rightNow == right.header) {
			rightPrev->link = leftNow;
		}
		else {
			right.header->link = header->link;
			swap(header, right.header);
		}
		right.header->link = right.header;
	}

	int Count() const
	{
		int len = 0;
		for (ChainNode* now = header->link; now != header; now = now->link) len++;
		return len;
	}

	T Min() const
	{
		if (IsEmpty()) throw "There is no Node";
		T min = header->link->data;
		for (ChainNode* now = header->link; now != header; now = now->link)
		{
			if (min > now->data)
			{
				min = now->data;
			}
		}
		return min;
	}

	T* ToArray() const
	{
		int len = Count();
		T* arr = new T[len];
		int index = 0;
		for (ChainNode* now = header->link; now != header; now = now->link)
		{
			arr[index++] = now->data;
		}
		return arr;
	}

	void ArrangeMerge(CircularList<T>& right)
	{
		if (header == header->link)
		{
			swap(header, right.header);
			return;
		}
		if (right.header == right.header->link)
		{
			return;
		}
		
		ChainNode* leftNow = header->link;
		ChainNode* rightNow = right.header->link;
		ChainNode* mergedNow;
		bool bRightStart = false;

		if (leftNow->data > rightNow->data)
		{
			mergedNow = rightNow;
			rightNow = rightNow->link;
			bRightStart = true;
		}
		else
		{
			mergedNow = leftNow;
			leftNow = leftNow->link;
		}

		while (leftNow != header && rightNow != right.header)
		{
			if (leftNow->data > rightNow->data)
			{
				mergedNow = mergedNow->link = rightNow;
				rightNow = rightNow->link;
			}
			else
			{
				mergedNow = mergedNow->link = leftNow;
				leftNow = leftNow->link;
			}
		}
		
		if (leftNow == header) mergedNow->link = rightNow;
		else mergedNow->link = leftNow;


		if ((leftNow == header && !bRightStart) || (rightNow == right.header && bRightStart))
		{
			swap(header->link, right.header->link);
		}
		if (leftNow == header)
		{
			swap(header, right.header);
		}


		right.header->link = right.header;
		
	}
};

