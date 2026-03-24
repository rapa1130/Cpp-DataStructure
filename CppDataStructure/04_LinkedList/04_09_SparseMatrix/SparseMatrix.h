#include<iostream>
using namespace std;

struct Triple
{
    Triple(){}
    Triple(int row,int col, int val):row(row),col(col),val(val){}
    int row,col,val;
};

class Matrix;
class MatrixNode
{
        friend class Matrix;
        friend istream& operator>>(istream& is, Matrix& matrix);
        friend ostream& operator<<(ostream& is,const Matrix& matrix);
        friend Matrix operator+(const Matrix& left, const Matrix& right);
        friend Matrix operator*(const Matrix& left, const Matrix& right);
        friend MatrixNode* Advance(MatrixNode* now, MatrixNode* header);
        friend MatrixNode* AdvanceCol(MatrixNode* now,MatrixNode* header);
    public:
        MatrixNode(bool head,Triple* triple)
        {
            this->head = head;
            if(head)
            {
                down = right = next = this;
            }
            else
            {
                this->triple = *triple;
            }
        }
    private:
        bool head;
        MatrixNode* down;
        MatrixNode* right;
        union{
            Triple triple;
            MatrixNode* next;
        };
};

class Matrix
{
    public:
        friend istream& operator>>(istream& is, Matrix& matrix);
        friend ostream& operator<<(ostream& os, const Matrix& matrix);
        friend Matrix operator+(const Matrix& left, const Matrix& right);
        friend Matrix operator*(const Matrix& left, const Matrix& right);
        Matrix Transpose()
        {
            int p = max(header->triple.col,header->triple.row);
            MatrixNode** head = new MatrixNode*[p];
            for(int i=0; i<p; i++) head[i] = new MatrixNode(true,nullptr);
            
            MatrixNode* nodePtr = AdvanceCol(header->right,header);
            int currentRow = nodePtr->triple.col;
            MatrixNode* last = head[currentRow];

            while(nodePtr != header)
            {
                if(currentRow != nodePtr->triple.col)
                {
                    last->right = head[currentRow];
                    currentRow = nodePtr->triple.col;
                    last = head[currentRow];
                }
                Triple s = Triple(nodePtr->triple.col,nodePtr->triple.row,nodePtr->triple.val);
                last = last->right = new MatrixNode(false,&s);
                head[nodePtr->triple.row]->next = head[nodePtr->triple.row]->next->down = last; 

                nodePtr = AdvanceCol(nodePtr,header);
            }

            Matrix transposed;
            Triple t = Triple(header->triple.col,header->triple.row,header->triple.val);
            transposed.header = new MatrixNode(false,&t);

            last->right = head[currentRow];
            for(int i=0; i<p; i++) head[i]->next->down = head[i];
            for(int i=0; i<p-1; i++) head[i]->next = head[i+1];
            head[p-1]->next = transposed.header;
            transposed.header->right = head[0];
            delete[] head;

            return transposed;
        }
        Matrix(const Matrix& right)
        {
            Triple t = right.header->triple;
            int p = max(t.row,t.col);
            header = new MatrixNode(false,&t);
            if(p == 0) header->right = header;

            MatrixNode** head = new MatrixNode*[p];
            for(int i=0; i<p; i++) head[i] = new MatrixNode(true, nullptr);

            int currentRow = 0;
            MatrixNode* last = head[currentRow];
            MatrixNode* rightNow = Advance(right.header->right,right.header);

            while(rightNow != right.header)
            {
                if(currentRow != rightNow->triple.row)
                {
                    last->right = head[currentRow];
                    currentRow = rightNow->triple.row;
                    last = head[currentRow];
                }
                Triple s = rightNow->triple;
                last = last->right = new MatrixNode(false,&s);
                head[rightNow->triple.col]->next = head[rightNow->triple.col]->next->down = last;
                rightNow = Advance(rightNow,right.header);
            }

            last->right = head[currentRow];
            for(int i=0; i<p; i++) head[i]->next->down = head[i];
            for(int i=0; i<p-1; i++) head[i]->next = head[i+1];
            head[p-1]->next = header;
            header->right = head[0];
            delete[] head;
        }
        Matrix(){}
        void PrintInfo()
        {
            cout<<"rows:"<<header->triple.row<<endl;
            cout<<"cols:"<<header->triple.col<<endl;
            cout<<"nums:"<<header->triple.val<<endl;
        }
        ~Matrix()
        {
            if(!header) return;
            MatrixNode* x = header->right;
            header->right = av;
            av = header;
            while(x != header)
            {
                MatrixNode* y = x->right;
                x->right = av;
                av = y;
                x = x->next;
            }
            header = nullptr;
        }

    private:
        MatrixNode* header;
        static MatrixNode* av;
};

MatrixNode* Matrix::av = nullptr;

