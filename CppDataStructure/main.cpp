#include<iostream>
#include"04_LinkedList/04_07_Polynomial/Polynomial_CircularList.h"
// #include"04_LinkedList/04_04_Circular_List/Circular FakeHaed Last.h"
using namespace std;


int main()
{
	Polynomial pol1;
	pol1.AddTerm(3,14);
	pol1.AddTerm(2,8);
	pol1.AddTerm(1,0);

	Polynomial pol2;
	pol2.AddTerm(8,14);
	pol2.AddTerm(-3,10);
	pol2.AddTerm(10,6);

	cout<<"pol1: "<<pol1<<endl;
	cout<<"pol2: "<<pol2<<endl;

	Polynomial added = pol1+pol2;
	Polynomial multipied = pol1*pol2;

	
	cout<<"added: "<<added<<endl;
	cout<<"multiplied: "<<multipied<<endl;

	cout<<"enter the value of 'x' : ";
	float x;
	cin>>x;
	cout<<"when x is "<<x<<" , pol1 value is "<<pol1.Eval(x)<<endl;

	
}