// 15

#include <iostream>
#include <fstream>
#include <clocale>
#include "PautovIA_string.h"

using namespace std;

bool isRussianUpperConsonant(char c) {
    const char* consonants = "БВГДЖЗЙКЛМНПРСТФХЦЧШЩ";

    for (int i = 0; consonants[i] != '\0'; i++) {
        if (c == consonants[i]) {
            return true;
        }
    }
    return false;
}

int main() {
    setlocale(LC_ALL, "Russian");

    ifstream inputFile("tolstoy.txt");
    if (!inputFile.is_open()) {
        cout << "Ошибка: Не удалось открыть файл.\n";
        return 1;
    }

    PautovIA_string fullText;


    char ch;
    char buffer[1024];
    size_t bufIndex = 0;

    while (inputFile.get(ch)) {
        buffer[bufIndex++] = ch;
        if (bufIndex >= 1023) {
            buffer[bufIndex] = '\0';
            fullText.append(PautovIA_string(buffer));
            bufIndex = 0;
        }
    }
    // Добавляем остаток
    if (bufIndex > 0) {
        buffer[bufIndex] = '\0';
        fullText.append(PautovIA_string(buffer));
    }
    inputFile.close();

    if (fullText.length() == 0) {
        cout << "Файл пуст.\n";
        return 1;
    }

    cout << "Текст загружен. Всего символов: " << fullText.length() << "\n";

    // Частотный анализ
    long long frequency[256] = { 0 };

    for (size_t i = 0; i < fullText.length(); i++) {
        unsigned char symbol = (unsigned char)fullText[i];
        frequency[symbol]++;
    }

    // Вывод в файл
    ofstream outputFile("analysis.txt");
    if (!outputFile.is_open()) {
        cerr << "Ошибка создания analysis.txt\n";
        return 1;
    }

    outputFile << "Частотный анализ символов:\n";
    for (int i = 0; i < 256; i++) {
        if (frequency[i] > 0) {
            // Если символ печатный, выводим его, иначе код
            if (i >= 32) {
                outputFile << "'" << (char)i << "' : " << frequency[i] << "\n";
            }
            else {
                outputFile << "Код " << i << " : " << frequency[i] << "\n";
            }
        }
    }

    // Поиск самых частых заглавных согласных
    char maxChar1 = '\0';
    long long maxCount1 = -1;

    char maxChar2 = '\0';
    long long maxCount2 = -1;

    // Проходим по всем символам
    for (int i = 0; i < 256; i++) {
        if (isRussianUpperConsonant((char)i)) {
            long long currentCount = frequency[i];

            if (currentCount > maxCount1) {
                // Сдвигаем текущий первый на второе место
                maxCount2 = maxCount1;
                maxChar2 = maxChar1;

                // Обновляем первый
                maxCount1 = currentCount;
                maxChar1 = (char)i;
            }
            else if (currentCount > maxCount2) {
                // Обновляем только второй
                maxCount2 = currentCount;
                maxChar2 = (char)i;
            }
        }
    }

    // Вывод
    cout << "------------------------------------------------\n";
    outputFile << "------------------------------------------------\n";

    if (maxCount1 > 0) {
        cout << "Самая частая заглавная согласная: " << maxChar1 << " (" << maxCount1 << " раз)\n";
        outputFile << "Самая частая заглавная согласная: " << maxChar1 << " (" << maxCount1 << " раз)\n";
    }
    else {
        cout << "Заглавных согласных не найдено.\n";
    }

    if (maxCount2 > 0) {
        cout << "Вторая по частоте заглавная согласная: " << maxChar2 << " (" << maxCount2 << " раз)\n";
        outputFile << "Вторая по частоте заглавная согласная: " << maxChar2 << " (" << maxCount2 << " раз)\n";
    }
    else {
        cout << "Второй заглавной согласной не найдено.\n";
    }

    outputFile.close();
    cout << "Полный анализ сохранен в файл analysis.txt\n";

    return 0;
}
