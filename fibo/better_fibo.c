#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef unsigned long long inter;

inter fibo(int nth, inter *stru){

    //change logic

    if(nth > 100) {
        return 1;
    }
    if (nth <= 2) {
        stru[nth] = 1;
        return 1;
    }
    if (stru[nth])
    {
        return stru[nth];
    }
    
    stru[nth] = fibo(nth - 1, stru) + fibo(nth - 2, stru);
    return stru[nth];
}

int main(){
    int nth = 0;
    inter *memor = (inter*)malloc(sizeof(inter)*101);
    printf("Insert a n-th number of the fibonacci sequence, being the first and second equals to one.\n");
    scanf("%d", &nth);
    clock_t start, end;
    start = clock();
    printf("The %dth of the fibonnacci sequence is: %llu\n", nth, fibo(nth, memor));
    end = clock();
    double time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken by program is : %f", time_taken);
    free(memor);
    return 0;
}