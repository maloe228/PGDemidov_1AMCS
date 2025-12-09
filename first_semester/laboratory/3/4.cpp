// 18

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <windows.h>

using namespace std;


unsigned int g_seed = 12345;


void mySrand(unsigned int seed) {
    g_seed = seed;
}

int myRand() {
    g_seed = g_seed * 1103515245 + 12345;
    return (unsigned int)(g_seed / 65536) % 32768;
}


void clearInputBuffer() {
    cin.clear();
    while (cin.get() != '\n');
}


int** allocateMatrix(int rows, int cols) {
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

void freeMatrix(int**& matrix, int rows) {
    if (matrix == nullptr) return;
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}

// Функции меню

// 1. Генерация случайной матрицы
void generateRandomMatrix(int**& matrix, int& rows, int& cols) {
    freeMatrix(matrix, rows);

    cout << "Введите размерность квадратной матрицы (N): ";
    while (!(cin >> rows) || rows <= 0) {
        cout << "Некорректный ввод. Введите положительное число: ";
        clearInputBuffer();
    }
    cols = rows;

    matrix = allocateMatrix(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Генерация числа от -10 до 10
            matrix[i][j] = myRand() % 21 - 10;
        }
    }
    cout << "Матрица " << rows << "x" << cols << " сгенерирована.\n";
}

// 2. Вывод матрицы
void printMatrixToScreen(int** matrix, int rows, int cols) {
    if (matrix == nullptr) {
        cout << "Ошибка: Матрица пуста.\n";
        return;
    }
    cout << "--- Матрица ---\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }
}

// 3. Сохранение в файл
void saveMatrixToFile(int** matrix, int rows, int cols) {
    if (matrix == nullptr) {
        cout << "Ошибка: Матрица пуста.\n";
        return;
    }
    char filename[100];
    string fname;
    cout << "Введите имя файла: ";
    cin >> fname;

    ofstream file(fname);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла.\n";
        return;
    }

    file << rows << " " << cols << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file << matrix[i][j] << " ";
        }
        file << endl;
    }
    file.close();
    cout << "Сохранено в " << fname << ".\n";
}

// 4. Ввод с клавиатуры
void inputMatrixFromKeyboard(int**& matrix, int& rows, int& cols) {
    freeMatrix(matrix, rows);

    cout << "Введите строки: ";
    while (!(cin >> rows) || rows <= 0) {
        cout << "Число должно быть > 0: ";
        clearInputBuffer();
    }

    cout << "Введите столбцы: ";
    while (!(cin >> cols) || cols <= 0) {
        cout << "Число должно быть > 0: ";
        clearInputBuffer();
    }

    matrix = allocateMatrix(rows, cols);
    cout << "Введите элементы (" << rows * cols << " шт):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            while (!(cin >> matrix[i][j])) {
                cout << "Это не число. Повторите ввод элемента: ";
                clearInputBuffer();
            }
        }
    }
    cout << "Матрица загружена.\n";
}

// 5. Загрузка из файла
void loadMatrixFromFile(int**& matrix, int& rows, int& cols) {
    string fname;
    cout << "Введите имя файла: ";
    cin >> fname;

    ifstream file(fname);
    if (!file.is_open()) {
        cout << "Ошибка: Не удалось открыть файл.\n";
        return;
    }

    freeMatrix(matrix, rows);

    if (!(file >> rows >> cols) || rows <= 0 || cols <= 0) {
        cout << "Ошибка: Некорректные данные в файле.\n";
        file.close();
        return;
    }

    matrix = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> matrix[i][j];
        }
    }
    file.close();
    cout << "Загружено.\n";
}

