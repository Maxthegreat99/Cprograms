#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "TCWin.h"

int Debuging() {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {6, 0};

    SelfWrite("AUUUUUUUGHGHHHHHHHHHHH",45,1,100,1);

    system("cls");
    echoOff();
    canonOff();

    printf("EEEEE?\n");
    printf("EEEEE?\n");
    printf("EEEEE?\n");
    printf("EEEEE?\n");
    SetConsoleCursorPosition(hConsole, pos);
    WriteConsole(hConsole, "\rHello\n", 7, NULL, NULL);
    Sleep(10000000);

    return 0;

}
