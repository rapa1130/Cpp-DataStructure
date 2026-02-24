#pragma once
#include"Stack.h"
#include<map>
#include<string>


using namespace std;
bool IsOperand(char ch)
{
	return ch >= 'A' && ch <= 'Z';
}



std::map<char, int> icp;
std::map<char, int> isp;

string PostFix(const string& exp) {
	string postFixed;
	Stack<char> operatorStack;
	for (char token : exp)
	{
		if (IsOperand(token))
		{
			postFixed.push_back(token);
		}
		else if (token == ')')
		{
			for (; operatorStack.Top() != '('; operatorStack.Pop())
			{
				postFixed.push_back(operatorStack.Top());
			}
			operatorStack.Pop();
		}
		else 
		{
			if (!operatorStack.IsEmpty())
			{
				for (; isp[operatorStack.Top()] >= icp[token]; operatorStack.Pop())
				{
					postFixed.push_back(operatorStack.Top());
				}
			}
			operatorStack.Push(token);
		}
	}

	for (; !operatorStack.IsEmpty(); operatorStack.Pop())
	{
		postFixed.push_back(operatorStack.Top());
	}

	return postFixed;
}



int main() 
{	
	icp['*'] = isp['*'] = 7;
	icp['/'] = isp['/'] = 7;
	icp['+'] = isp['+'] = 6;
	icp['-'] = isp['-'] = 6;
	
	icp['>'] = isp['>'] = 5;
	icp['<'] = isp['<'] = 5;

	isp['('] = 0;
	icp['('] = 8;

	string exp = "A*(B+C)";
	cout<<PostFix(exp);
}