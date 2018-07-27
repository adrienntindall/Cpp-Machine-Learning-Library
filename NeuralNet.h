#include "Matrix.h"
#include <string>

class NeuralNet {
	private:
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
		
		//Other functions
		void print();
		void save();
		void save(std::string file);
		double cost(Matrix X, Matrix y, int m);
		
		
};

double sigmoid(double x);
double* randomize(int length);