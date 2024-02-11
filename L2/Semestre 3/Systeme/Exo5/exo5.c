#include <stdio.h>

int main(int argc, char* argv[],char* env[]){
    int j=0;
    printf("Nb arg : %i\n\nListe arg : \n", argc);
    for(int i=0;i<argc;i++){
        printf("%s ",argv[i]);
    }
    printf("\n\nListe env : ");
    while(env[j]!=NULL){
        printf("%s",env[j]);
        j++;
    }
    return 0;
}