#include<iostream>
#include"04_LinkedList/04_09_SparseMatrix/SparseMatrix.h"
using namespace std;

int main()
{	
	Matrix m1;
	cout<<"m1)"<<endl;
	cin>>m1;
	cout<<"m1_"<<endl<<m1<<endl;
	
	Matrix m2(m1);
	cout<<m2;
}