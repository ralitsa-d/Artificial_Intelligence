#include<iostream>
#include<list>
#include<iomanip>
#include"State.h"
using namespace std;

list<State> successors_afterOponent(State state) {
	list<State> l;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if ((state.getTable())[i][j] != 'X' && (state.getTable())[i][j] != 'O') {
				State newState;
				newState = state;
				newState.setTable(i, j);
				l.push_back(newState);
			}
		}
	}
	return l;
}

list<State> successors_afterMe(State state) {
	list<State> l;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if ((state.getTable())[i][j] != 'X' && (state.getTable())[i][j] != 'O') {
				State newState;
				newState = state;
				newState.setTableOponent(i, j);
				l.push_back(newState);
			}
		}
	}
	return l;
}

bool terminal_test(State s) {
	//rows
	if (s.getTable()[0][0] == 'X' && s.getTable()[0][1] == 'X' && s.getTable()[0][2] == 'X') {
		return true;
	}
	if (s.getTable()[0][0] == 'O' && s.getTable()[0][1] == 'O' && s.getTable()[0][2] == 'O') {
		return true;
	}
	if (s.getTable()[1][0] == 'X' && s.getTable()[1][1] == 'X' && s.getTable()[1][2] == 'X') {
		return true;
	}
	if (s.getTable()[1][0] == 'O' && s.getTable()[1][1] == 'O' && s.getTable()[1][2] == 'O') {
		return true;
	}
	if (s.getTable()[2][0] == 'X' && s.getTable()[2][1] == 'X' && s.getTable()[2][2] == 'X') {
		return true;
	}
	if (s.getTable()[2][0] == 'O' && s.getTable()[2][1] == 'O' && s.getTable()[2][2] == 'O') {
		return true;
	}

	//cols
	if (s.getTable()[0][0] == 'X' && s.getTable()[1][0] == 'X' && s.getTable()[2][0] == 'X') {
		return true;
	}
	if (s.getTable()[0][0] == 'O' && s.getTable()[1][0] == 'O' && s.getTable()[2][0] == 'O') {
		return true;
	}
	if (s.getTable()[0][1] == 'X' && s.getTable()[1][1] == 'X' && s.getTable()[2][1] == 'X') {
		return true;
	}
	if (s.getTable()[0][1] == 'O' && s.getTable()[1][1] == 'O' && s.getTable()[2][1] == 'O') {
		return true;
	}
	if (s.getTable()[0][2] == 'X' && s.getTable()[1][2] == 'X' && s.getTable()[2][2] == 'X') {
		return true;
	}
	if (s.getTable()[0][2] == 'O' && s.getTable()[1][2] == 'O' && s.getTable()[2][2] == 'O') {
		return true;
	}

	//diags
	if (s.getTable()[0][0] == 'X' && s.getTable()[1][1] == 'X' && s.getTable()[2][2] == 'X') {
		return true;
	}
	if (s.getTable()[0][0] == 'O' && s.getTable()[1][1] == 'O' && s.getTable()[2][2] == 'O') {
		return true;
	}
	if (s.getTable()[0][2] == 'X' && s.getTable()[1][1] == 'X' && s.getTable()[2][0] == 'X') {
		return true;
	}
	if (s.getTable()[0][2] == 'O' && s.getTable()[1][1] == 'O' && s.getTable()[2][0] == 'O') {
		return true;
	}


	//nobody wins
	int br = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (s.getTable()[i][j] != ' ') {
				br++;
			}
		}
	}
	if (br == 9) {
		return true;
	}

	return false;
}



