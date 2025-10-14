// 5

#include <iostream>

int main() {
    std::cout << "x y z | A B" << "\n";
    std::cout << "-------------" << "\n";
    for (int x = 0; x <= 1; ++x) {
        for (int y = 0; y <= 1; ++y) {
            for (int z = 0; z <= 1; ++z) {
                bool A = ((x || y) && z || !(x || y) && !z) && (x && y && z);
                bool B = !(x && y && z);
                std::cout << x << " " << y << " " << z << " | " << A << " " << B << "\n";
            }
        }
    }
    return 0;
}
