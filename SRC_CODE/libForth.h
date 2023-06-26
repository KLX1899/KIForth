//                >>>FORTH FUNCTIONS LIBRARY<<<

//                  CREATED BY AMIR KALAKI

//                      26 / JUNE / 2023

//        COPYRIGHT © 2023 AMIR KALAKI. ALL RIGHTS RESERVED.



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <curses.h>


#define SIZE 150                    //Size of stack in GForth is 150
#define NULL ((void *)0)



int top = -1 , STACK[SIZE];

char *keyWords[] = {".\"" , "(" , ")" , ":" , "." , ";" , "cr" , "dup" , "drop"     ,
"swap" , "rot" , "+" , "-" , "*" , "/" , ">" , "<" , "=" , "and" , "or" , "xor"     ,
"not" , "if" , "then" , "begin" , "until" , "do" , "loop" , ".s" , "/mod" , "mod"   ,
"negate" , "nip" , "tuck" , "t_swap" , "t_dup" , "t_over" , "t_drop" , "s\""       };
// include fileName.fs
// clear , reset , restart      : clear desktop
//





//ok()          :   Printing it shows that the command is done
void ok() 
{
    printf("> ok\n");
}



//printStack()  :   Prints the number of elements in the stack and their values
void printStack() //printStack():Prints the number of elements in the stack and their values
{
    printf ("<%d>\t" , (top + 1));
    if ((top + 1) > 9)
    {
        for (int i = (top - 8) ; i < (top + 1) ; i++)
        {
            printf ("%d    " , STACK[i]);
        }
        printf("\n");
    }
    else
    {
        for (int i = 0 ; i < (top + 1) ; i++)
        {
            printf ("%d    " , STACK[i]);
        }
        printf("\n");
    }
}



//push()        :   Adds entered numbers to top of the stack
void push(int number)
{
    if (top == SIZE - 1)    //Oveflow checking
    {
        printf("\n\n\t\t[-] STACK OVERFLOW!\n\n");
    }
    else
    {
    //    number = atoi(token);        //Adding numbers to the stack
        top = top + 1;
        STACK[top] = (int) number;
    }
}



//pop()        :   Adds entered numbers to top of the stack
void pop()
{
    if (top == -1)    //Underflow checking
    {
        printf("\n\n\t\t[-] STACK UNDERFLOW!\n\n");
    }
    else
    {
        STACK[top] = '\0';
        top = top - 1;
    }

}



//inputString() :   Takes the input string and checks it and refers to the corresponding function
void inputString()
{
    char input[1000];                //Input string
    const char separator = ' ';      //Specify separator
    char *token;                     //The storage address that strtok() returns

    printf("> ");                    //Prompt sign
    gets(input);
    token = strtok(input, &separator);
    ok();

    while( token != NULL )
    {
        if (isdigit(*token) > 0)     //Checks if this token is number or text
        {
            push(atoi(token));
        }
        else
        {
            if (strcasecmp(token , "bye") == 0)     //Bye is a keyword and is used to close the program
            {
                printf("goodbye\n");
                exit(0);
            }
            for (int i = 0; i < sizeof(keyWords); i++)
            {
               if (strcasecmp(token , *(keyWords + i)) == 0)
               {
                    printf("yeah!\n");
                    
                    switch (i)
                    {
                    case 6:                         //cr
                        printf("\n");
                        break;

                    case 7:                         //dup
                        push(STACK[top]);
                        break;

                    case 8:                         //drop
                        pop();
                        break;

                    case 9:                         //swap
                        printf("swap ");
                        break;
                    
                    case 28:                         //.s
                        printStack();
                        break;
                    
                    default:
                        printf("sag ");
                        break;
                    }
                    break;
               }
            }
        }
        
        //Passing other tokens
        token = strtok(NULL, &separator);
    }
}

