#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define s_size strlen(s)

char **strsplit(const char *s, const char sep){
    int nb_separateur = 0;
    for(int i=0;i<s_size;i++){
        if (s[i] == sep){
            nb_separateur++;
        }
    }
    int tableau = malloc(4*sizeof(char*));
    for(int i=0; i<4*sizeof(char*); i++){
        tableau[i] = malloc(sizeof(char*));
    }
    int case_tab = 0;
    int previous_j = 0;
    for(int j=0;j<s_size;j++){
        if (s[j] == sep){
            for (int k=previous_j;k<j;k++){
                strcat(*tableau[0],s[k]);
                case_tab++;
                previous_j = j+1;
            }
        }
    }
    tableau[nb_separateur+1] = NULL;
    return tableau;
}

int main(char* argv[]){
    **tableau[] = strsplit(argv[1],argv[2]);
    int i=0;
    while (*tableau[i]!=NULL){
        printf(*tableau[i]);
        i++;
    }
    return 0;
}