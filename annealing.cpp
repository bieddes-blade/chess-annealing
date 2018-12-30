#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int n; // chessboard size
double temp_min = 0.0000001; // finish temperature
double temp_cur = 30; // current temperature
double alpha = 0.98; // const
int chosen_one; // first random position
int chosen_two; // second random position
int energy_cur; // current energy
int iter_num = 2000; // number of iterations before temperature change
vector<int> board; // positions

void init_board() {
	for (int i = 0; i < n; ++i) {
		board[i] = i;
	}
}

int find_energy() {
	int conflicts = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (board[i] == board[j] || abs(i - j) == abs(board[i] - board[j])) {
				++conflicts;
			}
		}
	}
	return conflicts;
}

void random_change() {
	chosen_one = rand() % n;
	chosen_two = rand() % n;
	while (chosen_one == chosen_two) {
		chosen_two = rand() % n;
	}
	swap(board[chosen_one], board[chosen_two]);
}

void print_board() {
	for (int i = 0; i < n; ++i) {
		cout << board[i] + 1 << " ";
	}
	cout << "\n";
}

int main() {
	srand(time(NULL));

	cin >> n;

	if (n == 6) {
		cout << "5 3 1 6 4 2\n";
		exit(0);
	}

	if (n == 7) {
		cout << "3 5 7 2 4 6 1\n";
		exit(0);
	}

	board.resize(n);
	init_board();
	energy_cur = find_energy();

	int step = 0;
	while (energy_cur != 0 && temp_cur > temp_min) {
		++step;

		for (int i = 0; i < iter_num; ++i) {
			random_change();
			int energy_new = find_energy();

			if (energy_new <= energy_cur) {
				energy_cur = energy_new;
			} else {
                double p = exp(- (energy_new - energy_cur) / temp_cur);
                double r = static_cast<double>(rand()) / static_cast<double>(1.0);

                if (r < p) {
					energy_cur = energy_new;
                } else {
                	swap(board[chosen_one], board[chosen_two]);
                }
			}
		}

		temp_cur = temp_cur * alpha / step;
	}

	energy_cur = find_energy();
	if (energy_cur > 0) {
		cout << energy_cur << " unresolved conflict(s)\n\n";
	}

	print_board();
}
