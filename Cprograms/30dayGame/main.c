#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <Mmsystem.h>
#include "tesing.c"
#include "betterStrings.h"

#pragma comment(lib,"dxguid.lib")

#define CUTE_SOUND_IMPLEMENTATION
#define CUTE_SOUND_SCALAR_MODE
#include "cute_sound.h"

/**< TODOS
COMBAT
CRAFT
INVENTORY:
STORY*/
/*variables used for geometric calculations*/
int k;
double sin() ,cos();

/*Player stats*/
int GLOBAL_PlayerHealth = 100;
int GLOBAL_PlayerTemp = 50;
int GLOBAL_PlayerHunger = 75;
int GLOBAL_PlayerDamage = 0;
char GLOBAL_PlayerWeapon[100];
char GLOBAL_PlayerInventory[11][20];
int GLOBAL_PlayerShots = 1;
int GLOBAL_PlayerReload = 0;
int GLOBAL_PlayerAccuracy = 0;


/*this is a global variable containing most if not all choices and answers for the game, theres a maximum of six arguements per choice player can make,and a minimum of 2. when making a new choice there should always be 6 arguements added, the one which are not needed must be named "NULL"*/
const char *GLOBAL_Choices[] =   {"???","Loots item","advance","NULL","NULL","NULL","advance","loot item","lose hp","nothing","go back", "NULL","go back", "advance", "loot item","eat","NULL", "NULL","loot item", "go back", "go back","go back","loot item","loot item"};

/*global array containing most of the game dialogue,each prefix of the answers says what happens when they are chosen, LOOT means that the game gives an item to the player when something happens, BACK makes the player go back in choices, and static makes the player not advance but still have an event happen*/
const char *GLOBAL_ChoicesAns[] = { "DONUT )QO90w82ieaiom", "LOOT 4 AMOUNT 1 You got something", "you advance","NULL","NULL","NULL", "you advance", "LOOT 5 AMOUNT 2 you got something","LOSEHP 20 you lose hp","you advance", "BACK you go back","NULL", "BACK you go back", "you advance", "LOOT 6 AMOUNT 3 you got something","you eat something","NULL","NULL", "LOOT 7 AMOUNT 4 STATIC you got something", "BACK you go back", "BACK you go back","BACK you go back","LOOT 8 AMOUNT 5 STATIC you got something","LOOT 4 AMOUNT 6 STATIC you got something"};
/*global array containing all items and the items logic, each item contain its own stat which is taken and replaced as the player's stats when needed.*/
char *GLOBAL_Items[] = {"DMG 20 ACCURACY 50 RELOAD 5 SHOTS 1 Shotgun","DMG 13 ACCURACY 80 RELOAD 3 SHOTS 1 Pistol","DMG 20 ACCURACY 25 RELOAD 7 SHOTS 2 Double-barrel shotgun","DMG 10 ACCURACY 80 RELOAD 10 SHOTS 3 AK-47","MATERIAL Metal scraps","MATERIAL Wood","MATERIAL Food cans","MATERIAL Bullets","MATERIAL Illegal gun parts","EQUIPABLE Coat"};
/*int array to contain the quantity of items in the inventory for each of the items in the items array*/
int GLOBAL_ItemAmount[] = {1,0,0,0,0,0,0,0,0,0};
/*Char determining what should happen*/
char GLOBAL_Input;
/*integers to calculate next choices to display*/
int GLOBAL_ChoiceMade=0;
int GLOBAL_NextChoices=0;
int GLOBAL_NextAns=0;
int GLOBAL_Score=0;
int GLOBAL_InventoryOpened=0;

/*int to store returned value of a function*/
int GLOBAL_Returned = 0;


