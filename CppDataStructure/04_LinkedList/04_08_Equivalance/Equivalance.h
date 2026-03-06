#include<iostream>
#include"../../03_StackAndQueue/03_2_Stack/Stack.h"
using namespace std;

class ENode
{
    private:
        int data;
        ENode* link;
        ENode(int data = -1,ENode* link = nullptr) :data(data),link(link){}
        friend void Equivalance();
};

void Equivalance()
{
    int n;
    cin>>n;    

    ENode** first = new ENode*[n];
    bool* out = new bool[n];
    fill(first,first+n,nullptr);
    fill(out,out+n,false);

    int r;
    cin>> r;
    int i,j;
    
    for(int k=0; k<r; k++)
    {
        cin>>i>>j;
        first[i] = new ENode(j,first[i]);
        first[j] = new ENode(i,first[j]);
    }


    for(int now=0; now < n; now++)
    {
        if(!out[now])
        {
            out[now] = true;
            ENode* x = first[now];
            stack<int> stk;
            cout<<endl<<now;

            while(true)
            {
                while(x != nullptr)
                {
                    int next = x->data;
                    if(!out[next])
                    {
                        out[next] = true;
                        cout<<", "<<x->data;
                        stk.push(x->data);
                    }
                    x = x->link;
                }
                if(stk.empty()) break;
                x = first[stk.top()];
                stk.pop();
            }
        }
    }

    for(int i = 0; i < n; i++)
    {
        while(first[i])
        {
            ENode* toDel = first[i];
            first[i] = first[i]->link;
            delete toDel;
        }
    }
    delete[] first;
    delete[] out;
    //동적 메모리 해제하기

}