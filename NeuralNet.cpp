#include "MiscFunctions.h"
#include "NeuralNet.h"
#include <math.h>
#include <iostream>

namespace Metagross {
	NeuralNet::NeuralNet() {
		layers = 2;
		theta = new Matrix[layers-1];
		net = new Matrix[2];
		theta[0] = Matrix(2, 1);
		net[0] = Matrix(2, 1);
		net[1] = Matrix(1, 1);
		lambda = 0;
		Delta = new Matrix[layers-1];
	}

	NeuralNet::NeuralNet(std::string file) {
		//reads in net size and node weights from file
	}

	NeuralNet::NeuralNet(int layers, int* nodeAmt) {
		this->layers = layers;
		net = new Matrix[layers];
		theta = new Matrix[layers];
		for(int x = 1; x < layers; x++) {
			theta[x-1] = Matrix(nodeAmt[x], nodeAmt[x-1] + 1, randomize(nodeAmt[x]*nodeAmt[x-1]));
		}
		for(int x = 0; x < layers; x++) {
			net[x] = Matrix(nodeAmt[x], 1);
		}
		lambda = 0;
	}

	NeuralNet::~NeuralNet() {
		delete theta;
		delete net;
		delete Delta;
	}

	void NeuralNet::forwardPropigate(Matrix X) {
		if(!(X.isVector())) {
			std::cout << "Error: trying to forward propagate a non vector. Maybe you meant to use train(Matrix X) instead?" << std::endl;
			exit(EXIT_FAILURE);
		}j
		if(X.getCols() != 1) {
			X = ~X;
		}
		if(X.getRows() != theta[0].getCols()) {
			std::cout << "Error: trying to forward propagate data that is " << X.getRows() << " in length, when it needs to be " << theta[0].getCols() << " in length." << std::endl;
			exit(EXIT_FAILURE);
		}
		for(int x = 0; x < layers-1; x++) {
			net[x] = X;
			X = (~sigmoid(X.addRow(ones(1, 1), 0)*theta[x]));
		}
		net[layers-1] = X;
	}

	void NeuralNet::backPropigate(Matrix y) {
		Matrix* delta = new Matrix[layers];
		delta[layers-1] = net[layers-1] - y;
		for(int x = layers-2; x > 0; x--) {
			delta[x] = (~theta[x]*delta[x+1]) & net[x] & (1 - net[x]);
		}
		for(int x = 0; x < layers-1; x++) {
			Delta[x] += delata[x+1]*~net[x];
		}
		
		delete delta;
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
		forwardPropigate(X);
		Matrix a = net[layers-1];
		for(int x = 0; x < layers; x++) {
			J = sum(-y&log(a) - (1 - y)&log(1-a))/m;
		
		}
		//fix & finish later
		return J;
	}
	
	Matrix NeuralNet::predict(Matrix X) {
		forwardPropigate(X);
		return net[layers-1];
	}
}