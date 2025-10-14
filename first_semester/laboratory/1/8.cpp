// 10

#include <iostream>
#include <cmath>
#include <iomanip>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

// Функции для интегралов
double f1(double x) { return exp(2 * x) * pow(x, 3); }
double f2(double x) { return 1.0 / (x * x + 3.0); } // заменено
double f3(double x) { return log(x + 2) / (cos(x) * cos(x)); }
double f4(double x) { return sqrt(exp(x) + 1); }

// Численные методы
double rectangle(double a, double b, int n, double (*f)(double)) {
    double h = (b - a) / n, sum = 0;
    for (int i = 0; i < n; ++i) sum += f(a + i * h);
    return sum * h;
}

double trapezoid(double a, double b, int n, double (*f)(double)) {
    double h = (b - a) / n, sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; ++i) sum += f(a + i * h);
    return sum * h;
}

double simpson(double a, double b, int n, double (*f)(double)) {
    if (n % 2 != 0) n++; // n должно быть четным
    double h = (b - a) / n, sum = f(a) + f(b);
    for (int i = 1; i < n; ++i) {
        if (i % 2 == 0) sum += 2 * f(a + i * h);
        else sum += 4 * f(a + i * h);
    }
    return sum * h / 3.0;
}

// Универсальная функция для вычисления интеграла
void compute_integral(const string& name, double a, double b, double (*f)(double), int n) {
    double r = rectangle(a, b, n, f);
    double t = trapezoid(a, b, n, f);
    double s = simpson(a, b, n, f);

    cout << setw(5) << name << "\t"
        << setw(12) << fixed << setprecision(6) << r << "\t"
        << setw(12) << fixed << setprecision(6) << t << "\t"
        << setw(12) << fixed << setprecision(6) << s << "\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    const int N = 10000; // количество разбиений
    cout << "Интеграл\tПрямоуг\tТрапеции\tСимпсон\n";

    compute_integral("a", 0.0, 1.0, f1, N);
    compute_integral("b", -7.0 / 3.0, 7.0 / 3.0, f2, N);
    compute_integral("c", -M_PI / 4, M_PI / 4, f3, N);
    compute_integral("d", -6.0, 17.0, f4, N);

    return 0;
}
