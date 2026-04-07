#include<iostream>
#include"05_Tree/05_04_BinaryTreeExtra/TreeProposition.h"
using namespace std;

int main()
{
	TreeProposition t;
	cout<<"Before Calculate)"<<endl;
	t.PreOrder();
	cout<<endl<<"After Calculate)"<<endl;
	t.CalculateProposition();
	t.PreOrder();
}