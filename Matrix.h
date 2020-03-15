#pragma once
#include<iostream>

class Matrix
{
	int dim;
	double **matrix;
public:
	Matrix(int _dim);
	~Matrix();
	Matrix(const Matrix& another_matrix);
	Matrix operator+ (const Matrix& another_matrix);
	Matrix operator* (const Matrix& another_matrix);
	Matrix &operator= (const Matrix& another_matrix);
	Matrix getSubmatrix(int a, int b);
	int Det();
	Matrix opposite();
	friend std::ostream& operator <<(std::ostream& out, const Matrix& m);
	friend std::istream& operator >>(std::istream& in, Matrix m);
	
};

