#include<iostream>
#include<vector>
#include<time.h>
#include<cstdlib>
#include<assert.h>
#include <iostream>
#include <random>
using namespace std;

struct city {
	int x;
	int y;
	city(int a, int b) {
		x = a;
		y = b;
	}
	city& operator=(const city& other) {
		if (this != &other) {
			x = other.x;
			y = other.y;
		}
		return *this;
	}
	void print() {
		cout << x << " " << y << endl;
	}
};

struct individual {
	vector<city> cities;
	individual() {
		city c(0, 0);
		cities.push_back(c);
	}
	individual(vector<city> vect) {
		for (int i = 0; i < vect.size(); i++) {
			cities.push_back(vect[i]);
		}
	}
	individual& operator=(const individual& other) {
		if (this != &other) {
			cities.clear();
			for (int i = 0; i < other.cities.size(); i++) {
				cities.push_back(other.cities[i]);
			}
		}
		return *this;
	}
	void print() {
		for (int i = 0; i < cities.size(); i++) {
			cities[i].print();
		}
		cout << endl;
	}
};

struct Hash {
	int index;
	double distance;
	Hash(int i, double d) {
		index = i;
		distance = d;
	}
	Hash& operator=(const Hash& other) {
		if (this != &other) {
			index = other.index;
			distance = other.distance;
		}
		return *this;
	}
	void print() {
		cout << index << ": " << distance << endl;
	}
};

struct Pair {
	individual i1;
	individual i2;
	Pair(individual ind1, individual ind2) {
		i1 = ind1;
		i2 = ind2;
	}
	Pair& operator=(const Pair& other) {
		if (this != &other) {
			i1 = other.i1;
			i2 = other.i2;
		}
		return *this;
	}
	void print() {
		cout << endl;
		i1.print();
		i2.print();
		cout << endl;
	}

};

bool member(int x, int y, vector<int> xs, vector<int> ys) {
	for (int i = 0; i < xs.size(); i++) {
		if (x == xs[i] && y == ys[i]) {
			return true;
		}
	}
	return false;
}

vector<city> generateCitiesCoordinates(int N, vector<int>& xs, vector<int>& ys) { //може да са нужни vector<int>&
	vector<city> cities;
	srand(time(0));
	for (int i = 0; i < N; i++) {
		int r1 = rand() % 1000;
		int r2 = rand() % 1000;
		while (member(r1, r2, xs, ys)) {
			//srand(time(0));
			r1 = rand() % 1000;
			r2 = rand() % 1000;
		}
		city c(r1, r2);
		cities.push_back(c);
		xs.push_back(r1);
		ys.push_back(r2);
	}
	return cities;
}

bool member2(int x, vector<int> xs) {
	for (int i = 0; i < xs.size(); i++) {
		if (x == xs[i]) {
			return true;
		}
	}
	return false;
}

individual generateRandomPath(vector<city> cities) {
	vector<city> path;
	vector<int> indexes;
	int randomIndex;
	srand(time(nullptr));
	for (int j = 0; j < cities.size(); j++) {
		//srand(time(nullptr));
		//default_random_engine generator;
		//uniform_int_distribution<int> distribution(0, cities.size() - 1);
		randomIndex = rand() % cities.size();
		//randomIndex = distribution(generator);
		while (member2(randomIndex, indexes)) {
			randomIndex = rand() % cities.size();
			//randomIndex = distribution(generator);
		}
		indexes.push_back(randomIndex);
		path.push_back(cities[randomIndex]);
	}
	individual ind(path);
	return ind;
}

vector<individual> create_first_population(vector<city> cities, int numberOfParents) {
	vector<individual> firstPopulation;
	for (int i = 0; i < numberOfParents; i++) {
		//srand(time(0));
		individual ind = generateRandomPath(cities);
		firstPopulation.push_back(ind);
	}
	return firstPopulation;
}

