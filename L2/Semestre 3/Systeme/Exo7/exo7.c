#include <stdio.h>

int main(char* argv[]){
    float number,result = .0;
    for(int i=0; i<5; i++){
        printf("Entrez le nombre numéro %i : ", i+1);
        scanf("%f", &number);
        result += number;
    }
    result /= 5.0;
    printf("\nLa moyenne de ces 5 nombres est : %f\n\n",result);
    return 0;
}