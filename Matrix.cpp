#include"Matrix.h"
#include <iostream>
#include "cmath"
#include <clocale>
using namespace std;


Matrix::Matrix(int _dim) {
	this->dim = _dim;
	this->matrix = new double*[dim];
	for (int i = 0; i < dim; i++) {
		this->matrix[i] = new double[dim];
	}
}
Matrix::Matrix(const Matrix& another_matrix) {
	this->dim = another_matrix.dim;
	this->matrix = new double*[dim];
	for (int i = 0; i < dim; i++) {
		this->matrix[i] = new double[dim];
	}
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			this->matrix[i][j] = another_matrix.matrix[i][j];
		}
	}
}
Matrix::~Matrix() {
	for (int i = 0; i < dim; i++)
		delete[] matrix[i];
	delete[] matrix;
}
Matrix Matrix::operator+ (const Matrix& another_matrix) {
	Matrix temp(dim);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			matrix[i][j] =this->matrix[i][j] + another_matrix.matrix[i][j];
		}
	}
	return *this;
}
Matrix Matrix::operator* (const Matrix& another_matrix) {
	Matrix temp(dim);
	double element = 0;
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			for (int k = 0; k < dim; k++) {
				element += another_matrix.matrix[k][j] * this->matrix[i][k];
			}
			temp.matrix[i][j] = element;
			element = 0;
		}
	}
	return temp;
}
Matrix& Matrix::operator= (const Matrix& another_matrix) {
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			this->matrix[i][j] = another_matrix.matrix[i][j];
		}
	}
	return *this;
}
Matrix Matrix::getSubmatrix(int exclusiveRow, int exclusiveColumn)
{
	double temp_dim = this->dim - 1;
	Matrix temp_matrix(temp_dim);
	int ki = 0;
	for (int i = 0; i < dim; i++) {
		if (i != exclusiveRow) {
			for (int j = 0, kj = 0; j < dim; j++) {
				if (j != exclusiveColumn) {
					temp_matrix.matrix[ki][kj] = this->matrix[i][j];
					kj++;
				}
			}
			ki++;
		}
	}
	return temp_matrix;
}
int Matrix::Det()
{
	int det = 0;
	int sign = 1;
	if (dim == 1)
		det = matrix[0][0];
	else if (dim == 2)
		det = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
	else {
		for (int i = 0; i < dim; i++) {
			int m = dim - 1;
			for (int j = 0; j < dim; j++) {
				
				Matrix temp_matrix(dim - 1);
				temp_matrix=getSubmatrix(i, j);
				det += sign * this->matrix[i][j] * temp_matrix.Det();
				sign = -sign;
				
			}
			sign = 1;
		}
	}
	return det;
}
Matrix Matrix::opposite() {
	
		Matrix opposite_matrix(dim);
		int sign;
		int thisDet = (*this).Det();
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {
				Matrix temp_matrix(dim - 1);
				temp_matrix = getSubmatrix(i, j);

				if ((i + j) % 2) { sign = -1; }
				else { sign = 1; }
				opposite_matrix.matrix[j][i] = sign * temp_matrix.Det() / thisDet;



			}
		}
		return opposite_matrix;
	
}
std::ostream& operator <<(std::ostream &out, const Matrix& m) {
	for (int i = 0; i < m.dim; i++) {
		for (int j = 0; j < m.dim; j++) {
			out << m.matrix[i][j] << " ";
		}
		out << "\n";
	}
	return out;
}
std::istream& operator >>(std::istream &in, Matrix m) {
	for (int i = 0; i < m.dim; i++) {
		for (int j = 0; j < m.dim; j++) {
			in >> m.matrix[i][j];
		}

	}
	return in;
}