int terminal_test_utility(State s, int depth) {
	//rows
	if (s.getTable()[0][0] == 'X' && s.getTable()[0][1] == 'X' && s.getTable()[0][2] == 'X') {
		return 10 - depth;

	}
	if (s.getTable()[0][0] == 'O' && s.getTable()[0][1] == 'O' && s.getTable()[0][2] == 'O') {
		return -10 + depth;
	}
	if (s.getTable()[1][0] == 'X' && s.getTable()[1][1] == 'X' && s.getTable()[1][2] == 'X') {
		return 10 - depth;
	}
	if (s.getTable()[1][0] == 'O' && s.getTable()[1][1] == 'O' && s.getTable()[1][2] == 'O') {
		return -10;
	}
	if (s.getTable()[2][0] == 'X' && s.getTable()[2][1] == 'X' && s.getTable()[2][2] == 'X') {
		return 10 - depth;
	}
	if (s.getTable()[2][0] == 'O' && s.getTable()[2][1] == 'O' && s.getTable()[2][2] == 'O') {
		return -10 + depth;
	}

	//cols
	if (s.getTable()[0][0] == 'X' && s.getTable()[1][0] == 'X' && s.getTable()[2][0] == 'X') {
		return 10 - depth;
	}
	if (s.getTable()[0][0] == 'O' && s.getTable()[1][0] == 'O' && s.getTable()[2][0] == 'O') {
		return -10 + depth;
	}
	if (s.getTable()[0][1] == 'X' && s.getTable()[1][1] == 'X' && s.getTable()[2][1] == 'X') {
		return 10 - depth;
	}
	if (s.getTable()[0][1] == 'O' && s.getTable()[1][1] == 'O' && s.getTable()[2][1] == 'O') {
		return -10 + depth;
	}
	if (s.getTable()[0][2] == 'X' && s.getTable()[1][2] == 'X' && s.getTable()[2][2] == 'X') {
		return 10 - depth;
	}
	if (s.getTable()[0][2] == 'O' && s.getTable()[1][2] == 'O' && s.getTable()[2][2] == 'O') {
		return -10 + depth;
	}

	//diags
	if (s.getTable()[0][0] == 'X' && s.getTable()[1][1] == 'X' && s.getTable()[2][2] == 'X') {
		return 10 - depth;
	}
	if (s.getTable()[0][0] == 'O' && s.getTable()[1][1] == 'O' && s.getTable()[2][2] == 'O') {
		return -10 + depth;
	}
	if (s.getTable()[0][2] == 'X' && s.getTable()[1][1] == 'X' && s.getTable()[2][0] == 'X') {
		return 10 - depth;
	}
	if (s.getTable()[0][2] == 'O' && s.getTable()[1][1] == 'O' && s.getTable()[2][0] == 'O') {
		return -10 + depth;
	}


	//nobody wins
	int br = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (s.getTable()[i][j] != ' ') {
				br++;
			}
		}
	}
	if (br == 9) {
		return 0;
	}
	return 0;
}


void terminal_test_winner(State s) {
	//rows
	if (s.getTable()[0][0] == 'X' && s.getTable()[0][1] == 'X' && s.getTable()[0][2] == 'X') {
		cout << "You lost!";
	}
	if (s.getTable()[0][0] == 'O' && s.getTable()[0][1] == 'O' && s.getTable()[0][2] == 'O') {
		cout << "You won!";
	}
	if (s.getTable()[1][0] == 'X' && s.getTable()[1][1] == 'X' && s.getTable()[1][2] == 'X') {
		cout << "You lost!";
	}
	if (s.getTable()[1][0] == 'O' && s.getTable()[1][1] == 'O' && s.getTable()[1][2] == 'O') {
		cout << "You won!";
	}
	if (s.getTable()[2][0] == 'X' && s.getTable()[2][1] == 'X' && s.getTable()[2][2] == 'X') {
		cout << "You lost!";
	}
	if (s.getTable()[2][0] == 'O' && s.getTable()[2][1] == 'O' && s.getTable()[2][2] == 'O') {
		cout << "You won!";
	}

	//cols
	if (s.getTable()[0][0] == 'X' && s.getTable()[1][0] == 'X' && s.getTable()[2][0] == 'X') {
		cout << "You lost!";
	}
	if (s.getTable()[0][0] == 'O' && s.getTable()[1][0] == 'O' && s.getTable()[2][0] == 'O') {
		cout << "You won!";
	}
	if (s.getTable()[0][1] == 'X' && s.getTable()[1][1] == 'X' && s.getTable()[2][1] == 'X') {
		cout << "You lost!";
	}
	if (s.getTable()[0][1] == 'O' && s.getTable()[1][1] == 'O' && s.getTable()[2][1] == 'O') {
		cout << "You won!";
	}
	if (s.getTable()[0][2] == 'X' && s.getTable()[1][2] == 'X' && s.getTable()[2][2] == 'X') {
		cout << "You lost!";
	}
	if (s.getTable()[0][2] == 'O' && s.getTable()[1][2] == 'O' && s.getTable()[2][2] == 'O') {
		cout << "You won!";
	}

	//diags
	if (s.getTable()[0][0] == 'X' && s.getTable()[1][1] == 'X' && s.getTable()[2][2] == 'X') {
		cout << "You lost!";
	}
	if (s.getTable()[0][0] == 'O' && s.getTable()[1][1] == 'O' && s.getTable()[2][2] == 'O') {
		cout << "You won!";
	}
	if (s.getTable()[0][2] == 'X' && s.getTable()[1][1] == 'X' && s.getTable()[2][0] == 'X') {
		cout << "You lost!";
	}
	if (s.getTable()[0][2] == 'O' && s.getTable()[1][1] == 'O' && s.getTable()[2][0] == 'O') {
		cout << "You won!";
	}


	//nobody wins
	int br = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (s.getTable()[i][j] != ' ') {
				br++;
			}
		}
	}
	if (br == 9) {
		cout << "Nobody wins!";
	}

}

