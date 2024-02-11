#include <stdio.h>
#include <stdlib.h>

char* alphabet = "abcdefghijklmnopqrstuvwxyz";
float compte[] = {.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0,.0};

int numero(char x){
    int result;
    for(int i=0; i<26; i++){
        alphabet++;
        if (x == alphabet[i]){
            result = i;
        }
    } 
    return result;
}

void probaFinal(){
    for(int i=0; i<26; i++){
        compte[i] /= 26;
        printf("Taux de %c : %f",alphabet[i],compte[i]);
    }
    printf("Total : 1");
}

int main(int argc, char* argv[]){
    FILE * fd; 
    fd = fopen(argv[1],"r");
    int compteur = 0;
    char c;
    while (fread(&c,8,fd) != '\0'){
        compte[numero(fread(&c,8,fd))] ++;
        compteur ++;
    }
    probaFinal();
    fclose(fd);
}