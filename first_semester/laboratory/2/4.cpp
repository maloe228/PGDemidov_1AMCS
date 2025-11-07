// 3

#include <iostream>
#include <cmath>

using std::cout;
using std::cin;

// Колличество рядов
int calculateRows(int n) {
    return (n + 3) / 4;
}

// Корды ячейки по номеру
void numberToCoords(int number, int* row, int* col) {
    *row = (number - 1) / 4;
    *col = (number - 1) % 4;
}

// Номер ячейки по кординатам
int coordsToNumber(int row, int col, int totalCells) {
    int num = row * 4 + col + 1;
    if (num < 1 || num > totalCells) return -1;
    return num;
}

// Принадлежность клетки полю
bool isValidCoords(int row, int col, int totalCells) {
    if (row < 0) return false;
    int rows = calculateRows(totalCells);
    if (row >= rows) return false;
    if (col < 0 || col >= 4) return false;
    int num = coordsToNumber(row, col, totalCells);
    return num != -1;
}

// Отрисовка поля с выделением зелёным клеток из массива markedCells
void drawField(int totalCells, int* markedCells, int markedCount) {
    int rows = calculateRows(totalCells);
    int cellNum = 1;

    for (int r = 0; r < rows; ++r) {
        for (int s = 0; s < r * 3; ++s) cout << " ";

        for (int c = 0; c < 4; ++c) {
            if (cellNum > totalCells) break;

            bool marked = false;
            for (int k = 0; k < markedCount; ++k) {
                if (markedCells[k] == cellNum) {
                    marked = true;
                    break;
                }
            }

            if (marked) cout << "\033[32m"; // зелёный цвет

            if (cellNum < 10)
                cout << "[" << cellNum << "  ]";
            else if (cellNum < 100)
                cout << "[" << cellNum << " ]";
            else
                cout << "[" << cellNum << "]";

            if (marked) cout << "\033[0m"; // сброс цвета

            ++cellNum;
        }
        cout << '\n';
    }
}

// Передвижение сломаного короля
void getWoundedKingMoves(int row, int col, int totalCells, int* moveRows, int* moveCols, int* moveNumbers, int* count) {

    // Массивы смещения
    int directions_row[4] = { -1, 0, 0, 1 };
    int directions_col[4] = { -1, 1, -1, 1 };

    *count = 0;
    for (int i = 0; i < 4; ++i) {
        int newRow = row + directions_row[i];
        int newCol = col + directions_col[i];

        if (isValidCoords(newRow, newCol, totalCells)) {
            moveRows[*count] = newRow;
            moveCols[*count] = newCol;
            moveNumbers[*count] = coordsToNumber(newRow, newCol, totalCells);
            ++(*count);
        }
    }
}

// Доступные ходы для коня
void getKnightMoves(int row, int col, int totalCells, int* moveRows, int* moveCols, int* moveNumbers, int* count) {
    int directions_row[8] = { -2, -2, -1, -1, 1, 1, 2, 2 };
    int directions_col[8] = { -1, 1, -2, 2, -2, 2, -1, 1 };

    *count = 0;
    for (int i = 0; i < 8; ++i) {
        int newRow = row + directions_row[i];
        int newCol = col + directions_col[i];

        if (isValidCoords(newRow, newCol, totalCells)) {
            moveRows[*count] = newRow;
            moveCols[*count] = newCol;
            moveNumbers[*count] = coordsToNumber(newRow, newCol, totalCells);
            ++(*count);
        }
    }
}

// Достижимые клетки за два хода из стартовой позиции (ответ по указателю в result)
void findTwoMoveReachable(int startPos, int totalCells, int isKnight, int* result, int* resultCount) {
    int startRow, startCol;
    numberToCoords(startPos, &startRow, &startCol);

    int firstRows[8], firstCols[8], firstNumbers[8];
    int firstCount = 0;

    if (isKnight)
        getKnightMoves(startRow, startCol, totalCells, firstRows, firstCols, firstNumbers, &firstCount);
    else
        getWoundedKingMoves(startRow, startCol, totalCells, firstRows, firstCols, firstNumbers, &firstCount);

    *resultCount = 0;

    for (int i = 0; i < firstCount; ++i) {
        int secondRows[8], secondCols[8], secondNumbers[8];
        int secondCount = 0;

        if (isKnight)
            getKnightMoves(firstRows[i], firstCols[i], totalCells, secondRows, secondCols, secondNumbers, &secondCount);
        else
            getWoundedKingMoves(firstRows[i], firstCols[i], totalCells, secondRows, secondCols, secondNumbers, &secondCount);

        for (int j = 0; j < secondCount; ++j) {
            int cellNum = secondNumbers[j];
            bool found = false;
            for (int k = 0; k < *resultCount; ++k)
                if (result[k] == cellNum) { found = true; break; }

            if (!found && cellNum != startPos)
                result[(*resultCount)++] = cellNum;
        }
    }
}

