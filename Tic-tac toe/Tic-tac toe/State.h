#pragma once
#include<iostream>
#include<vector>
#include<assert.h>
#include<iomanip>
using namespace std;

class State {
private:
	vector<vector<char>> table;
public:
	State() {
		for (int i = 0; i < 3; i++) {
			vector<char> v;
			for (int j = 0; j < 3; j++) {
				v.push_back(' ');
			}
			table.push_back(v);
		}
	}
	void add(int i, int j) {
		this->table[i][j] = 'X';
	}

	State& operator=(const State& s) {
		if (this != &s) {
			this->table = s.getTable();
		}
		return *this;
	}

	vector<vector<char>> getTable() const {
		return this->table;
	}

	void setTable(int i, int j) {
		this->table[i][j] = 'X';
	}

	void setTableOponent(int i, int j) {
		this->table[i][j] = 'O';
	}

	void print() const {
		for (int i = 0; i < 3; i++) {
			cout << "|";
			for (int j = 0; j < 3; j++) {
				cout << table[i][j] << "|";
			}
			cout << endl;
		}
		cout << endl;
	}

};