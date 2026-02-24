#pragma once

#include<iostream>

using namespace std;

class SparseMatrix;
class MatrixTerm
{
public:
	MatrixTerm(const MatrixTerm& mt) :row(mt.row), col(mt.col), value(mt.value) {}
	MatrixTerm() : row(-1), col(-1), value(0) {}
	MatrixTerm(int row, int col, int value) : row(row), col(col), value(value) {}
private:
	friend ostream& operator<<(ostream& os, const SparseMatrix& sm);
	friend class SparseMatrix;
	int row, col, value;
};

class SparseMatrix
{
public:
	SparseMatrix(int rows, int cols);
	SparseMatrix(const SparseMatrix& right);
	SparseMatrix Transpose() const;
	SparseMatrix operator*(const SparseMatrix& right) ;
	SparseMatrix operator+(const SparseMatrix& right) const;
	void PushTerm(const MatrixTerm& term);
	friend ostream& operator<<(ostream& os, const SparseMatrix& sm);
private:
	MatrixTerm* sm;
	int rows, cols, terms, capacity;
};

SparseMatrix::SparseMatrix(int rows, int cols)
	:rows(rows), cols(cols), terms(0), capacity(4)
{
	sm = new MatrixTerm[capacity];
}

SparseMatrix::SparseMatrix(const SparseMatrix& right)
	:terms(right.terms), cols(right.cols), rows(right.rows), capacity(right.capacity)
{
	sm = new MatrixTerm[capacity];
	copy_n(right.sm, terms, sm);
}

SparseMatrix SparseMatrix::Transpose() const
{
	int* colCount = new int[cols] {0};
	for (int i = 0; i < terms; i++)
	{
		colCount[sm[i].col]++;
	}
	int* start = new int[cols];

	start[0] = 0;
	for (int i = 0; i < cols - 1; i++)
	{
		start[i + 1] = start[i] + colCount[i];
	}

	SparseMatrix transposed(cols, rows);
	transposed.capacity = capacity;
	transposed.sm = new MatrixTerm[capacity];
	transposed.terms = terms;

	for (int i = 0; i < terms; i++)
	{
		const MatrixTerm& nowTerm = sm[i];
		int nowStart = start[nowTerm.col]++;
		transposed.sm[nowStart] = MatrixTerm(nowTerm.col, nowTerm.row, nowTerm.value);
	}

	delete[] colCount;
	delete[] start;
	return transposed;
}

SparseMatrix SparseMatrix::operator*(const SparseMatrix& right)
{
	if (cols != right.rows)
	{
		cout << "left's row have to be equal right's col";
		return SparseMatrix(-1, -1);
	}
	SparseMatrix transposedRight = right.Transpose();
	SparseMatrix multiplied(rows, right.cols);

	transposedRight.PushTerm(MatrixTerm(right.cols, -1, 0));
	PushTerm(MatrixTerm(rows, 0, 0));

	int currRowBegin = 0;
	int currRowIndex = 0;
	int currRowLeft = sm[0].row;
	int sum = 0;
	while (currRowIndex < terms)
	{
		int currColIndex = 0;
		int currColRight = transposedRight.sm[0].row;

		while (currColIndex <= right.terms)
		{
			if (currRowLeft != sm[currRowIndex].row)
			{
				multiplied.PushTerm(MatrixTerm(currRowLeft, currColRight, sum));
				sum = 0;
				currRowIndex = currRowBegin;
				while (currColRight == transposedRight.sm[currColIndex].row)
				{
					currColIndex++;
				}
				currColRight = transposedRight.sm[currColIndex].row;
			}
			else if (currColRight != transposedRight.sm[currColIndex].row)
			{
				multiplied.PushTerm(MatrixTerm(currRowLeft, currColRight, sum));
				sum = 0;
				currRowIndex = currRowBegin;
				currColRight = transposedRight.sm[currColIndex].row;
			}
			else if (sm[currRowIndex].col < transposedRight.sm[currColIndex].col)
			{
				currRowIndex++;
			}
			else if (sm[currRowIndex].col == transposedRight.sm[currColIndex].col)
			{
				sum += sm[currRowIndex].value * transposedRight.sm[currColIndex].value;
				currRowIndex++;
				currColIndex++;
			}
			else // sm[currRowIndex].row > transposedRight.sm[currColIndex].row
			{
				currColIndex++;
			}
		}
		while (sm[currRowIndex].row == currRowLeft)
		{
			currRowIndex++;
		}
		currRowBegin = currRowIndex;
		currRowLeft = sm[currRowIndex].row;
	}

	return multiplied;
}

SparseMatrix SparseMatrix::operator+(const SparseMatrix& right) const
{
	if (rows != right.rows || cols != right.cols)
	{
		cout << "row and cols doesn't match when adding Matrix" << endl;
		return SparseMatrix(-1, -1);
	}

	SparseMatrix added(rows, cols);

	int nowLeft = 0;
	int nowRight = 0;
	while (nowLeft < terms && nowRight < right.terms)
	{
		const MatrixTerm& nowLeftTerm = sm[nowLeft];
		const MatrixTerm& nowRightTerm = right.sm[nowRight];
		if (nowLeftTerm.row > nowRightTerm.row)
		{
			added.PushTerm(MatrixTerm(nowRightTerm));
			nowRight++;
		}
		else if (nowLeftTerm.row < nowRightTerm.row)
		{
			added.PushTerm(MatrixTerm(nowLeftTerm));
			nowLeft++;
		}
		else if (nowLeftTerm.col > nowRightTerm.col)
		{
			added.PushTerm(MatrixTerm(nowRightTerm));
			nowRight++;
		}
		else if (nowLeftTerm.col < nowRightTerm.col)
		{
			added.PushTerm(MatrixTerm(nowLeftTerm));
			nowLeft++;
		}
		else
		{
			MatrixTerm addedTerm;
			addedTerm.row = nowLeftTerm.row;
			addedTerm.col = nowLeftTerm.col;
			addedTerm.value = nowLeftTerm.value + nowRightTerm.value;
			added.PushTerm(addedTerm);
			nowLeft++; nowRight++;
		}
	}
	while (nowLeft < terms)
	{
		added.PushTerm(sm[nowLeft++]);
	}
	while (nowRight < right.terms)
	{
		added.PushTerm(right.sm[nowRight++]);
	}

	return added;
}

void SparseMatrix::PushTerm(const MatrixTerm& term)
{
	if (term.value != 0)
	{
		if (terms == capacity) {
			capacity *= 2;
			MatrixTerm* temp = new MatrixTerm[capacity];
			copy(sm, sm + terms, temp);
			delete[] sm;
			sm = temp;
		}
		sm[terms++] = term;
	}
}

ostream& operator<<(ostream& os, const SparseMatrix& sm)
{

	int** toPrint = new int* [sm.rows];
	for (int i = 0; i < sm.rows; i++)
	{
		toPrint[i] = new int[sm.cols];
		fill_n(toPrint[i], sm.cols, 0);
	}

	for (int i = 0; i < sm.terms; i++)
	{
		const MatrixTerm& nowTerm = sm.sm[i];
		toPrint[nowTerm.row][nowTerm.col] = nowTerm.value;
	}
	for (int i = 0; i < sm.rows; i++)
	{
		for (int j = 0; j < sm.cols; j++) {
			os.width(5);
			os << toPrint[i][j] << " ";
		}
		os << endl;
	}

	return os;
}

