#include "GeneticAlgorithm.h"
#include "MiscFunctions.h"

template <typename T>
GeneticAlgorithm<T>::GeneticAlgorithm() {
	indv = 0;
	isMax = true;
	gen = 0;
}

template <typename T>
GeneticAlgorithm<T>::GeneticAlgorithm(int popCnt) {
	indv = popCnt;
	pop = new T[indv];
	isMax = true;
	gen = 0;
}

template <typename T>
GeneticAlgorithm<T>::GeneticAlgorithm(int popCnt, T* popu) {
	indv = popCnt;
	pop = new T[indv];
	for(int x = 0; x < indv; x++) {
		pop[x] = popu[x];
	}
	isMax = true;
	gen = 0;
}

template <typename T>
GeneticAlgorithm<T>::GeneticAlgorithm(bool max) {
	isMax = max;
	indv = 0;
	gen = 0;
	indv = 0;
}

template <typename T>
GeneticAlgorithm<T>::GeneticAlgorithm(int popCnt, bool max) {
	isMax = max;
	indv = popCnt;
	gen = 0;
	pop = new T[indv];
}

template <typename T>
GeneticAlgorithm<T>::GeneticAlgorithm(int popCnt, T* popu, bool max) {
	indv = popCnt;
	pop = new T[indv];
	for(int x = 0; x < indv; x++) {
		pop[x] = popu[x];
	}
	isMax = max;
	gen = 0;
}

template <typename T>
GeneticAlgorithm<T>::~GeneticAlgorithm() {
	delete[] pop;
}

template <typename T>
T* GeneticAlgorithm<T>::mergeSort(T* list, int len){
	if(len == 1) return list;
	else if(len == 2) {
		T* ret = new T[2];
		ret[0] = min(list[0], list[1]);
		ret[1] = max(list[0], list[1]);
		delete[] list;
		return ret;
	}
	int len1 = len - len/2;
	int len2 = len - len1;
	T* l1 = new T[len1];
	for(int x = 0; x < len1; x++) {
		l1[x] = list[x];
	}
	T* l2 = new T[len2];
	for(int x = 0; x < len2; x++) {
		l2[x] = list[len1+x];
	}
	l1 = mergeSort(l1, len1);
	l2 = mergeSort(l2, len2);
	int n = 0;
	int m = 0;
	T* ret = new T[len];
	for(int x = 0; x < len; x++) {
		if(n == len1) {
			ret[x] = l2[m];
			m++;
		}
		else if(m == len2) {
			ret[x] = l1[n];
			n++;
		}
		else if(l1[n] > l2[m]) {
			ret[x] = l2[m];
			m++;
		}
		else {
			ret[x] = l1[n];
			n++;
		}
	}
	delete[] list;
	return ret;
}

template <typename T>
T GeneticAlgorithm<T>::min(T t1, T t2) {
	return t1.score > t2.score ? t2 : t1;
}

template <typename T>
T GeneticAlgorithm<T>::max(T t1, T t2) {
	return t1.score > t2.score ? t1 : t2;
}

template <typename T>
void GeneticAlgorithm<T>::shuffle(T* list, int len) {
	for(int x = 0; x < len; x++) {
		swap(std::rand()%len, std::rand()%len, list); 
	}
}

template<typename T>
void GeneticAlgorithm<T>::swap(int x, int y, T* list) {
	T temp = list[x];
	list[x] = list[y];
	list[y] = temp;
}

template <typename T>
void GeneticAlgorithm<T>::nextGen(double (*s)(T), T (*m)(T)) {;
	for(int x = 0; x < indv; x++) {
		pop[x].score = s(pop[x]);
	}
	shuffle(pop, indv);
	T* newGen = new T[indv];
	int curLim = indv;
	int n = 0;
	for(int x = 0; x < indv/2; x++) {
		int pos = std::rand()%curLim;
		T winner = pop[pos];
		for(int y = 0; y < indv/50; y++) {
			int tpos = std::rand()%curLim;
			winner = isMax ? max(winner, pop[tpos]):min(winner, pop[tpos]);
			if(pop[pos].score != pop[tpos].score) pos = tpos;
		}
		newGen[n] = m(winner);
		newGen[n+1] = m(winner);
		n+=2;
		swap(pos, curLim-1, pop);
		curLim--;
	}
	for(int x = 0; x < indv; x++) {
		pop[x] = newGen[x];
	}
	delete[] newGen;
}