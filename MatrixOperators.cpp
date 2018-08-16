#include "Matrix.h"
#include <iostream>
#include <math.h>
#include <stdexcept>

namespace Metagross {
	Matrix& Matrix::operator=(const Matrix& m) {
		if(*this != m) {
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
		return *this;
		
	}
	
	Matrix Matrix::operator+(const Matrix& m) const {
		if(rows != m.rows || cols != m.cols) {
			std::cout << "Error: Can't add matrices of size " << rows << " x " << cols << " and " << m.rows << " x " << m.cols << std::endl;
			std::exit(EXIT_FAILURE);
		}
		double** temp = new double*[rows];
		for(int x = 0; x < rows; x++) {
			temp[x] = new double[cols];
			for(int y = 0; y < cols; y++) 
				temp[x][y] = values[x][y] + m.values[x][y];
		}
		return Matrix(rows, cols, temp);
	}

	Matrix Matrix::operator-(const Matrix& m) const {
		if(rows != m.rows || cols != m.cols) {
			std::cout << "Can't add matrices of size " << rows << " x " << cols << " and " << m.rows << " x " << m.cols << std::endl;
			std::exit(EXIT_FAILURE);
		}
		double** temp = new double*[rows];
		for(int x = 0; x < rows; x++) {
			temp[x] = new double[cols];
			for(int y = 0; y < cols; y++)
				temp[x][y] = values[x][y] - m.values[x][y];
		}
		return Matrix(rows, cols, temp);	
	}

	Matrix Matrix::operator*(const Matrix& m) const {
		if(cols != m.rows) {
			std::cout << "Can't multiply matrices of size " << rows << " x " << cols << " and " << m.rows << " x " << m.cols << std::endl;
			std::exit(EXIT_FAILURE);
		}
		double** temp = new double*[rows];
		for(int x = 0; x < rows; x++) {
			temp[x] = new double[m.cols];
			for(int y = 0; y < m.cols; y++) {
				temp[x][y] = 0;
				for(int z = 0; z < cols; z++) 
					temp[x][y] += values[x][z]*m.values[z][y];
			}
		}	
		return Matrix(rows, m.cols, temp);
	}
	
	//Element wise multiplication
	Matrix Matrix::operator&(const Matrix& m) const {
		if(rows == m.rows && cols == m.cols) {
			double** temp = new double*[rows];
			for(int x = 0; x < rows; x++) {
				temp[x] = new double[cols];
				for(int y = 0; y < cols; y++) {
					temp[x][y] = values[x][y] * m.values[x][y];
				}
			}
			return Matrix(rows, cols, temp);
		}
		else if(rows == m.rows && (cols == 1 && m.cols == 1)) {
			double** temp = new double*[rows];
			bool c = (cols == 1);
			for(int x = 0; x < rows; x++) {
				temp[x] = new double[c ? m.cols : cols];
				for(int y = 0; y < c ? m.cols : cols; y++) {
					temp[x][y] = values[x][c ? 0 : y] * m.values[x][c ? y : 0];
				}
			}
			return Matrix(rows, cols, temp);
		}
		else if((rows == 1 || m.rows == 1) && cols == m.cols) {
			bool r = (rows == 1);
			double** temp = new double*[r ? m.rows : rows];
			for(int x = 0; x < r ? m.rows : rows; x++) {
				temp[x] = new double[cols];
				for(int y = 0; y < cols; y++) {
					temp[x][y] = values[r ? 0 : x][y] * m.values[r ? x : 0][y];
				}
			}
			return Matrix(rows, cols, temp);
		}
		else if((rows == 1 && m.cols == 1) || (m.rows == 1 && m.cols == 1)) {
			bool r = (rows == 1);
			bool c = (cols == 1);
			double** temp = new double*[r ? m.rows : rows];
			for(int x = 0; x < r ? m.rows : rows; x++) {
				temp[x] = new double[c ? m.cols : cols];
				for(int y = 0; y < c ? m.cols : cols; y++) {
					temp[x][y] = values[r ? 0 : x][c ? 0 : y] * m.values[r ? x : 0][c ? y : 0];
				}
			}
			return Matrix(rows, cols, temp);
		}
		else {
			std::cout << "Error when doing element wise multiplication" << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}
	
	Matrix Matrix::operator+=(const Matrix& m) const {
		if(rows != m.rows || cols != m.cols) {
			std::cout << "Error: Can't add matrices of size " << rows << " x " << cols << " and " << m.rows << " x " << m.cols << std::endl;
			std::exit(EXIT_FAILURE);
		}
		double** temp = new double*[rows];
		for(int x = 0; x < rows; x++) {
			temp[x] = new double[cols];
			for(int y = 0; y < cols; y++) 
				temp[x][y] = values[x][y] + m.values[x][y];
		}
		return Matrix(rows, cols, temp);
	}
	
	Matrix Matrix::operator+(const int& m) const {
		double** temp = new double*[rows];
		for(int x = 0; x < rows; x++) {
			temp[x] = new double[cols];
			for(int y = 0; y < cols; y++)
				temp[x][y] = values[x][y] + m;
		}
		return Matrix(rows, cols, temp);
	}

	Matrix Matrix::operator-(const int& m) const {
		double** temp = new double*[rows];
		for(int x = 0; x < rows; x++) {
			temp[x] = new double[cols];
			for(int y = 0; y < cols; y++)
				temp[x][y] = values[x][y] - m;
		}
		return Matrix(rows, cols, temp);
	}

	Matrix Matrix::operator*(const int& m) const {
		double** temp = new double*[rows];
		for(int x = 0; x < rows; x++) {
			for(int y = 0; y < cols; y++)
				temp[x][y] = values[x][y] * m;
		}
		return Matrix(rows, cols, temp);
	}

	Matrix Matrix::operator/(const int& m) const {
		double** temp = new double*[rows];
		
		for(int x = 0; x < rows; x++) {
			for(int y = 0; y < cols; y++)
				temp[x][y] = values[x][y] / m;
		}
		return Matrix(rows, cols, temp);
	}

	Matrix Matrix::operator^(const int& m) const {
		Matrix ret = Matrix(rows, cols);
		for(int x = 0; x < rows; x++) {
			for(int y = 0; y < cols; y++) {
				ret.set(x, y, pow(values[x][y], m));
			}
		}
		return ret;
	}

	Matrix Matrix::operator+(const double& m) const {
		double** temp = new double*[rows];
		for(int x = 0; x < rows; x++) {
			temp[x] = new double[cols];
			for(int y = 0; y < cols; y++)
				temp[x][y] = values[x][y] + m;
		}
		return Matrix(rows, cols, temp);
	}

	Matrix Matrix::operator-(const double& m) const {
		double** temp = new double*[rows];
		for(int x = 0; x < rows; x++) {
			temp[x] = new double[cols];
			for(int y = 0; y < cols; y++)
				temp[x][y] = values[x][y] - m;
		}
		return Matrix(rows, cols, temp);
	}

	Matrix Matrix::operator*(const double& m) const {
		double** temp = new double*[rows];
		for(int x = 0; x < rows; x++) {
			temp[x] = new double[cols];
			for(int y = 0; y < cols; y++) 
				temp[x][y] = values[x][y] * m;
		}
		return Matrix(rows, cols, temp);
	}

	Matrix Matrix::operator/(const double& m) const {
		double** temp = new double*[rows];
		for(int x = 0; x < rows; x++) {
			temp[x] = new double[cols];
			for(int y = 0; y < cols; y++)
				temp[x][y] = values[x][y] / m;
		}
		return Matrix(rows, cols, temp);
	}

	Matrix operator+(const double& x, const Matrix&m) {
		return m + x;
	}

	Matrix operator-(const double& x, const Matrix&m) {
		return -m + x;
	}

	Matrix operator*(const double& x, const Matrix&m) {
		return m * x;
	}

	Matrix operator/(const double& x, const Matrix&m) {
		return m^(-1) * x;
	}

	Matrix Matrix::operator+(const float& m) const {
		double** temp = new double*[rows];
		for(int x = 0; x < rows; x++) {
			temp[x] = new double[cols];
			for(int y = 0; y < cols; y++) 
				temp[x][y] = values[x][y] + m;
		}
		return Matrix(rows, cols, temp);
	}

	Matrix Matrix::operator-(const float& m) const {
		double** temp = new double*[rows];
		for(int x = 0; x < rows; x++) {
			temp[x] = new double[cols];
			for(int y = 0; y < cols; y++) 
				temp[x][y] = values[x][y] - m;
		}
		return Matrix(rows, cols, temp);
	}

	Matrix Matrix::operator*(const float& m) const {
		double** temp = new double*[rows];
		for(int x = 0; x < rows; x++) {
			temp[x] = new double[cols];
			for(int y = 0; y < cols; y++)
				temp[x][y] = values[x][y] * m;
		}
		return Matrix(rows, cols, temp);
	}

	Matrix Matrix::operator/(const float& m) const {
		double** temp = new double*[rows];
		for(int x = 0; x < rows; x++) {
			temp[x] = new double[cols];
			for(int y = 0; y < cols; y++)
				temp[x][y] = values[x][y] / m;
		}
		return Matrix(rows, cols, temp);
	}

	Matrix Matrix::operator~() const {
		return Matrix(rows, cols, values).transpose();
	}

	Matrix Matrix::operator-() const {
		return Matrix(rows, cols, values) * -1;
	}
	
	bool Matrix::operator==(const Matrix& m) const {
		bool eq = true;
		while(eq) {
			for(int x = 0; x < rows; x++) {
				for(int y = 0; y < cols; y++) {
					if(values[x][y] == m.values[x][y]) continue;
					else eq = false;
				}
			}
			break;
		}
		return eq;
	}
	
	bool Matrix::operator!=(const Matrix& m) const {
		return !(*this==m);
	}
}