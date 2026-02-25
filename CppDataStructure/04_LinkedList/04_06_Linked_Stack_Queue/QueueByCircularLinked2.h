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
                ChainNode(const T& data,ChainNode* link = nullptr):data(data),link(link){}
                ChainNode():link(nullptr){}
                friend ostream& operator<<(ostream& os,const Queue<T>& queue);
        };
    public:
        Queue() :last(nullptr) {}
        void Push(const T& e)
        {
            if(last) last=last->link = new ChainNode(e,last->link);
            else
            {
                last = new ChainNode(e);
                last->link = last;
            }
        }
        void Pop()
        {
            if(IsEmpty()) throw "Cannot Pop Empty Queue";
            if(last == last->link)
            {
                delete last;
                last = nullptr;
            }
            else
            {
                ChainNode* first = last->link;
                last->link = first->link;
                delete first; 
            }
        }
         T Front() const
        {
            return last->link->data;
        }
        T Rear() const
        {
            return last->data;
        }
        bool IsEmpty() const
        {
            return last==nullptr;
        }
        int Count() const
        {
            if(!last) return 0;

            ChainNode* first = last->link;
            ChainNode* now= first;
            int len = 0;
            do
            {
                len++;
                now = now->link;
            } while (now != first);
            return len;
        }
        friend ostream& operator<<(ostream& os,const Queue<T>& queue)
        {
            if(!queue.last) return os;

            ChainNode* first = queue.last->link;
            ChainNode* now = first;
            do
            {
                os<<now->data<<" ";
                now = now->link;
            } while (now != first);
            os<<endl;
            return os;
        }
    private:
        ChainNode* last;

};