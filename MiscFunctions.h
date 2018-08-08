#ifndef MISC_FUNC_H
#define MISC_FUNC_H

#include <algorithm>
#include "Matrix.h"

namespace Metagross {
	//Misc. Matrix Functions
	double sum(Matrix m);
	Matrix identity(int size);
	Matrix log(Matrix m);
	Matrix ones(int rows, int cols);

	//Misc. math functions
	double sigmoid(double x);

	//Misc. utility functions
	double* randomize(int length);

}
#endif /*MISC_FUNC_H*/