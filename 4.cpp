#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

int main(){
	setlocale(LC_ALL, "Russian"); // Подключаем отображение русског

	double x, y;
	int num;
	std::cin >> x >> y;
	std::cin >> num;

	if (num == 1) {
		if ((((y <= x * x) && (x <= 0) && (y >= 2 - x)) || ((x >= 0) && (y <= x*x) && (x <= 2-x) && (y >= 0)))) {
			std::cout << "Принадлежит";
			return 0;
		}
		else {
			std::cout << "Не принадлежит";
			return 0;
		}
	}
	if ((num == 2) && (x >= 0) && (y >= 0)) {

		// Сводим к общему случаю
		while (x >= 2) {
			x -= 2;
		}
		while (y >= 2) {
			y -= 2;
		}

		
		// Левый нижний
		if ((x <= 1) && (y <= 1) && ((sqrt((x - 0) * (x - 0) + (y - 1) * (y - 1))) <= 1)) {
			std::cout << "Принадлежит";
			return 0;
		}

		// Правый нижний 000
		if ((x <= 2) && (x > 1) && (y <= 1) && ((sqrt((x - 1) * (x - 1) + (y - 0) * (y - 0))) <= 1)) {
			std::cout << "Принадлежит";
			return 0;
		}

		// Левый верхний
		if ((x <= 1) && (y <= 2) && (y > 1) && ((sqrt((x - 1) * (x - 1) + (y - 1) * (y - 1))) <= 1)) {
			std::cout << "Принадлежит";
			return 0;
		}

		// Правый верхний
		if ((x <= 2) && (x > 1) && (y <= 2) && (y > 1) && ((sqrt((x - 1) * (x - 1) + (y - 2) * (y - 2))) <= 1)) {
			std::cout << "Принадлежит";
			return 0;
		}
		else {
			std::cout << "Не принадлежит";
			return 0;
		}
	}
}
