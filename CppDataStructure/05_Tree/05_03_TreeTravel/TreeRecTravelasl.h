#pragma once
#include<iostream>
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
        }
        //생성자
        //파괴자
        //전위
        void PreOrder() const
        {
            _preOrder(root);
        }
        //중위
        void PostOrder() const
        {
            _postOrder(root);
        }
        //후위
        void InOrder() const
        {
            _inOrder(root);
        }
    private:
        //visit
        void Visit(TreeNode<T>* now) const
        {
            cout<<now->data<<" ";
        }
        //postOrder_workhorse
        //inOrder_workhorse
        void _preOrder(TreeNode<T>* now) const
        {
            if(now)
            {
                Visit(now);
                _preOrder(now->leftLink);
                _preOrder(now->rightLink);
            }
        }
        void _inOrder(TreeNode<T>* now) const
        {
            if(now)
            {
                _inOrder(now->leftLink);
                _inOrder(now->rightLink);
                Visit(now);
            }
        }
        void _postOrder(TreeNode<T>* now) const
        {
            if(now)
            {
                _postOrder(now->leftLink);
                 Visit(now);
                _postOrder(now->rightLink);
            }
        }
        TreeNode<T>* root;  
};