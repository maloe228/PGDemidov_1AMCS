#include <iostream>

int main() {
	int n, max = 0;
	std::cin >> n;

	int* numbers{ new int[n] }; // динамический массив из n чисел

	for (int i = 0; i < n; i++){ // Ввод в массив

		std::cin >> numbers[i];
	}

	for (int i = 0; i < n; i++) { 

		if (numbers[i] > max) { // Ищем максимальное
			max = numbers[i];
		}
	}

	std::cout << max;
	return 0;
}
