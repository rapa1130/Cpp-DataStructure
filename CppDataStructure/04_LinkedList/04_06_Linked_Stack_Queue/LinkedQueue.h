#pragma once
#include<iostream>
using namespace std;


template<typename T>
class Queue
{
    private:
        class ChainNode
            {
                public:
                T data;
                ChainNode* link;
                friend ostream& operator<<(ostream& os,const Queue<T>& queue);
                ChainNode():link(nullptr){}
                ChainNode(const T& data,ChainNode* link):data(data),link(link){}
            };
    public:
        Queue():front(nullptr),rear(nullptr) {}
        void Push(const T& e)
        {
            if(IsEmpty()) front = rear = new ChainNode(e,nullptr);
            else rear = rear->link = new ChainNode(e,nullptr);
        }
        void Pop()
        {
            if(IsEmpty()) throw "Cannot Pop Empty Queue";
            // if(front==rear)rear = nullptr;
            ChainNode* toDel = front;
            front = front->link;
            delete toDel;
        }
        T Front() const
        {
            return front->data;
        }
        T Rear() const
        {
            return rear->data;
        }
        int Count() const
        {
            int len = 0;
            for(ChainNode* now=front;now!=nullptr;now=now->link) len++;
            return len;
        }
        bool IsEmpty() const
        {
            return front==nullptr;
        }
        friend ostream& operator<<(ostream& os,const Queue<T>& queue)
        {
            for(ChainNode* now =queue.front;now!=nullptr;now=now->link)
            {
                os<<now->data<<" ";
            }
            os<<endl;
            return os;
        }
    private:
        ChainNode* front;
        ChainNode* rear;
};