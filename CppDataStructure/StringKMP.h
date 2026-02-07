#include<iostream>
using namespace std;



class String
{
public:
	String()
		:size(0), capacity(8)
	{
		arr = new char[capacity];
	}
	String(const char* charArr)
		:size(0), capacity(8)
	{
		arr = new char[capacity];
		for (int index = 0; charArr[index] != '\0'; index++)
		{
			PushBack(charArr[index]);
		}
	}
	String(const String& right)
		:size(right.size), capacity(right.capacity)
	{
		arr = new char[capacity];
		copy(right.arr, right.arr + right.size, arr);
	}
	String operator=(const String& right)
	{
		if (this == &right)
		{
			return *this;
		}
		capacity = right.capacity;
		size = right.size;
		arr = new char[capacity];
		copy_n(right.arr, right.size, arr);
		return *this;
	}
	void PushBack(char ch)
	{
		if (size == capacity)
		{
			capacity *= 2;
			char* temp = new char[capacity];
			copy(arr, arr + size, temp);
			delete[] arr;
			arr = temp;
		}
		arr[size++] = ch;
	}
	String Delete(int start, int length)
	{

	}
	friend ostream& operator<<(ostream& os, const String& str);
	String operator+(const String& right)
	{
		String added(*this);
		for (int i = 0; i < right.size; i++)
		{
			added.PushBack(right.arr[i]);
		}
		return added;
	}
	char& operator[](int index)
	{
		return arr[index];
	}
	char operator[](int index) const
	{
		return arr[index];
	}

	int* FailureFunction() const
	{
		int* failureFunc = new int[size];
		failureFunc[0] = -1;
		int i = -1;
		for (int j = 1; j < size; j++)
		{
			i = failureFunc[j - 1];
			if (arr[i + 1] == arr[j]) failureFunc[j] = i + 1;
			else {
				while (arr[i + 1] != arr[j] && i >= 0) i = failureFunc[i];
				failureFunc[j] = i;
			}
		}
		return failureFunc;
	}
	//find
	int Find(const String& pat)
	{
		int* f = pat.FailureFunction();
		int posP = 0;
		int posS = 0;
		int lengthP = pat.size;
		int lengthS = size;
		while (posP < lengthP && posS < lengthS)
		{
			if (arr[posS] == pat.arr[posP])
			{
				posP++; posS++;
			}
			else
			{
				if (posP == 0)
				{
					posS++;
				}
				else
				{
					posP = f[posP - 1] + 1;
				}
			}
		}
		if (posP < lengthP)
		{
			return -1;
		}
		else
		{
			return posS - lengthP;
		}
	}

	String SubStr(int start, int end)
	{
		String subStr;
		for (int i = start; i < end; i++) {
			subStr.PushBack(arr[i]);
		}
		return subStr;
	}

private:
	char* arr;
	int size;
	int capacity;
};

ostream& operator<<(ostream& os, const String& str)
{
	char* toPrint = new char[str.size + 1];
	copy(str.arr, str.arr + str.size, toPrint);
	toPrint[str.size] = '\0';
	os << toPrint;
	return os;
}
