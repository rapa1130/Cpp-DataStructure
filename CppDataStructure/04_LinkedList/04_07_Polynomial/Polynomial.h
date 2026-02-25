#pragma once
#include"../04_03_Template_Chain/ReusableChain.h"
#include<iostream>
using namespace std;


struct Term
{
    int coef;
    int exp;
    Term(){}
    Term(int coef,int exp) : coef(coef),exp(exp){}
    void Set(int coef,int exp)
    {
        this->coef = coef;
        this->exp = exp;
    }
};

class Polynomial
{
    public:
        Polynomial(){}
        void AddTerm(int coef,int exp)
        {
            list.PushBack(Term(coef,exp));
        }
        Polynomial operator+(const Polynomial& right) const
        {
            Polynomial ret;
            ChainList<Term>::ChainIterator leftIter = list.begin();
            ChainList<Term>::ChainIterator rightIter = right.list.begin();
            while(leftIter != list.end() && rightIter != right.list.end())
            {
                if(leftIter->exp > rightIter->exp)
                {
                    ret.AddTerm(leftIter->coef,leftIter->exp);
                    leftIter++;
                }
                else if(leftIter->exp < rightIter->exp)
                {
                    ret.AddTerm(rightIter->coef,rightIter->exp);
                    rightIter++;
                }
                else // leftIter->exp == rightIter->exp
                {
                    int addedCoef = leftIter->coef + rightIter->coef;
                    ret.AddTerm(addedCoef, leftIter->exp);
                    leftIter++;
                    rightIter++;
                }
            }
            while(leftIter != list.end())
            {
                ret.AddTerm(leftIter->coef,leftIter->exp);
                leftIter++;
            }
            while(rightIter != right.list.end())
            {
                ret.AddTerm(rightIter->coef,rightIter->exp);
                rightIter++;
            }
            return ret;
        }
        friend ostream& operator<<(ostream& os, const Polynomial& poly)
        {
            for(auto iter=poly.list.begin();iter!=poly.list.end();)
            {
                os<<iter->coef<<"X^"<<iter->exp;
                iter++;
                if(iter!=poly.list.end()) os<<" + ";
            }
            return os;
        }

    private:
        ChainList<Term> list;
};