// MazeGen.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
int counter = 0;
int counter2 = 0;
std::string getval(bool wall) {
	if (wall)
		return "[]";
	else
		return "  ";
}

class maze {
	bool is_wall[8][8];//[] row [] column
	bool is_checked[8][8];
	bool can_move[8][8];
	int len = 8;
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

	void set_can_move() {
		for (int y = 0; y < len; y++) {
			for (int x = 0; x < len; x++) {
				can_move[x][y] = !is_wall[x][y];
			}
		}
		can_move[1][0] = false;
		can_move[len - 2][len - 1] = false;
	}

	void print() {
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < len; j++) {
				std::cout << getval(is_wall[i][j]);
			}
			std::cout << "\n";
		}
	}

	void print2() {
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < len; j++) {
				std::cout << getval(!can_move[i][j]);
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

	bool is_in_bounds(int x, int y) {
		return true;// x < len&& x > 0 && y < len && y > 0;
	}

	void flood_fill(int x, int y) {
		//std::cout << x << y << std::endl;
		//print2();
		//x = 1;
		//y = 1;
		counter2++;
		bool tmp = can_move[x][y];
		can_move[x][y] = false;
		if (tmp) {
			std::cout << "j " << tmp << std::endl;
			//if (can_move[x + 1][y] && is_in_bounds(x + 1, y)) {
				//std::cout << x + 1 <<" " << y << std::endl;

				flood_fill(x + 1, y);
			//}
			//if (can_move[x - 1][y] && is_in_bounds(x - 1, y)) {
				flood_fill(x - 1, y);
			//}
			//if (can_move[x][y - 1] && is_in_bounds(x, y - 1)) {
				flood_fill(x, y - 1);
			///}
			//if (can_move[x][y + 1] && is_in_bounds(x, y + 1)) {
				flood_fill(x, y + 1);
			//}
		}
	}

	bool is_filled() {
		counter = 0;
		bool flag = true;
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < len; j++) {
				//std::cout << is_checked[i][j] << std::endl;
				if (can_move[i][j]) {
					counter++;
					flag = false;
					//return false;
				}
			}
		}
		std::cout << flag << std::endl;
		print2();
		return flag;
	}

	bool can_go_everywhere(int r1, int r2) {
		can_move[r1][r2] = false;
		flood_fill(1, 1);
		std::cout << "bip " << counter2 << std::endl;
		counter2 = 0;
		return is_filled();
	}

	void generate() {
		set_can_move();
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
			std::cout << counter << std::endl;
			is_checked[r1][r2] = true;
			set_can_move();
			//can_move[r1][r2] = false;
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
