#include "Autoencoder.h"

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
		lambda = 0;
	}
	
	Autoencoder::Autoencoder(std::string file) {
		
	}
	
	Autoencoder::Autoencoder(int layers, int* nodeAmt) {
		
	}
	
	void Autoencoder::train(Matrix target) {
		
	}
	
	Matrix Autoencoder::encode(Matrix m) {
		
	}
	
	Matrix Autoencoder::decode(Matrix m) {
		
	}
}