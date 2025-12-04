// 17

#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>

using namespace std;

// Функция для выделения памяти под матрицу n x n
double** createMatrix(int n) {
    double** matrix = new double*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new double[n];
    }
    return matrix;
}

// Функция для освобождения памяти
void deleteMatrix(double** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Функция для чтения матрицы из файла
void readMatrix(ifstream& in, double** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> matrix[i][j];
        }
    }
}

// Функция для записи матрицы в файл
void printMatrix(ofstream& out, double** matrix, int n, const char* title) {
    out << title << ":" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            out << setw(10) << matrix[i][j] << " ";
        }
        out << endl;
    }
    out << "-----------------------------------" << endl;
}

// Умножение матриц (A * B)
double** multiplyMatrices(double** A, double** B, int n) {
    double** result = createMatrix(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// Сложение матриц (A + B)
double** addMatrices(double** A, double** B, int n) {
    double** result = createMatrix(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

// Вычитание матриц (A - B)
double** subtractMatrices(double** A, double** B, int n) {
    double** result = createMatrix(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

// Умножение матрицы на число (k * A)
double** scaleMatrix(double** A, double scalar, int n) {
    double** result = createMatrix(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = A[i][j] * scalar;
        }
    }
    return result;
}

// Создание единичной матрицы (E)
double** createIdentityMatrix(int n) {
    double** result = createMatrix(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
    return result;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    ifstream inFile("C:\\Users\\vaces\\CLionProjects\\prog1\\input.txt");
    ofstream outFile("C:\\Users\\vaces\\CLionProjects\\prog1\\output.txt");

    if (!inFile.is_open()) {
        cerr << "Ошибка: Не удалось открыть input.txt" << endl;
        return 1;
    }

    int n;
    inFile >> n; // Считываем размерность матрицы

    // 1. Считываем матрицу A
    double** A = createMatrix(n);
    readMatrix(inFile, A, n);
    printMatrix(outFile, A, n, "Матрица A");

    // 2. Вычисляем степени матрицы: A^2 и A^3
    double** A2 = multiplyMatrices(A, A, n);
    printMatrix(outFile, A2, n, "Матрица A^2");

    double** A3 = multiplyMatrices(A2, A, n);
    printMatrix(outFile, A3, n, "Матрица A^3");

    // 3. Вычисляем f(A) = 2*A^2 - A
    double** term2A2 = scaleMatrix(A2, 2.0, n);
    double** fA = subtractMatrices(term2A2, A, n);
    printMatrix(outFile, fA, n, "Значение f(A) = 2A^2 - A");

    // 4. Вычисляем g(A) = 2*A^3 - A + 3E
    double** term2A3 = scaleMatrix(A3, 2.0, n);
    double** term3E = createIdentityMatrix(n); // Создаем E
    double** temp3E_Scaled = scaleMatrix(term3E, 3.0, n); // Масштабируем до 3E

    // Сначала (2A^3 - A)
    double** tempG = subtractMatrices(term2A3, A, n);
    // Затем + 3E
    double** gA = addMatrices(tempG, temp3E_Scaled, n);
    printMatrix(outFile, gA, n, "Значение g(A) = 2A^3 - A + 3E");

    // 5. Итоговая сумма f(A) + g(A)
    double** result = addMatrices(fA, gA, n);
    printMatrix(outFile, result, n, "РЕЗУЛЬТАТ f(A) + g(A)");

    cout << "Вычисления завершены. Результат записан в output.txt" << endl;

    // --- Очистка памяти ---
    deleteMatrix(A, n);
    deleteMatrix(A2, n);
    deleteMatrix(A3, n);
    deleteMatrix(term2A2, n);
    deleteMatrix(fA, n);
    deleteMatrix(term2A3, n);
    deleteMatrix(term3E, n);
    deleteMatrix(temp3E_Scaled, n);
    deleteMatrix(tempG, n);
    deleteMatrix(gA, n);
    deleteMatrix(result, n);

    inFile.close();
    outFile.close();

    return 0;
}

// 3
// 1 2 3
// 4 5 6
// 7 8 9
