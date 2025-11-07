// 7

#include <iostream>

int main() {
    std::cout << "Enter the size for array\n";
    int size;
    std::cin >> size;


    std::cout << "Enter the K\n";
    int k;
    std::cin >> k;


    int *arr = new int[size];

    std::cout << "Enter the array\n";
    for (int i = 0; i < size; i++) {
        std::cin >> arr[i];
    }

    // Ввели массив и номер серии

    // Поиск K-й серии
    int total_series = 0;
    int i = 0;
    int del_start_index = -1; // Индекс начала K-й серии
    int del_end_index = -1;   // Индекс конца K-й серии

    while (i < size) {
        int start_index = i;

        // Ищем конец текущей серии
        while (i < size - 1 && arr[i] == arr[i + 1]) {
            i++;
        }
        int end_index = i + 1;

        total_series++; // Каждая такая последовательность серия

        if (total_series == k) {
            // Найдена K-я серия
            del_start_index = start_index;
            del_end_index = end_index;
        }

        i++;
    }

    // Удаление и вывод
    if (k > total_series) {
        // K больше, чем общее количество серий
        for (int j = 0; j < size; j++) {
            std::cout << arr[j] << " ";
        }
        std::cout << "\n";
        delete[] arr;
        return 0;
    }
    else {
        // Удаление

        int newSize = size - (del_end_index - del_start_index);

        // Выделяем новый массив
        int* newArr = new int[newSize];
        int new_arr_index = 0;

        // Копируем элементы до начала удаляемой серии
        for (int j = 0; j < del_start_index; ++j) {
            newArr[new_arr_index] = arr[j];
            ++new_arr_index;
        }

        // Копируем элементы после конца удаляемой серии
        for (int j = del_end_index; j < size; ++j) {
            newArr[new_arr_index++] = arr[j];
        }

        delete[] arr;

        // Вывод
        for (int j = 0; j < newSize; ++j) {
            std::cout << newArr[j] << " ";
        }
        std::cout << "\n";

        delete[] newArr;
        return 0;
    }
}
