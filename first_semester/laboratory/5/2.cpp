// 11

#include <iostream>
#include <fstream>
#include "PautovIA_string.h"

using namespace std;

PautovIA_string transformWord(const PautovIA_string& source) {
    size_t len = source.length();

    // Если слово пустое или из 1 буквы, менять нечего
    if (len <= 1) {
        return source;
    }

    // 1. Получаем последнюю букву
    char lastChar = source[len - 1];

    // 2. Создаем новую пустую строку для результата
    PautovIA_string result;

    // 3. Проходим по слову до предпоследнего символа
    for (size_t i = 0; i < len - 1; i++) {
        // Если текущий символ НЕ совпадает с последним -> добавляем его
        if (source[i] != lastChar) {
            // Наш append принимает строку, поэтому делаем временную строку из 1 символа
            char tempBuffer[2];
            tempBuffer[0] = source[i];
            tempBuffer[1] = '\0'; // Обязательный терминальный ноль

            result.append(PautovIA_string(tempBuffer));
        }
    }

    // 4. Обязательно добавляем саму последнюю букву в конец
    char lastBuffer[2];
    lastBuffer[0] = lastChar;
    lastBuffer[1] = '\0';
    result.append(PautovIA_string(lastBuffer));

    return result;
}

int main() {
    const char* inputFileName = "input.txt";
    const char* outputFileName = "output.txt";

    PautovIA_string currentWord;
    PautovIA_string lastWordOfText;

    ifstream inFileFirstPass(inputFileName);

    if (!inFileFirstPass.is_open()) {
        cerr << "Error: Could not open input file!" << endl;
        return 1;
    }

    while (inFileFirstPass >> currentWord) {
        lastWordOfText = currentWord;
    }

    inFileFirstPass.close();

    // Если файл был пуст, выходим
    if (lastWordOfText.length() == 0) {
        cout << "File is empty." << endl;
        return 0;
    }


    ifstream inFileSecondPass(inputFileName);
    ofstream outFile(outputFileName);

    if (!outFile.is_open()) {
        cerr << "Error: Could not create output file!" << endl;
        return 1;
    }

    while (inFileSecondPass >> currentWord) {
        // "Вывести слова, которые отличны от последнего слова текста"
        if (currentWord != lastWordOfText) {

            // Преобразуем слово
            PautovIA_string newWord = transformWord(currentWord);

            // Записываем в файл с пробелом
            outFile << newWord << " ";
        }
    }

    inFileSecondPass.close();
    outFile.close();

    cout << "Done! Check output.txt" << endl;

    return 0;
}
