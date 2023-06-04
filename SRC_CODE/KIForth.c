//          >>>KIForth - Forth interpreter with C<<<

//                  CREATED BY AMIR KALAKI

//                      30 / MAY / 2023

//        COPYRIGHT © 2023 AMIR KALAKI. ALL RIGHTS RESERVED.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 150                    //Size of stack in GForth is 150


int top = -1 , STACK[SIZE];
// It does not support spaces after :_ , ."_ , ... and upper or lower case and if a number is at the beginning of the expression
char *keyWords[] = {".\"" , "(" , ")" , ":" , "." , ";" , "cr" , "dup" , "drop" , "swap" , "rot" , "+" , "-" , "*" , "/" , ">" , "<" , "=" , "and" , "or" , "xor" , "not" , "if" , "then" , "begin" , "until" , "do" , "loop" , ".s" , "/mod" , "mod" , "negate" , "nip" , "tuck" , "2swap" , "2dup" , "2over" , "2drop" , "s\""};
char bye[] = "bye";

void ok() 
{
    printf("ok\n");
}


void printStack() {

    printf ("<%d>\t" , (top + 1));
    if ((top + 1) > 9)
    {
        for (int i = (top - 8) ; i < (top + 1) ; i++)
        {
            printf ("%d    " , STACK[i]);
        }
        ok();
    }
    else
    {
        for (int i = 0 ; i < (top + 1) ; i++)
        {
            printf ("%d    " , STACK[i]);
        }
        ok();
    }
    

}


void inputString()
{
    char input[SIZE];                //Input string
    const char separator = ' ';      //Specify separator
    char *token;                     //The storage address that strtok() returns

    gets(input);
    token = strtok(input, &separator);
    ok();

    while( token != NULL )
    {
        if (isdigit(*token) > 0)
        {
            push(token);
        }
        else
        {
            for (int i = 0; i < sizeof(*token); i++)
            {
                tolower(*(token + i));
            }
            
            /*tolower(*token);
            if (strcmp(token , ".s") == 0)
            {
                printStack();
            }*/
            if (strcmp(token , "bye") == 0)
            {
                printf("goodbye\n");
                exit(0);
            }
            for (int i = 0; i < sizeof(keyWords); i++)
            {
               if (strcmp(token , *(keyWords + i)) == 0)
               {
                    printf("yeah!\n");
                    break;
               }
            }
        }
        
        //Passing other tokens
        token = strtok(NULL, &separator);
    }
}


void push(char *token)
{
    long int number;                 //The storage location of the number that atoi() returns
    
    //Oveflow checking
    if (top == SIZE - 1)
    {
        printf("\n\n\t\t[-] STACK OVERFLOW!\n\n");
    }
    else
    {
        number = atoi(token);
        top = top + 1;
        STACK[top] = (int) number;
    }
}


int main() {

    printf ("\n\n\t\t>>>FORTH SATCK DEMO<<<\n");
    for (int i = 0; i < 60; i++)
    {
        printf("-");
    }
    printf("\nKIForth version 1.0\nEnter the \"bye\" command to close the program.");
    printf ("\n\n");
    input:
        inputString();
    goto input;
    
}