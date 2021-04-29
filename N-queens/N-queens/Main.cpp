#include<iostream>
#include<vector>
#include<cstdlib>
#include<math.h>
#include<iomanip>
#include<chrono>
using namespace std;

bool onTheSameRow(int i1, int j1, int i2, int j2) {
	if (i1 == i2) {
		return true;
	}
	else {
		return false;
	}
}
bool onTheSameCol(int i1, int j1, int i2, int j2) {
	if (j1 == j2) {
		return true;
	}
	else return false;
}
bool onTheSameDiag(int i1, int j1, int i2, int j2) {
	if (abs(i1 - i2) == abs(j1 - j2)) {
		return true;
	}
	else {
		return false;
	}
}



int number_of_conflicts(int i1, int j1, int N, vector<int> places_queens) {
	int conflicts = 0;
	for (int i2 = 0; i2 < N; i2++) {
		int j2 = places_queens[i2];
		if (onTheSameCol(i1, j1, i2, j2)) conflicts++;
		if (onTheSameDiag(i1, j1, i2, j2)) conflicts++;
	}
	conflicts = conflicts - 2;
	return conflicts;
}



bool member(int r, vector<int> vect) {
	for (int i = 0; i < vect.size(); i++) {
		if (vect[i] == r) return true;
	}
	return false;
}

int main() {
	int N;
	std::cout << "Enter N: ";
	cin >> N;
	vector<int> cols;
	for (int i = 0; i < N; i++) {
		cols.push_back(0);
	}
	vector<int> diag1, diag2;
	for (int i = 0; i < 2 * N - 1; i++) {
		diag1.push_back(0);
		diag2.push_back(0);
	}
	vector<int> places_for_queens;
	for (int i = 0; i < N; i++) {

		int r = rand() % N;
		while (member(r, places_for_queens)) {

			r = rand() % N;
		}
		places_for_queens.push_back(r);
		cols[r]++;
		int diffij = i - r;
		int d1_index = diffij + N - 1;
		diag1[d1_index]++;
		int sumij = i + r;
		diag2[sumij]++;
	}
	/*std::cout << "Check: ";
	for (int i = 0; i < N; i++) {
		std::cout << places_for_queens[i] << " ";
	}
	std::cout << endl;*/

	/*vector<vector<int>> table(
		N,
		vector<int>(N)
	);*/


	/*for (int i = 0; i < N; i++) {
		int j = places_for_queens[i];
		int confl_ij = number_of_conflicts(i, j, N, places_for_queens);
		table[i][j] = confl_ij;
	}*/
	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << table[i][j];
		}
		cout << endl;
	}*/

	/*vector<int> vect_conflicts;
	for (int i = 0; i < N; i++) {
		int j = places_for_queens[i];
		int number_confl = number_of_conflicts(i, j, N, places_for_queens);
		vect_conflicts.push_back(number_confl);
	}*/






	unsigned long long t_beginning = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();


	int max = 1;
	int imax;
	int jmax;
	int jmin;
	int min;
	vector<int> vectMax;
	vector<int> vectMin;
	while (max != 0) {
		max = 0;
		imax = 0; jmax = 0;
		for (int i = 0; i < N; i++) {
			int j = places_for_queens[i];
			int d1 = i - j + N - 1;
			int d2 = i + j;
			int conflicts = cols[j] + diag1[d1] + diag2[d2] - 3;
			//int conflicts = vect_conflicts[i];
			//int conflicts = table[i][j];
			//int conflicts = number_of_conflicts(i, j, N, places_for_queens);
			if (conflicts > max) {
				max = conflicts;
				//imax = i;
				//jmax = j;
			}
		}
		if (max == 0) break;
		for (int i = 0; i < N; i++) {
			int j = places_for_queens[i];
			int d1 = i - j + N - 1;
			int d2 = i + j;
			int conflicts = cols[j] + diag1[d1] + diag2[d2] - 3;
			//int conflicts = vect_conflicts[i];
			//int conflicts = table[i][j];
			//int conflicts = number_of_conflicts(i, j, N, places_for_queens);
			if (conflicts == max) {
				vectMax.push_back(i);
			}
		}
		int randIndex = rand() % (vectMax.size());
		imax = vectMax[randIndex];
		jmax = places_for_queens[imax];
		while (!vectMax.empty()) {
			vectMax.pop_back();
		}

		int d1 = imax - jmax + N - 1;
		int d2 = imax + jmax;
		cols[jmax]--;
		diag1[d1]--;
		diag2[d2]--;



		jmin = 0;
		min = INT_MAX;
		for (int j = 0; j < N; j++) {
			places_for_queens[imax] = j;
			int _d1 = imax - j + N - 1;
			int _d2 = imax + j;
			cols[j]++;
			diag1[_d1]++;
			diag2[_d2]++;
			int conflicts = cols[j] + diag1[_d1] + diag2[_d2] - 3;
			//int conflicts = number_of_conflicts(imax, j, N, places_for_queens);
			if (conflicts < min) {
				min = conflicts;
				//jmin = j;
			}

			cols[j]--;
			diag1[_d1]--;
			diag2[_d2]--;
		}

		for (int j = 0; j < N; j++) {
			places_for_queens[imax] = j;
			int _d1 = imax - j + N - 1;
			int _d2 = imax + j;
			cols[j]++;
			diag1[_d1]++;
			diag2[_d2]++;
			int conflicts = cols[j] + diag1[_d1] + diag2[_d2] - 3;
			//int conflicts = number_of_conflicts(imax, j, N, places_for_queens);
			if (conflicts == min) {
				vectMin.push_back(j);
			}
			cols[j]--;
			diag1[_d1]--;
			diag2[_d2]--;
		}
		int randIndex2 = rand() % vectMin.size();
		jmin = vectMin[randIndex2];
		while (!vectMin.empty()) {
			vectMin.pop_back();
		}

		places_for_queens[imax] = jmin;
		int _d1 = imax - jmin + N - 1;
		int _d2 = imax + jmin;
		cols[jmin]++;
		diag1[_d1]++;
		diag2[_d2]++;



		if (jmax == jmin) {
			imax = rand() % N;
			int oldj = places_for_queens[imax];
			int _d1_1 = imax - oldj + N - 1;
			int _d2_1 = imax + oldj;
			cols[oldj]--;
			diag1[_d1_1]--;
			diag2[_d2_1]--;

			int newplace = rand() % N;
			places_for_queens[imax] = newplace;
			int __d1 = imax - newplace + N - 1;
			int __d2 = imax + newplace;
			cols[newplace]++;
			diag1[__d1]++;
			diag2[__d2]++;
		}




		/*for (int i = 0; i < N; i++) {
			int j = places_for_queens[i];
			int number_confl = number_of_conflicts(i, j, N, places_for_queens);
			vect_conflicts[i] = number_confl;
		}*/

		/*for (int i = 0; i < N; i++) {
			int j = places_for_queens[i];
			int confl_ij = number_of_conflicts(i, j, N, places_for_queens);
			table[i][j] = confl_ij;
		}*/


		/*std::cout << "_Proverka_:";
		for (int i = 0; i < N; i++) {
			std::cout << places_for_queens[i];
		}
		std::cout << endl;*/

	}


	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (places_for_queens[i] == j) {
				std::cout << setw(3) << '*';
			}
			else {
				std::cout << setw(3) << '_';
			}
		}
		std::cout << std::endl;
	}*/


	unsigned long long t_end = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
	cout << t_end - t_beginning << endl;
	return 0;
}