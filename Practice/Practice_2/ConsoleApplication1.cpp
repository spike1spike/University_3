#include <iostream>
#include <cmath>

using namespace std;

double simpson_rule(double (*f)(double), double a, double b, int n) {
	if (n % 2 == 1) {
		n++;
	}
	double h = (b - a) / n;
	double sum = f(a) + f(b);

	for (int i = 1; i < n; i += 2) {
		sum += 4 * f(a + i * h);
	}
	for (int i = 2; i < n-1; i += 2) {
		sum += 2 * f(a + i * h);
	}

	return (h / 3) * sum;
}

double function(double x) {
	return 4 - abs(x);
}

int main() {
	setlocale(LC_CTYPE, "rus");

	for (int i = 2; i < 1001; i += 2) {
		double result = simpson_rule(function, -4, 4, i);
		cout << "Численное значение интеграла при n = " << i << ": " << result << endl;
	}

	return 0;
}