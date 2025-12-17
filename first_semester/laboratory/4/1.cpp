// 15

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <windows.h>

using namespace std;

const int MAX_AUTHORS = 5;

class PUBLISH {
private:
    string title;
    int year;
    string journal;
    string authors[MAX_AUTHORS];
    int authorCount;

public:
    PUBLISH() : year(0), authorCount(0) {}

    string getTitle() const { return title; }
    int getYear() const { return year; }
    string getJournal() const { return journal; }
    int getAuthorCount() const { return authorCount; }
    string getAuthor(int index) const { return (index >= 0 && index < authorCount) ? authors[index] : ""; }

    void setTitle(string t) { title = t; }
    void setYear(int y) { year = y; }
    void setJournal(string j) { journal = j; }

    // Метод принимает вектор и перезаписывает массив авторов
    void setAuthors(const vector<string>& newAuthors) {
        authorCount = min((int)newAuthors.size(), MAX_AUTHORS);
        for (int i = 0; i < authorCount; ++i) {
            authors[i] = newAuthors[i];
        }
    }

    bool hasAuthor(const string& name) const {
        for (int i = 0; i < authorCount; ++i) {
            if (authors[i] == name) return true;
        }
        return false;
    }

    void display() const {
        cout << "\n[ \"" << title << "\" | " << journal << " | " << year << " г. ]" << endl;
        cout << "Авторы: ";
        for (int i = 0; i < authorCount; ++i) {
            cout << authors[i] << (i == authorCount - 1 ? "" : ", ");
        }
        cout << endl;
    }
};

// Год -> Журнал
bool comparePubs(const PUBLISH& a, const PUBLISH& b) {
    if (a.getYear() != b.getYear()) return a.getYear() < b.getYear();
    return a.getJournal() < b.getJournal();
}

// Функция ввода авторов
vector<string> inputAuthors() {
    int count;
    cout << "Введите количество авторов (макс. " << MAX_AUTHORS << "): ";
    cin >> count; cin.ignore();
    vector<string> temp;
    for (int i = 0; i < count && i < MAX_AUTHORS; ++i) {
        string a;
        cout << "  Автор " << i + 1 << ": ";
        getline(cin, a);
        temp.push_back(a);
    }
    return temp;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    vector<PUBLISH> data;
    int menu;

    do {
        cout << "\n============= МЕНЮ =============";
        cout << "\n1. Добавить (Клавиатура)";
        cout << "\n2. Загрузить (Файл data.txt)";
        cout << "\n3. Сортировать и показать всё";
        cout << "\n4. Изменить запись";
        cout << "\n5. Удалить запись";
        cout << "\n6. Поиск по автору";
        cout << "\n7. Публикации за последние N лет";
        cout << "\n0. Выход";
        cout << "\n================================";
        cout << "\nВыбор: ";
        cin >> menu; cin.ignore();

        if (menu == 1) { // Добавление
            PUBLISH p;
            string s; int y;
            cout << "Название: "; getline(cin, s); p.setTitle(s);
            cout << "Год: "; cin >> y; cin.ignore(); p.setYear(y);
            cout << "Журнал: "; getline(cin, s); p.setJournal(s);
            p.setAuthors(inputAuthors());
            data.push_back(p);
        }
        else if (menu == 2) { // Файл
            ifstream in("data.txt");
            if (!in) {
                cout << "Ошибка: Файл data.txt не найден!" << endl;
            }
            else {
                string t, j, auth; int y, ac;
                while (getline(in, t) && in >> y >> ac) {
                    in.ignore();
                    getline(in, j);
                    vector<string> v;
                    for (int i = 0; i < ac; ++i) { getline(in, auth); v.push_back(auth); }
                    PUBLISH p;
                    p.setTitle(t); p.setYear(y); p.setJournal(j); p.setAuthors(v);
                    data.push_back(p);
                }
                cout << "Данные загружены." << endl;
            }
        }
        else if (menu == 3) { // Сортировка и вывод
            if (data.empty()) cout << "Список пуст." << endl;
            else {
                int sortChoice;
                cout << "\n  [ СОРТИРОВКА ]" << endl;
                cout << "  1. По году издания" << endl;
                cout << "  2. По названию журнала" << endl;
                cout << "  Выбор: ";
                cin >> sortChoice; cin.ignore();

                if (sortChoice == 1) {
                    sort(data.begin(), data.end(), [](const PUBLISH& a, const PUBLISH& b) {
                        return a.getYear() < b.getYear();
                        });
                }
                else if (sortChoice == 2) {
                    sort(data.begin(), data.end(), [](const PUBLISH& a, const PUBLISH& b) {
                        return a.getJournal() < b.getJournal();
                        });
                }
                for (const auto& item : data) item.display();
            }
        }
        else if (menu == 4) { // ИЗМЕНЕНИЕ
            string t;
            cout << "Введите точное название статьи для редактирования: ";
            getline(cin, t);
            bool found = false;
            for (auto& item : data) {
                if (item.getTitle() == t) {
                    cout << "\nЗапись найдена. Введите новые данные (кроме названия)." << endl;

                    // 1. Изменяем год
                    cout << "Новый год (было " << item.getYear() << "): ";
                    int y; cin >> y; cin.ignore();
                    item.setYear(y);

                    // 2. Изменяем журнал
                    cout << "Новый журнал (было " << item.getJournal() << "): ";
                    string j; getline(cin, j);
                    item.setJournal(j);

                    // 3. Изменяем авторов
                    cout << "Редактирование авторов (старые будут удалены)..." << endl;
                    item.setAuthors(inputAuthors());

                    found = true;
                    cout << "Запись успешно обновлена!" << endl;
                    break;
                }
            }
            if (!found) cout << "Информация не найдена." << endl;
        }
        else if (menu == 5) { // Удаление
            string t;
            cout << "Название для удаления: "; getline(cin, t);
            auto it = remove_if(data.begin(), data.end(), [&](const PUBLISH& p) { return p.getTitle() == t; });
            if (it != data.end()) {
                data.erase(it, data.end());
                cout << "Удалено." << endl;
            }
            else cout << "Информация не найдена." << endl;
        }
        else if (menu == 6) { // Поиск автора
            string a;
            cout << "Имя автора: "; getline(cin, a);
            bool found = false;
            for (const auto& item : data) {
                if (item.hasAuthor(a)) { item.display(); found = true; }
            }
            if (!found) cout << "Информация не найдена (автор не числится)." << endl;
        }
        else if (menu == 7) { // Последние N лет
            int n, curr = 2025;
            cout << "Введите N (лет): "; cin >> n;
            bool found = false;
            for (const auto& item : data) {
                if (item.getYear() >= (curr - n)) { item.display(); found = true; }
            }
            if (!found) cout << "За этот период публикаций нет." << endl;
        }

    } while (menu != 0);

    return 0;
}
