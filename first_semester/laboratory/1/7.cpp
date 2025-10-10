#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// 1. Стандартная функция
double f1(double x) {
    return cosh(x);
}

// 2. Вычисление каждого слагаемого отдельно
double factorial(int n) {
    double res = 1.0;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}

double f2(double x, double eps) {
    double sum = 0.0;
    for (int n = 0;; ++n) {
        double term = pow(x, 2*n) / factorial(2*n);
        sum += term;
        if (term < eps) break;
    }
    return sum;
}

// 3. Рекуррентное вычисление слагаемых
double f3(double x, double eps) {
    double sum = 1.0; // a0
    double term = 1.0;
    int n = 1;
    while (true) {
        term *= x*x / (2*n*(2*n-1));
        if (term < eps) break;
        sum += term;
        n++;
    }
    return sum;
}

int main() {
    int N;
    double A, B, eps;

    cin >> N >> A >> B >> eps;

    int precision_k = (int)ceil(-log10(eps));
    precision_k = max(1, precision_k + 1);
    cout << fixed << setprecision(precision_k);

    cout << "x\tf1(x)\tf2(x)\tf3(x)\n";

    for (int i = 0; i < N; ++i) {
        double x = A + i*(B-A)/(N-1);
        double y1 = f1(x);
        double y2 = f2(x, eps);
        double y3 = f3(x, eps);
        cout << x << "\t" << y1 << "\t" << y2 << "\t" << y3 << "\n";
    }

    return 0;
}