/*vector<individual> create_first_population(vector<city> cities, int numberOfParents) {

	vector<individual> firstPopulation;
	for (int i = 0; i < numberOfParents; i++) {
		vector<city> path;
		vector<int> indexes;
		int randomIndex;
		srand(time(0));
		for (int j = 0; j < cities.size(); j++) {
			default_random_engine generator;
			uniform_int_distribution<int> distribution(0, cities.size());
			//randomIndex = rand() % cities.size();
			randomIndex = distribution(generator);
			while (member2(randomIndex, indexes)) {
				//randomIndex = rand() % cities.size();
				randomIndex = distribution(generator);
			}
			indexes.push_back(randomIndex);
			path.push_back(cities[randomIndex]);
		}
		individual ind(path);
		firstPopulation.push_back(ind);
	}
	return firstPopulation;
}*/

double distanceBetweenCities(city c1, city c2) {
	return sqrt(pow(abs(c1.x - c2.x), 2) + pow(abs(c1.y - c2.y), 2));
}

double distanceForPath(individual individ) {
	double sum = 0.0;
	for (int i = 0; i < individ.cities.size() - 1; i++) {
		sum += distanceBetweenCities(individ.cities[i], individ.cities[i + 1]);
	}
	return sum;
}

vector<Hash> makeHash(vector<individual> population) {
	vector<Hash> vectorHash;
	for (int i = 0; i < population.size(); i++) {
		Hash h(i, distanceForPath(population[i]));
		vectorHash.push_back(h);
	}
	return vectorHash;
}

void selectionSort(vector<Hash>& vectorHash) {
	int min_idx;
	for (int i = 0; i < vectorHash.size() - 1; i++) {
		min_idx = i;
		for (int j = i + 1; j < vectorHash.size(); j++) {
			if (vectorHash[j].distance < vectorHash[min_idx].distance) {
				min_idx = j;
			}
		}
		swap(vectorHash[min_idx], vectorHash[i]);
	}
}

vector<individual> takeTheBestIndividuals(int percentage, vector<individual> population) {
	vector<individual> theBest;
	int numberOfIndividualsToTake = (percentage / 100)*(population.size());
	vector<Hash> populationHash = makeHash(population);
	selectionSort(populationHash);
	for (int i = 0; i < numberOfIndividualsToTake; i++) {
		theBest.push_back(population[populationHash[i].index]);
	}
	return theBest;
}

Pair cycleCrossover(Pair parents) {
	vector<city> citiesOfChild1;
	vector<city> citiesOfChild2;
	city c(0, 0);
	for (int i = 0; i < parents.i1.cities.size(); i++) {
		citiesOfChild1.push_back(c);
		citiesOfChild2.push_back(c);
	}

	vector<int> takenIndexes;
	while (takenIndexes.size() != parents.i1.cities.size()) {
		vector<city> vectorCities1, vectorCities2;
		int i = 0;
		while (!member2(i, takenIndexes)) {
			takenIndexes.push_back(i);
			city city1(parents.i1.cities[i].x, parents.i1.cities[i].y);
			citiesOfChild1[i] = city1;
			city city2(parents.i2.cities[i].x, parents.i2.cities[i].y);
			citiesOfChild2[i] = city2;
			for (int j = 0; j < parents.i1.cities.size(); j++) {
				if (parents.i1.cities[j].x == parents.i2.cities[i].x &&
					parents.i1.cities[j].y == parents.i2.cities[i].y) {
					i = j;
					break;
				}
			}
		}
		int a = 0;
		while (member2(a, takenIndexes) && a < parents.i1.cities.size()) {
			a++;
		}
		i = a;

		vector<city> vectorCities21, vectorCities22;
		while (!member2(i, takenIndexes)) {
			takenIndexes.push_back(i);
			city city1(parents.i1.cities[i].x, parents.i1.cities[i].y);
			citiesOfChild2[i] = city1;
			city city2(parents.i2.cities[i].x, parents.i2.cities[i].y);
			citiesOfChild1[i] = city2;
			for (int j = 0; j < parents.i1.cities.size(); j++) {
				if (parents.i1.cities[j].x == parents.i2.cities[i].x &&
					parents.i1.cities[j].y == parents.i2.cities[i].y) {
					i = j;
					break;
				}
			}
		}
	}
	individual child1(citiesOfChild1);
	individual child2(citiesOfChild2);
	Pair children(child1, child2);
	return children;
}

