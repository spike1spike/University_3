#include <vector>
#include <iostream>

int get_max_mass(const int capacity, const std::vector<int>& v_weight) {
	std::vector<bool> v_weight_bool(capacity + 1, false);
	v_weight_bool[0] = true;

	for (int w_curr : v_weight) {
		for (int i_dyn = capacity; i_dyn >= w_curr; i_dyn--) {
			if (v_weight_bool[i_dyn - w_curr]) { v_weight_bool[i_dyn] = true; }
		}
	}

	for (int i = (v_weight_bool.size() - 1); i >= 0; i--) {
		if (v_weight_bool[i]) { return i; }
	}
}

int main() {
	setlocale(LC_CTYPE, "rus");

	int n, M;
	std::cin >> n >> M;

	std::vector<int> w(n);
	for (int i = 0; i < n; i++) {
		std::cin >> w[i];
	}

	int max_mass = get_max_mass(M, w);
	std::cout << "Максимальная масса, которую можно забрать с собой: " << max_mass << " кг" << std::endl;

	return 0;
}