// 6. Характеристика: четное ли кол-во строк с неотрицательными элементами
void calculateCharacteristic(int** matrix, int rows, int cols) {
    if (matrix == nullptr) {
        cout << "Ошибка: Матрица пуста.\n";
        return;
    }

    int validRowsCount = 0;
    for (int i = 0; i < rows; ++i) {
        bool hasNegative = false;
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] < 0) {
                hasNegative = true;
                break;
            }
        }
        if (!hasNegative) {
            validRowsCount++;
        }
    }

    cout << "Строк без отрицательных элементов: " << validRowsCount << endl;
    if (validRowsCount % 2 == 0)
        cout << "Результат: ИСТИНА (четно).\n";
    else
        cout << "Результат: ЛОЖЬ (нечетно).\n";
}

// 7. Преобразование: B[i][j] = A[i][j] * max(строки i)
void transformMatrix(int** source, int rows, int cols, int**& dest, int& dRows, int& dCols) {
    if (source == nullptr) {
        cout << "Ошибка: Исходная матрица пуста.\n";
        return;
    }

    freeMatrix(dest, dRows);
    dRows = rows;
    dCols = cols;
    dest = allocateMatrix(dRows, dCols);

    for (int i = 0; i < rows; ++i) {
        int maxInRow = source[i][0];
        for (int j = 1; j < cols; ++j) {
            if (source[i][j] > maxInRow) {
                maxInRow = source[i][j];
            }
        }
        for (int j = 0; j < cols; ++j) {
            dest[i][j] = source[i][j] * maxInRow;
        }
    }
    cout << "Матрица B создана.\n";
}

// 8. Печать B
void printTransformedMatrix(int** matrixB, int rows, int cols) {
    if (matrixB == nullptr) {
        cout << "Матрица B не создана.\n";
        return;
    }
    cout << "--- Матрица B ---\n";
    printMatrixToScreen(matrixB, rows, cols);
}

// 9. Сохранение B
void saveTransformedMatrix(int** matrixB, int rows, int cols) {
    if (matrixB == nullptr) {
        cout << "Матрица B не создана.\n";
        return;
    }
    saveMatrixToFile(matrixB, rows, cols);
}

// --- Main ---

int main() {
    SetConsoleOutputCP(CP_UTF8);

    mySrand(static_cast<unsigned int>(time(0)));

    int** matrixA = nullptr;
    int rowsA = 0, colsA = 0;

    int** matrixB = nullptr;
    int rowsB = 0, colsB = 0;

    int choice;
    do {
        cout << "\n=== МЕНЮ ===\n";
        cout << "1. Генерация А\n2. Вывод А\n3. Сохранить А\n4. Ввод А (клавиатура)\n5. Загрузить А\n";
        cout << "6. Характеристика\n7. Преобразование в B\n8. Вывод B\n9. Сохранить B\n10. Выход\n";
        cout << "> ";

        if (!(cin >> choice)) {
            clearInputBuffer();
            choice = 0;
        }

        switch (choice) {
            case 1: generateRandomMatrix(matrixA, rowsA, colsA); break;
            case 2: printMatrixToScreen(matrixA, rowsA, colsA); break;
            case 3: saveMatrixToFile(matrixA, rowsA, colsA); break;
            case 4: inputMatrixFromKeyboard(matrixA, rowsA, colsA); break;
            case 5: loadMatrixFromFile(matrixA, rowsA, colsA); break;
            case 6: calculateCharacteristic(matrixA, rowsA, colsA); break;
            case 7: transformMatrix(matrixA, rowsA, colsA, matrixB, rowsB, colsB); break;
            case 8: printTransformedMatrix(matrixB, rowsB, colsB); break;
            case 9: saveTransformedMatrix(matrixB, rowsB, colsB); break;
            case 10: cout << "Выход.\n"; break;
            default: cout << "Неверный выбор.\n";
        }

    } while (choice != 10);

    freeMatrix(matrixA, rowsA);
    freeMatrix(matrixB, rowsB);

    return 0;
}

// C:\\Users\\vaces\\CLionProjects\\prog1\\input.txt
// C:\\Users\\vaces\\CLionProjects\\prog1\\output.txt

// 4 5
// 0 -5 8 1 3
// 1 7 10 0 4
// 2 2 -1 9 5
// 3 1 2 6 3
