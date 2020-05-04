//Copyright (c) Frederico Bento 2020

//Librarys:
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>

//Global Variables:
int LIFES=12;
char LETTERSFOUND[30];
char LETTERSUSED[30];
int o=-1;
int y=-1;

//Prototypes:
void creddits();
void start();
int submenu(char*);
int checkLetter(char*, char* );
void print(char*, int);
int checkWon(char*, int);
int checkLose();

//Structures
typedef struct wordi{
    char character[12];
}wordi;

//MAIN:
void main (void){
    int mainOP=1;
    int op,i;
    do{
        do{
            for(i=0;i<30;i++){
            LETTERSFOUND[i]='\0';
            LETTERSUSED[i]='\0';
            }
            system("CLS");
            printf("### Hangman C Version ###\n");
            printf("1. Choose a word\n");
            printf("2. Exit\n");
            printf("3. Credits\n");
            printf("Option: ");
            int args = scanf("%d", &op);
            if (args < 1)
            {
                op=0;
                char dummy;
                scanf("%c", &dummy);  
            }
        }while(op>3 || op<1);
        switch (op)
        {
        case 1:
            start();
            break; 
        case 2:
            mainOP=0;
            break;
        case 3:
            creddits();
            break;
        }
    }while(mainOP==1);
}

//Functions:
void creddits(){
    system("CLS");
    printf("### CREDITS ###\n");
    printf("Made by Frederico Bento\n");
    printf("Github: https://github.com/FredericoBento ");
    getch();
}

void start(){
    int i;
    char word[12];
    fflush(stdin);
    do{
    LIFES=12;
    for(i=0;i<30;i++){
            LETTERSFOUND[i]='\0';
            LETTERSUSED[i]='\0';
    }
    y=-1;
    o=-1;
    system("CLS");
    printf("### GAME START ###\n");
    printf("Choose a word (4-12 letter): ");
    scanf("%s",word);
    }while (strlen(word)>12 || strlen(word)<4 || isdigit(*word)==1 || !islower(*word) || ispunct(*word));
    submenu(word); 
}

int submenu(char* word){
int op,i,r;
int p;
int var=1;
int flag1=1;
int flag2=1;
int wordSize = strlen(word);
   do{ 
       r = checkLose();
        if(r==0)
            break;
    do{
        r = checkLose();
        if(r==0){
            system("CLS");
            printf("YOU LOSE ##");
            getch();
            break;
        }
            
        system("CLS");
        printf("### PLAYER 2 MENU ###\t\t\t\t\t\t\t\t LIFES: %d\n",LIFES);
        print(word,wordSize);
        printf("\n");
        printf("1. Guess a letter\n");
        printf("2. Guess the word (-3 LIFES)\n");
        printf("3. Exit\n");
        printf("Option: ");
        scanf("%d",&op);
    }while(op>3 || op<1 || isdigit(op)==1);

    if(op==1)
    {
        char letter[1];
        do{
        var=1;
        do{
        fflush(stdin);
        system("CLS");
        printf("### PLAYER 2 ###\t\t\t\t\t\t\t\t LIFES: %d\n",LIFES);
        printf("Letter: ");
        scanf("%s",letter);
        }while(strlen(letter)!=1 || isdigit(letter[0])==1 || !islower(*letter) || ispunct(*letter));
        flag1=1;
        flag2=1;
        for(i=0;i<29;i++){
            if(letter[0]==LETTERSFOUND[i]){
                flag1=0;
                var=0;
            }else if(letter[0]==LETTERSUSED[i]){
                flag2=0;
                var=0;
            }
        }
        if(flag1==0){
            printf("You already found that letter");
            getch();
        }else if(flag2==0){
             printf("You already tried that letter");
             getch();
        }
        
    }while(var==0);
        p = checkLetter(word, letter);
        if(p==1){
            printf("## YOU WON ##");
            op=3;
            getch();
        }
    }else if(op==2){
        char wordInputed[wordSize];
        do{
        system("CLS");
        printf("### PLAYER 2 ###\t\t\t\t\t\t\t\t LIFES: %d\n",LIFES);
        printf("Word (%d Letters): ",wordSize);
        scanf("%s",wordInputed);
        }while(strlen(wordInputed)!=wordSize || isdigit(*wordInputed)==1 || !islower(*wordInputed) || ispunct(*wordInputed));
        if(strcmp(wordInputed,word)==0){
            system("CLS");
            printf("## YOU WON ##");
            getch();
            op=3;
        }else{
            printf("\n## INCORRECT ");
            getch();
            LIFES = LIFES-3;
            r = checkLose();
            if(r==0){
                op=3;
                printf("YOU LOSE ##");
                getch();
            }
        }
    }
   }while(op!=3);
}

int checkLetter(char* word, char* letter){
   int i,r;
   int var=0;
   int flag=0;
   int wordSize = strlen(word);
   for(i=0;i<wordSize;i++) {
       if(word[i]==letter[0]){
        LETTERSFOUND[++o] = letter[0];
        flag=1;
       }
    }
    LETTERSUSED[++y] = letter[0];
    if(flag==0)
        LIFES--;
    flag=0;
    print(word,wordSize);
    var = checkWon(word, wordSize);
    getch();
    return var;
}

void print(char* word, int wordSize){
    int z,i,p;
    struct wordi wordi1;
    for(i=0;i<wordSize;i++)
        wordi1.character[i]='\0';

    p=strlen(LETTERSFOUND);
    for(i=0;i<wordSize;i++){
        for(z=0;z<p;z++){
            if(LETTERSFOUND[z]==word[i]){
                wordi1.character[i]=word[i];
            }    
        }
    }
    for(i=0;i<wordSize;i++){
        if(wordi1.character[i]=='\0'){
            printf(" _ ");
        }else printf(" %c ",wordi1.character[i]);
    }
}

int checkWon(char* word, int wordSize){
    int i=0;
    int aux=0;
    int retorno;
    for(i=0;i<wordSize;i++)
        if(LETTERSFOUND[i]!='\0')
            aux++;
    if(aux==wordSize){
        system("CLS");
        printf("## YOU WON ##");
        getch();
        return 1;
    }else return 0;
}

int checkLose(){
    if(LIFES==0)
        return 0;
    else return 1;
}