ostream& operator<<(ostream& os, const Matrix& matrix)
{
    int row = matrix.header->triple.row;
    int col = matrix.header->triple.col;

    int** toPrint2D = new int*[row];
    for(int i=0;i<row;i++) toPrint2D[i] = new int[col];
    for(int i=0;i<row;i++) fill_n(toPrint2D[i],col,0);
    for(MatrixNode* nowHead = matrix.header->right; nowHead != matrix.header; nowHead = nowHead->next)
    {
        for(MatrixNode* now = nowHead->right;now!=nowHead;now=now->right)
        {
            toPrint2D[now->triple.row][now->triple.col] = now->triple.val;
            // os<<"r:"<<now->triple.row<<" c:"<<now->triple.col<<" v:"<<now->triple.val<<endl;
        }
    }
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            os<<toPrint2D[i][j]<<" ";
        }
        os<<endl;
    }
    return os;
}

istream& operator>>(istream& is, Matrix& matrix)
{
    Triple s;
    cin>>s.row>>s.col>>s.val;
    int p = max(s.row,s.col);
    matrix.header = new MatrixNode(false,&s);
    if(p==0)
    {
        matrix.header->right = matrix.header;
        return is;
    }
    MatrixNode** head = new MatrixNode*[p];
    for(int i = 0 ; i<p;i++)
    {
        head[i] = new MatrixNode(true, nullptr);
    }

    int currentRow = 0;
    MatrixNode* last = head[0];

    int r = s.val;

    for(int i = 0; i < r; i++)
    {
        Triple t;
        cin>>t.row>>t.col>>t.val;
        if(t.row > currentRow)
        {
            last->right = head[currentRow];
            currentRow = t.row;
            last = head[currentRow];
        }
        last = last->right = new MatrixNode(false,&t);
        head[t.col]->next= head[t.col]->next->down = last;
    }

    last->right = head[currentRow];
    for(int i = 0; i < p; i++) head[i]->next->down = head[i];
    for(int i = 0 ; i < p-1 ; i++)  head[i]->next = head[i+1];
    head[p-1]->next = matrix.header;
    matrix.header->right = head[0];
    delete[] head;

    return is;
}

MatrixNode* Advance(MatrixNode* now, MatrixNode* header)
{
    now = now->right;
    while(now->head)
    {
        if(now->next == header) return header;
        else now = now->next->right;
    }
    return now;
}

Matrix operator+(const Matrix& left, const Matrix& right)
{
    int leftRow = left.header->triple.row;
    int rightRow = right.header->triple.row;
    int leftCol = left.header->triple.col;
    int rightCol = right.header->triple.col;

    if(leftRow!= rightRow || leftCol!=rightCol)
    {
        throw "Cannot add diffetent row col matrix";
    }
    
    int p = max(leftRow,leftCol);
    MatrixNode** head=new MatrixNode*[p];
    for(int i = 0; i<p;i++)
    {
        head[i] = new MatrixNode(true,nullptr);
    }

    int currentRow = 0;
    MatrixNode* last = head[0];
    int elementCount = 0;

    MatrixNode* leftNow = left.header->right->right;
    MatrixNode* rightNow = right.header->right->right;
    while(leftNow != left.header && rightNow != right.header)
    {
        int leftRow = leftNow->triple.row;
        int rightRow = rightNow->triple.row;
        int leftCol = leftNow->triple.col;
        int rightCol = rightNow->triple.col;
        if(leftRow > rightRow || (leftRow == rightRow && leftCol > rightCol))
        {
            if(currentRow < rightNow->triple.row)
            {
                last->right = head[currentRow];
                currentRow = rightNow->triple.row;
                last = head[currentRow];
            }
            last = last->right = new MatrixNode(false,&rightNow->triple);
            head[rightNow->triple.col]->next = head[rightNow->triple.col]->next->down = last;
            rightNow = Advance(rightNow,right.header);
        }
        else if(leftRow < rightRow || (leftRow == rightRow && leftCol < rightCol))
        {
            if(currentRow < leftNow->triple.row)
            {
                last->right = head[currentRow];
                currentRow = leftNow->triple.row;
                last = head[currentRow];
            }
            last = last->right = new MatrixNode(false,&leftNow->triple);
            head[leftNow->triple.col]->next = head[leftNow->triple.col]->next->down = last;
            leftNow = Advance(leftNow,left.header);
        }
        else
        {
            if(currentRow < leftNow->triple.row)
            {
                last->right = head[currentRow];
                currentRow = leftNow->triple.row;
                last = head[currentRow];
            }
            Triple added;
            added.row = leftNow->triple.row;
            added.col = leftNow->triple.col;
            added.val = leftNow->triple.val + rightNow->triple.val;

            last = last->right = new MatrixNode(false,&added);
            head[added.col]->next = head[added.col]->next->down = last;

            leftNow = Advance(leftNow,left.header);
            rightNow = Advance(rightNow,right.header);
        }
        elementCount++;
    }
    while(leftNow != left.header)
    {
        if(currentRow < leftNow->triple.row)
        {
            last->right = head[currentRow];
            currentRow = leftNow->triple.row;
            last = head[currentRow];
        }
        last = last->right = new MatrixNode(false,&leftNow->triple);
        head[leftNow->triple.col]->next = head[leftNow->triple.col]->next->down = last;
        leftNow = Advance(leftNow,left.header);
        elementCount++;
    }
    while(rightNow != right.header)
    {
        if(currentRow < rightNow->triple.row)
        {
            last->right = head[currentRow];
            currentRow = rightNow->triple.row;
            last = head[currentRow];
        }
        last = last->right = new MatrixNode(false,&rightNow->triple);
        head[rightNow->triple.col]->next = head[rightNow->triple.col]->next->down = last;

        rightNow = Advance(rightNow,right.header);
        elementCount++;
    }

    last->right = head[currentRow];
    for(int i =0; i < p; i++) head[i]->next->down = head[i];
    for(int i =0; i<p-1 ; i++) head[i]->next = head[i+1];

    Matrix ret;
    Triple t = Triple(leftRow,leftCol,elementCount);
    ret.header = new MatrixNode(false,&t);
    ret.header->right = head[0];
    head[p-1]->next = ret.header;

    delete[] head;
    return ret;
}

