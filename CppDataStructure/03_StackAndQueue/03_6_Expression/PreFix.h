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

float EvalPrefix(const string& prefix)
{
	map<char, float> variables;
	
	for (int i = 0; i < prefix.size(); i++)
	{
		if (IsOperand(prefix[i]))
		{
			variables[prefix[i]] = 0.0f;
		}
	}
	for (auto iter = variables.begin(); iter != variables.end(); iter++)
	{
		cout << iter->first << ":";
		cin >> iter->second;
	}


	Stack<float> operands;
	for (int i = prefix.size() - 1; i >= 0; i--)
	{
		if (IsOperand(prefix[i]))
		{
			float value = variables[prefix[i]];
			operands.Push(value);
		}
		else
		{
			char oper = prefix[i];
			float firstOperand = operands.Top();
			operands.Pop();
			float secondOperand = operands.Top();
			operands.Pop();
			float result;
			switch (oper)
			{
			case '+':
				result = firstOperand + secondOperand;
				break;

			case '-':
				result = firstOperand - secondOperand;
				break;

			case '/':
				result = firstOperand / secondOperand;
				break;

			case '*':
				result = firstOperand * secondOperand;
				break;
			default:
				cout << "operator is not °¡°¨½ÂÁ¦" << endl;
			}
			operands.Push(result);
		}
	}
	return operands.Top();
}

string PreFix(const string& exp)
{
	string prefixed;

	prefixed.resize(exp.size());
	int nowIndex = exp.size() - 1;
	Stack<char> opStack;
	for (string::const_reverse_iterator expRiter = exp.rbegin(); expRiter != exp.rend(); expRiter++)
	{
		if (IsOperand(*expRiter))
		{
			prefixed[nowIndex--] = *expRiter;
		}
		else if (*expRiter == '(')
		{
			for (; opStack.Top() != ')'; opStack.Pop())
			{
				prefixed[nowIndex--] = opStack.Top();
			}
			opStack.Pop();
		}
		else 
		{
			for (; isp[opStack.Top()] > icp[*expRiter]; opStack.Pop())
			{
				prefixed[nowIndex--] = opStack.Top();
			}
			opStack.Push(*expRiter);
		}
	}
	
	while (!opStack.IsEmpty())
	{
		prefixed[nowIndex--] = opStack.Top();
		opStack.Pop();
	}
	
	int i;
	for (i = 0; prefixed[i] == 0; i++);
	return prefixed.substr(i);
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
	
	isp[')'] = 0;
	icp[')'] = 8;

	string exp = "A/B-C+D*E-A*C";
	string prefixed = PreFix(exp);
	cout << "Prefixed : " << prefixed << endl;
	float result = EvalPrefix(prefixed);
	cout << "result : " << result << endl;
}