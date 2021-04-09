#include "func.h"

int32_t getRandomNum(int32_t min, int32_t max) {
    const static auto seed = chrono::system_clock::now().time_since_epoch().count();
    static mt19937_64 generator(seed);
    uniform_int_distribution<int32_t> dis(min, max);
    return dis(generator);
}

int getNum() {
    int tmp = 0;
    cin >> tmp;
    if (cin.fail()) cout << "Error. Enter number:" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return tmp;
}

int getFieldSizeFromHuman() {
    int size = 0;
    do {
        cout << "Enter field size (2 < size < 10): ";
        size = getNum();
    } while (size < 3 || size > 9);

    return size;
}


int getSizeLineForWin(const int sizeField) {
    int tmp = 0;
    do {
        cout << "Enter size line for win (2 < size < " << sizeField + 1 << "): ";
        tmp = getNum();

    } while (tmp < 3 || tmp > sizeField);
    return tmp;
}

void initField(Cell** arr, int size) {
    for (int k = 0; k < size; ++k) {
        arr[k] = new Cell[size];
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            arr[i][j] = Cell::EMPTY;
        }
    }

}

void printField(Cell** arr, int size) {
    system("cls");
    cout << "    ";
    for (int i = 0; i < size; i++) {
        cout << i + 1 << " ";
    }
    cout << endl;
    for (int i = 0; i < size; i++) {
        cout << i + 1 << " | ";
        for (int j = 0; j < size; j++) {
            cout << (char)arr[i][j] << " ";
        }
        cout << "|";
        cout << endl;
    }
}

void deInitField(Cell** arr, int size) {

    for (int k = 0; k < size; ++k) {
        delete[] arr[k];
    }
    delete[] arr;


}

bool isEmptyCell(Cell** arr, int x, int y) {
    return arr[y][x] == Cell::EMPTY;
}

Coord getCoordFromHuman(Cell** arr, int size) {

    int tmpX, tmpY;
    Coord a{ 0, 0 };
    do {

        do {
            cout << "Enter a number for X (min - " << 1 << ", max - " << size << "): ";
            tmpX = getNum() - 1;
        } while (tmpX < 0 || tmpX >= size);

        do {
            cout << "Enter a number for Y (min - " << 1 << ", max - " << size << "): ";
            tmpY = getNum() - 1;
        } while (tmpY < 0 || tmpY >= size);

        if (isEmptyCell(arr, tmpX, tmpY)) {
            break;
        }
        else {
            cout << "Error. Cell is not empty!" << endl;
        }


    } while (true);
    a.x = tmpX;
    a.y = tmpY;

    return a;
}

bool changeField(Cell** arr, Cell c, int x, int y) {


    if (isEmptyCell(arr, x, y)) {
        arr[y][x] = c;
        return true;
    }
    else {
        return false;
    }

}

Cell checkWin(Cell** arr, int size, int sizeLineForWin, Cell cell) {

    char tmp;
    Cell res;
    int countHorizontal = 0, countVertical = 0, countDiag1 = 0, countDiag2 = 0;

    for (size_t i = 0; i < size; i++) {
        countVertical = 0;
        for (size_t j = 0; j < size - 1; j++) {
            if (arr[j][i] != Cell::EMPTY) {

                if (arr[j][i] == cell && arr[j + 1][i] == cell) {

                    countVertical++;
                    res = arr[j][i];
                    if (countVertical >= sizeLineForWin - 1) {
                        return res;
                    }
                }
                else {
                    countVertical = 0;
                }

            }
        }

    }

    for (size_t i = 0; i < size; i++) {
        countHorizontal = 0;
        for (size_t j = 0; j < size - 1; j++) {
            if (arr[i][j] != Cell::EMPTY) {

                if (arr[i][j] == cell && arr[i][j + 1] == cell) {
                    countHorizontal++;
                    res = arr[i][j];
                    if (countHorizontal >= sizeLineForWin - 1) {
                        return res;
                    }
                }
                else {
                    countHorizontal = 0;
                }

            }
        }

    }
    countDiag1 = 0;
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - 1; j++) {
            if (arr[i][j] != Cell::EMPTY) {
                if (arr[i][j] == cell && arr[i + 1][j + 1] == cell) {

                    for (size_t k = 1; k < sizeLineForWin; k++)
                    {
                        if (i + k >= size || j + k >= size) break;
                        if (arr[i][j] == cell && arr[i + k][j + k] == cell) {
                            countDiag1++;
                            res = arr[i][j];
                            if (countDiag1 >= sizeLineForWin - 1) {
                                return res;
                            }
                        }
                    }
                }
                else {
                    countDiag1 = 0;
                }
            }
        }
    }

    for (size_t i = 0; i < size - 1; i++) {
        countDiag1 = 0;
        for (size_t j = 1; j < size; j++) {
            if (arr[i][j] != Cell::EMPTY) {
                if (arr[i][j] == cell &&  arr[i+1][j - 1] == cell) { 

                    for (size_t k = 1; k < sizeLineForWin; k++)
                    {
                        if (i + k >= size || j - k < 0) break;
                        if (arr[i][j] == cell && arr[i+k][j-k] == cell) {
                            countDiag2++;                   
                            res = arr[i][j];
                            if (countDiag2 >= sizeLineForWin - 1) {
                                return res;
                            }
                        }
                    }
                }
                else {
                    countDiag1 = 0;
                }
            }
        }
    }

    return null;
}


Coord checkPreWin(Cell** arr, int size, int sizeLineForWin, Cell c) {
    Coord crd{ -1, -1};

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (isEmptyCell(arr, j, i))
            {
                arr[i][j] = c;
                
                if (checkWin(arr, size, sizeLineForWin, c)) {
                    crd.x = j;
                    crd.y = i;
                    arr[i][j] = EMPTY;
                    return crd;
                }
                arr[i][j] = EMPTY;
            }
        }
    }

    return crd;
}


Coord getCoordFromAI(Cell** arr, int size, int sizeLineForWin, int& countTurn, Cell cell) {
    int coutn = 0;
    Coord crd{};
    
    int tmpX, tmpY;
    if (countTurn < 2) {
        
        if (isEmptyCell(arr, size / 2, size / 2))
        {
            crd.y = size / 2;
            crd.x = size / 2;
        }
        else 
        {
            do {
                tmpX = getRandomNum(0, size - 1);
                tmpY = getRandomNum(0, size - 1);
            } while (!(isEmptyCell(arr, tmpX, tmpY)));
            crd.y = tmpY;
            crd.x = tmpX;
        }
        cin.get();
        return crd;
    }

    //Проверка на возможную победу игрока или АИ
    Coord a = checkPreWin(arr, size, sizeLineForWin, cell);
    if (a.x >= 0) return a;
    Cell tmpCell;
    (cell == CROSS) ? tmpCell = ZERO : tmpCell = CROSS;
    a = checkPreWin(arr, size, sizeLineForWin, tmpCell);
    if (a.x >= 0) return a;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {

        }
    }
    crd.x = getRandomNum(0, size - 1);
    crd.y = getRandomNum(0, size - 1);
 
    cin.get();
    return crd;
}

void whoFirst(Cell& hum, Cell& AI) {

    if (getRandomNum(0, 1000) > 500)
    {
        hum = Cell::CROSS;
        AI = Cell::ZERO;
    }
    else {
        hum = Cell::ZERO;
        AI = Cell::CROSS;
    }

}


