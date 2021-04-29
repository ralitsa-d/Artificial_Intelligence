#include<iostream>
#include<vector>
#include<cstdlib>
#include<math.h>
#include<iomanip>
#include<chrono>
#include<fstream>
#include <stdlib.h>
#include <time.h>  
using namespace std;

int cnt = 0;
int cnt_erase = 0;
int cnt_insert = 0;
int cnt_recursion = 0;
int cnt_recursion_only = 0;
int cnt_change = 0;
bool solution_is_found = false;


bool member_in_row(char x, int row, vector<vector<char>> table) {
	for (int j = 0; j < table[row].size(); j++) {
		if (x == table[row][j]) {
			return true;
		}
	}
	return false;
}

bool member_in_col(char x, int col, vector<vector<char>> table) {
	for (int i = 0; i < table.size(); i++) {
		if (x == table[i][col]) {
			return true;
		}
	}
	return false;
}

bool member_in_square(char x, int row, int col, vector<vector<char>> table) {
	if (row % 3 == 0) {
		if (col % 3 == 0) {
			for (int i = row; i < row + 3; i++) {
				for (int j = col; j < col + 3; j++) {
					if (x == table[i][j]) {
						return true;
					}
				}
			}
		}
		if (col % 3 == 1) {
			for (int i = row; i < row + 3; i++) {
				for (int j = col - 1; j < col + 2; j++) {
					if (x == table[i][j]) {
						return true;
					}
				}
			}
		}
		if (col % 3 == 2) {
			for (int i = row; i < row + 3; i++) {
				for (int j = col - 2; j < col + 1; j++) {
					if (x == table[i][j]) {
						return true;
					}
				}
			}
		}
	}

	if (row % 3 == 1) {
		if (col % 3 == 0) {
			for (int i = row - 1; i < row + 2; i++) {
				for (int j = col; j < col + 3; j++) {
					if (x == table[i][j]) {
						return true;
					}
				}
			}
		}
		if (col % 3 == 1) {
			for (int i = row - 1; i < row + 2; i++) {
				for (int j = col - 1; j < col + 2; j++) {
					if (x == table[i][j]) {
						return true;
					}
				}
			}
		}
		if (col % 3 == 2) {
			for (int i = row - 1; i < row + 2; i++) {
				for (int j = col - 2; j < col + 1; j++) {
					if (x == table[i][j]) {
						return true;
					}
				}
			}
		}
	}

	if (row % 3 == 2) {
		if (col % 3 == 0) {
			for (int i = row - 2; i < row + 1; i++) {
				for (int j = col; j < col + 3; j++) {
					if (x == table[i][j]) {
						return true;
					}
				}
			}
		}
		if (col % 3 == 1) {
			for (int i = row - 2; i < row + 1; i++) {
				for (int j = col - 1; j < col + 2; j++) {
					if (x == table[i][j]) {
						return true;
					}
				}
			}
		}
		if (col % 3 == 2) {
			for (int i = row - 2; i < row + 1; i++) {
				for (int j = col - 2; j < col + 1; j++) {
					if (x == table[i][j]) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

vector<vector<char>> createDomains(vector<vector<char>> table) {
	vector<vector<char>> domains;
	for (int i = 0; i < 81; i++) {
		vector<char> empty;
		domains.push_back(empty);
	}
	for (int i = 0; i < table.size(); i++) {
		for (int j = 0; j < table[i].size(); j++) {
			if (table[i][j] == '-') {
				vector<char> domain;
				for (char a = '1'; a <= '9'; a++) {
					if (!member_in_row(a, i, table) && !member_in_col(a, j, table) && !member_in_square(a, i, j, table)) {
						domain.push_back(a);
					}
				}
				domains[i * 9 + j] = domain;
			}
		}
	}
	return domains;
}

bool member(int x, vector<int> affectedDomains) {
	for (int i = 0; i < affectedDomains.size(); i++) {
		//cnt++;
		if (x == affectedDomains[i]) {
			return true;
		}
	}
	return false;
}

vector<int> removeValueFromDomainsInRow(vector<vector<char>>& domains, int row, char value) {
	vector<int> affectedDomains;
	for (int col = 0; col < 9; col++) {
		cnt_erase++;
		vector<char> previousDomain = domains[row * 9 + col];
		domains[row * 9 + col].clear();
		for (int i = 0; i < previousDomain.size(); i++) {
			cnt_erase++;
			if (previousDomain[i] == value) {
				if (!member(row * 9 + col, affectedDomains)) {
					affectedDomains.push_back(row * 9 + col);
				}
				//domains[row * 9 + col].erase(domains[row * 9 + col].begin() + i);
			}
			if (previousDomain[i] != value) {
				domains[row * 9 + col].push_back(previousDomain[i]);
			}
		}
	}
	return affectedDomains;
}

void insertValueInDomainsInRow(vector<vector<char>>& domains, int row, char value, vector<int> affectedDomains) {
	for (int i = 0; i < affectedDomains.size(); i++) {
		cnt_insert++;
		domains[affectedDomains[i]].push_back(value);
	}
}

vector<int> removeValueFromDomainsInCol(vector<vector<char>>& domains, int col, char value) {
	vector<int> affectedDomains;
	for (int row = 0; row < 9; row++) {
		cnt_erase++;
		vector<char> previousDomain = domains[row * 9 + col];
		domains[row * 9 + col].clear();
		for (int i = 0; i < previousDomain.size(); i++) {
			cnt_erase++;
			if (previousDomain[i] == value) {
				if (!member(row * 9 + col, affectedDomains)) {
					affectedDomains.push_back(row * 9 + col);
				}
				//domains[row * 9 + col].erase(domains[row * 9 + col].begin() + i);
			}
			if (previousDomain[i] != value) {
				domains[row * 9 + col].push_back(previousDomain[i]);
			}
		}
	}
	return affectedDomains;
}

void insertValueInDomainsInCol(vector<vector<char>>& domains, int col, char value, vector<int> affectedDomains) {
	for (int i = 0; i < affectedDomains.size(); i++) {
		cnt_insert++;
		domains[affectedDomains[i]].push_back(value);
	}
}

vector<int> removeValueFromDomainsInBox(vector<vector<char>>& domains, int row, int col, char value) {
	vector<int> affectedDomains;
	if (row % 3 == 0) {
		if (col % 3 == 0) {
			for (int i = row; i < row + 3; i++) {
				for (int j = col; j < col + 3; j++) {
					vector<char> previousDomain = domains[row * 9 + col];
					domains[row * 9 + col].clear();
					for (int k = 0; k < previousDomain.size(); k++) {
						cnt_erase++;
						if (previousDomain[k] == value) {
							if (!member(row * 9 + col, affectedDomains)) {
								affectedDomains.push_back(row * 9 + col);
							}
						}
						if (previousDomain[k] != value) {
							domains[row * 9 + col].push_back(previousDomain[k]);
						}
					}
				}
			}
		}
		if (col % 3 == 1) {
			for (int i = row; i < row + 3; i++) {
				for (int j = col - 1; j < col + 2; j++) {
					vector<char> previousDomain = domains[row * 9 + col];
					domains[row * 9 + col].clear();
					for (int k = 0; k < previousDomain.size(); k++) {
						cnt_erase++;
						if (previousDomain[k] == value) {
							if (!member(row * 9 + col, affectedDomains)) {
								affectedDomains.push_back(row * 9 + col);
							}
						}
						if (previousDomain[k] != value) {
							domains[row * 9 + col].push_back(previousDomain[k]);
						}
					}
				}
			}
		}
		if (col % 3 == 2) {
			for (int i = row; i < row + 3; i++) {
				for (int j = col - 2; j < col + 1; j++) {
					vector<char> previousDomain = domains[row * 9 + col];
					domains[row * 9 + col].clear();
					for (int k = 0; k < previousDomain.size(); k++) {
						cnt_erase++;
						if (previousDomain[k] == value) {
							if (!member(row * 9 + col, affectedDomains)) {
								affectedDomains.push_back(row * 9 + col);
							}
						}
						if (previousDomain[k] != value) {
							domains[row * 9 + col].push_back(previousDomain[k]);
						}
					}
				}
			}
		}
	}
	if (row % 3 == 1) {
		if (col % 3 == 0) {
			for (int i = row - 1; i < row + 2; i++) {
				for (int j = col; j < col + 3; j++) {
					vector<char> previousDomain = domains[row * 9 + col];
					domains[row * 9 + col].clear();
					for (int k = 0; k < previousDomain.size(); k++) {
						cnt_erase++;
						if (previousDomain[k] == value) {
							if (!member(row * 9 + col, affectedDomains)) {
								affectedDomains.push_back(row * 9 + col);
							}
						}
						if (previousDomain[k] != value) {
							domains[row * 9 + col].push_back(previousDomain[k]);
						}
					}
				}
			}
		}
		if (col % 3 == 1) {
			for (int i = row - 1; i < row + 2; i++) {
				for (int j = col - 1; j < col + 2; j++) {
					vector<char> previousDomain = domains[row * 9 + col];
					domains[row * 9 + col].clear();
					for (int k = 0; k < previousDomain.size(); k++) {
						cnt_erase++;
						if (previousDomain[k] == value) {
							if (!member(row * 9 + col, affectedDomains)) {
								affectedDomains.push_back(row * 9 + col);
							}
						}
						if (previousDomain[k] != value) {
							domains[row * 9 + col].push_back(previousDomain[k]);
						}
					}
				}
			}
		}
		if (col % 3 == 2) {
			for (int i = row - 1; i < row + 2; i++) {
				for (int j = col - 2; j < col + 1; j++) {
					vector<char> previousDomain = domains[row * 9 + col];
					domains[row * 9 + col].clear();
					for (int k = 0; k < previousDomain.size(); k++) {
						cnt_erase++;
						if (previousDomain[k] == value) {
							if (!member(row * 9 + col, affectedDomains)) {
								affectedDomains.push_back(row * 9 + col);
							}
						}
						if (previousDomain[k] != value) {
							domains[row * 9 + col].push_back(previousDomain[k]);
						}
					}
				}
			}
		}
	}
	if (row % 3 == 2) {
		if (col % 3 == 0) {
			for (int i = row - 2; i < row + 1; i++) {
				for (int j = col; j < col + 3; j++) {
					vector<char> previousDomain = domains[row * 9 + col];
					domains[row * 9 + col].clear();
					for (int k = 0; k < previousDomain.size(); k++) {
						cnt_erase++;
						if (previousDomain[k] == value) {
							if (!member(row * 9 + col, affectedDomains)) {
								affectedDomains.push_back(row * 9 + col);
							}
						}
						if (previousDomain[k] != value) {
							domains[row * 9 + col].push_back(previousDomain[k]);
						}
					}
				}
			}
		}
		if (col % 3 == 1) {
			for (int i = row - 2; i < row + 1; i++) {
				for (int j = col - 1; j < col + 2; j++) {
					vector<char> previousDomain = domains[row * 9 + col];
					domains[row * 9 + col].clear();
					for (int k = 0; k < previousDomain.size(); k++) {
						cnt_erase++;
						if (previousDomain[k] == value) {
							if (!member(row * 9 + col, affectedDomains)) {
								affectedDomains.push_back(row * 9 + col);
							}
						}
						if (previousDomain[k] != value) {
							domains[row * 9 + col].push_back(previousDomain[k]);
						}
					}
				}
			}
		}
		if (col % 3 == 2) {
			for (int i = row - 2; i < row + 1; i++) {
				for (int j = col - 2; j < col + 1; j++) {
					vector<char> previousDomain = domains[row * 9 + col];
					domains[row * 9 + col].clear();
					for (int k = 0; k < previousDomain.size(); k++) {
						cnt_erase++;
						if (previousDomain[k] == value) {
							if (!member(row * 9 + col, affectedDomains)) {
								affectedDomains.push_back(row * 9 + col);
							}
						}
						if (previousDomain[k] != value) {
							domains[row * 9 + col].push_back(previousDomain[k]);
						}
					}
				}
			}
		}
	}
	cnt_erase += 9;
	return affectedDomains;
}

void insertValueInDomainsInBox(vector<vector<char>>& domains, int row, int col, char value, vector<int> affectedDomains) {
	for (int i = 0; i < affectedDomains.size(); i++) {
		domains[affectedDomains[i]].push_back(value);
	}
}

/*void updateDomains(vector<vector<char>>& table, vector<vector<char>>& domains, int row, int col) {
	int indexOfDomain = row * 9 + col;
	vector<char> previousDomain = domains[indexOfDomain];
	domains[indexOfDomain].clear();
	for (int i = 0; i < previousDomain.size(); i++) {
		if (previousDomain[i] != table[row][col]) {
			domains[indexOfDomain].push_back(previousDomain[i]);
		}
	}
}*/



bool isSolution(vector<vector<char>> table) {
	int count = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (table[i][j] == '-') {
				count++;
			}
		}
	}
	if (count == 0) {
		return true;
	}
	else {
		return false;
	}
	cnt += 81;
}

bool solution_is_correct(vector<vector<char>> table) {
	for (char ch = '1'; ch <= '9'; ch++) {
		int countCh11 = 0, countCh12 = 0, countCh13 = 0;
		int countCh21 = 0, countCh22 = 0, countCh23 = 0;
		int countCh31 = 0, countCh32 = 0, countCh33 = 0;

		for (int i = 0; i < 9; i++) {
			int countCh_row = 0, countCh_col = 0;

			for (int j = 0; j < 9; j++) {
				// in row
				if (table[i][j] == ch) {
					countCh_row++;
				}
				// in col
				if (table[j][i] == ch) {
					countCh_col++;
				}
				// in square 11
				if (i < 3 && j < 3 && table[i][j] == ch) {
					countCh11++;
				}
				// in square 12
				if (i < 3 && j >= 3 && j < 6 && table[i][j] == ch) {
					countCh12++;
				}
				// in square 13
				if (i < 3 && j >= 6 && j < 9 && table[i][j] == ch) {
					countCh13++;
				}
				// in square 21
				if (i >= 3 && i < 6 && j < 3 && table[i][j] == ch) {
					countCh21++;
				}
				// in square 22
				if (i >= 3 && i < 6 && j >= 3 && j < 6 && table[i][j] == ch) {
					countCh22++;
				}
				// in square 23
				if (i >= 3 && i < 6 && j >= 6 && j < 9 && table[i][j] == ch) {
					countCh23++;
				}
				// in square 31
				if (i >= 6 && i < 9 && j < 3 && table[i][j] == ch) {
					countCh31++;
				}
				// in square 32
				if (i >= 6 && i < 9 && j >= 3 && j < 6 && table[i][j] == ch) {
					countCh32++;
				}
				// in square 33
				if (i >= 6 && i < 9 && j >= 6 && j < 9 && table[i][j] == ch) {
					countCh33++;
				}
			}
			if (countCh_row != 1 || countCh_col != 1) {
				return false;
			}
		}
		if (countCh11 != 1 || countCh12 != 1 || countCh13 != 1 ||
			countCh21 != 1 || countCh22 != 1 || countCh23 != 1 ||
			countCh31 != 1 || countCh32 != 1 || countCh33 != 1) {
			return false;
		}
	}
	return true;
}

void print(vector<vector<char>> table) {
	cout << endl;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << setw(3);
			cout << table[i][j];
			if (j == 2 || j == 5) cout << setw(3) << "|";
		}
		cout << endl;
		if (i == 2 || i == 5) {
			cout << endl;
		}
	}
	cnt += 81;
}

bool memberInVector(int index, vector<int> vectorOfIndexes) {
	for (int i = 0; i < vectorOfIndexes.size(); i++) {
		cnt++;
		if (vectorOfIndexes[i] == index) {
			return true;
		}
	}
	return false;
}

bool thereAreEmptyDomains(vector<vector<char>> domains, vector<int> vectorOfIndexes, vector<bool> alreadyAssignedCells) {
	int count = 0;
	for (int i = 0; i < 81; i++) {
		if (alreadyAssignedCells[i] == true) {
			count++;
		}
	}
	if (count == 81) {
		return false;
	}
	for (int i = 0; i < 81; i++) {
		cnt++;
		if (domains[i].size() == 0 && !memberInVector(i, vectorOfIndexes) && alreadyAssignedCells[i] == false) {
			return true;
		}
	}
	return false;
}

bool itIsSafeTo_assignValue_and_updateDomains(vector<vector<char>> table, vector<vector<char>> domains, int row, int col, char value,
	vector<bool> alreadyAssignedCells, vector<int> indexesOfGivenNumbers) {
	//Ќе промен€ме домейните или таблицата, просто провер€ваме, ако ги променим, какво ще стане

	table[row][col] = value;
	alreadyAssignedCells[row * 9 + col] = true;

	removeValueFromDomainsInRow(domains, row, table[row][col]);
	removeValueFromDomainsInCol(domains, col, table[row][col]);
	removeValueFromDomainsInBox(domains, row, col, table[row][col]);

	if (thereAreEmptyDomains(domains, indexesOfGivenNumbers, alreadyAssignedCells)) {
		return false;
	}
	else {
		return true;
	}
}

bool solveSudoku(vector<vector<char>>& table, vector<vector<char>>& domains, vector<bool>& alreadyAssignedCells, vector<int>& indexesOfGivenNumbers) {
	cnt_recursion++;
	cnt_recursion_only++;
	if (isSolution(table)) {
		if (solution_is_correct(table)) {
			if (solution_is_found == false) {
				print(table);
			}
			solution_is_found = true;
		}
		return true;
	}
	else {
		int min = 10;
		vector<char> currentDomain;
		int currentRow = 0;
		int currentCol = 0;
		for (int i = 0; i < 81; i++) {
			cnt_recursion++;
			if (domains[i].size() > 0 && domains[i].size() < min && alreadyAssignedCells[i] == false) {
				min = domains[i].size();
				currentDomain = domains[i];
				currentRow = i / 9;
				currentCol = i % 9;
			}
			if (min == 1) {
				break;
			}
		}

		for (int i = 0; i < currentDomain.size(); i++) {
			cnt_recursion++;
			table[currentRow][currentCol] = currentDomain[i];
			alreadyAssignedCells[currentRow * 9 + currentCol] = true;

			vector<int> affectedDomainsInRow = removeValueFromDomainsInRow(domains, currentRow, table[currentRow][currentCol]);
			vector<int> affectedDomainsInCol = removeValueFromDomainsInCol(domains, currentCol, table[currentRow][currentCol]);
			vector<int> affectedDomainsInBox = removeValueFromDomainsInBox(domains, currentRow, currentCol, table[currentRow][currentCol]);

			if (!thereAreEmptyDomains(domains, indexesOfGivenNumbers, alreadyAssignedCells)) {
				cnt_change++;
				solveSudoku(table, domains, alreadyAssignedCells, indexesOfGivenNumbers);

				table[currentRow][currentCol] = '-';
				alreadyAssignedCells[currentRow * 9 + currentCol] = false;

				insertValueInDomainsInRow(domains, currentRow, currentDomain[i], affectedDomainsInRow);
				insertValueInDomainsInCol(domains, currentCol, currentDomain[i], affectedDomainsInCol);
				insertValueInDomainsInBox(domains, currentRow, currentCol, currentDomain[i], affectedDomainsInBox);
			}
			else {
				table[currentRow][currentCol] = '-';
				alreadyAssignedCells[currentRow * 9 + currentCol] = false;

				insertValueInDomainsInRow(domains, currentRow, currentDomain[i], affectedDomainsInRow);
				insertValueInDomainsInCol(domains, currentCol, currentDomain[i], affectedDomainsInCol);
				insertValueInDomainsInBox(domains, currentRow, currentCol, currentDomain[i], affectedDomainsInBox);
				return false;
			}
		}
	}
}

int main() {
	unsigned long long t_beginning = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

	vector<vector<char>> sudokuTable;
	vector<int> indexesOfGivenNumbers; //индексите на числата, които са дадени първоначално

	ifstream file;
	file.open("easy.txt", ios::in);
	if (file.is_open()) {
		cout << "file is open" << endl;
	}
	else {
		cout << "file is NOT open" << endl;
	}
	vector<char> row;
	char ch;
	int i = 0;
	int j = 0;
	while (!file.eof()) {
		file >> ch;
		if (ch >= '1' && ch <= '9') {
			indexesOfGivenNumbers.push_back(i * 9 + j);
		}
		row.push_back(ch);

		if (j == 8) {
			sudokuTable.push_back(row);
			i++;
			row.clear();
		}

		j++;
		if (j == 9) { //ако сме достигнали кра€ на реда
			j = 0;
		}
	}

	print(sudokuTable);

	vector<vector<char>> domains = createDomains(sudokuTable);

	vector<bool> alreadyAssignedCells;
	for (int i = 0; i < 81; i++) {
		cnt++;
		alreadyAssignedCells.push_back(false);
	}
	for (int i = 0; i < indexesOfGivenNumbers.size(); i++) {
		cnt++;
		alreadyAssignedCells[indexesOfGivenNumbers[i]] = true;
	}

	bool b = solveSudoku(sudokuTable, domains, alreadyAssignedCells, indexesOfGivenNumbers);

	unsigned long long t_end = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
	cout << endl;
	cout << "Time: ";
	cout << t_end - t_beginning << endl;
	cout << endl;
	cout << "Number of iterations on recursion: " << cnt_recursion << endl;
	cout << "Number of iterations on erasing: " << cnt_erase << endl;
	cout << "Number of iterations on inserting: " << cnt_insert << endl;
	cout << "Number of other iterations: " << cnt << endl;
	cout << "Number of recursions only: " << cnt_recursion_only << endl;
	cout << "Number of changes: " << cnt_change << endl;
	cout << endl;
	cout << "Number of iterations: " << cnt + cnt_recursion + cnt_erase + cnt_insert << endl;
	return 0;
}