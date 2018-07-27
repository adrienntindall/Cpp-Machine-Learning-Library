#ifndef MATRIX_H
#define MATRIX_H

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
		
		//Destructor
		~Matrix();
		
		//Modifier functions
		void set(int x, int y, double val);
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
		bool isVector(); //Returns whether or not the matrix is a vector
		bool isSquare();
		double sum();
		double det();
		Matrix transpose();
		Matrix inverse();
		Matrix minor(int r, int c);
		
		//Operators
		Matrix operator+(const Matrix& m) const;
		Matrix operator-(const Matrix& m) const;
		Matrix operator*(const Matrix& m) const;
		Matrix operator=(const Matrix& m) const;
		
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
};

double sum(Matrix m);
Matrix identity(int size);
Matrix log(Matrix m);
Matrix ones(int rows, int cols);

#endif /*MATRIX_H*/