int maxValue(State, int, int, int);
int minValue(State, int, int, int);


//afterOponent = x;
//afterMe = o;
int maxValue(State state, int a, int b, int depth) {
	if (terminal_test(state)) return terminal_test_utility(state, depth);
	int v = INT_MIN;
	list<State> l = successors_afterOponent(state);
	for (std::list<State>::iterator it = l.begin(); it != l.end(); ++it) {
		int value = minValue(*it, a, b, depth + 1);
		if (value > v) {
			v = value;
		}
		if (v > b) {
			return v;
		}
		if (v > a) {
			a = v;
		}
		if (v == 10 - depth) break;
	}
	return v;
}

int minValue(State state, int a, int b, int depth) {
	if (terminal_test(state)) return terminal_test_utility(state, depth);
	int v = INT_MAX;
	list<State> l = successors_afterMe(state);
	for (std::list<State>::iterator it = l.begin(); it != l.end(); ++it) {
		int value = maxValue(*it, a, b, depth + 1);
		if (value < v) {
			v = value;
		}
		if (v < a) {
			return v;
		}
		if (v < b) {
			b = v;
		}
		if (v == -10 + depth) break;
	}
	return v;
}

State minimaxDecision(State s, int a, int b, int depth) {
	int v = maxValue(s, a, b, depth);
	list<State> l = successors_afterOponent(s);
	for (std::list<State>::iterator it = l.begin(); it != l.end(); ++it) {
		if (minValue(*it, a, b, depth + 1) == v) {
			return *it;
		}
	}
}


int main() {
	cout << "Choose whether to start first(1) or second(2): ";
	int choice;
	cin >> choice;
	assert(choice == 1 || choice == 2);

	if (choice == 1) {
		State s;
		cout << "Your turn: ";
		int i, j;
		cin >> i >> j;
		s.setTableOponent(i, j);
		s.print();
		State state = minimaxDecision(s, INT_MIN, INT_MAX, 0);
		state.print();
		do {
			cout << "Your turn: ";
			cin >> i >> j;
			state.setTableOponent(i, j);
			if (!terminal_test(state)) {
				state.print();
				//cout << endl;
			}
			if (terminal_test(state)) {
				state.print();
				cout << endl;
				terminal_test_winner(state);
				cout << endl;
				break;
			}
			state = minimaxDecision(state, INT_MIN, INT_MAX, 0);
			state.print();
			if (terminal_test(state)) {
				terminal_test_winner(state);
				cout << endl;
			}
		} while (!terminal_test(state));
	}
	if (choice == 2) {
		State s;
		State state = minimaxDecision(s, INT_MIN, INT_MAX, 0);
		state.print();
		int utilityVal = 0;
		while (!terminal_test(state)) {
			cout << "Your turn: ";
			int i, j;
			cin >> i >> j;
			state.setTableOponent(i, j);
			state.print();
			//cout << endl;
			state = minimaxDecision(state, INT_MIN, INT_MAX, 0);
			state.print();
			if (terminal_test(state)) {
				terminal_test_winner(state);
				cout << endl;
			}
		}
	}

	/*State s;
	State state = minimaxDecision(s);
	state.print();
	int utilityVal = 0;
	while (!terminal_test(state)) {
		cout << "Your turn: ";
		int i, j;
		cin >> i >> j;
		state.setTableOponent(i, j);
		state = minimaxDecision(state);
		state.print();
	}*/


	/*State s;
	cout << "Your turn: ";
	int i, j;
	cin >> i >> j;
	s.setTableOponent(i, j);
	s.print();
	State state = minimaxDecision(s);
	state.print();
	do {
		cout << "Your turn: ";
		cin >> i >> j;
		state.setTableOponent(i, j);
		if (!terminal_test(state)) {
			state.print();
			cout << endl;
		}
		if (terminal_test(state)) {
			state.print();
			cout << endl;
			terminal_test_winner(state);
			cout << endl;
			break;
		}
		state = minimaxDecision(state);
		state.print();
	} while (!terminal_test(state));
	*/

	return 0;
}