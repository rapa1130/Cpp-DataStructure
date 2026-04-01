#pragma once
#include<iostream>
#include"../../03_StackAndQueue/03_2_Stack/Stack.h"
#include"../../03_StackAndQueue/03_3_Queue/Queue.h"
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
            :leftLink(nullptr),rightLink(rightLink) {}
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
        //생성자
        //파괴자
        
        void InOrder_Iterative() const
        {
            Stack<TreeNode<T>*> s;
            TreeNode<T>* now = root;
            while(true)
            {
                while(now)
                {
                    s.Push(now);
                    now = now->leftLink;
                }
                if(s.IsEmpty()) return;
                now = s.Top();
                Visit(now);
                s.Pop();
                now = now->rightLink;
            }
        }
        
        void PostOrder_Iterative() const
        {
            Stack<TreeNode<T>*> s;
            TreeNode<T>* now = root;
            TreeNode<T>* last = nullptr;
            while(true)
            {
                while(now)
                {
                    s.Push(now);
                    now = now->leftLink;
                }
                if(s.IsEmpty()) return;
                
                now = s.Top();
                s.Pop();

                if(!now->rightLink)
                {
                    Visit(now);
                    last = now;
                    now = now->rightLink;
                }
                else if(now->rightLink == last)
                {
                    Visit(now);
                    last = now;
                    now = nullptr;
                }
                else if(now->rightLink != last)
                {
                    s.Push(now);
                    now = now->rightLink;
                }
            }
        }

        void PreOrder_Iterative() const
        {
            Stack<TreeNode<T>*> s;
            TreeNode<T>* now = root;
            while(true)
            {
                while(now)
                {
                    s.Push(now);
                    Visit(now);
                    now = now->leftLink;
                }
                if(s.IsEmpty()) return;
                now = s.Top();
                now = now->rightLink;
                s.Pop();
            }
        }

        void LevelOrder_Iterative() const
        {
            if(root == nullptr) return;
            Queue<TreeNode<T>*> q;
            q.PushBack(root);
            TreeNode<T>* now;
            while(!q.IsEmpty())
            {
                now = q.Front();
                Visit(now);
                q.PopFront();
                if(now->leftLink) q.PushBack(now->leftLink);
                if(now->rightLink) q.PushBack(now->rightLink);
            }
        }

    private:
        void Visit(TreeNode<T>* now) const
        {
            cout<<now->data<<" ";
        }
        TreeNode<T>* root;  
        
};