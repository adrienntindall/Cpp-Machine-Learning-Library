#include "NeuralNet.h"
#include "LinearRegression.h"
#include <iostream>

using namespace std;

int main() {
	const int len = 900;
	double* data = new double[len];
	for(int x = 0; x < len; x++) {
		data[x] = x + x%2;
	}
	Matrix m(3, 3, data);
	m.print();
	//std::cout << m.det();
	(m.inverse()*m).print();
}
