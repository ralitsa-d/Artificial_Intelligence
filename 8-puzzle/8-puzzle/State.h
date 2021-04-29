#pragma once
#include<iostream>
#include<iomanip>
#include<vector>
#include<math.h>
using namespace std;

enum Direction { left, right, up, down, none };

class State {
private:
	vector<int> vect;

	//number of rows and colls
	int rows;

	//coordinates of the blank tile
	int coordX;
	int coordY;

	//direction
	Direction dir;

	int g;

	bool visited;

	void pr() const {
		for (int i = 0; i < rows; i++) {
			if ((i + 1) % rows) {
				cout << endl;
			}
			cout << setw(3) << vect[i];
		}
	}


public:
	State() {
		this->rows = 3;
		this->coordX = 2;
		this->coordY = 2;
		this->dir = Direction(4);
		this->g = 0;
		//this->visited = false;

		this->vect.resize(rows*rows);
		for (int i = 1; i <= rows * rows - 1; i++) {
			vect.push_back(i);
		}
		vect.push_back(0);
	}

	State(int number_of_rows, const vector<int>& v, int g, const Direction d) {
		this->rows = number_of_rows;
		int x;
		int y;
		for (int i = 0; i < v.size(); i++) {
			this->vect.push_back(v[i]);
			if (v[i] == 0) {
				x = i / number_of_rows;
				y = i % number_of_rows;
			}
		}
		this->coordX = x;
		this->coordY = y;
		this->dir = d;
		this->g = g;
		//this->visited = vis;
	}

	State(int number_of_rows, const vector<int>& v) {
		this->rows = number_of_rows;
		int x;
		int y;
		for (int i = 0; i < v.size(); i++) {
			this->vect.push_back(v[i]);
			if (v[i] == 0) {
				x = i / number_of_rows;
				y = i % number_of_rows;
			}
		}
		this->coordX = x;
		this->coordY = y;
	}


	State(const State& s) {
		this->rows = s.rows;
		this->vect = s.vect;
		this->coordX = s.coordX;
		this->coordY = s.coordY;
		this->dir = s.dir;
		this->g = s.g;
		//this->visited = s.visited;
	}
	State& operator=(const State& s) {
		if (this != &s) {
			this->rows = s.rows;
			this->vect = s.vect;
			this->coordX = s.coordX;
			this->coordY = s.coordY;
			this->dir = s.dir;
			this->g = s.g;
			//this->visited = s.visited;
		}
		return *this;
	}
	~State() {
		//delete parent;
	}
	int getCoordX() const {
		return this->coordX;
	}
	int getCoordY() const {
		return this->coordY;
	}
	Direction getDir() const {
		return this->dir;
	}
	int getRows() const {
		return this->rows;
	}
	vector<int> getVector() const {
		return this->vect;
	}
	void setVector(const vector<int>& v) {
		this->vect = v;
	}
	void setRows(const int r) {
		this->rows = r;
	}
	void setCoordX(const int x) {
		this->coordX = x;
	}
	void setCoordY(const int y) {
		this->coordY = y;
	}
	void setDir(const Direction d) {
		this->dir = d;
	}
	bool getVisited() const {
		return this->visited;
	}
	void setVisited(const bool b) {
		this->visited = b;
	}
	friend bool operator== (const State& a, const State& b) {
		return (a.vect == b.vect);
	}
	friend bool operator!=(const State& a, const State& b) {
		return (a.vect != b.vect);
	}

	int hManhattan(const State& s, int coordinates_of_blank_tile) {
		int dist = 0;
		//get the coordinates of each tile
		for (int i = 0; i < (s.getRows())*(s.getRows()); i++) {
			int tile = s.getVector()[i];
			if (tile != 0) {
				int real_index;
				if (tile <= coordinates_of_blank_tile) {
					real_index = tile - 1;
				}
				else if (tile > coordinates_of_blank_tile) {
					real_index = tile;
				}

				//coordinates where it should be
				int newX = real_index / (s.getRows());
				int newY = real_index % (s.getRows());

				//coordinates where it is
				int x = i / (s.getRows());
				int y = i % (s.getRows());

				int mancost = abs(newX - x) + abs(newY - y);
				dist = dist + mancost;
			}
			else if (tile == 0) {
				dist = dist + 0;
			}
		}
		return dist;
	}

	int getG() const {
		return g;
	}

	void setG(int newG) {
		this->g = newG;
	}

	int cost(const State& s, int blankTile) {
		return hManhattan(s, blankTile) + getG();
	}

	bool operator==(const State& s2) {
		bool eq = true;
		for (int i = 0; i < getVector().size(); i++) {
			if (getVector()[i] != s2.getVector()[i]) {
				eq = false;
			}
		}
		return eq;
		//return this->getVector() == s2.getVector();
	}

	void print() const {
		//this->pr();
		vector<int> v = this->getVector();
		for (int i = 0; i < v.size(); i++) {
			cout << v[i] << " ";
		}
		cout << endl;
	}

	void printMatrix() const {
		vector<int> v = this->getVector();
		int N = this->getRows();
		for (int i = 0; i < v.size(); i++) {
			if (i % N == 0) {
				cout << endl;
			}
			cout << setw(3) << v[i];
		}
		cout << endl;
		Direction d = Direction(this->dir);
		switch (dir) {
		case 0: cout << "left"; break;
		case 1: cout << "right"; break;
		case 2: cout << "up"; break;
		case 3: cout << "down"; break;
		case 4: cout << "none"; break;
		}
		cout << endl;
	}

};