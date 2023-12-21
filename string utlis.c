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
char *dyn_str_cpy=dyn_str;

while(*s!='\0'){

        if(*s==oldChar){

            *s=newChar;
            }

        *dyn_str=*s;

        s++;
        dyn_str++;

    }

    *dyn_str='\0';

return dyn_str_cpy;

}

// QUESTION NO : 3

void removeChar(char *s, char c){

char *ptr=s;

char *p;

while(*s!='\0'){

if(*s==c){

*s=*(s+1);
p=s+1;

while( *p != '\0'){

*p = *(p+1);
p++;
}

}

s++;
}

printf("\nAfter removing %c we get : ",c);

while(*ptr!='\0'){

printf("%c",*ptr);
ptr++;

}


}

// QUESTION NO : 4

char * removeCharCopy( char *s, char c){


char *ptr=s;

char *p;

while(*s!='\0'){

if(*s==c){

*s=*(s+1);
p=s+1;

while( *p != '\0'){

*p = *(p+1);
p++;