#pragma once
#include<iostream>
using namespace std;


class IntChainList
{
private:
	class ChainNode
	{
	public:
		ChainNode(int data = 0, ChainNode* link = nullptr) : data(data), link(link) {}
		friend ostream& operator<<(ostream& os, IntChainList& cl);
		int data;
		ChainNode* link;
	};
public:
	IntChainList() :first(nullptr) {}

	void Insert(int data, ChainNode* toInsert)
	{
		if (first == nullptr)
		{
			first = new ChainNode(data, nullptr);
		}
		else
		{
			toInsert->link = new ChainNode(data, toInsert->link);
		}
	}
	void PushFront(int data)
	{
		first = new ChainNode(data, first);
	}

	void Delete(ChainNode* before, ChainNode* toDelete = nullptr)
	{
		if (before != nullptr)
		{
			before->link = toDelete->link;
		}
		else
		{
			first = toDelete->link;
		}
		delete toDelete;
	}

	int Length() const
	{
		int len = 0;
		for (ChainNode* now = first; now != nullptr; now = now->link)
		{
			len++;
		}
		return len;
	}

	IntChainList& Merge(IntChainList& right)
	{
		ChainNode* leftNow = first;
		ChainNode* rightNow = right.first;
		IntChainList merged;
		merged.first = first;

		while (leftNow != nullptr && rightNow != nullptr)
		{
			ChainNode* leftNext = leftNow->link;
			ChainNode* rightNext = rightNow->link;
			leftNow->link = rightNow;
			if(leftNext != nullptr) rightNow->link = leftNext;
			leftNow = leftNext;
			rightNow = rightNext;
		}

		first = nullptr;
		right.first = nullptr;

		return merged;
	}

	IntChainList& ArrangeMerge(IntChainList& right)
	{
		IntChainList merged;
		ChainNode* leftNow = first;
		ChainNode* rightNow = right.first;
		ChainNode* mergedNow = nullptr;
		first = nullptr;
		right.first = nullptr;

		while (leftNow != nullptr && rightNow != nullptr)
		{
			if (leftNow->data < rightNow->data)
			{
				if (mergedNow) mergedNow = mergedNow->link = leftNow;
				else merged.first = mergedNow = leftNow;
				leftNow = leftNow->link;
			}
			else 
			{
				if (mergedNow) mergedNow = mergedNow->link = rightNow;
				else merged.first = mergedNow = rightNow;
				rightNow = rightNow->link;
			}
		}
		
		if (leftNow == nullptr)
		{
			mergedNow->link = rightNow;
		}

		if (rightNow == nullptr)
		{
			mergedNow->link = leftNow;
		}

		return merged;
	}
	friend ostream& operator<<(ostream& os, IntChainList& cl)
	{
		for (ChainNode* now = cl.first; now != nullptr; now = now->link)
		{
			os << now->data << " ";
		}
		os << endl;

		return os;
	}
private:
	ChainNode* first;
};