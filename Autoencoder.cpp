#include "Autoencoder.h"
#include <iostream>
#include <algorithm>

namespace Metagross {
	Autoencoder::Autoencoder() {
		encLayer = 1;
		layers = 3;
		int l[3] = {2, 1, 2};
		theta = new Matrix[layers-1];
		net = new Matrix[layers];
		for(int x = 0; x < layers-1; x++) {
			theta[x] = Matrix(l[x+1], l[x] + 1, randomize(l[x+1]*l[x]));
		}
		for(int x = 0; x < layers; x++) {
			net[x] = Matrix(l[x], 1);
		}
		lambda = 0;
	}
	
	Autoencoder::Autoencoder(std::string file) {
		
	}
	
	Autoencoder::Autoencoder(int layers, int* nodeAmt) {
		if(layers < 3) {
			std::cout << "Error: cannot make an auto encoder with less than 3 layers." << std::endl;
			exit(EXIT_FAILURE);
		}
		if(nodeAmt[0] != nodeAmt[layers-1]) {
			std::cout << "Error: cannot make an auto encoder that has inequal input and output sizes." << std::endl;
			exit(EXIT_FAILURE);
		}
		this->layers = layers;
		theta = new Matrix[layers-1];
		net = new Matrix[layers];
		for(int x = 0; x < layers-1; x++) {
			theta[x] = Matrix(nodeAmt[x+1], nodeAmt[x] + 1, randomize(nodeAmt[x+1]*nodeAmt[x]));
		}
		lambda = 0;
		encLayer = 1;
		int mn = nodeAmt[1];
		for(int x = 1; x < layers-1; x++) {
			if(std::min(mn, nodeAmt[x] != mn) {
				mn = nodeAmt[x];
				encLayer = x;
			}
		}
		for(int x = 0; x < layers; x++) {
			net[x] = Matrix(nodeAmt[x], 1);
		}
	}
	
	~Autoencoder() {
		delete theta;
		delete net;
	}
	
	void Autoencoder::train(Matrix target) {
		if(target.getRows() != net[0].getRows()) {
			if(target.getCols() != net[0].getRows()) {
				std::cout << "Error: neither dimension of input matches the size of the input layer (auto encoder)." << std::endl;
				exit(EXIT_FAILURE);
			}
			else {
				target = ~target;
			}
		}
		for(int x = 0; x < target.getCols(); x++) {
			forwardPropagate(target.getCol(x));
			backPropagate(target.getCol(x));
		}
	}
	
	Matrix Autoencoder::encode(Matrix m) {
		
	}
	
	Matrix Autoencoder::decode(Matrix m) {
		
	}
}