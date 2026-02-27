#include <clocale>﻿
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
	for (int i = 2; i < n - 1; i += 2) {
		sum += 2 * f(a + i * h);
	}

	return (h / 3) * sum;
}

double function_1(double x) {
	return 4 + x;
}

double function_2(double x) {
	return 4 - x;
}

int main() {
	setlocale(LC_CTYPE, "rus");

	for (int i = 2; i < 11; i += 2) {
		double result_1 = simpson_rule(function_1, -4, 0, i);
		double result_2 = simpson_rule(function_2, 0, 4, i);
		double result = result_1 + result_2;
		cout << "Численное значение интеграла при n = " << i << ": " << result << endl;
	}

	return 0;
}