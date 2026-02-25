#pragma once
#include<iostream>
using namespace std;

template<typename T>
class Stack
{
    private:
        class ChainNode
        {
            public:
            T data;
            ChainNode* link;
            friend ostream& operator<<(ostream& os,const Stack<T>& stack);
            ChainNode():link(nullptr){}
            ChainNode(const T& data,ChainNode* link):data(data),link(link){}
        };
    public:
        Stack() :top(nullptr) {}
        T Top() const
        {
            return top->data;
        }
        int Count() const
        {
            int len = 0;
            for(ChainNode* now = top;now!=nullptr;now=now->link) len++;
            return len;
        }
        void Push(const T& e)
        {
            top = new ChainNode(e,top);
        }
        bool IsEmpty() const
        {
            return top == nullptr;
        }
        void Pop()
        {
            if(IsEmpty()) throw "Empty Stack cannot be Poped";
        }
        friend ostream& operator<<(ostream& os,const Stack<T>& stack)
        {
            for(ChainNode* now = stack.top;now!=nullptr;now=now->link)
            {
                cout<<now->data<<" ";
            }
            cout<<endl;
            return os;
        }
    private:
        ChainNode* top;
};