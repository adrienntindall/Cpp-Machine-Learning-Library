#include "NeuralNet.h"
#include "LinearRegression.h"
#include "KMeans.h"
#include "GeneticAlgorithm.h"
#include <iostream>
#include <math.h>

using namespace std;

int main() {
	const int len = 9;
	double* data = new double[len];
	for(int x = 0; x < len; x++) {
		data[x] = -x;
	}
	Matrix m(3, 3, data);
	m.print();
	m.toFile("m");
	Matrix n("m");
	n.print();
}
