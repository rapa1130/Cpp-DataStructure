#pragma once
#include<iostream>
#include"../../04_LinkedList/04_04_Circular_List/CircularList.h"
using namespace std;

template<typename T>
class Queue
{
    public:
        Queue()
        {
            list = CircularList<T>();
        }
        void Push(const T& e)
        {
            list.PushBack(e);
        }
        void Pop()
        {
            list.PopFront();
        }
        bool IsEmpty() const
        {
            return list.IsEmpty();
        }
        int Count() const
        {
            return list.Length();
        }
        friend ostream& operator<<(ostream& os,const Queue<T> queue)
        {
            os<<queue.list;
            return os;
        }
    private:
        CircularList<T> list;
};