void mutation(Pair children) {
	srand(time(0));
	int randomIndex1 = rand() % children.i1.cities.size();
	int randomIndex2 = rand() % children.i1.cities.size();
	swap(children.i1.cities[randomIndex1], children.i1.cities[randomIndex2]);

	srand(time(0));
	int randomIndex3 = rand() % children.i1.cities.size();
	int randomIndex4 = rand() % children.i1.cities.size();
	swap(children.i2.cities[randomIndex3], children.i2.cities[randomIndex4]);
}



vector<individual> createNewPopulation(int percentage, vector<individual> population) {
	vector<individual> theBest = takeTheBestIndividuals(percentage, population);
	vector<individual> newGeneration;

	int sizeOfPopulation;
	if (population.size() % 2 == 0) sizeOfPopulation = population.size() / 2;
	if (population.size() % 2 == 1) sizeOfPopulation = population.size() / 2 + 1;

	for (int i = 0; i < sizeOfPopulation; i++) {
		int randomIndex1 = rand() % theBest.size();
		int randomIndex2 = rand() % theBest.size();
		while (randomIndex1 == randomIndex2) {
			randomIndex2 = rand() % theBest.size();
		}
		Pair parents(theBest[randomIndex1], theBest[randomIndex2]);
		Pair children = cycleCrossover(parents);
		mutation(children);
		newGeneration.push_back(children.i1);
		newGeneration.push_back(children.i2);
	}
	return newGeneration;
}

void evolve(int percentage, vector<individual>& population, int count) {
	if (count < 10) {
		vector<individual> newPopulation = createNewPopulation(percentage, population);
		//population.clear();
		for (int i = 0; i < newPopulation.size(); i++) {
			population.push_back(newPopulation[i]);
		}
		//population = newPopulation;
		vector<Hash> populationHash = makeHash(newPopulation);
		for (int i = 0; i < populationHash.size(); i++) {
			cout << endl;
			populationHash[i].print();
			cout << endl;
		}
		evolve(percentage, population, count++);
	}
}


int main() {
	int N;
	cout << "Enter N (number between 1 and 100) (number of cities): ";
	cin >> N;
	assert(N > 0 && N <= 100);
	vector<int> xs, ys;
	vector<city> cities = generateCitiesCoordinates(N, xs, ys);
	/*for (int i = 0; i < cities.size(); i++) {
		cities[i].print();
	}*/
	int firstPopulation_number;
	cout << "How many paths do you want to generate as a first population? : ";
	cin >> firstPopulation_number;

	//srand(time(0));
	vector<individual> firstPopulation = create_first_population(cities, firstPopulation_number);
	for (int i = 0; i < firstPopulation.size(); i++) {
		firstPopulation[i].print();
	}

	//vector<Hash> populationDistances(makeHash(firstPopulation));
	/*for (int i = 0; i < populationDistances.size(); i++) {
		populationDistances[i].print();
	}*/

	/*cout << "Enter percentage: ";
	int percentage;
	cin >> percentage;

	vector<individual> newGeneration = createNewPopulation(percentage, firstPopulation);

	for (int i = 0; i < newGeneration.size(); i++) {
		newGeneration[i].print();
	}*/

	/*evolve(percentage, newGeneration, 0);
	vector<Hash> populationHash = makeHash(newGeneration);
	selectionSort(populationHash);
	cout << endl;
	cout << "The minimum distance so far: ";
	cout << populationHash[0].distance;*/

	return 0;
}