MatrixNode* AdvanceCol(MatrixNode* now,MatrixNode* header)
{
    now = now->down;
    while(now->head)
    {
        if(now->next == header) return header;
        else now = now->next->down;
    }
    return now;
}

Matrix operator*(const Matrix& left, const Matrix& right)
{
    int leftRow = left.header->triple.row;
    int leftCol = left.header->triple.col;
    int rightRow = right.header->triple.row;
    int rightCol = right.header->triple.col;

    if(leftCol != rightRow)
    {
        throw "to multiply Matrix, Set same left col and right row";
    }

    int p = max(leftRow,rightCol);
    MatrixNode** head = new MatrixNode*[p];
    for(int i=0; i<p; i++) head[i] = new MatrixNode(true,nullptr);
    MatrixNode* leftRowPtr = Advance(left.header->right,left.header);
    int nowLeftRow = leftRowPtr->triple.row;
    MatrixNode* last;
    int numOfElement = 0;

    while(leftRowPtr != left.header)
    {
        int sum = 0;
        MatrixNode* leftRowBegin = leftRowPtr;
        MatrixNode* rightColPtr = AdvanceCol(right.header->right,right.header);
        int nowRightCol = rightColPtr->triple.col;
        nowLeftRow = leftRowPtr->triple.row;
        last = head[nowLeftRow];
        
        while(rightColPtr != right.header)
        {
            if(nowLeftRow != leftRowPtr->triple.row)
            {
                if(sum != 0)
                {
                    Triple t= Triple(nowLeftRow,nowRightCol,sum);
                    last = last->right = new MatrixNode(false,&t);
                    head[nowRightCol]->next = head[nowRightCol]->next->down = last;
                }

                leftRowPtr = leftRowBegin;
                while(rightColPtr != right.header && rightColPtr->triple.col == nowRightCol)  
                    rightColPtr = AdvanceCol(rightColPtr,right.header);
                if(rightColPtr != right.header) nowRightCol = rightColPtr->triple.col;
                sum = 0;
                numOfElement++;
            }
            else if(nowRightCol != rightColPtr->triple.col)
            {
                if(sum != 0)
                {
                    Triple t= Triple(nowLeftRow,nowRightCol,sum);
                    last = last->right = new MatrixNode(false,&t);
                    head[nowRightCol]->next = head[nowRightCol]->next->down = last;
                }
                leftRowPtr = leftRowBegin;
                nowRightCol = rightColPtr->triple.col;
                sum = 0;
                numOfElement++;
            }
            else if(leftRowPtr->triple.col > rightColPtr->triple.row)
            {
                rightColPtr = AdvanceCol(rightColPtr,right.header);
            }
            else if(leftRowPtr->triple.col < rightColPtr->triple.row)
            {
                leftRowPtr = Advance(leftRowPtr,left.header);
            }
            else //leftRowPtr->triple.row == rightColPtr->triple.col
            {
                sum += leftRowPtr->triple.val * rightColPtr->triple.val;
                leftRowPtr = Advance(leftRowPtr,left.header);
                rightColPtr = AdvanceCol(rightColPtr,right.header);              
            }
        }

        if(sum!=0)
        {
            Triple t= Triple(nowLeftRow,nowRightCol,sum);
            last = last->right = new MatrixNode(false,&t);
            head[nowRightCol]->next = head[nowRightCol]->next->down = last;
            numOfElement++;
        }
        
        last->right = head[nowLeftRow];

        while(leftRowPtr != left.header && nowLeftRow == leftRowPtr->triple.row)
        {
            leftRowPtr = Advance(leftRowPtr,left.header);
        }
        
    }

    Matrix ret;
    Triple t = Triple(leftRow,rightCol,numOfElement);
    ret.header = new MatrixNode(false,&t);
    ret.header->right = head[0];
    last->right = head[nowLeftRow];
    for(int i=0;i<p;i++) head[i]->next->down = head[i];
    for(int i=0;i<p-1;i++) head[i]->next = head[i+1];
    head[p-1]->next = ret.header;
    delete[] head;

    return ret;
}