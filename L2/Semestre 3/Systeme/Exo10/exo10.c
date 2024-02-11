#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
    int result = 0, multiplier = 1;
    for(int i=(strlen(argv[1])); i>0; i--){
        result += (argv[1][i-1]-48)*multiplier;
        multiplier *= 10;
    }
    printf("%i\n", result);
    return 0;
}