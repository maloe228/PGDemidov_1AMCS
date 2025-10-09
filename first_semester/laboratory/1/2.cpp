// https://drive.google.com/file/d/1gQvBOuD49Vs7P5Kn9NZLA0Egt8mYAAYI/view?usp=sharing

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

constexpr double EPS = 1e-9; // Вычисление в момент компиляции

int main() {
    setlocale(LC_ALL, "Russian");
    cout << fixed << setprecision(6);


    double a, b;
    cin >> a >> b;

    // a = 1
    if (fabs(a - 1) < EPS) { // Берём модуль разности и проверяем меньше ли он погрешности
        if (fabs(b) < EPS) {
            cout << "Бесконечное количество решений\n";
        }
        else {
            cout << "Нет решений\n";
        }
        return 0;
    }

    // a = -1
    if (fabs(a + 1) < EPS) {
        if (fabs(b) < EPS) {
            cout << "Бесконечное количество решений\n";
            return 0;
        }
        else {
            cout << (b / 2.0) << "\n";
        }
    }

    // Общие случаи
    else {
        bool flag = false;

        double x1 = b / (1 - a);
        if (x1 >= -EPS && a * x1 + b >= -EPS) {
            cout << x1 << "\n";
            flag = true;
        }

        double x2 = -b / (1 + a);
        if (x2 >= -EPS && a * x2 + b < EPS) {
            cout << x2 << "\n";
            flag = true;
        }

        double x3 = -b / (a + 1);
        if (x3 < EPS && a * x3 + b >= -EPS) {
            cout << x3 << "\n";
            flag = true;
        }

        double x4 = -b / (a - 1);
        if (x4 < EPS && a * x4 + b < EPS) {
            cout << x4 << "\n";
            flag = true;
        }

        if (!flag)
            cout << "Нет решений\n";
    }


    return 0;
}
