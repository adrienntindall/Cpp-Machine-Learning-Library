#include "LinearRegression.h"

LinearRegression::LinearRegression() {
	m = 0;
	n = 2;
	initTheta();
}

LinearRegression::LinearRegression(int features) {
	m = 0;
	n = features;
	initTheat();
}

LinearRegression::LinearRegression(double a) {
	m = 0;
	n = 2;
	initTheat();
	alpha = a;
}

LinearRegression::LinearRegression(int f, double a) {
	m = 0;
	n = f;
	alpha = a;
	initTheat();
}

LinearRegression::~LinearRegression() {
	
}

void LinearRegression::train(Matrix X) {
	m = X.getRows();
	theta = theta - alpha/m*(h(X) - y) * X;
}

void LinearRegression::trainNormal(Matrix X) {
	theta = (~X*X).inverse() * ~X * ;
}

void LinearRegression::initTheta() {
	double* data = new double[n+1];
	for(int x = 0; x < n+1; x++) {
		data[x] = std::rand();
	}
	theta = Matrix(1, n+1, data);
}

Matrix LinearRegression::h(Matrix X) {
	return (theta*X);
}