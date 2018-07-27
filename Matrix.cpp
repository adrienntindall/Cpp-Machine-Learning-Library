#include "Matrix.h"
#include <iostream>
#include <math.h>
#include <stdexcept>

Matrix::Matrix() {
	rows = 1;
	cols= 1;
	values = new double*[rows];
	for(int x = 0; x < cols; x++) {
		values[x] = new double[cols];
	}
	values[0][0] = 0;
}

Matrix::Matrix(int row, int col) {
	rows = row;
	cols = col;
	values = new double*[rows];
	for(int x = 0; x < rows; x++) {
		values[x] = new double[cols];
		for(int y = 0; y < cols; y++) {
			values[x][y] = 0;
		}
	}
}

Matrix::Matrix(int row, int col, double* data) {
	int n = 0;
	rows = row;
	cols = col;
	values = new double*[rows];
	for(int x = 0; x < rows; x++) {
		values[x] = new double[cols];
		for(int y = 0; y < cols; y++) {
			values[x][y] = data[n];
			n++;
		}
	}	
}

Matrix::Matrix(int row, int col, double** data) {
	values = data;
	rows = row;
	cols = col;	
}

Matrix::~Matrix() {
	delete[] values;
}

void Matrix::set(int x, int y, double val) {
	values[x][y] = val;
}

void Matrix::setRow(double* r, int loc) {
	values[loc] = r;
}

void Matrix::setCol(double* c, int loc) {
	for(int x = 0; x < rows; x++) {
		values[x][loc] = c[x];
	}
}

void Matrix::setRow(Matrix m, int loc) {
	for(int x = 0; x < m.getRows(); x++) {
		values[loc+x] = m.getRow(x);
	}
}

void Matrix::setCol(Matrix m, int loc) {
	for(int y = 0; y < m.getCols(); y++) {
		for(int x = 0; x < rows; x++) {
			values[x][y+loc] = m.at(x, loc);
		}
	}
}

void Matrix::map(double (*f)(double)) {
	for(int x = 0; x < rows; x++) {
		for(int y = 0; y < cols; y++) {
			values[x][y] = f(values[x][y]);
		}
	}
}

Matrix Matrix::addRow(double* r, int loc) {
	double** newVal = new double*[rows+1];
	int n = 0;
	for(int x = 0; x < rows + 1; x++) {
		newVal[x] = new double[cols];
		if(x == loc) {
			for(int y = 0; y < cols; y++) {
				newVal[x][y] = r[y];
			}
		}
		else {
			newVal[x] = values[n];
			n++;
		}
	}
	return Matrix(rows + 1, cols, newVal);
}

Matrix Matrix::addCol(double* c, int loc) {
	double** newVal = new double*[cols+1];
	int n = 0;
	for(int x = 0; x < cols + 1; x++) {
		newVal[x] = new double[rows];
		if(x == loc) {
			for(int y = 0; y < cols; y++) {
				newVal[x][y] = c[y];
			}
		}
		else {
			newVal[x] = getRow(n);
			n++;
		}
	}
	Matrix(cols + 1, rows, newVal).print();
	std::cout << std::endl;
	return Matrix(cols + 1, rows, newVal).transpose();
}

Matrix Matrix::addRow(Matrix m, int loc) {
	if(cols != m.getCols()) {
		std::cout << "Column mismatch when appending rows" << std::endl;
		return *this;
	}
	else if(loc < 0 || loc > rows) {
		std::cout << "Trying to append row at position " << loc << ". Value is out of bound" << std::endl;
	}
	int mLen = m.getRows();
	double** newVal = new double*[rows + mLen];
	int n = 0;
	int p = 0;
	for(int x = 0; x < rows + mLen; x++) {
		newVal[x] = new double[cols];
		if(x >= loc && x < loc+mLen) {
			newVal[x] = m.getRow(p);
			p++;
		}
		else {
			newVal[x] = values[n];
			n++;
		}
	}
	return Matrix(rows + mLen, cols, newVal);
}

Matrix Matrix::addCol(Matrix m, int loc) {
	if(rows != m.getRows()) {
		std::cout << "Row mismatch when appending columns" << std::endl;
		return *this;
	}
	else if(loc < 0 || loc > rows) {
		std::cout << "Trying to append row at position " << loc << ". Value is out of bound" << std::endl;
	}
	Matrix t = transpose();
	int mLen = m.getCols();
	double** newVal = new double*[cols + mLen];
	int n = 0;
	int p = 0;
	for(int x = 0; x < rows; x++) {
		newVal[x] = new double[rows];
		if(x >= loc && x < loc+mLen) {
			newVal[x] = m.getCol(p);
			p++;
		}
		else {
			newVal[x] = t.getRow(n);
			n++;
		}
	}
	return Matrix(cols + mLen, rows, newVal).transpose();
}

