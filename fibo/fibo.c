#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int fibo(int nth){
    if (nth <= 2) return 1;
    return fibo(nth-1) + fibo(nth-2);
}

int main(){
    int nth = 0;
    printf("Insert a n-th number of the fibonacci sequence, being the first and second equals to one.\n");
    scanf("%d", &nth);
    clock_t start, end;
    start = clock();
    printf("The %dth number of fibonacci sequence is %d\n", nth, fibo(nth));
    end = clock();
    double time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken by program is : %f", time_taken);    
    return 0;
}