// 7

#include <iostream>

int main() {
    for (int s = 1; s <= 9; ++s) { // S не может быть 0
        for (int i = 0; i <= 9; ++i) {
            if (i == s) continue;
            for (int x = 0; x <= 9; ++x) {
                if (x == s || x == i) continue;
                for (int n = 1; n <= 9; ++n) { // N не может быть 0
                    if (n == s || n == i || n == x) continue;
                    for (int e = 0; e <= 9; ++e) {
                        if (e == s || e == i || e == x || e == n) continue;

                        int SIX = 100 * s + 10 * i + x;
                        int NINE = 1010 * n + 100 * i + e;

                        if (3 * SIX == 2 * NINE) {
                            std::cout << "S=" << s << '\n' << "I=" << i << '\n' << "X=" << x << '\n' << "N=" << n << '\n' << "E=" << e << '\n' << "SIX = " << SIX << '\n' << "NINE = " << NINE << "\n";
                        }
                    }
                }
            }
        }
    }

    return 0;
}
