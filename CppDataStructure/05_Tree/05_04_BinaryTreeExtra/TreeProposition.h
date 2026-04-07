#pragma once
#include<iostream>
using namespace std;


class TreeProposition;

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
           // cout<<now->data<<" ";
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


enum Operator
{
    AND,
    OR,
    NOT,
    TRUE,
    FALSE
};

//template<>/
class TreeProposition : public Tree<pair<Operator,bool>>
{
    public:
        TreeProposition()
        {
            TreeNode<pair<Operator,bool>>* now;
            now = root = new TreeNode<pair<Operator,bool>>(pair<Operator,bool>(Operator::OR,false));
            now->leftLink = new TreeNode<pair<Operator,bool>>(pair<Operator,bool>(Operator::OR,false));
            now->rightLink = new TreeNode<pair<Operator,bool>>(pair<Operator,bool>(Operator::NOT,false));
            now->rightLink->rightLink = new TreeNode<pair<Operator,bool>>(pair<Operator,bool>(Operator::TRUE,true));
            
            now = now->leftLink;
            now->leftLink = new TreeNode<pair<Operator,bool>>(pair<Operator,bool>(Operator::AND,false));
            now->leftLink->leftLink = new TreeNode<pair<Operator,bool>>(pair<Operator,bool>(Operator::TRUE,true));
            now->leftLink->rightLink = new TreeNode<pair<Operator,bool>>(pair<Operator,bool>(Operator::NOT,false));
            now->leftLink->rightLink->rightLink = new TreeNode<pair<Operator,bool>>(pair<Operator,bool>(Operator::TRUE,false));

            now = now->rightLink = new TreeNode<pair<Operator,bool>>(pair<Operator,bool>(Operator::AND,false));
            now->rightLink = new TreeNode<pair<Operator,bool>>(pair<Operator,bool>(Operator::TRUE,false));
            now = now->leftLink = new TreeNode<pair<Operator,bool>>(pair<Operator,bool>(Operator::NOT,false));
            now->rightLink = new TreeNode<pair<Operator,bool>>(pair<Operator,bool>(Operator::TRUE,false));
        }
       
        void CalculateProposition()
        {
            _calculateProposition(root);
        }

        virtual void Visit(TreeNode<pair<Operator,bool>>* now) const override
        {
            switch (now->data.first)
            {
            case Operator::AND:
                cout<<"AND";
                break;
            case Operator::OR:
                cout<<"OR";
                break;
            case Operator::NOT:
                cout<<"NOT";
                break;
            case Operator::TRUE:
                cout<<"TRUE";
                break;
            case Operator::FALSE:
                cout<<"FALSE";
                break;
            default:
                break;
            }

            cout<<" | ";

            if(now->data.second)
            {
                cout<<"true";
            }
            else
            {
                cout<<"false";
            }
            cout<<endl;
        }
    private:
        void _calculateProposition(TreeNode<pair<Operator,bool>>* now)
        {
            if(!now) return;
            _calculateProposition(now->leftLink);
            _calculateProposition(now->rightLink); 

            switch (now->data.first)
            {
            case Operator::OR:
                now->data.second = now->leftLink->data.second || now->rightLink->data.second;
                break;
            case Operator::AND:
                now->data.second = now->leftLink->data.second && now->rightLink->data.second;
                break;
            case Operator::NOT:
                now->data.second = !now->rightLink->data.second;
                break;
            case Operator::TRUE:
                now->data.second = true;
                break;
            case Operator::FALSE:
                now->data.second = false;
                break;

            default:
                break;
            }
        }
};


//참값 생성 함수
//한 참값 리스트를 받아서 트리에 대해 진리값을 계산하는 알고리즘.