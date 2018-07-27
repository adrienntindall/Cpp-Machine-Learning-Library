#include "NeuralNet.h"
#include <math.h>

NeuralNet::NeuralNet() {
	//default; creates 2 layer NN with 2 ins and 1 out
}

NeuralNet::NeuralNet(std::string file) {
	//reads in net size and node weights from file
}

NeuralNet::NeuralNet(int layers, int* nodeAmt) {
	
}

NeuralNet::~NeuralNet() {
	
}

void NeuralNet::forwardPropigate(Matrix X) {
	
}

void NeuralNet::backPropigate(Matrix y) {
	
}

void NeuralNet::print() {
	
}

void NeuralNet::save() {
	save("NeuralNet.txt");
}

void NeuralNet::save(std::string file) {
	
}

double NeuralNet::cost(Matrix X, Matrix y, int m) {
	//ak3 = sigmoid(Theta2*[ones(m, 1) sigmoid(Theta1*X')']')';
	//J = sum(sum(-y.*log(ak3)-(1-y).*log(1-ak3)))/m + lambda*(sum(sum(Theta1(:, 2:end).^2)) + sum(sum(Theta2(:, 2:end).^2)))/(2*m);
	double J = 0;
	Matrix a = X; //fix later; meant to be akl where l is the second to last layer
	for(int x = 0; x < layers; x++) {
		//J = sum(-y*log(a) + (1 - y)*log(1-a))/m;
	
	}
	return J;
}

double sigmoid(double x) {
	return 1/(1 + exp(-x));
}

double* randomize(int length) {
	double* r = new double[length];
	for(int x = 0; x < length; x++) {
		r[x] = rand();
	}
	return r;
}