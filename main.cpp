#include "NeuralNet.h"
#include "LinearRegression.h"
#include "KMeans.h"
#include "GeneticAlgorithm.h"
#include <iostream>
#include <math.h>
#include <time.h>

using namespace Metagross;

int main() {
	const int len = 1000000;
	double* data = new double[len];
	for(int x = 0; x < len; x++) {
		data[x] = x%18;
	}
	Matrix m(10, 2, data);
	(m+~m).print();
	
}
