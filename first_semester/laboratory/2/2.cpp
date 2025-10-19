#include <iostream>

int main() {
    std::cout << "Enter the size for array\n";
    int size;
    if (!(std::cin >> size) || size <= 0) {
        std::cerr << "Invalid size or input.\n";
        return 1;
    }

    std::cout << "Enter the K (1-based index of series to delete)\n";
    int k;
    if (!(std::cin >> k) || k <= 0) {
        std::cerr << "Invalid K. K must be a positive integer.\n";
        return 1;
    }

    int *arr = new int[size];

    std::cout << "Enter the array\n";
    for (int i = 0; i < size; i++) {
        std::cin >> arr[i];
    } // Ввели массив и номер серии

    // --- 1. Поиск K-й серии и подсчет общего числа серий (длина >= 1) ---
    int total_series = 0;
    int i = 0;
    int del_start_index = -1; // Индекс начала K-й серии
    int del_end_index = -1;   // Индекс конца (эксклюзивный) K-й серии
    
    while (i < size) {
        int start_index = i;
        
        // Ищем конец текущей серии
        while (i < size - 1 && arr[i] == arr[i + 1]) {
            i++;
        }
        int end_index = i + 1;
        
        total_series++; // Каждая такая последовательность (длина >= 1) - это серия
        
        if (total_series == k) {
            // Найдена K-я серия
            del_start_index = start_index;
            del_end_index = end_index;
        }

        i++; // Переходим к следующему элементу, который будет началом новой серии
    }

    // --- 2. Вывод и удаление ---
    if (k > total_series) {
        // Случай А: K больше, чем общее количество серий
        std::cout << "K is greater than the total series count. Array remains:\n";
        for (int j = 0; j < size; j++) {
            std::cout << arr[j] << " ";
        }
        std::cout << "\n";
        delete[] arr;
        return 0;
    }
    else {
        // Случай B: K-я серия найдена и должна быть удалена
        
        int del_count = del_end_index - del_start_index;
        int newSize = size - del_count;
        
        // Выделяем новый массив, так как in-place изменение размера опасно
        int* newArr = new int[newSize];
        int new_arr_index = 0;

        // Копируем элементы до начала удаляемой серии
        for (int j = 0; j < del_start_index; ++j) {
            newArr[new_arr_index++] = arr[j];
        }

        // Пропускаем диапазон [del_start_index, del_end_index)

        // Копируем элементы после конца удаляемой серии
        for (int j = del_end_index; j < size; ++j) {
            newArr[new_arr_index++] = arr[j];
        }
        
        // Освобождаем старый массив
        delete[] arr;
        
        // Вывод и освобождение нового массива
        std::cout << "Array after deleting the " << k << "-th series:\n";
        for (int j = 0; j < newSize; ++j) {
            std::cout << newArr[j] << " ";
        }
        std::cout << "\n";
        
        delete[] newArr;
        return 0;
    }
}
