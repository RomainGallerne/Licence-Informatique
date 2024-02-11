#include "pair.h"
#include "impair.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
    if (pair(atoi(argv[1]))){
        printf("n est pair !\n");
    }
    else{
        printf("n est impair !\n");
    }
}