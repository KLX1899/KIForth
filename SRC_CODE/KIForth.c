//          >>>KIForth - Forth interpreter with C<<<

//                  CREATED BY AMIR KALAKI

//                      29 / JUNE / 2023

//        COPYRIGHT © 2023 AMIR KALAKI. ALL RIGHTS RESERVED.



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libForth.h"



int main() {

    //system("gnome-terminal -x sh -c './KIForth.c; exec bash'");
    printf ("\n\n\t\t>>>FORTH SATCK DEMO<<<\n");
    for (int i = 0; i < 60; i++)
    {
        printf("-");
    }
    printf("\nKIForth version 1.0\nEnter the \"bye\" command to close the program.");
    printf ("\n\n");
    input:
        command();
    goto input;
    
}