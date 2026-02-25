#pragma once
#include"../04_04_Circular_List/Circular FakeHaed Last.h" 
#include<iostream>
using namespace std;


struct Term
{
    int coef;
    int exp;
    Term():exp(-1){}
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

        Polynomial(const Polynomial& right)
        {
            for(CircularList<Term>::Iterator iter = right.list.begin();iter!=right.list.end();iter++)
            {
                list.PushBack(Term(iter->coef,iter->exp));
            }
        }

        void AddTerm(int coef,int exp)
        {
            list.PushBack(Term(coef,exp));
        }
        
        float Eval(float x)
        {
            float ret = 0.0f;
            for(auto iter = list.begin();iter!=list.end();iter++)
            {
                ret += iter->coef * pow(x,iter->exp);
            }
            return ret;
        }

        Polynomial operator*(const Polynomial& right) const
        {
            Polynomial multiplied;

            for(auto liter=list.begin();liter!=list.end();liter++)
            {
                Polynomial temp;
                for(auto riter = right.list.begin();riter!=right.list.end();riter++)
                {
                    int exp = liter->exp + riter->exp;
                    int coef = liter->coef * riter->coef;
                    temp.AddTerm(coef,exp);
                }
                multiplied = temp + multiplied;
            }

            return multiplied;
        }
        Polynomial operator+(const Polynomial& right) const
        {
            Polynomial ret;
            CircularList<Term>::Iterator leftIter = list.begin();
            CircularList<Term>::Iterator rightIter = right.list.begin();
            while(true)
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
                    if(leftIter->exp == -1) return ret;
                    int addedCoef = leftIter->coef + rightIter->coef;
                    if(addedCoef) ret.AddTerm(addedCoef, leftIter->exp);
                    leftIter++;
                    rightIter++;
                }
            }
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
        CircularList<Term> list;
};