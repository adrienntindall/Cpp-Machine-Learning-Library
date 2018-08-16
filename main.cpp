#include "NeuralNet.h"
#include "LinearRegression.h"
#include "KMeans.h"
#include "GeneticAlgorithm.h"
#include "Autoencoder.h"
#include <iostream>
#include <math.h>
#include <time.h>
#include <ctime>
#include <chrono>

using namespace Metagross;

int main() {
	Matrix X = Matrix(2, 5000);
	Matrix y = Matrix(1, 5000);
	for(int x = 0; x < 5000; x++) {
		int a = rand()%2;
		int b = rand()%2;
		bool c = (a != b);
		X.set(0, x, double(a));
		X.set(1, x, double(b));
		y.set(0, x, double(c));
	}
	
	int l[] = {2, 1};
	NeuralNet nn = NeuralNet(2, l);
	
	nn.train(X, y);
	
	Matrix in(2, 1);
	Matrix out(1, 1);
	
	for(int x = 0; x < 9999; x++) {
		int a = rand()%2;
		int b = rand()%2;
		bool c = (a != b);
		in.set(0, 0, double(a));
		in.set(1, 0, double(b));
		out.set(0, 0, double(c));
		(nn.predict(in)-out).print();
	}
}
