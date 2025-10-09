// https://drive.google.com/file/d/1gQvBOuD49Vs7P5Kn9NZLA0Egt8mYAAYI/view?usp=sharing

#include <iostream>
#include <cmath>
#include <iomanip>

constexpr double EPS = 1e-9; // Вычисление в момент компиляции

int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << std::fixed << std::setprecision(6);


    double a, b;
    std::cin >> a >> b;

    // a = 1
    if (fabs(a - 1) < EPS) { // Берём модуль разности и проверяем меньше ли он погрешности
        if (fabs(b) < EPS) {
            std::cout << "Бесконечное количество решений\n";
        }
        else {
            std::cout << "Нет решений\n";
        }
        return 0;
    }

    // a = -1
    if (fabs(a + 1) < EPS) {
        if (fabs(b) < EPS) {
            std::cout << "Бесконечное количество решений\n";
            return 0;
        }
        else {
            std::cout << (b / 2.0) << "\n";
        }
    }

    // Общие случаи
    else {
        bool flag = false;

        double x1 = b / (1 - a);
        if (x1 >= -EPS && a * x1 + b >= -EPS) {
            std::cout << x1 << "\n";
            flag = true;
        }

        double x2 = -b / (1 + a);
        if (x2 >= -EPS && a * x2 + b < EPS) {
            std::cout << x2 << "\n";
            flag = true;
        }

        double x3 = -b / (a + 1);
        if (x3 < EPS && a * x3 + b >= -EPS) {
            std::cout << x3 << "\n";
            flag = true;
        }

        double x4 = -b / (a - 1);
        if (x4 < EPS && a * x4 + b < EPS) {
            std::cout << x4 << "\n";
            flag = true;
        }

        if (!flag)
            std::cout << "Нет решений\n";
    }


    return 0;
}
