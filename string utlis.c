#include<stdio.h>
#include "string_utils.h"
#include<stdlib.h>
#include<string.h>


// QUESTION NO : 1
void replaceChar(char *s, char oldChar, char newChar){

char *ch=s;

while(*s != '\0'){

if(*s== oldChar){

*s = newChar;

}
s++;

}

printf("\nAfter Replacement we get : ");

while ( ch != (s+1) ){
    
    printf("%c",*ch);
    ch++;
    }


}

// QUESTION NO : 2

char *replaceCharCopy(char *s, char oldChar, char newChar){

char *dyn_str = (char*) malloc(strlen(s)+ 1); 