/*the function checks if the player should have items in their inventory depending on the itemAmount array, and updates it. The function can also add new items to the player's inventory in specified amounts.
if tries to be equiped but it is not in the players inventory or that it isnt a valid item, the function returns 0 else it returns 1*/
int InitializeItems(char *ItemToEquip,char *ItemToDrop,int AmountToDrop){
    /*variables used to manipulate the content of the item strings*/

    char Word2[] = "                                              ";
    char Word[] = "                                               ";
    /*returned variable*/
    int i;
    int ItemFound=0;

    /*initialize the player's inventory.*/
    strcpy(GLOBAL_PlayerInventory[0],"NULL                             ");
    strcpy(GLOBAL_PlayerInventory[1],"NULL                             ");
    strcpy(GLOBAL_PlayerInventory[2],"NULL                             ");
    strcpy(GLOBAL_PlayerInventory[3],"NULL                             ");
    strcpy(GLOBAL_PlayerInventory[4],"NULL                             ");
    strcpy(GLOBAL_PlayerInventory[5],"NULL                             ");
    strcpy(GLOBAL_PlayerInventory[6],"NULL                             ");
    strcpy(GLOBAL_PlayerInventory[7],"NULL                             ");
    strcpy(GLOBAL_PlayerInventory[8],"NULL                             ");
    strcpy(GLOBAL_PlayerInventory[9],"NULL                             ");


    /*iterates through all the items in the items array*/
    for(i=0;i!=sizeof(GLOBAL_Items)/sizeof(GLOBAL_Items[0])-1;i++)
    {
        /*checks if the item is a weapon and if the item is in the player's inventory and then initializes the weapon in the player's inventory*/
        if(strncmp(GLOBAL_Items[i],"DMG",3)==0 && GLOBAL_ItemAmount[i] > 0){

            /*long process of deleting the words not needed to display to the player*/
            strcpy(Word,GLOBAL_Items[i]);
            DeleteWord(Word,"DMG ");
            strncpy(Word2,Word,3);
            Word2[3] = '\0';
            DeleteWord(Word,Word2);
            DeleteWord(Word,"ACCURACY ");
            strncpy(Word2,Word,2);
            Word2[3] = '\0';
            DeleteWord(Word,Word2);
            DeleteWord(Word,"RELOAD ");
            strncpy(Word2,Word,2);
            Word2[2]='\0';
            DeleteWord(Word,Word2);
            DeleteWord(Word,"SHOTS ");
            strncpy(Word2,Word,2);
            Word2[2]='\0';
            DeleteWord(Word,Word2);

            /*the final version of variable word is printed in the string part of the player's inventory*/
            strcpy(GLOBAL_PlayerInventory[i],Word);

            /*if the weapon is to be equipped the function takes the information it needs from the string(dmg,accuracy etc...) then puts them in the player's stats and then cuts whole string except the weapon's name and finally put the weapon's name as the current weapon the player has*/
            if(ItemToEquip==GLOBAL_Items[i] || GLOBAL_PlayerDamage==0){

                strcpy(Word,GLOBAL_Items[i]);
                DeleteWord(Word,"DMG ");
                strncpy(Word2,Word,3);
                Word2[3] = '\0';
                GLOBAL_PlayerDamage = atoi(Word2);
                DeleteWord(Word,Word2);
                DeleteWord(Word,"ACCURACY ");
                strncpy(Word2,Word,3);
                Word2[3]='\0';
                GLOBAL_PlayerAccuracy = atoi(Word2);
                DeleteWord(Word,Word2);
                DeleteWord(Word,"RELOAD ");
                strncpy(Word2,Word,2);
                Word2[2]='\0';
                GLOBAL_PlayerReload = atoi(Word2);
                DeleteWord(Word,Word2);
                DeleteWord(Word,"SHOTS ");
                strncpy(Word2,Word,2);
                Word2[2] = '\0';
                GLOBAL_PlayerShots = atoi(Word2);
                DeleteWord(Word,Word2);

                ItemFound = 1;




                strcpy(GLOBAL_PlayerWeapon,Word);

            }

        }

        if(strncmp(GLOBAL_Items[i],"MATERIAL",8)==0){

            if(GLOBAL_Items[i]==ItemToDrop){
                /*adds the amount dropped to the player's item amount*/
                GLOBAL_ItemAmount[i]+=AmountToDrop;
            }
            /*if the item is in the player's inventory*/
            if(GLOBAL_ItemAmount[i]>0){


                /*initializes the item*/
                strcpy(Word,GLOBAL_Items[i]);
                DeleteWord(Word,"MATERIAL ");
                strcpy(GLOBAL_PlayerInventory[i],Word);

            }



        }



    }

    if(ItemFound!=1 && strcmp(ItemToEquip,"NULL")!=0){
        /* there was no item to equip or the function wasnt meant to equip an item*/
        return 0;


    }
    else{
        return ItemFound;
    }

}

