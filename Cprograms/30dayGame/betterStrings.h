/*
    Better strings Windows by Fireball_2000
*/

#ifndef BS_H
#define BS_H

#include <windows.h>
#include <conio.h>
#include <mmsystem.h>
int Search(char[], char[]);
void DeleteWord(char[], char[]);

/* Function returns the index of str where word is found */
int Search(char str[], char word[])
{
    int l, i, j;

    /* finding length of word */
    for (l = 0; word[l] != '\0'; l++);

    for (i = 0, j = 0; str[i] != '\0' && word[j] != '\0'; i++)
    {
        if (str[i] == word[j])
        {
            j++;
        }
        else
        {
            j = 0;
        }
    }

    if (j == l)
    {
        /* substring found */
        return (i - j);
    }
    else
    {


        return  - 1;
    }
}


/*function used to remove a word from a string*/
void DeleteWord(char str[], char word[]){
    int i, j = 0, k = 0,n = 0;
    int flag = 0;

    char neww[100];


    for(i = 0 ; str[i] != '\0' ; i++)
    {
        k = i;

        while(str[i] == word[j])
        {
            i++,j++;
            if(j == strlen(word))
            {
                flag = 1;
                break;
            }
        }
    j = 0;

    if(flag == 0)
        i = k;
    else
        flag = 0;

    neww[n++] = str[i];
    }

    neww[n] = '\0';


    strcpy(str,neww);


}

/* emptys stdin */
void empty_stdin(void) {
    int c = getchar();

    while (c != '\n' && c != EOF)
        c = getchar();
}

/* function used to write text with each word apearing after a short interval */
int SelfWrite(char str[],int interval,int allowUserInput,int maxCharsPerLine,int cutWords){

    int i=0;
    int f=0;

    while(str[i]!='\0'){

        if( (str[i] != ' ' && maxCharsPerLine != 0) || (cutWords != 1 && f==maxCharsPerLine)){
            int numberOfChar = 0;
            int y = i+1;

            CONSOLE_SCREEN_BUFFER_INFO CursorPos;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

            GetConsoleScreenBufferInfo(hConsole,&CursorPos);

            while(str[y] != ' ' && str[y] !='\0'){

                numberOfChar += 1;
                y++;
            }
            if( (numberOfChar + f >= maxCharsPerLine && cutWords == 1 ) || (f == maxCharsPerLine) ){

            CursorPos.dwCursorPosition.Y += 1;
            CursorPos.dwCursorPosition.X = 0;
            SetConsoleCursorPosition(hConsole,CursorPos.dwCursorPosition);
            f=0;


            }


        }
        printf("%c",str[i]);



        Sleep(interval);
        i++;
        f++;
        if (allowUserInput==1 && kbhit()!=0){

            interval=0;
        }
    }
    Sleep(1000000);

    return 0;
}
#endif /* BS_H */
