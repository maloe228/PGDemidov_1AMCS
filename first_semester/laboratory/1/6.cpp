#include <iostream>
#include <cmath>

int main() {
    int N, res = 0;
    std::cin >> N;

    double a1;
    std::cin >> a1;

    for (int i = 0; i < N-1; ++i) {
        double a2;
        std::cin >> a2;

        int cond1 = (a1 * a2 > 0);
        int cond2 = (fabs(a1) > fabs(a2));
        int increment = cond1 * cond2;
        res += increment;
        a1 = a2;
    }
    std::cout << res;
}
