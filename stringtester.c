#include<stdio.h>
#include "string_utils.h"
#include<stdlib.h>
#include<string.h>

int main(){
int choice;
printf("\nEnter Question No you want to execute (1-5) : ");
scanf("%d",&choice);

// QUESTION NO : 1

if (choice==1){
   printf("\nTest Case 1\n");

char str[8]="MURT_Z_";

char oldChar='_';
char newChar='A';

replaceChar(str , oldChar, newChar);
