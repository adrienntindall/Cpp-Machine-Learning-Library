#ifndef KM_H
#define KM_H

#include <utility>
#include "Matrix.h"

typedef std::pair<double, double> point;

class KMeans {
	private:
		int m; //number of data points
		int c; //number of clusters
		int* near; //corresponds to the cluster index that the equivalently indexed data is referring to
		point* data; //coordinates of point locations
		point* clusters; //coordinates of cluster locations
		
	public:
		//Constructors
		KMeans();
		KMeans(int clusterAmt);
		KMeans(int amt, point* d);
		KMeans(int amt, point* d, int clusterAmt);
		
		//Destructor
		~KMeans();
		
		//Modifier Functions
		void add(point p);
		void add(int amt, point* p);
		void setClusterAmt(int c);
		void initClusters();
		
		//Accessors Functions
		point getCentroid(int cNum); //Gets the location of the cNumth cluster
		point* getCluster(int num); //Gets all points part of the numth cluster
		
		
		//Utility Functions
		double calcDist(point p1, point p2);
		
		//Model Functions
		void train();
		int predict(point p);
};

#endif /*KM_H*/