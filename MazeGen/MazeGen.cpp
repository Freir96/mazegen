// MazeGen.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

std::string getval(bool wall) {
	if (wall)
		return "[]";
	else
		return "  ";
}

class maze {
	bool is_wall[6][6];//[] row [] column
	bool is_checked[6][6];
	int len = 6;
public:
	void start() {
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < len; j++) {
				is_wall[i][j] = false;
				is_checked[i][j] = false;
			}
		}
		for (int i = 0; i < len; i++) {
			is_wall[i][0] = true;
			is_wall[i][len - 1] = true;
			is_wall[0][i] = true;
			is_wall[len - 1][i] = true;
			is_checked[i][0] = true;
			is_checked[i][len - 1] = true;
			is_checked[0][i] = true;
			is_checked[len - 1][i] = true;
		}
		is_wall[1][0] = false;
		is_wall[len - 2][len - 1] = false;
	}

	void print() {
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < len; j++) {
				std::cout << getval(is_wall[i][j]);
			}
			std::cout << "\n";
		}
	}

	bool shouldIcheck() {
		//std::cout << "bip" << std::endl;
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < len; j++) {
				//std::cout << is_checked[i][j] << std::endl;
				if (!is_checked[i][j])
					return true;
			}
		}
		return false;
	}

	bool is_corner(int r1, int r2) {
		if (is_wall[r1 + 1][r2] && is_wall[r1][r2 + 1] && is_wall[r1 + 1][r2 + 1])
			return true;
		if (is_wall[r1 - 1][r2] && is_wall[r1][r2 - 1] && is_wall[r1 - 1][r2 - 1])
			return true;
		if (is_wall[r1 + 1][r2] && is_wall[r1][r2 - 1] && is_wall[r1 + 1][r2 - 1])
			return true;
		if (is_wall[r1 - 1][r2] && is_wall[r1][r2 + 1] && is_wall[r1 - 1][r2 + 1])
			return true;
		return false;
	}

	bool can_go_everywhere(int r1, int r2) {
		return true;
	}

	void generate() {
		while (shouldIcheck()) {
			//std::cout << "testing" << std::endl;
			int r1 = rand() % (len - 1), r2 = rand() % (len - 1);
			while (is_checked[r1][r2]) {
				r1 = rand() % (len - 1), r2 = rand() % (len - 1);
			}
			//std::cout << r1 << r2 << std::endl;
			if (!is_corner(r1, r2) && can_go_everywhere(r1, r2))
				is_wall[r1][r2] = true;
			else
				is_wall[r1][r2] = false;
			is_checked[r1][r2] = true;
		}
	}
};

int main()
{
	srand(time(NULL));
	maze m;
	m.start();
	m.generate();
	m.print();
	return 0;
}
