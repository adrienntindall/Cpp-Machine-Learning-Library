#ifndef GA_H
#define GA_H

template <typename T> //must have a memeber 'score'
class GeneticAlgorithm {
	private:
		bool isMax; //True if a higher score is better, false otherwise (default true)
		int gen; //Current generation
		int indv; //Amount of individuals in the population
		T* pop;
		
	public:
		//Constructors
		GeneticAlgorithm();
		GeneticAlgorithm(int popCnt);
		GeneticAlgorithm(int popCnt, T* pop);
		GeneticAlgorithm(bool max);
		GeneticAlgorithm(int popCnt, bool max);
		GeneticAlgorithm(int popCnt, T* pop, bool max);
		
		//Destructor
		~GeneticAlgorithm();
		
		//Modifier Functions
		
		//Typical Genetic Algorithm stuff
		void nextGen(double (*s)(T), T (*m)(T)); //Goes to the next generation with score function s and mutator function m
		
		//Misc. Functions
		void swap(int, int, T*);
		void shuffle(T*, int);
		T min(T t1, T t2);
		T max(T t1, T t2);
		T* mergeSort(T* list, int len);
		
		//Operators
		
		
};

#endif /*GA_H*/