Matrix Matrix::reshape(int row, int col) {
	if(rows*cols != row*col) {
		std::cout << "Matrix of size " << rows*cols << " can not be reshapen to size " << row*col << std::endl;
		return *this;
	}
	else {
		double* temp = new double[rows*cols];
		int n = 0;
		for(int x = 0; x < rows; x++) {
			for(int y = 0; y < cols; y++) {
				temp[n] = values[x][y];
				n++;
			}
		}
		return Matrix(row, col, temp);
	}
}

int Matrix::getRows() {
	return rows;
}

int Matrix::getCols() {
	return cols;
}

double* Matrix::getRow(int x) {
	return values[x];
}

double* Matrix::getCol(int x) {
	double* data = new double[rows];
	for(int z = 0; z < rows; z++) {
		data[z] = at(z, x);
	}
	return data;
}

Matrix Matrix::getRow(int start, int end) {
	Matrix m = Matrix(end-start, getCols());
	for(int x = start; x < end; x++) {
		m.setRow(getRow(x), x);
	}
	return m;
}

Matrix Matrix::getCol(int start, int end) {
	Matrix m = Matrix(getRows(), end-start);
	for(int x = start; x < end; x++) {
		m.setCol(getCol(x), x);
	}
	return m;
}

double Matrix::at(int x, int y) {
	return values[x][y];
}

void Matrix::print() {
	for(int x = 0; x < rows; x++) {
		for(int y = 0; y < cols; y++) {
			std::cout << values[x][y] << " ";
		}
		std::cout << std::endl;
	}	
}

bool Matrix::isVector() {
	return (rows == 1 || cols == 1);
}

bool Matrix::isSquare() {
	return (rows == cols);
}

double Matrix::sum() {
	double amnt = 0;
	for(int x = 0; x < rows; x++) {
		for(int y = 0; y < cols; y++) {
			amnt += values[x][y];
		}
	}
	return amnt;
}

double sum(Matrix m) {
	double amnt = 0;
	for(int x = 0; x < m.getRows(); x++) {
		for(int y = 0; y < m.getCols(); y++) {
			amnt += m.at(x, y);
		}
	}
	return amnt;
}

double Matrix::det() {
	if(!isSquare()) {
		std::cout << "Error: cannot take the determinate of a non-square matrix." << std::endl;
		return 0;
	}
	if(rows == 2) {
		return at(0, 0)*at(1,1) - at(0, 1)*at(1, 0);
	}
	double d = 0;
	for(int x = 0; x < cols; x++) {
		d += pow(-1, x)*at(0, x)*(minor(0, x).det());
	}
	return d;
}

Matrix Matrix::transpose() {
	Matrix m = Matrix(cols, rows);
	for(int x = 0; x < rows; x++) {
		for(int y = 0; y < cols; y++) {
			m.set(y, x, values[x][y]);
		}
	}
	return m;
}

Matrix Matrix::inverse() {
	if(!isSquare()) {
		std::cout << "Error: cannot take the inverse of a non-square matrix." << std::endl;
		return *this;
	}
	double d = det();
	if(d == 0) {
		std::cout << "Error: cannot take the inverse of a matrix where the determinate is 0" << std::endl;
		return *this;
	}
	d = 1/d;
	Matrix m = Matrix(rows, cols);
	for(int x = 0; x < rows; x++) {
		for(int y = 0; y < cols; y++) {
			m.set(x, y, pow(-1, x+y)*minor(x, y).det()*d);
		}
	}
	return m.transpose();
}

Matrix Matrix::minor(int row, int col) {
	Matrix m = Matrix(rows-1, cols-1);
	for(int x = 0; x < m.getRows(); x++) {
		for(int y = 0; y < m.getCols(); y++) {
			int xval = (x < row) ? x : x + 1;
			int yval = (y < col) ? y : y + 1;
			m.set(x, y, at(xval, yval));
		}
	}
	return m;
}

Matrix identity(int size) {
	Matrix m = Matrix(size, size);
	for(int x = 0; x < size; x++) {
		m.set(x, x, 1);
	}
	return m;
}

Matrix log(Matrix m) {
	m.map(std::log);
	return m;
}

Matrix ones(int rows, int cols) {
	Matrix m = Matrix(rows, cols);
	return m+1;
}