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
printf("\nTest Case 2\n");

char str_2[8]="AOMSaTS";

oldChar='A';
newChar='C';

replaceChar(str_2 , oldChar, newChar);

// Test Case 3

printf("\nTest Case 3\n");

char str_3[12]="M__YE M__YE";

oldChar='_';
newChar='O';

replaceChar(str_3 , oldChar, newChar);

}

// QUESTION NO : 2

if (choice==2){
    
    //TEST CASE:1

char str[8]="MOOP";
char oldChar='P';
char newChar='N';

char *dyn_arr_ptr = replaceCharCopy(str , oldChar, newChar);

printf("\nAfter Replace of %c with %c we get : %s",oldChar,newChar,dyn_arr_ptr);

 //TEST CASE:2

char str_2[8]="AOMSaTS";
 oldChar='A';
 newChar='C';

char *dyn_arr_ptr_2 = replaceCharCopy(str_2 , oldChar, newChar);
printf("\nAfter Replace of %c with %c we get : %s",oldChar,newChar,dyn_arr_ptr_2);

 //TEST CASE:3

char str_3[12]="M__YE M__YE";
 oldChar='_';
 newChar='O';
 char *dyn_arr_ptr_3 = replaceCharCopy(str_3 , oldChar, newChar);

printf("\nAfter Replace of %c with %c in we get : %s",oldChar,newChar,dyn_arr_ptr_3);

}

// QUESTION NO : 3

if(choice==3){

//test case : 1

char str[9]="MURT_AZA";

char c='_';

removeChar(str,c);

//test case : 2

char str_2[9]="COMSIATS";

 c='I';

removeChar(str_2,c);

//test case : 3

char str_3[7]="ABC_DE";

 c='_';

removeChar(str_3,c);


}

// QUESTION NO : 4

if(choice==4){



//TEST CASE :1

char str[9]="MURT_AZA";
char c='_';

char *ptr = removeCharCopy(str,c);

printf("\nAfter Removing %c from %s we get : %s",c,str,ptr);

//TEST CASE :2

char str_2[9]="COMSIATS";
 c='I';

char *ptr_2 = removeCharCopy(str_2,c);

printf("\nAfter Removing %c from %s we get : %s",c,str_2,ptr_2);

//TEST CASE :3

char str_3[7]="ABC_DE";

 c='_';

char *ptr_3 = removeCharCopy(str_3,c);

printf("\nAfter Removing %c from %s we get : %s",c,str_3,ptr_3);

}


}