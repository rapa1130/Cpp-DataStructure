#pragma once
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
        
        void NoStackInOrder()
        {
            TreeNode<T>* p,*q,*r,*r1,*top,*lastRight,*av;
            p = q = root;
            top = lastRight = nullptr;

            while(true)
            {
                while(true)
                {
                    if(!p->leftLink && !p->rightLink) // 말단노드
                    {
                        Visit(p);
                        break;
                    }
                    else if(!p->leftLink) // right 연결
                    {
                        Visit(p);
                        r = p->rightLink;
                        p->rightLink = q;
                        q = p;
                        p = r;
                    }
                    else // left 연결
                    {
                        r = p->leftLink;
                        p->leftLink = q;
                        q = p;
                        p = r;
                    }
                }
                av = p; 
                while(true)
                {
                    if(p == root) return;
                    if(!q->leftLink) // q -> p right를 통해 연결
                    {
                        r = q->rightLink;
                        q->rightLink = p;
                        p = q;
                        q = r;
                    }
                    else if(!q->rightLink) // q -> p left를 통해 연결
                    {
                        Visit(q);
                        r = q->leftLink;
                        q->leftLink = p;
                        p = q;
                        q = r;
                    }
                    else // 양방향
                    {
                        if(q == lastRight)
                        {
                            lastRight = top->rightLink;
                            r = top->leftLink;
                            top->leftLink = top->rightLink = nullptr;
                            top = r;

                            r = q->rightLink;
                            q->rightLink = p;
                            p = q;
                            q = r;
                        }
                        else
                        {
                            Visit(q);
                            av->leftLink = top;
                            av->rightLink = lastRight;
                            top = av;
                            lastRight = q;

                            r = q->leftLink;
                            q->leftLink = p;
                            p = q->rightLink;
                            q->rightLink = r;
                            break;
                        }
                    }
                }
            }
        }

    private:
        void Visit(TreeNode<T>* now) const
        {
            cout<<"now:"<<now->data<<endl;
        }
        TreeNode<T>* root;  
        
};

