#include "pair.h"
#include "impair.h"

int pair(unsigned int i){
    if (i==0)
        return 1;
    else
        return impair(i-1);
}