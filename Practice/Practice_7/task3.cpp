#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>

int find_max_subarray_cross(const std::vector<int>& v, int i_left, int i_mid, int i_right) {
	int sum = 0;
	int left_sum = std::numeric_limits<int>::min();
	for (int i = i_mid; i >= i_left; i--) {
		sum += v[i];
		left_sum = std::max(left_sum, sum);
	}

	sum = 0;
	int right_sum = std::numeric_limits<int>::min();
	for (int i = (i_mid + 1); i <= i_right; i++) {
		sum += v[i];
		right_sum = std::max(right_sum, sum);
	}

	return (left_sum + right_sum);
}

int find_max_subarray(const std::vector<int>& v, int i_left, int i_right) {
	if (i_left == i_right) { return v[i_left]; }

	int i_mid = (i_left + i_right) / 2;
	int max_left = find_max_subarray(v, i_left, i_mid);
	int max_cross = find_max_subarray_cross(v, i_left, i_mid, i_right);
	int max_right = find_max_subarray(v, i_mid + 1, i_right);

	return std::max({ max_left, max_cross, max_right });
}

int main() {
	setlocale(LC_CTYPE, "rus");
	
	int n;
	std::cin >> n;

	std::vector<int> v(n);
	for (int i = 0; i < n; i++) {
		std::cin >> v[i];
	}

	int max_sum = find_max_subarray(v, 0, v.size() - 1);
	std::cout << "Максимальная сумма подотрезка: " << max_sum << std::endl;

	return 0;
}