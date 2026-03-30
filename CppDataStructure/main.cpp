#include<iostream>
#include"05_Tree/05_03_TreeTravel/TreeRecTravelsal.h"
using namespace std;

int main()
{
	cout<<"C++ Compile succed"<<endl;
	Tree<int> t;
	cout<<"Hello"<<endl;
	t.InOrder_Iterative(); cout<<endl;
	t.PreOrder_Iterative(); cout<<endl;
	t.PostOrder_Iterative();
}