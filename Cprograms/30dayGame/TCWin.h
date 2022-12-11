/*
    TERMINAL CONTROL FOR WINDOWS BY FIREBALL_2000
    credits to greggs ink for part of the code and concept
*/
#ifndef TCW_H
#define TCW_H

#include <windows.h>
#include <stdlib.h>

#define TC_NRM  "\x1B[0m"
#define TC_RED  "\x1B[1;31m"
#define TC_GRN  "\x1B[1;32m"
#define TC_YEL  "\x1B[1;33m"
#define TC_BLU  "\x1B[1;34m"
#define TC_MAG  "\x1B[1;35m"
#define TC_CYN  "\x1B[1;36m"
#define TC_WHT  "\x1B[1;37m"

#define TC_B_NRM  "\x1B[0m"
#define TC_B_RED  "\x1B[0;31m"
#define TC_B_GRN  "\x1B[0;32m"
#define TC_B_YEL  "\x1B[0;33m"
#define TC_B_BLU  "\x1B[0;34m"
#define TC_B_MAG  "\x1B[0;35m"
#define TC_B_CYN  "\x1B[0;36m"
#define TC_B_WHT  "\x1B[0;37m"

#define TC_BG_NRM "\x1B[40m"
#define TC_BG_RED " \x1B[41m"
#define TC_BG_GRN "\x1B[42m"
#define TC_BG_YEL "\x1B[43m"
#define TC_BG_BLU "\x1B[44m"
#define TC_BG_MAG "\x1B[45m"
#define TC_BG_CYN "\x1B[46m"
#define TC_BG_WHT "\x1B[47m"


/*
   Enable keyboard echo on terminal (console) input
 */
void echoOn()
{
#ifdef _WIN32


    HANDLE h;
    DWORD mode;

    h = GetStdHandle(STD_INPUT_HANDLE);
    if (GetConsoleMode(h, &mode))
    {
        mode |= ENABLE_ECHO_INPUT;
        SetConsoleMode(h, mode);
    }

#endif
}

/*
   Disable keyboard echoing on terminal (console) input
*/
void echoOff()
{
#ifdef _WIN32

    HANDLE h;
    DWORD mode;

    h = GetStdHandle(STD_INPUT_HANDLE);
    if (GetConsoleMode(h, &mode))
    {
        mode &= ~ENABLE_ECHO_INPUT;
        SetConsoleMode(h, mode);
    }

#endif
}
/*
    Disable canonical mode for console(reads directly on input without waiting for \n)
*/
void canonOff()
{
#ifdef _WIN32
    DWORD mode;
    HANDLE console = GetStdHandle(STD_INPUT_HANDLE);

    GetConsoleMode(console, &mode);
    SetConsoleMode(console, mode & ~(ENABLE_LINE_INPUT));



#endif
}
/*
    Enable Canonical mode for console
*/
void canonOn()
{
#ifdef _WIN32

    DWORD mode;
    HANDLE console = GetStdHandle(STD_INPUT_HANDLE);

    GetConsoleMode(console, &mode);
    SetConsoleMode(console, mode | (ENABLE_LINE_INPUT));


#endif
}

#endif /* TCW_H */
