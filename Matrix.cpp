#include "Matrix.h"
#include "MiscFunctions.h"
#include <iostream>
#include <math.h>
#include <fstream>

namespace Metagross {
	//Default constructor
	Matrix::Matrix() {
		rows = 1;
		cols= 1;
		values = new double*[rows];
		for(int x = 0; x < cols; x++) {
			values[x] = new double[cols];
		}
		values[0][0] = 0;
	}

	//Initializes Matrix as a row x col matrix with each cell containing the default value 0
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

	//Initializes Matrix as a row x col matrix with each cell containing values from unwrapped double* data
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

	//Initializes Matrix as a row x col matrix with corresponding values from data
	Matrix::Matrix(int row, int col, double** data) {
		values = data;
		rows = row;
		cols = col;	
	}

	//Read in a file made with Matrix.toFile()
	Matrix::Matrix(std::string file) {
		std::ifstream in;
		in.open(file);
		std::string temp;
		getline(in, temp, ' ');
		rows = std::stoi(temp);
		getline(in, temp, '\n');
		cols = std::stoi(temp);
		values = new double*[rows];
		for(int x = 0; x < rows; x++) {
			values[x] = new double[cols];
			for(int y = 0; y < cols; y++) {
				if(y != cols-1) getline(in, temp, ' ');
				else getline(in, temp, '\n');
				values[x][y] = std::stod(temp);
			}
		}
		in.close();
	}

	//Copy constructor
	Matrix::Matrix(const Matrix& m) {
		rows = m.rows;
		cols = m.cols;
		values = new double*[rows];
		for(int x = 0; x < rows; x++) {
			values[x] = new double[cols];
			for(int y = 0; y < cols; y++) {
				values[x][y] = m.values[x][y];
			}
		}
	}

	//Destructor
	Matrix::~Matrix() {
		delete[] values;
	}

	//Sets the value of cell (x, y) with val and returns the matrix
	Matrix Matrix::set(int x, int y, double val) {
		if(!(x < 0 || y < 0 || x >= rows || y >= cols)) {
			values[x][y] = val;
			return *this;
		}
		else {
			std::cout << "Error: position " << x << ", " << y << " is out of bounds of the matrix." << std::endl; 
			std::exit(EXIT_FAILURE);
		}
	}

	void Matrix::iset(int x, int y, double val) {
		if(!(x < 0 || y < 0 || x >= rows || y >= cols)) {
			values[x][y] = val;
		}
		else {
			std::cout << "Error: position " << x << ", " << y << " is out of bounds of the matrix." << std::endl; 
			std::exit(EXIT_FAILURE);
		}
	}
	
