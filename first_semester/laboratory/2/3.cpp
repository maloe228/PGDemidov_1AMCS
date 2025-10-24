#include <fstream>

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
    int maxi = 0, l = n + 1;
    for (int i = 0; i < n; i++) {
        if (!found && arr[i] % 2 != 0) {
            if (arr[i] > maxi) {
                maxi = arr[i];
                l = i;
            }
            found = true;
        }
    }
    if (l ==  n + 1) {
        return arr;
    }

    return removeElement(arr, n,l);
}

// Минимальное среди положительных чётных
int* minimal_positive(int* arr, int &n) {
    bool found = false;
    int mini = 0, l = n + 1;
    for (int i = 1; i < n; i++) {
        if (!found && arr[i] % 2 == 0) {
            if (arr[i] < mini) {
                mini = arr[i];
                l = i;
            }
            found = true;
        }
    }
    if (l == n + 1) {
        return arr;
    }

    return removeElement(arr,n,l);
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
        int i_otv = 0;
        for (int j = 0; j < n; j++) {
            if (isPerfect(arr[j])) {
                i_otv = i;
                break;
            }
        }
        arr = removeElement(arr, n, i_otv);
    }
    return arr;
}


int main() {
    std::ifstream fin;
    fin.open("array.txt");

    int n; // Число элементов массива из файла
    fin>>n;

    int* arr = new int[n]; // Считали данные из файла в массив и закрыли файл
    for (int i = 0; i < n; i++) {
        fin>>arr[i];
    }
    fin.close();


    for (int i = 0; i < 2; i++) {
        arr = highest_positive(arr, n);
        arr = minimal_positive(arr, n);
        arr = index_2_Perfect(arr, n);
    }


    std::ofstream fout;
    fout.open("output.txt");
    for (int i = 0; i < n; i++) {
        fout << arr[i] << ' ';
    }


    fout.close();
    delete[] arr;
    return 0;
}
