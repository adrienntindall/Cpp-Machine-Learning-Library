#include <math.h>
#include <algorithm>
#include "MiscFunctions.h"

namespace Metagross {
	double Matrix::sum() {
		double amnt = 0;
		for(int x = 0; x < rows; x++) {
			for(int y = 0; y < cols; y++) {
				amnt += values[x][y];
			}
		}
		return amnt;
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
	
	double sigmoid(double x) {
		return 1/(1 + exp(-x));
	}

	Matrix sigmoid(Matrix x) {
		x.map(sigmoid);
		return x;
	}
	
	double* randomize(int length) {
		double* r = new double[length];
		for(int x = 0; x < length; x++) {
			r[x] = (double)rand() / RAND_MAX;
		}
		return r;
	}
}