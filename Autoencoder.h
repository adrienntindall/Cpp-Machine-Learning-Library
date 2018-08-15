#ifndef AE_H
#define AE_H

#include "Matrix.h"
#include "NeuralNet.h"

namespace Metagross {
	class Autoencoder : public NeuralNet{
		private:
			int encLayer;
			
		public:
			//Constructors
			Autoencoder();
			Autoencoder(std::string file);
			Autoencoder(int layers, int* nodeAmt);
			
			//Train function
			void train(Matrix target);
			
			//Encode/Decode Functions
			Matrix encode(Matrix m);
			Matrix decode(Matrix m);
	};
}

#endif /*AE_H*/