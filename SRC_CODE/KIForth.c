//          >>>KIForth - Forth interpreter with C<<<

//                  CREATED BY AMIR KALAKI

//                      27 / MAY / 2023

//        COPYRIGHT © 2023 AMIR KALAKI. ALL RIGHTS RESERVED.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 150                    //Size of stack in GForth is 150


int top = -1 , STACK[SIZE];


void push()
{
    char input[SIZE];                //Input string
    const char separator = ' ';      //Specify separator
    char *token;                     //The storage address that strtok() returns
    long int number;                 //The storage location of the number that atoi() returns
    
    //Oveflow checking
    if (top == SIZE - 1)
    {
        printf("\n\n\t\t[-] STACK OVERFLOW!\n\n");
    }
    else
    {
        gets(input);

        //Input tokenizing by separator
        token = strtok(input, &separator);

        while( token != NULL )
        {
            number = atoi(token);
            top = top + 1;
            STACK[top] = (int) number;
            // printf( " %s\n", token );
    
            //Passing other tokens
            token = strtok(NULL, &separator);
        }

        
    }
}


void printStack() {

    printf ("\n<%d>\t" , (top + 1));
    if ((top + 1) > 10)
    {
        for (int i = (top - 9) ; i < (top + 1) ; i++)
        {
            printf ("%d    " , STACK[i]);
        }
        printf("\n\n");
    }
    else
    {
        for (int i = 0 ; i < (top + 1) ; i++)
        {
            printf ("%d    " , STACK[i]);
        }
        printf("\n\n");
    }
    

}


int main() {

    printf ("\n\n\t\t>>>FORTH SATCK DEMO<<<\n");
    for (int i = 0; i < 60; i++)
    {
        printf("-");
    }
    printf ("\n\n");
    push();
    printStack();
    
    
}