	//Sets the row at the specified position loc to the value contained in r
	void Matrix::setRow(double* r, int loc) {
		if(!(loc < 0 || loc >= rows))
			values[loc] = r;
		else {
			std::cout << "Error: trying to set row " << loc << " in matrix, which is out of bounds" << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}

	//Sets the column at the specified poisiton loc to the value contained in c
	void Matrix::setCol(double* c, int loc) {
		if(!(loc < 0 || loc >= cols))
			for(int x = 0; x < rows; x++) {
				values[x][loc] = c[x];
			}
		else {
			std::cout << "Error: trying to set column " << loc << " in matrix, which is out of bounds" << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}

	//Replaces a section of rows of the Matrix with m starting at loc
	void Matrix::setRow(Matrix m, int loc) {
		if(!(loc < 0 || loc+m.getRows() >= rows))
			for(int x = 0; x < m.getRows(); x++) {
				values[loc+x] = m.getRow(x);
			}
		else {
			std::cout << "Error: trying to set rows " << loc << " - " << loc+m.getRows() << " in matrix, which is out of bounds" << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}

	//Replaces a section of columns of the Matrix with m starting at loc
	void Matrix::setCol(Matrix m, int loc) {
		if(!(loc < 0 || loc+m.getCols() >= cols))
			for(int y = 0; y < m.getCols(); y++) {
				for(int x = 0; x < rows; x++) {
					values[x][y+loc] = m.at(x, loc);
				}
			}
		else {
			std::cout << "Error: trying to set columns " << loc << " - " << loc+m.getCols() << " in matrix, which is out of bounds" << std::endl;
			std::exit(EXIT_FAILURE);
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
		std::cout << std::endl;
		return Matrix(cols + 1, rows, newVal).transpose();
	}

	Matrix Matrix::addRow(Matrix m, int loc) {
		if(cols != m.getCols()) {
			std::cout << "Column mismatch when appending rows" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		else if(loc < 0 || loc > rows) {
			std::cout << "Trying to append row at position " << loc << ". Value is out of bound" << std::endl;
			std::exit(EXIT_FAILURE);
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
			std::exit(EXIT_FAILURE);
		}
		else if(loc < 0 || loc > rows) {
			std::cout << "Trying to append column at position " << loc << ". Value is out of bound" << std::endl;
			std::exit(EXIT_FAILURE);
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
			std::exit(EXIT_FAILURE);
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

	//Returns a matrix of the columns in the Matrix from start to end-1
	Matrix Matrix::getCol(int start, int end) {
		Matrix m = Matrix(getRows(), end-start);
		for(int x = start; x < end; x++) {
			m.setCol(getCol(x), x);
		}
		return m;
	}

	//Returns the value in the Matrix at the position (x, y)
	double Matrix::at(int x, int y) {
		if(x < 0 || y < 0 || x >= rows || y >= cols) {
			std::cout << "Error: position (" << x << ", " << y << ") is out of range of the matrix." << std::endl;
			std::exit(EXIT_FAILURE);
		}
		return values[x][y];
	}

	//Prints all the values in the Matrix
	void Matrix::print() {
		for(int x = 0; x < rows; x++) {
			for(int y = 0; y < cols; y++) {
				std::cout << values[x][y] << " ";
			}
			std::cout << std::endl;
		}	
	}

	//Exports the matrix to a readable file with the name "Filename"
	void Matrix::toFile(std::string fname) {
		std::ofstream out;
		out.open(fname);
		out << rows << ' ' << cols << std::endl;
		for(int x = 0; x < rows; x++) {
			for(int y = 0; y < cols; y++) {
				out << at(x, y) << ' ';
			}
			out << std::endl;
		}
		out.close();
	}

	//Returns whether or not the Matrix is a vector
	bool Matrix::isVector() {
		return (rows == 1 || cols == 1);
	}

	//Returns whether or not the Matrix is a square matrix
	bool Matrix::isSquare() {
		return (rows == cols);
	}

	//Returns the sum of all the values in the Matrix
	double sum(Matrix m) {
		double amnt = 0;
		for(int x = 0; x < m.getRows(); x++) {
			for(int y = 0; y < m.getCols(); y++) {
				amnt += m.at(x, y);
			}
		}
		return amnt;
	}

	//Returns the determinate of a square matrix
	double Matrix::det() {
		if(!isSquare()) {
			std::cout << "Error: cannot take the determinate of a non-square matrix." << std::endl;
			std::exit(EXIT_FAILURE);
		}
		if(rows < 2) {
			std::cout << "Error: cannot take the determinate of a 1 x 1 matrix." << std::endl;
			std::exit(EXIT_FAILURE);
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

	//Returns the trace of a square matrix
	double Matrix::trace() {
		if(!isSquare()) {
			std::cout << "Error: cannot take the trace of a non-square matrix." << std::endl;
			std::exit(EXIT_FAILURE);
		}
		if(rows < 2) {
			std::cout << "Error: cannot take the trace of a 1 x 1 matrix." << std::endl;
			std::exit(EXIT_FAILURE);
		}
		double t = 0;
		for(int x = 0; x < rows; x++) {
			t += at(x, x);
		}
		return t;
	}

	//Returns the transpose of the Matrix
	Matrix Matrix::transpose() {
		Matrix m = Matrix(cols, rows);
		for(int x = 0; x < rows; x++) {
			for(int y = 0; y < cols; y++) {
				m.set(y, x, values[x][y]);
			}
		}
		return m;
	}

	//Returns the inverse of the Matrix if it is square and if the determinate is not zero
	Matrix Matrix::inverse() {
		if(!isSquare()) {
			std::cout << "Error: cannot take the inverse of a non-square matrix." << std::endl;
			std::exit(EXIT_FAILURE);
		}
		double d = det();
		if(d == 0) {
			std::cout << "Error: cannot take the inverse of a matrix where the determinate is 0" << std::endl;
			std::exit(EXIT_FAILURE);
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


	//Returns the minor matrix of Matrix centered at position (row, col)
	Matrix Matrix::minor(int row, int col) {
		if(rows == 1 || cols == 1) {
			std::cout << "Error: trying to take the minor of a vector." << std::endl;
			std::exit(EXIT_FAILURE);
		}
		if(row < 0 || col < 0 || row >= rows || col >= cols) {
			std::cout << "Error: trying to take the minor centered at position (" << row << ", " << col << "), which is out of bounds" << std::endl;
			std::exit(EXIT_FAILURE);
		}
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
}