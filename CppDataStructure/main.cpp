#include<iostream>
#include"05_Tree/05_03_TreeTravel/TreeIterator.h"
using namespace std;

int main()
{
	Tree<int> t;
	
	
	for(Tree<int>::IteratorLevelOrder iter(t.begin()); iter != t.end(); ++iter)
	{
		cout<<*iter<<" ";
	}
}