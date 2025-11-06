#include <fstream>
#include <iostream>

// Удаление элемента по индексу
int* removeElement(int* arr, int& n, int index) {
    int* newArr = new int[n-1];
    for (int i = 0, j = 0; i < n; ++i) {
        if (i != index) {
            newArr[j++] = arr[i];
        }
    }
    delete[] arr;
    n = n - 1;
    return newArr;
}

// Максимальное среди положительных нечётных
int* highest_positive(int* arr, int &n) {
    bool found = false;
    int maxi = 0, l = -1;

    for (int i = 0; i < n; i++) {
        if (arr[i] > 0 && arr[i] % 2 != 0) {
            if (!found) {
                maxi = arr[i];
                l = i;
                found = true;
            } else {
                if (arr[i] > maxi) {
                    maxi = arr[i];
                    l = i;
                }
            }
        }
    }

    if (l == -1) {
        return arr;
    }

    return removeElement(arr, n, l);
}

// Минимальное среди положительных чётных
int* minimal_positive(int* arr, int &n) {
    bool found = false;
    int mini = 0, l = -1;

    for (int i = 0; i < n; i++) {
        if (arr[i] > 0 && arr[i] % 2 == 0) {
            if (!found) {
                mini = arr[i];
                l = i;
                found = true;
            } else {
                if (arr[i] < mini) {
                    mini = arr[i];
                    l = i;
                }
            }
        }
    }

    if (l == -1) {
        return arr;
    }

    return removeElement(arr, n, l);
}

// Совершенность
bool isPerfect(int n) {
    if (n <= 1) {
        return false;
    }
    int sum = 1;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            sum += i;
            if (i * i != n) {
                sum += n / i;
            }
        }
    }
    return sum == n;
}

// Индексы первых двух совершенных
int* index_2_Perfect(int* arr, int &n) {
    for (int i = 0; i < 2; ++i) {
        int i_otv = -1;
        for (int j = 0; j < n; j++) {
            if (isPerfect(arr[j])) {
                i_otv = j;
                break;
            }
        }
        if (i_otv != -1) {
            arr = removeElement(arr, n, i_otv);
        }
        else {
            break;
        }
    }
    return arr;
}

int* readArray(const char* filename, int& n) {
    std::ifstream fin;
    fin.open(filename);

    if (!fin.is_open()) {
        std::cout << "Error input file\n";
        n = 0;
        return nullptr;
    }

    fin >> n;
    if (n <= 0) {
        std::cout << "Invalid array size\n";
        fin.close();
        n = 0;
        return nullptr;
    }

    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        fin >> arr[i];
    }
    fin.close();
    return arr;
}

void writeArray(const char* filename, int* arr, int n) {
    std::ofstream fout;
    fout.open(filename);

    if (!fout.is_open()) {
        std::cout << "Error opening output file\n";
        return;
    }

    for (int i = 0; i < n; i++) {
        fout << arr[i] << ' ';
    }
    fout.close();
}

int main() {
    const char* inputFile = "C:\\Users\\vaces\\CLionProjects\\prog\\array.txt";
    const char* outputFile = "C:\\Users\\vaces\\CLionProjects\\prog\\output.txt";

    int n;
    int* arr = readArray(inputFile, n);

    // Файл не открылся
    if (arr == nullptr) {
        return 1;
    }


    for (int i = 0; i < 2; i++) {
        arr = highest_positive(arr, n);
        arr = minimal_positive(arr, n);
        arr = index_2_Perfect(arr, n);
    }

    writeArray(outputFile, arr, n);

    delete[] arr;
    return 0;
}
