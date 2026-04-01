#pragma once
#include<iostream>
#include"../../03_StackAndQueue/03_2_Stack/Stack.h"
#include"../../03_StackAndQueue/03_3_Queue/Queue.h"
#include<queue>
using namespace std;

template<typename T>
class Tree;

template<typename T>
class TreeNode
{
    friend class Tree<T>;
    public:
        TreeNode(const T& data,TreeNode* leftLink = nullptr, TreeNode* rightLink = nullptr)
            :data(data),leftLink(leftLink),rightLink(rightLink) {}
        TreeNode()
            :leftLink(nullptr),rightLink(nullptr) {}
    private:
        T data;
        TreeNode* leftLink;
        TreeNode* rightLink;
};

template<typename T>
class Tree
{
    public:
        Tree() :root(nullptr) { 
            TreeNode<int>* now;
            now = root = new TreeNode<int>(1);
            now = now->leftLink = new TreeNode<int>(2);
            now = now->leftLink = new TreeNode<int>(3);
            now = now->leftLink = new TreeNode<int>(4);
            now = root->rightLink = new TreeNode<int>(5);
            now = now->rightLink = new TreeNode<int>(6);
        }

        class IteratorInOrder
        {
            public:
                IteratorInOrder(TreeNode<T>* start)
                    :now(start) {
                        Next();
                }
                IteratorInOrder(const IteratorInOrder& right)
                {
                    now = right.now;
                    nowRet = right.nowRet;
                    s = right.s;    
                }
                IteratorInOrder operator++()
                {
                    Next();
                    return *this;
                }
                IteratorInOrder operator++(int)
                {
                    IteratorInOrder ret(*this);
                    Next();
                    return ret;
                }
                T operator->()
                {
                    return nowRet->data;
                }

                bool operator==(const IteratorInOrder& right)
                {
                    return nowRet == right.nowRet; 
                }

                bool operator!=(const IteratorInOrder& right)
                {
                    return nowRet != right.nowRet; 
                }
            private:
                void Next() 
                {
                    while(now)
                    {
                        s.Push(now);
                        now = now->leftLink;
                    }
                    if(s.IsEmpty()) {
                        nowRet =nullptr; 
                        return;
                    }
                    now = s.Top();
                    nowRet = now;
                    s.Pop();
                    now = now->rightLink;
                }
                Stack<TreeNode<T>*> s;
                TreeNode<T>* now;
                TreeNode<T>* nowRet;
        };

        // TreeNode<T>* begin()
        // {
        //     return root;
        // }

        // TreeNode<T>* end()
        // {
        //     return nullptr;
        // }

        TreeNode<T>* begin()
        {
            return root;
        }

        TreeNode<T>* end()
        {
            return nullptr;
        }
        //전위 반복자
        class IteratorPreOrder
        {
            public:
                IteratorPreOrder(TreeNode<T>* start)
                    :now(start)
                {}
                IteratorPreOrder(const IteratorPreOrder& right)
                    :s(right.s), now(right.now)
                {}

                IteratorPreOrder operator++()
                {
                    Next();
                    return *this;
                }
                IteratorPreOrder operator++(int)
                {
                    IteratorPreOrder ret(*this);
                    Next();
                    return ret;
                }
                bool operator==(const IteratorPreOrder& right)
                {
                    return now == right.now;
                }
                bool operator!=(const IteratorPreOrder& right)
                {
                    return now != right.now;
                }
                T operator*()
                {
                    return now->data;
                }
            private:
                void Next()
                {
                    if(now == nullptr) return;
                    if(now->leftLink)
                    {
                        s.Push(now);
                        now = now->leftLink;
                    }
                    else if(now->rightLink)  now = now->rightLink;
                    else
                    {
                        while(!s.IsEmpty())
                        {
                            now = s.Top()->rightLink;
                            s.Pop();
                            if(now != nullptr) return;
                        }
                        now = nullptr;
                    }
                }
                TreeNode<T>* now;
                Stack<TreeNode<T>*> s;
        };

        //후위 반복자
        class IteratorPostOrder
        {
            public:
                IteratorPostOrder(TreeNode<T>* start)
                    :now(start),last(nullptr) 
                    {
                        Next();
                    }
                //==
                bool operator==(const IteratorPostOrder& right)
                {
                    return nowRet == right.nowRet;
                }
                //!=
                bool operator!=(const IteratorPostOrder& right)
                {
                    return nowRet != right.nowRet;
                }
                //++
                IteratorPostOrder operator++()
                {
                    Next();
                    return *this;
                }
                //++ int
                 IteratorPostOrder operator++(int)
                {
                    IteratorPostOrder ret(*this);
                    Next();
                    return ret;
                }
                IteratorPostOrder(const IteratorPostOrder& other)
                    :s(other.s),now(other.now),last(other.last),nowRet(other.nowRet)
                    {}
                //*
                T operator*()
                {
                    return nowRet->data;
                }

            private:
                void Next()
                {
                    while(true)
                    {
                        while(now)
                        {
                            s.Push(now);
                            now = now->leftLink;
                        }
                        if(s.IsEmpty())
                        {
                            nowRet = nullptr;
                            return;
                        }
                        nowRet = now = s.Top();

                        if(now->rightLink == nullptr || last == now->rightLink) 
                        {
                            last = now;
                            now = nullptr;
                            s.Pop();
                            return;
                        }
                        else now = now->rightLink;
                    }
                }
                TreeNode<T>* now;
                TreeNode<T>* last;
                TreeNode<T>* nowRet;
                Stack<TreeNode<T>*> s;
        };

        //레벨순서 반복자
        class IteratorLevelOrder
        {
            public:
                IteratorLevelOrder(TreeNode<T>* start)
                {
                    // q.PushBack(start);
                    if(start != nullptr) q.push(start);
                    Next();
                }
                IteratorLevelOrder(const IteratorLevelOrder& other)
                    :now(other.now), q(other.q) {}
                IteratorLevelOrder operator++()
                {
                    Next();
                    return *this;
                }
                IteratorLevelOrder operator++(int)
                {
                    IteratorLevelOrder ret(*this);
                    Next();
                    return ret;
                }
                bool operator==(const IteratorLevelOrder& right)
                {
                    return now == right.now;
                }
                bool operator!=(const IteratorLevelOrder& right)
                {
                    return now != right.now;
                }
                T operator*()
                {
                    return now->data;
                }
            private:
                void Next()
                {
                    if(q.empty())
                    {
                        now = nullptr;
                        return;
                    }
                    now = q.front();
                    q.pop();
                    if(now->leftLink) q.push(now->leftLink);
                    if(now->rightLink)  q.push(now->rightLink);
                }
                TreeNode<T>* now;
                queue<TreeNode<T>*> q;
        };
    private:
        void Visit(TreeNode<T>* now) const
        {
            cout<<"now:"<<now->data<<endl;
        }
        TreeNode<T>* root;  
        
};

