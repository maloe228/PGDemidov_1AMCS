// 3

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <windows.h>

using namespace std;

// Функция для выделения памяти под матрицу
int** allocateMatrix(int n) {
    int** mat = new int*[n];
    for (int i = 0; i < n; ++i) {
        mat[i] = new int[n];
    }
    return mat;
}

// Функция для освобождения памяти
void freeMatrix(int** mat, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] mat[i];
    }
    delete[] mat;
}

// Вычисление миноров.
int** getSubmatrix(int** mat, int n, int rowToRemove, int colToRemove) {
    int** subMat = allocateMatrix(n - 1);
    int subI = 0;
    for (int i = 0; i < n; ++i) {
        if (i == rowToRemove) continue; // Пропускаем удаляемую строку
        int subJ = 0;
        for (int j = 0; j < n; ++j) {
            if (j == colToRemove) continue; // Пропускаем удаляемый столбец
            subMat[subI][subJ] = mat[i][j];
            subJ++;
        }
        subI++;
    }
    return subMat;
}

// Вычисление определителя
int calculateDeterminantRecursive(int** mat, int n) {
    if (n == 1) return mat[0][0];
    if (n == 2) return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

    int det = 0;

    for (int j = 0; j < n; ++j) {
        int** subMat = getSubmatrix(mat, n, 0, j);
        int sign = (j % 2 == 0) ? 1 : -1;
        det += sign * mat[0][j] * calculateDeterminantRecursive(subMat, n - 1);
        freeMatrix(subMat, n - 1);
    }
    return det;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    ifstream inputFile("C:\\Users\\vaces\\CLionProjects\\prog1\\input.txt");
    ofstream outputFile("C:\\Users\\vaces\\CLionProjects\\prog1\\output.txt");

    if (!inputFile.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл input.txt" << endl;
        return 1;
    }

    int n;
    inputFile >> n; // Считываем размерность

    if (n < 1) {
        cerr << "Ошибка: Некорректный размер матрицы" << endl;
        return 1;
    }

    // Выделение памяти и чтение матрицы
    int** matrix = allocateMatrix(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inputFile >> matrix[i][j];
        }
    }
    inputFile.close();


    long long totalDeterminant = 0;
    int lastRowIndex = n - 1; // Последняя строка (индексация с 0)

    // Проход по элементам последней строки
    for (int j = 0; j < n; ++j) {
        int element = matrix[lastRowIndex][j];

        // Создаем подматрицу для минора (вычеркиваем последнюю строку и j-й столбец)
        int** subMat = getSubmatrix(matrix, n, lastRowIndex, j);

        // Вычисляем определитель подматрицы (минор)
        int minorVal = calculateDeterminantRecursive(subMat, n - 1); // Размерность на 1 меньше

        // Освобождаем память подматрицы сразу, как она стала не нужна
        freeMatrix(subMat, n - 1);

        // Определяем знак (-1)^(row + col).
        // row = lastRowIndex, col = j.
        int signPower = lastRowIndex + j;
        int sign = (signPower % 2 == 0) ? 1 : -1;

        int term = sign * element * minorVal;
        totalDeterminant += term;

        // Пошаговая запись в файл
        outputFile << "Шаг " << j + 1 << ":\n";
        outputFile << "  Элемент A[" << lastRowIndex << "][" << j << "] = " << element << "\n";
        outputFile << "  Знак (-1)^(" << lastRowIndex << "+" << j << ") = " << (sign > 0 ? "+" : "-") << "1\n";
        outputFile << "  Минор (определитель подматрицы) M_" << lastRowIndex << "," << j << " = " << minorVal << "\n";
        outputFile << "  Слагаемое: " << sign << " * " << element << " * " << minorVal << " = " << term << "\n";
        outputFile << "  Текущая сумма: " << totalDeterminant << "\n";
        outputFile << "------------------------------------------------------------\n";
    }

    outputFile << "Итоговый определитель: " << totalDeterminant << endl;
    cout << "Вычисление завершено. Результат: " << totalDeterminant << endl;

    outputFile.close();
    freeMatrix(matrix, n);

    return 0;
}

// 3
// 1 2 3
// 0 4 5
// 1 0 6
