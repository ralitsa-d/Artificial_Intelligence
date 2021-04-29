#include<iostream>
#include<string>
#include<cstring>
#include<stack>
#include<queue>
#include<list>
#include<vector>
#include<stack>
#include<math.h>
#include<iomanip>
#include<assert.h>
#include"State.h"

using namespace std;

stack<State> st;
int br;

list<State> Neighbours(State s) {
	//parent = s;
	list<State> list;
	State sLeft;
	State sRight;
	State sUp;
	State sDown;
	int x = s.getCoordX();
	int y = s.getCoordY();
	int index = x * s.getRows() + y;

	if (y < s.getRows() - 1) {
		vector<int> v = s.getVector();
		int newX = s.getCoordX();
		int newY = s.getCoordY() + 1;
		int other_index = newX * s.getRows() + newY;
		int temp = v[index];
		v[index] = v[other_index];
		v[other_index] = temp;
		State newState(s.getRows(), v, s.getG() + 1, Direction(1));
		sRight = newState;
		list.push_back(sRight);
	}

	if (y > 0) {
		vector<int> v = s.getVector();
		int newX = s.getCoordX();
		int newY = s.getCoordY() - 1;
		int other_index = newX * s.getRows() + newY;
		int temp = v[index];
		v[index] = v[other_index];
		v[other_index] = temp;
		State newState(s.getRows(), v, s.getG() + 1, Direction(0));
		sLeft = newState;
		list.push_back(sLeft);
	}

	if (x > 0) {
		vector<int> v = s.getVector();
		int newX = s.getCoordX() - 1;
		int newY = s.getCoordY();
		int other_index = newX * s.getRows() + newY;
		int temp = v[index];
		v[index] = v[other_index];
		v[other_index] = temp;
		State newState(s.getRows(), v, s.getG() + 1, Direction(2));
		sUp = newState;
		list.push_back(sUp);
	}

	if (x < s.getRows() - 1) {
		vector<int> v = s.getVector();
		int newX = s.getCoordX() + 1;
		int newY = s.getCoordY();
		int other_index = newX * s.getRows() + newY;
		int temp = v[index];
		v[index] = v[other_index];
		v[other_index] = temp;
		State newState(s.getRows(), v, s.getG() + 1, Direction(3));
		sDown = newState;
		list.push_back(sDown);
	}
	return list;
}


int search(State s, const State& goalState, int g, int threshold, int blankTile) {
	int f = s.cost(s, blankTile);
	if (f > threshold) {
		return f;
	}
	if (s == goalState) {
		return -1;
	}
	int min = INT_MAX;
	list<State> l = Neighbours(s);
	for (std::list<State>::iterator it = l.begin(); it != l.end(); ++it) {
		int temp = search((*it), goalState, g + 1, threshold, blankTile);
		if (temp == -1) {
			st.push(*it);
			br++;
			return -1;
		}
		if (temp < min) {
			min = temp;
		}
	}
	return min;
}

void IDA_star(State start, const State& goalState, int coordinates_of_blank_tile) {
	int threshold = start.hManhattan(start, coordinates_of_blank_tile);
	while (1) {
		int temp = search(start, goalState, 0, threshold, coordinates_of_blank_tile);
		if (temp == -1) cout << "FOUND" << endl; break;
		if (temp != -1) {
			threshold = temp;
		}
	}
}



int main() {
	cout << "Enter number of tiles: "; //8 for 8-puzzle
	int numberOfTiles;
	cin >> numberOfTiles;
	int N = sqrt(numberOfTiles + 1);
	vector<int> tiles;
	int tileNum;
	for (int i = 0; i < N*N; i++) {
		cout << "Enter tile " << i + 1 << ": ";
		cin >> tileNum;
		tiles.push_back(tileNum);
	}
	State s(N, tiles, 0, Direction(4));
	s.printMatrix();

	/*State parent;
	list<State> l = Neighbours(s);
	for (std::list<State>::iterator it = l.begin(); it != l.end(); ++it) {
		it->printMatrix();
		int dist = it->cost(*it);
		Direction dir = it->getDir();
		switch (dir) {
		case 0: cout << "left"; break;
		case 1: cout << "right"; break;
		case 2: cout << "up"; break;
		case 3: cout << "down"; break;
		case 4: cout << "none"; break;
		}
		cout << endl << dist << endl;
	}*/

	vector<int> tiles_of_goal;
	int blank;
	cout << "Enter where the blank tile should be: ";
	cin >> blank;
	assert(blank >= 0 && blank <= numberOfTiles);
	for (int i = 0; i < blank; i++) {
		tiles_of_goal.push_back(i + 1);
	}
	tiles_of_goal.push_back(0);
	for (int i = blank + 1; i < N*N; i++) {
		tiles_of_goal.push_back(i);
	}
	State goalState(N, tiles_of_goal);
	goalState.setDir(Direction(4));
	cout << "Goal State is: " << endl;
	goalState.printMatrix();
	cout << endl << endl;

	s.setVisited(false);



	IDA_star(s, goalState, blank);
	st.push(s);
	if (s != goalState && br == 0) {
		cout << "DOES NOT NAVE A SOLUTION" << endl;
	}
	else {
		cout << "It takes " << br << " steps to goal state." << endl;
		cout << "And the path is: " << endl;

		while (!st.empty()) {
			State state = st.top();
			state.printMatrix();
			st.pop();
		}
	}

	system("pause");
	return 0;
}