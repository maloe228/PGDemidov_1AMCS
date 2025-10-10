#include <iostream>
#include <cmath>

using namespace std;

// int pairC(double a[], int n, int i = 0, int j = 0){
//     if (j < n - 1) {
//         if (a[j] * a[j+1] > 0  &&  fabs(a[j]) > fabs(a[j+1])) {
//             return pairC(a, n, i + 1, j + 1);
//         }
//         return pairC(a, n, i, j + 1);
//     }
//     return i;
// }

int pairC(double a[], int n, int i = 0, int j = 0) {
    if (j >= n - 1) {
        return i; // Возвращаем накопленный счетчик
    }
    int cond1 = (a[j] * a[j+1] > 0);
    int cond2 = (fabs(a[j]) > fabs(a[j+1]));
    int increment = cond1 * cond2;
    int new_i = i + increment;
    return pairC(a, n, new_i, j + 1);
}

int main() {
    int n;
    cin >> n;

    double* numbers{ new double[n] }; // динамический массив из n чисел

    for (int i = 0; i < n; i++){ // Ввод в массив
        std::cin >> numbers[i];
    }

    cout << pairC(numbers, n);

    delete[] numbers;
    return 0;
}