// Кратчайший путь между startPos и endPos по BFS(поиск в ширину)
// Работает через очередь
void findShortestPath(int startPos, int endPos, int totalCells, int isKnight, int* path, int* pathLength) {

    // Начальная и конечная позиции совпадают
    if (startPos == endPos) {
        path[0] = startPos;
        *pathLength = 1;
        return;
    }

    const int MAX = totalCells + 10; // Макс размер массива с запасом
    int* visited = new int[MAX](); // Посещённые клетки
    int* parent = new int[MAX]; // Предыдущие клетки
    int* queue = new int[MAX]; // ОЧЕРЕДЬ
    int front = 0, rear = 0; // Начало и конец очереди

    visited[startPos] = 1; // Начальная клетка посещена
    parent[startPos] = -1; // Нет предыдущей
    queue[rear++] = startPos; // Добавляем начальную клетку в очередь

    // Продолжаем пока очередь не пуста
    while (front < rear) {
        int current = queue[front++]; // Извлекаем клетку и сдвигаем указатель
        int r, c; // Корды
        numberToCoords(current, &r, &c); // Номер клетки в корды

        int moveRows[8], moveCols[8], moveNumbers[8], count = 0; // До 8 из-за коня
        if (isKnight)
            getKnightMoves(r, c, totalCells, moveRows, moveCols, moveNumbers, &count); // Заполняем
        else
            getWoundedKingMoves(r, c, totalCells, moveRows, moveCols, moveNumbers, &count); // Заполняем

        // Перебор возможных ходов
        for (int i = 0; i < count; ++i) {
            int next = moveNumbers[i];
            if (!visited[next]) { // Проверка не посетили ли мы уже эту клетку
                visited[next] = 1; // Отметка посещения
                parent[next] = current; // ОТкуда пришли
                queue[rear++] = next; // Новая клетка в конец очереди

                // Если достигли конечной позиции востанавливаем путь и подсчитываем его длинну
                if (next == endPos) {
                    int temp[100], len = 0;
                    for (int v = next; v != -1; v = parent[v])
                        temp[len++] = v;

                    *pathLength = len;
                    for (int i = 0; i < len; ++i)
                        path[i] = temp[len - 1 - i];

                    delete[] visited;
                    delete[] parent;
                    delete[] queue;
                    return;
                }
            }
        }
    }

    *pathLength = 0;
    delete[] visited;
    delete[] parent;
    delete[] queue;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int n, startPos, endPos, pieceType;

    cout << "Введите количество клеток (n): ";
    cin >> n;
    cout << "Введите начальную позицию: ";
    cin >> startPos;
    cout << "Введите конечную позицию: ";
    cin >> endPos;
    cout << "Выберите фигуру (0 - Раненый Король, 1 - Конь): ";
    cin >> pieceType;

    cout << "\nПоле:\n";
    int none[1] = { 0 };
    drawField(n, none, 0);

    int* reachable = new int[n];
    int reachableCount = 0;
    findTwoMoveReachable(startPos, n, pieceType, reachable, &reachableCount);

    cout << "\nКлетки, достижимые за два хода из " << startPos << ":\n";
    drawField(n, reachable, reachableCount);

    int* path = new int[n];
    int pathLength = 0;
    findShortestPath(startPos, endPos, n, pieceType, path, &pathLength);

    if (pathLength > 0) {
        cout << "\nКратчайший путь из " << startPos << " в " << endPos << ":\n";
        for (int i = 0; i < pathLength; ++i) {
            cout << path[i];
            if (i < pathLength - 1) cout << " -> ";
        }
        cout << "\nДлина пути: " << (pathLength - 1) << " ходов\n";

        drawField(n, path, pathLength);
    }
    else {
        cout << "\nПуть не найден.\n";
    }

    delete[] reachable;
    delete[] path;
    return 0;
}
