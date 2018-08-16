#ifndef MATRIX_H
#define MATRIX_H

#include <string>

namespace Metagross {
	class Matrix {
		private:
			int rows;
			int cols;
			double** values;
			
		public:
			//Constructors
			Matrix();
			Matrix(int row, int col);
			Matrix(int row, int col, double* data);
			Matrix(int row, int col, double** data);
			Matrix(std::string file);
			
			//Copy constructor
			Matrix(const Matrix& m);
			
			//Destructor
			~Matrix();
			
			//Modifier functions
			Matrix set(int x, int y, double val);
			void iset(int x, int y, double val); //inplace set function
			void setRow(double* r, int loc);
			void setCol(double* c, int loc);
			void setRow(Matrix r, int loc);
			void setCol(Matrix c, int loc);
			void map(double (*f)(double));
			Matrix addRow(double* row, int loc);
			Matrix addCol(double* col, int loc);
			Matrix addRow(Matrix row, int loc);
			Matrix addCol(Matrix col, int loc);
			Matrix reshape(int row, int col); //Returns false if the matrix can't be reshapen
			
			//Accessor Functions
			int getRows();
			int getCols();
			double at(int x, int y);
			double* getRow(int x);
			double* getCol(int x);
			Matrix getRow(int start, int end);
			Matrix getCol(int start, int end);
			
			//Other Functions
			void print();
			void toFile(std::string file);
			bool isVector(); //Returns whether or not the matrix is a vector
			bool isSquare();
			double sum();
			double det();
			double trace();
			Matrix transpose();
			Matrix inverse();
			Matrix minor(int r, int c);
			Matrix diagonal();
			
			//Operators
			Matrix operator+(const Matrix& m) const;
			Matrix operator-(const Matrix& m) const;
			Matrix operator*(const Matrix& m) const;
			Matrix operator&(const Matrix& m) const; //Element wise multiplication
			
			Matrix operator+=(const Matrix& m) const;
			
			Matrix operator+(const int& x) const;
			Matrix operator-(const int& x) const;
			Matrix operator*(const int& x) const;
			Matrix operator/(const int& x) const;
			Matrix operator^(const int& x) const;
			
			Matrix operator+(const double& x) const;
			Matrix operator-(const double& x) const;
			Matrix operator*(const double& x) const;
			Matrix operator/(const double& x) const;
			
			Matrix operator+(const float& x) const;
			Matrix operator-(const float& x) const;
			Matrix operator*(const float& x) const;
			Matrix operator/(const float& x) const;
			
			Matrix operator~() const; //returns transpose
			Matrix operator-() const; //returns all values * -1
			
			bool operator==(const Matrix& m) const;
	};

	//More operators...
	Matrix operator+(const double& x, const Matrix&m);
	Matrix operator-(const double& x, const Matrix&m);
	Matrix operator*(const double& x, const Matrix&m);
	Matrix operator/(const double& x, const Matrix&m);
}
#endif /*MATRIX_H*/