#include <iostream>

int main() {
	int n, max = 0;
	std::cin >> n;

	int* numbers{ new int[n] }; // динамический массив из n чисел

	for (int i = 0; i < n; i++){ // Ввод в массив

		std::cin >> numbers[i];
	}

	if (n % 2 != 2) {
		for (int i = 0; i < n-1; i += 2) {
			
			int b = numbers[i]; // создали дополнительную переменную
			numbers[i] = numbers[i + 1]; // меняем местами
			numbers[i + 1] = b; // значения элементов
			
		}

	}
	else {
		for (int i = 0; i < n; i += 2) {

			int b = numbers[i]; // создали дополнительную переменную
			numbers[i] = numbers[i + 1]; // меняем местами
			numbers[i + 1] = b; // значения элементов

		}

	}

	for (int i = 0; i < n; i++) {
		std::cout << numbers[i] << " "; // выводим элементы массива
	}
	
	return 0;

}
