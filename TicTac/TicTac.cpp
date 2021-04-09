#include <iostream>
#include "func.h"


int main() {
    int sizeLineForWin = 3, countTurn = 0;
    int sizeField = getFieldSizeFromHuman();
    Cell cellHuman{}, cellAI{};
    if (sizeField > 3) sizeLineForWin = getSizeLineForWin(sizeField);

    Cell** field = new Cell * [sizeField];
    initField(field, sizeField);
    whoFirst(cellHuman, cellAI);
    Coord crd{};
    Cell whoTurn{};
    cellHuman = CROSS;
    while (true) {
        printField(field, sizeField);
        if (countTurn % 2 == 0) {
            whoTurn = Cell::CROSS;
            if (cellHuman == Cell::CROSS) {
                crd = getCoordFromHuman(field, sizeField);
                
            }
            else
            {
                crd = getCoordFromAI(field, sizeField, sizeLineForWin, countTurn, whoTurn);
            }
        }
        else {
            whoTurn = Cell::ZERO;
            if (cellHuman == Cell::CROSS) {
                crd = getCoordFromAI(field, sizeField, sizeLineForWin, countTurn, whoTurn);
            }
            else
            {
                crd = getCoordFromHuman(field, sizeField);
            }
        }

        //crd = getCoordFromHuman(field, sizeField);
        changeField(field, whoTurn, crd.x, crd.y);
        if (checkWin(field, sizeField, sizeLineForWin, whoTurn)) {
            printField(field, sizeField);
            cout << "WIN " << (char)whoTurn << endl;
            cin.get();
            break;
        }
        countTurn++;
    }


    deInitField(field, sizeField);
    return 0;
}
