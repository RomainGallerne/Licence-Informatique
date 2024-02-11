#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    float result = 0;
    for(int i=1; i<argc; i++){
        result += atoi(argv[i]);
    }
    result /= (argc-1);
    printf("La moyenne est : %f\n", result);
    return 0;
}