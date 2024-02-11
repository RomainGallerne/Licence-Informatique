#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *conversion(int i,char *s){
    if (i<10){
        s[0] = i+'0';
        s[1] = '\0';
    } 
    else {
        char unite = i%10 + '0';
        int l = strlen(conversion(i/10,s));
        s[l] = unite;
        s[l+1] = "\0";
    }
}

int main(){
    char s[256];
    printf("%s", conversion(372,s));
}