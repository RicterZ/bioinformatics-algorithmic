#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define COUNT 5

int main()
{
    int i, j;

    int capacity = 20;
    int c[COUNT+1][21] = {0};

    int w[COUNT] =  {3, 4, 7, 8, 9};
    int v[COUNT] =   {4, 5, 10, 11, 13};

    for (i=1; i<=COUNT; i++) {
        for (j=1; j<=capacity; j++) {
            c[i][j] = w[i-1] > j ? c[i-1][j] :
                      c[i-1][j-w[i-1]] + v[i-1] > c[i-1][j] ?
                      c[i-1][j-w[i-1]] + v[i-1] : c[i-1][j];
        }
    }

    for (i=0; i<=COUNT; i++) {
        for (j=0; j<=capacity; j++) {
            printf("%-2d ", c[i][j]);
        }
        puts("");
    }

    int temp_w = capacity;
    int x[COUNT] = {0};
    for (i=COUNT; i>=1; i--) {
        if (c[i-1][temp_w] == c[i][temp_w]) {
            x[i-1] = 0;
        } else {
            x[i-1] = 1;
            temp_w -= w[i-1];
        }

    }

    for (i=0; i<COUNT; i++) {
        printf("%d ", x[i]);
    }
    puts("");
    return 0;
}
