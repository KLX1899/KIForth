//                >>>FORTH FUNCTIONS LIBRARY<<<

//                  CREATED BY AMIR KALAKI

//                      27 / JUNE / 2023

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
"negate" , "nip" , "tuck" , "tswap" , "tdup" , "tover" , "tdrop" , "s\""       };
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



//pop()        :   Removes top of the stack
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



//swap()       :   Replaces number1 and number2
void swap(int number1 , int number2)
{
    int temp;

    temp = STACK[number1];
    STACK[number1] = STACK[number2];
    STACK[number2] = temp;
}



//tswap()       :   Replaces first two numbers and the second two numbers
void tswap(int number1 , int number2 , int number3 , int number4)
{
    if (top >= 3)
    {
        swap(number1 , number3);
        swap(number2 , number4);
    }
    else
    {
        printf("\n\n\t\t[-] Stack has less than four elements!\n\n");
    }
    
    
}



//add() :   1 2 + -->     3
void add()
{
    STACK[top - 1] = STACK[top - 1] + STACK[top];
    pop();
}



//sub() :   2 1 - -->     1
void sub()
{
    STACK[top - 1] = STACK[top - 1] - STACK[top];
    pop();
}




//mltp() :   2 3 * -->    6
void mltp()
{
    STACK[top - 1] = STACK[top - 1] * STACK[top];
    pop();
}




//divi() :   9 3 / -->    3
void divi()
{
    if (STACK[top] != 0)
    {
        STACK[top - 1] = STACK[top - 1] / STACK[top];
        pop();
    }
    else
    {
        printf("\n\n\t\t[-] DIVISION BY 0!\n\n");
    }
    
}




//mod() :    10 3 mod --> 2
void mod()
{
    STACK[top - 1] = STACK[top - 1] % STACK[top];
    pop();
}




// /mod() :   10 3 /mod -->  1 3
void mod_quotient()
{
    int a , b;

    a = STACK[top - 1];
    b = STACK[top];
    STACK[top - 1] = a % b;
    STACK[top] = a / b;
}




//negate() :   3 -->  -3
void negate()
{
    STACK[top] = -STACK[top];
}




//nip() :   3 7 nip  -->  7
void nip()
{
    STACK[top] = STACK[top - 1];
    pop();
}




//tuck() :   3 7 tuck  --> 3 7 3
void tuck()
{
    push(STACK[top - 1]);
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
                    case 6:                                 //cr        New line
                        printf("\n");
                        break;

                    case 7:                                 //dup       1 2   --> 1 2 2
                        push(STACK[top]);
                        break;

                    case 8:                                 //drop      1 2 3 -->   1 2
                        pop();
                        break;

                    case 9:                                 //swap      1 2   -->   2 1
                        swap(top , (top - 1) );
                        break;
                    
                    case 10:                                //rot       1 2 3 --> 2 3 1         (rotate)
                        swap( (top - 1) , (top - 2) );
                        swap(top , (top - 1) );                        
                        break;
                    
                    case 11:                                //add       1 2 + -->     3         (addition)
                        add();
                        break;
                    
                    case 12:                                //sub       2 1 - -->     1         (subtraction)
                        sub();
                        break;
                    
                    case 13:                                //mltp      2 3 * -->     6         (multiplication)
                        mltp();
                        break;
                    
                    case 14:                                //divi      9 3 / -->     3         (division)
                        divi();
                        break;
                    
                    case 28:                                //.s        Prints the stack
                        printStack();
                        break;
                    
                    case 29:                                // /mod     Shows remainder and quotient
                        mod_quotient();
                        break;
                    
                    case 30:                                //mod       Shows remainder
                        mod();
                        break;
                    
                    case 31:                                //negate    3 negate --> -3
                        negate();
                        break;
                    
                    case 32:                                //nip       3 7 nip  -->  7
                        nip();
                        break;
                    
                    case 33:                                //tuck      3 7 tuck --> 3 7 3
                        tuck();
                        break;
                    
                    case 34:                                //tswap      1 2 3 4 tswap --> 3 4 1 2
                        tswap(top , (top - 1) , (top - 2) , (top - 3) );
                        break;
                    
                    case 35:                                //tdup      1 2 tdup --> 1 2 1 2
                        if (top >= 1)
                        {
                            push(STACK[top - 1]);
                            push(STACK[top - 1]);
                        }
                        else
                        {
                            printf("\n\n\t\t[-] Stack has less than two elements!\n\n");
                        }
                        break;
                    
                    case 36:                                //tover      1 2 3 4 tover --> 1 2 3 4 1 2
                        if (top >= 3)
                        {
                            push(STACK[top - 3]);
                            push(STACK[top - 3]);
                        }
                        else
                        {
                            printf("\n\n\t\t[-] Stack has less than four elements!\n\n");
                        }
                        break;
                    
                    case 37:                                //tdrop      1 2 tdrop --> 
                        if (top >= 1)
                        {
                            pop();
                            pop();
                        }
                        else
                        {
                            printf("\n\n\t\t[-] Stack has less than two elements!\n\n");
                        }
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