/*function called when inventory is called*/
void Inventory(){
    int i;
    InitializeItems("NULL","NULL",-1);
    /*prints the player stats*/
    printf("\n\n\n");
    printf("Health    %d\n",GLOBAL_PlayerHealth);
    printf("Temperature resistance    %d\n",GLOBAL_PlayerTemp);
    printf("Hunger    %d\n",GLOBAL_PlayerHunger);
    printf("Weapon    %s\n",GLOBAL_PlayerWeapon);
    printf("Damage    %d\n",GLOBAL_PlayerDamage);
    printf("Accuracy    %d\n",GLOBAL_PlayerAccuracy);
    printf("Reload time    %ds\n",GLOBAL_PlayerReload);
    printf("Shots per bullets    %d\n",GLOBAL_PlayerShots);

    printf("\n\n");



    printf(" (1) Use items\n");
    printf(" (2) Equip an item\n");
    printf(" (3) back\n");

    printf(" \tMake a choice >> ");
    GLOBAL_Returned = scanf(" %i",&GLOBAL_ChoiceMade);
    printf("\n\n\n");
    /*checks if the  input is correct*/
    if(GLOBAL_Returned!=1 || GLOBAL_ChoiceMade < 1 || GLOBAL_ChoiceMade > 3){
        do{


            printf("~ Invalid input,please enter another input >> ");
            empty_stdin();

            }
        while(scanf("%i",&GLOBAL_ChoiceMade)!=1 || GLOBAL_ChoiceMade < 1 || GLOBAL_ChoiceMade > 3);

    }
    /*shows player's item and gives the player the choice to use them.*/
    if(GLOBAL_ChoiceMade==1){

        for(i=0;i!=sizeof(GLOBAL_PlayerInventory)/sizeof(GLOBAL_PlayerInventory[0])-1;i++){

            if(GLOBAL_ItemAmount[i]>0){

                printf("    %s    %d\n",GLOBAL_PlayerInventory[i],GLOBAL_ItemAmount[i]);

            }




        }


        printf("\n\n\n");
    }

}
/*Function called when entering combat*/
int Combat(){

    int EnemyOneHP = 100;
    int EnemyTwoHP = 100;
    int EnemyThreeHP = 100;
    int EnemyFourHP = 100;

    int EnemyAmount = 0;

    if(EnemyOneHP > 0){
        EnemyAmount+=1;
    }
    if(EnemyTwoHP>0){
        EnemyAmount+=1;
    }
    if(EnemyThreeHP>0){
        EnemyAmount+=1;
    }
    if(EnemyFourHP>0){
        EnemyAmount+=1;
    }



    return 0;
}
/*function is where the main gameplay will be stored, it meant to be run when player starts the game*/
int Playthrough(){
    /*is used to know how many options are being printed*/
    int ChoicesDisplaying = 0;

    int i;
    InitializeItems("NULL","NULL",-1);



    /*a for loop that continues forever unless i becomes less than -1 in that case when the player beats the game*/
    for(i=0;i>-1;i++){
        GLOBAL_InventoryOpened=0;
        /*This prints the first 2 choices*/
        printf(" (1) %s \n (2) %s \n",GLOBAL_Choices[GLOBAL_NextChoices],GLOBAL_Choices[GLOBAL_NextChoices+1]);
        ChoicesDisplaying = 2;
        /*This knows which arguements to show and not show*/
        if(strcmp(GLOBAL_Choices[GLOBAL_NextChoices+2],"NULL")!=0){

            printf(" (3) %s \n",GLOBAL_Choices[GLOBAL_NextChoices+2]);
            ChoicesDisplaying = 3;

            if(strcmp(GLOBAL_Choices[GLOBAL_NextChoices+3],"NULL")!=0){
                printf(" (4) %s \n",GLOBAL_Choices[GLOBAL_NextChoices+3]);
                ChoicesDisplaying += 1;
            }
            if(strcmp(GLOBAL_Choices[GLOBAL_NextChoices+4],"NULL")!=0){
                printf(" (5) %s \n",GLOBAL_Choices[GLOBAL_NextChoices+4]);
                ChoicesDisplaying += 1;
            }
            if(strcmp(GLOBAL_Choices[GLOBAL_NextChoices+5],"NULL")!=0){
                printf(" (6) %s \n",GLOBAL_Choices[GLOBAL_NextChoices+5]);
                ChoicesDisplaying += 1;
            }


        }

        printf(" \tMake a choice >> ");
        GLOBAL_Returned = scanf(" %c",&GLOBAL_Input);

        /*checks if player input is E or e, if not pass the input to an int and check if its valid*/
        if(GLOBAL_Input=='E' || GLOBAL_Input == 'e'){

                GLOBAL_InventoryOpened=1;
                empty_stdin();
                Inventory();

                GLOBAL_ChoiceMade = 0;

        }
        else if( isdigit(GLOBAL_Input)!=0 )
        {
            empty_stdin();
            GLOBAL_ChoiceMade = GLOBAL_Input - '0';

        }
        else{
            printf("~ Invalid input,please enter another input >> ");
            empty_stdin();
            GLOBAL_Returned = scanf("%i",&GLOBAL_ChoiceMade);
        }

        /* gets the player input and rejects it if the value inputed is lesser than 1, a string or greater than the amount of choices*/
        if( (GLOBAL_Returned!=1 && GLOBAL_InventoryOpened!=1) || (GLOBAL_ChoiceMade < 1 && GLOBAL_InventoryOpened!=1)  || (GLOBAL_ChoiceMade > ChoicesDisplaying && GLOBAL_InventoryOpened!=1) ){
                do{


                    printf("~ Invalid input,please enter another input >> ");
                    empty_stdin();

                }
                while(scanf("%i",&GLOBAL_ChoiceMade)!=1 || GLOBAL_ChoiceMade < 1 || GLOBAL_ChoiceMade > ChoicesDisplaying);

        }

        /*prints the answer to the players input*/
        if(GLOBAL_InventoryOpened==0){
            char Word[100];
            char Word2[100];
            int ItemToDrop = 0;
            int Amount = 0;
            int IsBack = 0;

            /*if the answer says to go back*/
            if(strncmp(GLOBAL_ChoicesAns[GLOBAL_NextAns+GLOBAL_ChoiceMade-1],"BACK",4)==0){

                strcpy(Word,GLOBAL_ChoicesAns[GLOBAL_NextAns+GLOBAL_ChoiceMade-1]);
                DeleteWord(Word,"BACK ");
                IsBack = 1;
                GLOBAL_NextChoices-= 6;
                GLOBAL_NextAns -=6;



            }
            /*if the answer says to loot an item*/
            else if(strncmp(GLOBAL_ChoicesAns[GLOBAL_NextAns+GLOBAL_ChoiceMade-1],"LOOT",4)==0){

                strcpy(Word,GLOBAL_ChoicesAns[GLOBAL_NextAns+GLOBAL_ChoiceMade-1]);
                DeleteWord(Word,"LOOT ");
                strncpy(Word2,Word,2);
                Word2[2] = '\0';
                ItemToDrop = atoi(Word2);
                DeleteWord(Word,Word2);
                DeleteWord(Word,"AMOUNT ");
                strncpy(Word2,Word,2);
                Word2[2]='\0';
                Amount = atoi(Word2);
                DeleteWord(Word,Word2);


                strcpy(Word2,GLOBAL_Items[ItemToDrop]);
                DeleteWord(Word2,"MATERIAL ");
                InitializeItems("NULL",GLOBAL_Items[ItemToDrop],Amount);
                printf("You got %d %s\n",Amount,Word2);




            }
            /**<DONUT */
            else if(strncmp(GLOBAL_ChoicesAns[GLOBAL_NextAns+GLOBAL_ChoiceMade-1],"DONUT",5)==0){
                /*donut logic*/
                float A=0, B=0, i, j, z[1760];
                char b[1760];
                strcpy(Word,GLOBAL_ChoicesAns[GLOBAL_NextAns+GLOBAL_ChoiceMade-1]);
                DeleteWord(Word,"DONUT ");


                printf("\x1b[2J");
                for(; ; ) {
                    memset(b,32,1760);
                    memset(z,0,7040);
                    for(j=0; 6.28>j; j+=0.07) {
                        for(i=0; 6.28 >i; i+=0.02) {
                            float sini=sin(i),
                            cosj=cos(j),
                            sinA=sin(A),
                            sinj=sin(j),
                            cosA=cos(A),
                            cosj2=cosj+2,
                            mess=1/(sini*cosj2*sinA+sinj*cosA+5),
                            cosi=cos(i),
                            cosB=cos(B),
                            sinB=sin(B),
                            t=sini*cosj2*cosA-sinj* sinA;
                        int x=40+30*mess*(cosi*cosj2*cosB-t*sinB),
                            y= 12+15*mess*(cosi*cosj2*sinB +t*cosB),
                            o=x+80*y,
                            N=8*((sinj*sinA-sini*cosj*cosA)*cosB-sini*cosj*sinA-sinj*cosA-cosi *cosj*sinB);
                        if(22>y&&y>0&&x>0&&80>x&&mess>z[o]){
                            z[o]=mess;
                            b[o]=".,-~:;=!*#$@"[N>0?N:0];
                        }
                        }
                    }
                printf("\x1b[d");
                for(k=0; 1761>k; k++)
                    putchar(k%80?b[k]:10);
                A+=0.04;
                B+= 0.02;
                }

            }


            else if(strncmp(GLOBAL_ChoicesAns[GLOBAL_NextAns+GLOBAL_ChoiceMade-1],"LOSEHP",6)==0){

                strcpy(Word,GLOBAL_ChoicesAns[GLOBAL_NextAns+GLOBAL_ChoiceMade-1]);
                DeleteWord(Word,"LOSEHP ");
                strncpy(Word2,Word,3);
                Word2[3] = '\0';
                Amount = atoi(Word2);
                GLOBAL_PlayerHealth -= Amount;
                DeleteWord(Word,Word2);
                printf("You lost %i HP\n",Amount);
            }
            else {
                strcpy(Word,GLOBAL_ChoicesAns[GLOBAL_NextAns+GLOBAL_ChoiceMade-1]);

            }
            if(IsBack!=1 && strncmp(Word,"STATIC",6)==0){

                DeleteWord(Word,"STATIC ");
                IsBack=1;
            }
            printf("~ %s\n \n",Word);
            if(IsBack!=1){

                GLOBAL_NextAns += 6;
                GLOBAL_NextChoices+= 6;
            }

            GLOBAL_Score+=20;
        }
        /*what happens on player's death*/
        if(GLOBAL_PlayerHealth<=0){
            printf("You died! your score is %d\n",GLOBAL_Score);
            i = -100;
        }

    }

    return 1;
}

int main() {
    /* FUCK YOU AND SEE YOU TOMMOROW */
	cs_init(NULL,44100,1024,NULL);

	system("pause");
    Playthrough();
    return 0;


}
