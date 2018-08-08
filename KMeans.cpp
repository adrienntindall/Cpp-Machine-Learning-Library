#include <math.h>
#include <algorithm>
#include <iostream>
#include "KMeans.h"

namespace Metagross {
	KMeans::KMeans() {
		m = 0;
		c = 2;
		data = new point[0];
		clusters = new point[2];
	}

	KMeans::KMeans(int cA) {
		m = 0;
		c = cA;
		data = new point[0];
		clusters = new point[cA];
	}

	KMeans::KMeans(int amt, point* p) {
		m = amt;
		c = 2;
		data = new point[amt];
		for(int x = 0; x < amt; x ++) {
			data[x] = p[x];
		}
		clusters = new point[c];
		initClusters();
	}

	KMeans::KMeans(int amt, point* d, int clusterAmt) {
		m = amt;
		c = clusterAmt;
		data = new point[amt];
		for(int x = 0; x < amt; x ++) {
			data[x] = d[x];
		}
		clusters = new point[c];
		initClusters();
	}

	KMeans::~KMeans() {
		delete[] data;
		delete[] clusters;
	}

	void KMeans::add(point p) {
		point* temp = data;
		data = new point[m+1];
		for(int x = 0; x < m; x++) {
			data[x] = temp[x];
		}
		data[m] = p;
		m++;
		delete[] temp;
	}

	void KMeans::add(int amt, point* p) {
		point* temp = data;
		data = new point[m+amt];
		for(int x = 0; x < m; x++) {
			data[x] = temp[x];
		}
		for(int x = 0; x < amt; x++) {
			data[m+x] = p[x];
		}
		m += amt;
		delete[] temp;
	}

	void KMeans::setClusterAmt(int a) {
		c = a;
		delete[] clusters;
		clusters = new point[c];
	}

	void KMeans::initClusters() {
		double mn = 99999;
		double mx = -99999;
		for(int x = 0; x < m; x++) {
			mn = std::min(std::min(data[x].first, mn), data[x].second);
			mx = std::max(std::max(data[x].first, mx), data[x].second);
		}
		for(int x = 0; x < c; x++) {
			clusters[x].first = std::rand()*(mx-mn)/RAND_MAX + mn;
			clusters[x].second = std::rand()*(mx-mn)/RAND_MAX + mn;
		}
	}

	double KMeans::calcDist(point p1, point p2) {
		double x1 = p1.first;
		double x2 = p2.first;
		double y1 = p1.second;
		double y2 = p2.second;
		return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
	}

	point KMeans::getCentroid(int cNum) {
		if(c < cNum) {
			std::cout << "Error: trying to get the location of cluster " << cNum <<", but there are only " << c << " clusters." << std::endl;
			return clusters[0];
		}
		else if (cNum < 0) {
			std::cout << "Error: trying to get the location of cluster " << cNum <<", which is a negative number" << std::endl;
			return clusters[0];
		}
		return clusters[cNum];
	}

	point* KMeans::getCluster(int num) {
		int amt = 0;
		for(int x = 0; x < m; x++) {
			if(near[x] == num) amt++;
		}
		point* temp = new point[amt];
		int n = 0;
		for(int x = 0; x < m; x++) {
			if(near[x] == num) {
				temp[n] = data[x];
				n++;
			}
		}
		return temp;
	}

	void KMeans::train() {
		near = new int[m];
		bool cont = true;
		while(cont) {
			for(int x = 0; x < m; x++) {
				double minDist = calcDist(clusters[0], data[x]);
				int close = 0;
				for(int y = 1; y < c; y++) {
					double dist = calcDist(clusters[y], data[x]);
					if(dist < minDist) {
						close = y;
						minDist = dist;
					}
				}
				near[x] = close;
			}
			cont = false;
			for(int z = 0; z < c; z++) {
				double xDist = 0;
				double yDist = 0;
				int amt = 0;
				for(int a = 0; a < m; a++) {
					if(near[a] == z) {
						xDist += data[a].first;
						yDist += data[a].second;
						amt++;
					}
				}
				if(amt != 0) {
					xDist /= amt;
					yDist /= amt;
				}
				else {
					xDist = clusters[z].first;
					yDist = clusters[z].second;
				}
				if(!(xDist == clusters[z].first && yDist == clusters[z].second)) cont = true;
				clusters[z].first = xDist;
				clusters[z].second = yDist;
			}
		}
	}
}