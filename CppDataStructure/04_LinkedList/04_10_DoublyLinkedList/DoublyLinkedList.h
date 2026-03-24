#pragma once
#include<iostream>
using namespace std;

class DblList;

class DblListNode
{
    public:
        friend class DblList;
        friend ostream& operator<<(ostream& os,const DblList& list);

        DblListNode(int val, DblListNode* left = nullptr,DblListNode* right = nullptr)
            :left(left),right(right),val(val) {}
        DblListNode() {}
        DblListNode(DblListNode* left,DblListNode* right)
            :left(left),right(right) {}
    private:
        DblListNode* left;
        DblListNode* right;
        int val;
};

class DblList
{
    public:
        DblList()
        {
            first->left = first->right = first = new DblListNode();
        }

        friend ostream& operator<<(ostream& os,const DblList& list);
        
        void PushBack(int val)
        {
            first->left = first->left->right = new DblListNode(val,first->left,first);
        }
        void PushFront(int val)
        {
            first->right = first->right->left = new DblListNode(val,first,first->right);
        }
        void PopBack()
        {
            if(IsEmpty()) throw "Cannot PopBack Empty List";
            DblListNode* toDelete = first->left;
            first->left = toDelete->left;
            toDelete->left->right = first;
            delete toDelete;
        }
        void PopFront()
        {
            if(IsEmpty()) throw "Cannot PopBack Empty List";
            DblListNode* toDelete = first->right;
            first->right = toDelete->right;
            toDelete->right->left = first;
            delete toDelete;
        }

        bool IsEmpty() const
        {
            return first == first->left;
        }


        void Insert(DblListNode* prev, DblListNode* toInsert)
        {
            toInsert->left=prev;
            toInsert->right = prev->right;
            prev->right = prev->right->left = toInsert;
        }
        void Delete(DblListNode* toDel)
        {
            toDel->left->right = toDel->right;
            toDel->right->left = toDel->left;
            delete toDel;
        }
        int Length() const
        {
            int len = 0;
            for(DblListNode* now = first->right; now != first; now = now->right) len++;
            return len;
        }
        
        ~DblList()
        {
            DblListNode* now = first->right;
            for( ; now != first; )
            {
                DblListNode* next = now->right;
                delete now;
                now = next;
            }
            delete first;
        }
    private:
        DblListNode* first;
};

ostream& operator<<(ostream& os,const DblList& list)
{
    for(DblListNode* now = list.first->right; now!= list.first; now = now->right)
    {
        os<<now->val<<" ";
    }
    os<<endl;
    return os;
}