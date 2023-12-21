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