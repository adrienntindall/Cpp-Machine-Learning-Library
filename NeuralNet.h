#ifndef NN_H
#define NN_H

#include "Matrix.h"
#include <string>

namespace Metagross {
	class NeuralNet {
		protected:
			Matrix* net;
			Matrix* theta;
			int layers;
			double lambda;
			
		public:
			//Constructors
			NeuralNet();
			NeuralNet(std::string file);
			NeuralNet(int layers, int* nodeAmt);
			
			//Destructor
			~NeuralNet();
			
			//Modifier functions
			void forwardPropigate(Matrix X);
			void backPropigate(Matrix y);
			
			//Accessor Functions
			
			
			//Other functions
			void print();
			void save();
			void save(std::string file);
			double cost(Matrix X, Matrix y, int m);
			
			
	};
}
#endif /*NN_H*/