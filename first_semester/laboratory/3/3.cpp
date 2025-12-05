// 6

#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>

using namespace std;

// Размерность матриц (статическая константа)
const int N = 2;

// Функция для чтения матрицы из файла
void readMatrix(ifstream& in, double matrix[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            in >> matrix[i][j];
        }
    }
}

// Функция для записи матрицы в файл
void writeMatrix(ofstream& out, double matrix[N][N], const char* name) {
    out << "Матрица " << name << ":" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            out << setw(10) << setprecision(4) << matrix[i][j] << " ";
        }
        out << endl;
    }
    out << endl;
}

// Умножение матриц: Res = A * B
void multiplyMatrices(double A[N][N], double B[N][N], double Res[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            Res[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                Res[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Вычитание матриц: Res = A - B
void subtractMatrices(double A[N][N], double B[N][N], double Res[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            Res[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Умножение матрицы на число: Res = num * A
void multiplyByScalar(double A[N][N], double num, double Res[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            Res[i][j] = A[i][j] * num;
        }
    }
}

// Нахождение определителя матрицы 2x2
double determinant(double A[N][N]) {
    return A[0][0] * A[1][1] - A[0][1] * A[1][0];
}

// Нахождение обратной матрицы для 2x2
bool inverseMatrix(double A[N][N], double Res[N][N]) {
    double det = determinant(A);
    if (det == 0) return false; // Обратной матрицы не существует

    // Формула для 2x2: меняем местами элементы главной диагонали,
    // меняем знаки побочной, и делим все на определитель.
    Res[0][0] = A[1][1] / det;
    Res[0][1] = -A[0][1] / det;
    Res[1][0] = -A[1][0] / det;
    Res[1][1] = A[0][0] / det;

    return true;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    ifstream inFile("C:\\Users\\vaces\\CLionProjects\\prog1\\input.txt");
    ofstream outFile("C:\\Users\\vaces\\CLionProjects\\prog1\\output.txt");


    if (!inFile.is_open()) {
        cout << "Ошибка: Не удалось открыть файл input.txt" << endl;
        return 1;
    }

    // 1. Объявление статических массивов
    double A[N][N], B[N][N], C[N][N];
    double AB[N][N];        // A * B
    double D[N][N];         // AB - C
    double D_inv[N][N];     // Обратная к D
    double C2[N][N];        // 2 * C
    double X[N][N];         // Результат

    // 2. Чтение данных
    readMatrix(inFile, A);
    readMatrix(inFile, B);
    readMatrix(inFile, C);

    outFile << "--- Исходные данные ---" << endl;
    writeMatrix(outFile, A, "A");
    writeMatrix(outFile, B, "B");
    writeMatrix(outFile, C, "C");

    // 3. Вычисления по шагам: X = (2C) * (AB - C)^(-1)

    // Шаг 1: AB = A * B
    multiplyMatrices(A, B, AB);
    writeMatrix(outFile, AB, "AB (произведение A и B)");

    // Шаг 2: D = AB - C
    subtractMatrices(AB, C, D);
    writeMatrix(outFile, D, "D (AB - C)");

    // Шаг 3: C2 = 2 * C
    multiplyByScalar(C, 2.0, C2);
    writeMatrix(outFile, C2, "2C");

    // Шаг 4: Обратная матрица D_inv
    if (!inverseMatrix(D, D_inv)) {
        outFile << "Ошибка: Определитель матрицы (AB - C) равен 0. Решения нет." << endl;
        cout << "Решения нет (детерминант 0)." << endl;
    } else {
        writeMatrix(outFile, D_inv, "D^(-1) (Обратная к AB-C)");

        // Шаг 5: X = 2C * D^(-1)
        // Внимание: уравнение XD = 2C, значит X = 2C * D^(-1).
        // Порядок умножения важен! Сначала 2C, потом D_inv.
        multiplyMatrices(C2, D_inv, X);

        outFile << "--- Ответ ---" << endl;
        writeMatrix(outFile, X, "X");

        cout << "Расчет завершен. Результаты сохранены в output.txt" << endl;
    }

    inFile.close();
    outFile.close();

    return 0;
}

// 1 1
// 3 4
// 2 1
// 1 1
// 1 2
// 1 3
