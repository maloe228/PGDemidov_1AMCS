// 3

#include <iostream>
#include <fstream>
#include "PautovIA_string.h"

using namespace std;


// Проверка, является ли символ русской буквой
bool isRusAlpha(unsigned char c) {
    return (c >= 192 && c <= 255);
}

// Верхний регистр
unsigned char toUpperRus(unsigned char c) {
    if (c >= 224 && c <= 255) { // Если маленькая буква
        return c - 32; // Сдвиг к большой в таблице ASCII
    }
    return c;
}

// Нормализация буквы Ё в Е
unsigned char normalizeYo(unsigned char c) {
    if (c == 184) return 229; // ё в е
    if (c == 168) return 197; // Ё в Е
    return c;
}

// Самое длинное слово
int findMaxWordLength(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) return 0;

    PautovIA_string word;
    int maxLen = 0;

    // Читаем файл по словам
    while (file >> word) {
        int currentLen = 0;
        // Считаем только буквы
        for (size_t i = 0; i < word.length(); i++) {
            unsigned char c = (unsigned char)word[i];
            c = normalizeYo(c);
            if (isRusAlpha(c) || c == 184 || c == 168) {
                currentLen++;
            }
        }
        if (currentLen > maxLen) {
            maxLen = currentLen;
        }
    }
    file.close();
    return maxLen;
}

// Шифрование / Дешифрование
char shiftChar(char c, int k, bool encrypt) {
    unsigned char uc = (unsigned char)c;

    uc = normalizeYo(uc);

    // Если не русская
    if (!isRusAlpha(uc)) {
        return (char)uc;
    }

    // Определяем начало алфавита
    unsigned char base;
    if (uc >= 192 && uc <= 223) base = 192; // 'А'
    else if (uc >= 224 && uc <= 255) base = 224; // 'а'
    else return (char)uc;

    // Размер алфавита без Ё = 32 буквы
    int alphaSize = 32;

    // Формула сдвига
    int index = uc - base;
    int newIndex;

    if (encrypt) {
        // Циклический сдвиг ВПРАВО
        newIndex = (index + k) % alphaSize;
    } else {
        // Обратный сдвиг ВЛЕВО
        // Добавляем чтобы избежать отрицательных чисел
        newIndex = (index - k % alphaSize + alphaSize) % alphaSize;
    }

    return (char)(base + newIndex);
}

// Функция обработки файла
void processFile(const char* inFile, const char* outFile, int k, bool encrypt) {
    ifstream fin(inFile, ios::binary);
    ofstream fout(outFile, ios::binary);

    char c;
    // Читаем посимвольно, чтобы сохранить пробелы и форматирование
    while (fin.get(c)) {
        fout << shiftChar(c, k, encrypt);
    }

    fin.close();
    fout.close();
}

// Сравнение файлов
bool compareFiles(const char* file1, const char* file2) {
    ifstream f1(file1, ios::binary);
    ifstream f2(file2, ios::binary);

    char c1, c2;
    while (true) {
        bool r1 = (bool)f1.get(c1);
        bool r2 = (bool)f2.get(c2);

        if (r1 != r2) return false; // Файлы разной длины
        if (!r1) break; // Оба закончились

        // Сравниваем символы.
        unsigned char uc1 = normalizeYo((unsigned char)c1);
        unsigned char uc2 = normalizeYo((unsigned char)c2);

        if (uc1 != uc2) return false;
    }
    return true;
}

int main() {

    const char* originalFile = "king.txt";
    const char* encryptedFile = "king_encrypted.txt";
    const char* decryptedFile = "king_decrypted.txt";

    // Находим ключ
    cout << "Analyzing text" << endl;
    int key = findMaxWordLength(originalFile);

    if (key == 0) {
        cerr << "Error: File not found" << originalFile << endl;
        return 1;
    }

    cout << "Key (Max Word Length): " << key << endl;

    // Шифруем
    cout << "Encrypting..." << endl;
    processFile(originalFile, encryptedFile, key, true);

    // Дешифруем
    cout << "Decrypting..." << endl;
    processFile(encryptedFile, decryptedFile, key, false);

    // Проверяем
    cout << "Comparing files..." << endl;
    if (compareFiles(originalFile, decryptedFile)) {
        cout << "SUCCESS!" << endl;
    } else {
        cout << "FAILURE!" << endl;
    }

    return 0;
}
