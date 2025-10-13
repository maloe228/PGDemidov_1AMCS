#include <iostream>

int main() {
    int n, m;
    std::cout << "Enter the size of the array: \n";
    std::cin >> n;
    std::cout << "Enter the 'M'\n";
    std::cin >> m;

    int arr[100];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (arr[i] + arr[k] + arr[j] == m) {
                    std::cout << arr[i] << " + " << arr[k] << " + " << arr[j] << " = " << m << "\n";
                    return 0;
                }
            }
        }
    }
    std::cout << "No solution\n";
    return 0;
}
