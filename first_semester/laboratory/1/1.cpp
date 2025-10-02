#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

int main(){

	double al;
	long double a, b;
	std::cin >> al;

	a = 1 - 4 * pow((sin(2 * al)),2);
	b = 2 * cos(4 * al) - 1;

	std::cout << std::fixed << std::setprecision(6) << '\n' << "A = " << a << '\n' << "B = " << b << '\n' << "A - B = " << a - b; // Точность вывода
}
