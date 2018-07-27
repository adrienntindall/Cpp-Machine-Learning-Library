#ifndef LR_H
#define LR_H

#include "Matrix.h"

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
		void trian(Matrix X);
		void trainNormal(Matrix X);
		
		//Accessor Functions
		
		//Other Functions
		void initTheta(); //randomly initializes theta values
		Matrix h(Matrix X);
};

#endif /*LR_H*/