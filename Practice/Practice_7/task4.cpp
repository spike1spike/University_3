#include <iostream>
#include <vector>

bool col_has_queen(const std::vector<std::vector<bool>>& chessboard_bool, int col) {
	for (int row = 0; row < chessboard_bool.size(); row++) {
		if (chessboard_bool[row][col]) { return true; }
	}

	return false;
}

bool diag_l_has_queen(const std::vector<std::vector<bool>>& chessboard_bool, int row, int col) {
	int orig_row = row;
	int orig_col = col;

	while ((row >= 0) && (col >= 0)) {
		if (chessboard_bool[row][col]) { return true; }
		row--;
		col--;
	}

	row = orig_row;
	col = orig_col;

	while ( (row <= (chessboard_bool.size() - 1)) && (col <= (chessboard_bool[0].size() - 1)) ) {
		if (chessboard_bool[row][col]) { return true; }
		row++;
		col++;
	}

	return false;
}

bool diag_r_has_queen(const std::vector<std::vector<bool>>& chessboard_bool, int row, int col) {
	int orig_row = row;
	int orig_col = col;

	while ((row >= 0) && (col <= (chessboard_bool[0].size() - 1))) {
		if (chessboard_bool[row][col]) { return true; }
		row--;
		col++;
	}

	row = orig_row;
	col = orig_col;

	while ((row <= (chessboard_bool.size() - 1)) && (col >= 0)) {
		if (chessboard_bool[row][col]) { return true; }
		row++;
		col--;
	}

	return false;
}

bool place_queens(std::vector<std::vector<bool>>& chessboard_bool, int n, int row) {
	if (n == 0) { return true; }

	for (int col = 0; col < chessboard_bool[0].size(); col++) {
		if (col_has_queen(chessboard_bool, col) ||
			diag_l_has_queen(chessboard_bool, row, col) ||
			diag_r_has_queen(chessboard_bool, row, col)) { continue; }

		chessboard_bool[row][col] = true;
		n--;
		
		row++;
		if (place_queens(chessboard_bool, n, row)) { return true; };

		row--;
		chessboard_bool[row][col] = false;
		n++;
	}

	return false;
}

void place_queens_init(std::vector<std::vector<bool>>& chessboard_bool, int n) {
	int row = 0;
	place_queens(chessboard_bool, n, row);
}

int main() {
	int n;
	std::cin >> n;

	std::vector<std::vector<bool>> chessboard_bool(n, std::vector<bool>(n, false));
	place_queens_init(chessboard_bool, n);

	for (const std::vector<bool>& row : chessboard_bool) {
		for (const bool& cell : row) {
			if (cell) { std::cout << "Q"; }
			else { std::cout << "."; }
		}
		std::cout << std::endl;
	}

	return 0;
}