#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "forthLIB.h"

#define SIZE 150                    //Size of stack in GForth is 150
#define NULL ((void *)0)


int top = -1 , STACK[SIZE];
// It does not support spaces after :_ , ."_ , ... and upper or lower case and if a number is at the beginning of the expression
char *keyWords[] = {".\"" , "(" , ")" , ":" , "." , ";" , "cr" , "dup" , "drop" , "swap" , "rot" , "+" , "-" , "*" , "/" , ">" , "<" , "=" , "and" , "or" , "xor" , "not" , "if" , "then" , "begin" , "until" , "do" , "loop" , ".s" , "/mod" , "mod" , "negate" , "nip" , "tuck" , "2swap" , "2dup" , "2over" , "2drop" , "s\""};
char bye[] = "bye";





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
        number = atoi(token);        //Adding numbers to the stack
        top = top + 1;
        STACK[top] = (int) number;
    }
}


void ok() 
{
    printf("> ok\n");
}


void printStack()
{
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
        number = atoi(token);        //Adding numbers to the stack
        top = top + 1;
        STACK[top] = (int) number;
    }
}


void inputString()
{
    char input[SIZE];                //Input string
    const char separator = ' ';      //Specify separator
    char *token;                     //The storage address that strtok() returns

    printf("> ");                    //Prompt sign
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
            if (strcasecmp(token , "bye") == 0)
            {
                printf("goodbye\n");
                exit(0);
            }
            for (int i = 0; i < sizeof(keyWords); i++)
            {
               if (strcasecmp(token , *(keyWords + i)) == 0)
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


