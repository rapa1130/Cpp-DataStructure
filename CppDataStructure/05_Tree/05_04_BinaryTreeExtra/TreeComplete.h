#pragma once
#include<iostream>
using namespace std;

template<typename T>
class Tree;

template<typename T>
class TreeNode
{
    friend class Tree<T>;
    friend class TreeProposition;
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
        }
        //복사생성자
        Tree(const Tree<T>& other)
        {
            root = Copy(other.root);
        }
        //파괴자
        ~Tree()
        {
            Destroy(root);
        }

        //비교 오버로딩
        bool operator==(const Tree<T>& right)
        {
            return Equal(root,right.root);
        }

        Tree<T>& operator=(const Tree<T>& right)
        {
            if(this == &right) return *this;
            root = Copy(right.root);
            return *this;
        }

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
        //리프노드수
        int GetLeafs() const
        {
            return _getLeafs(root);
        }
        //SwapTree
        void SwapTree()
        {
            _swapTree(root);
        }
    protected:
        void _swapTree(TreeNode<T>* now)
        {
            if(now == nullptr) return;
            swap(now->leftLink,now->rightLink);
            _swapTree(now->leftLink);
            _swapTree(now->rightLink);
        }
        int _getLeafs(TreeNode<T>* now) const
        {
            if(now == nullptr) return 0;
            if(now->leftLink == nullptr && now->rightLink == nullptr) return 1;
            return _getLeafs(now->leftLink) + _getLeafs(now->rightLink);
        }
        void Destroy(TreeNode<T>* now)
        {
            if(now == nullptr) return;
            Destroy(now->leftLink);
            Destroy(now->rightLink);
            delete now;
        }
        bool Equal(TreeNode<T>* left, TreeNode<T>* right)
        {
            if(!left && !right) return true; 
            return
            left &&
            right &&
            left->data == right->data &&
            Equal(left->leftLink,right->leftLink) && 
            Equal(left->rightLink,right->rightLink);
        }

        TreeNode<T>* Copy(TreeNode<T>* now)
        {
            if(now == nullptr) return nullptr;
            return new TreeNode<T>(now->data,Copy(now->leftLink),Copy(now->rightLink));
        }
        virtual void Visit(TreeNode<T>* now) const
        {
            cout<<now->data<<" ";
        }
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