// 12

#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);

    int n;
    cout << "Введите размер куба (n): ";
    cin >> n;

    if (n <= 0) {
        cout << "Размер должен быть положительным числом.\n";
        return 1;
    }

    // 3x massive
    int*** cube = new int**[n];
    for (int i = 0; i < n; ++i) {
        cube[i] = new int*[n];
        for (int j = 0; j < n; ++j) {
            cube[i][j] = new int[n];
        }
    }

    int redCount = 0;

    // Заполнение массива и подсчет красных кубов
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            for (int z = 0; z < n; ++z) {
                if (x % 3 == 0 && y % 5 == 0) {
                    cube[x][y][z] = 1; // 1 - Красный
                    redCount++;
                } else {
                    cube[x][y][z] = 0; // 0 - Белый
                }
            }
        }
    }

    // Вывод результатов на экран и в файл
    ofstream outFile("C:\\Users\\vaces\\CLionProjects\\prog1\\output.txt");

    if (!outFile.is_open()) {
        cout << "Ошибка открытия файла для записи!\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                delete[] cube[i][j];
            }
            delete[] cube[i];
        }
        delete[] cube;
        return 1;
    }

    cout << "\n--- Конфигурация Куба (Послойно по Z) ---\n";
    outFile << "--- Конфигурация Куба (Послойно по Z) ---\n";

    // Выводим слои
    for (int z = 0; z < n; ++z) {
        cout << "Слой Z = " << z << ":\n";
        outFile << "Слой Z = " << z << ":\n";

        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < n; ++y) {
                char symbol = (cube[x][y][z] == 1) ? 'R' : '.'; // R - Red, . - White
                cout << symbol << " ";
                outFile << symbol << " ";
            }
            cout << endl;
            outFile << endl;
        }
        cout << endl;
        outFile << endl;
    }

    cout << "Общее количество красных кубов: " << redCount << endl;
    outFile << "Общее количество красных кубов: " << redCount << endl;

    outFile.close();
    cout << "Данные также записаны в файл 'cube_output.txt'" << endl;

    // Освобождение памяти
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            delete[] cube[i][j];
        }
        delete[] cube[i];
    }
    delete[] cube;

    return 0;
}
