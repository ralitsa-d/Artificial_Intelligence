#include<iostream>
#include<vector>
#include<fstream>
#include <typeinfo>
#include<iomanip>
#include<chrono>
using namespace std;

int cnt_recursion = 0;
int cnt_recursion_only = 0;
int cnt_check = 0;
int cnt_search = 0;
int cnt_change = 0;
bool solution_is_found = false;

bool member_in_row(char x, int row, vector<vector<char>> table) {
	for (int j = 0; j < table[row].size(); j++) {
		cnt_check++;
		if (x == table[row][j]) {
			return true;
		}
	}
	return false;
}

bool member_in_col(char x, int col, vector<vector<char>> table) {
	for (int i = 0; i < table.size(); i++) {
		cnt_check++;
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
				cnt_check++;
				for (int j = col; j < col + 3; j++) {
					cnt_check++;
					if (x == table[i][j]) {
						return true;
					}
				}
			}
		}
		if (col % 3 == 1) {
			for (int i = row; i < row + 3; i++) {
				cnt_check++;
				for (int j = col - 1; j < col + 2; j++) {
					cnt_check++;
					if (x == table[i][j]) {

						return true;
					}
				}
			}
		}
		if (col % 3 == 2) {
			for (int i = row; i < row + 3; i++) {
				cnt_check++;
				for (int j = col - 2; j < col + 1; j++) {
					cnt_check++;
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
				cnt_check++;
				for (int j = col; j < col + 3; j++) {
					cnt_check++;
					if (x == table[i][j]) {

						return true;
					}
				}
			}
		}
		if (col % 3 == 1) {
			for (int i = row - 1; i < row + 2; i++) {
				cnt_check++;
				for (int j = col - 1; j < col + 2; j++) {
					cnt_check++;
					if (x == table[i][j]) {

						return true;
					}
				}
			}
		}
		if (col % 3 == 2) {
			for (int i = row - 1; i < row + 2; i++) {
				cnt_check++;
				for (int j = col - 2; j < col + 1; j++) {
					cnt_check++;
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
				cnt_check++;
				for (int j = col; j < col + 3; j++) {
					cnt_check++;
					if (x == table[i][j]) {

						return true;
					}
				}
			}
		}
		if (col % 3 == 1) {
			for (int i = row - 2; i < row + 1; i++) {
				cnt_check++;
				for (int j = col - 1; j < col + 2; j++) {
					cnt_check++;
					if (x == table[i][j]) {

						return true;
					}
				}
			}
		}
		if (col % 3 == 2) {
			for (int i = row - 2; i < row + 1; i++) {
				cnt_check++;
				for (int j = col - 2; j < col + 1; j++) {
					cnt_check++;
					if (x == table[i][j]) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

vector<vector<vector<char>>> Neighbours(vector<vector<char>> table) {
	vector<vector<vector<char>>> vectorWithNeighbours;
	int row_of_firstBlank;
	int col_of_firstBlank;
	for (int i = 0; i < table.size(); i++) {
		cnt_search++;
		for (int j = 0; j < table[i].size(); j++) {
			cnt_search++;
			if (table[i][j] == '-') {
				row_of_firstBlank = i;
				col_of_firstBlank = j;
				goto next;
			}
		}
	}

next:
	for (char a = '1'; a <= '9'; a++) {
		cnt_search++;
		if (!member_in_row(a, row_of_firstBlank, table) && !member_in_col(a, col_of_firstBlank, table) &&
			!member_in_square(a, row_of_firstBlank, col_of_firstBlank, table)) {
			table[row_of_firstBlank][col_of_firstBlank] = a;
			vector<vector<char>> sudokuTable = table;
			table[row_of_firstBlank][col_of_firstBlank] = '-';
			vectorWithNeighbours.push_back(sudokuTable);
		}
	}

	return vectorWithNeighbours;
}

bool solveSudoku(vector<vector<char>>& table) {
	cnt_recursion++;
	cnt_recursion_only++;
	int count = 0;
	for (int i = 0; i < table.size(); i++) {
		cnt_recursion++;
		for (int j = 0; j < table[i].size(); j++) {
			cnt_recursion++;
			if (table[i][j] == '-') {
				count++;
			}
		}
	}
	if (count == 0) {
		if (solution_is_found == false) {
			cout << endl;
			for (int i = 0; i < table.size(); i++) {
				for (int j = 0; j < table[i].size(); j++) {
					cout << setw(3);
					cout << table[i][j];
					if (j == 2 || j == 5) cout << setw(3) << "|";
				}
				cout << endl;
				if (i == 2 || i == 5) {
					cout << endl;
				}
			}
		}
		solution_is_found = true;
		/*cout << endl;
		for (int i = 0; i < table.size(); i++) {
			for (int j = 0; j < table[i].size(); j++) {
				cout << setw(3);
				cout << table[i][j];
				if (j == 2 || j == 5) cout << setw(3) << "|";
			}
			cout << endl;
			if (i == 2 || i == 5) {
				cout << endl;
			}
		}*/
		return true;
	}
	vector<vector<vector<char>>> neighbours = Neighbours(table);
	if (neighbours.size() > 0) {
		for (int i = 0; i < neighbours.size(); i++) {
			cnt_change++;
			solveSudoku(neighbours[i]);
		}
	}
	else {
		return false;

	}
}

int main() {
	unsigned long long t_beginning = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

	vector<vector<char>> sudokuTable;

	ifstream file;
	file.open("difficultGame1.txt", ios::in);
	if (file.is_open()) {
		cout << "file is open" << endl;
	}
	else {
		cout << "file is NOT open" << endl;
	}
	vector<char> row_i;
	char ch;
	int i = 0;
	while (!file.eof()) {
		file >> ch;
		row_i.push_back(ch);
		if (i == 8) {
			sudokuTable.push_back(row_i);
			row_i.clear();
		}
		i++;
		if (i == 9) {
			i = 0;
		}
	}

	for (int i = 0; i < sudokuTable.size(); i++) {
		for (int j = 0; j < sudokuTable[i].size(); j++) {
			cout << setw(3);
			cout << sudokuTable[i][j];
			if (j == 2 || j == 5) cout << setw(3) << "|";
		}
		cout << endl;
		if (i == 2 || i == 5) {
			cout << endl;
		}
	}

	bool b = solveSudoku(sudokuTable);

	unsigned long long t_end = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
	cout << endl;
	cout << "Time: ";
	cout << t_end - t_beginning << endl;
	cout << endl;
	//cout << "Number of iterations on recursion: " << cnt_recursion << endl;
	//cout << "Number of iterations on checking: " << cnt_check << endl;
	//cout << "Number of iterations on searching: " << cnt_search << endl;
	cout << "Number of recursions only: " << cnt_recursion_only << endl;
	//cout << "Number of changes: " << cnt_change << endl;
	cout << endl;
	//cout << "Number of iterations: " << cnt_recursion + cnt_check + cnt_search << endl;

	return 0;
}