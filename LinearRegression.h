#ifndef LR_H
#define LR_H

#include "Matrix.h"
#include "MiscFunctions.h"

class LinearRegression {
	private:
		int n;
		int m;
		double alpha;
		Matrix theta;
		
	public:
		//Constructors
		LinearRegression();
		LinearRegression(int features);
		LinearRegression(double alpha);
		LinearRegression(int features, double aplha);
		
		//Destructor
		~LinearRegression();
		
		//Modifier Functions
		void train(Matrix X, Matrix y);
		void train(Matrix X, Matrix y, double lambda);
		void trainNormal(Matrix X, Matrix y);
		void trainNormal(Matrix X, Matrix y, double lambda);
		
		//Accessor(?) Functions
		double test(Matrix X, Matrix y);
		Matrix predict(Matrix X);
		
		//Other Functions
		void initTheta(); //randomly initializes theta values
		Matrix h(Matrix X);
};

#endif /*LR_H*/