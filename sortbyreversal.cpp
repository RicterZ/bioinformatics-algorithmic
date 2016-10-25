#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#define abs(x) ((x) >= 0 ? (x) : (-x))
#define MAX 12

bool find_reduction(int array[])
{
    int i;
    for (i=1; i<MAX; i++) {
        if (array[i-1] > array[i]) {
            return true;
        }
    }
    return false;
}

void find_breakpoint(int array[], int array_bp[], int *length)
{
    int tmp, i, j = 0;
    for (i=1; i<MAX; i++) {
        tmp = array[i] - array[i-1];
        if (abs(tmp) > 1) {
            array_bp[i] = i;
            j ++;
        }
    }
    *length = j;
}

bool in_array(int array[], int num, int length)
{
    int i;
    for (i=0; i<length; i++) {
        if (array[i] == num)
            return true;
    }
    return false;
}

void print_breakpoint(int array[], int array_bp[], int *length)
{
    int i, j;
    // printf("Permutation: ");
    for (i=0; i<MAX; i++) {
        /*
        if (in_array(array_bp, i, *length)) {
            printf("| ");
        }
        */
        printf("%-3d", array[i]);
    }
    puts("");
    /*
    printf("\nBreakpoints: ");
    for (i=0; i<*length; i++) {
        printf("%d ", array_bp[i]);
    }
    printf(", Length: %d\n", *length);
    */
}

void reverse(int array[], int start, int end)
{
    if (start > end) {
        return;
    }
    
    int i, temp;
    int *array_temp = (int *)malloc(sizeof(int) * MAX);
    memcpy(array_temp, array, sizeof(int) * MAX);

    temp = start;
    for (i=end; i>=start; i--) {
        array[temp] = array_temp[i];
        temp ++;
    }
    
    free(array_temp);
}

void sort(int array[])
{
    int array_bp_length, i, j;
    int *array_bp = (int *)malloc(sizeof(int) * (MAX));
    
    int *array_temp = (int *)malloc(sizeof(int) * (MAX));
    int *array_bp_temp = (int *)malloc(sizeof(int) * (MAX));
    
    int *array_result = (int *)malloc(sizeof(int) * (MAX));
    int *array_bp_result = (int *)malloc(sizeof(int) * (MAX));
    
    memset(array_bp, 0, sizeof(int) * MAX);
    
    find_breakpoint(array, array_bp, &array_bp_length);
    print_breakpoint(array, array_bp, &array_bp_length);
    
    int min = array_bp_length;
    int array_temp_bp_length;
    
    int x_i, x_j;
    
    memcpy(array_result, array, sizeof(int) * MAX);
    memcpy(array_bp_result, array_bp, sizeof(int) * MAX);
    while (1) {
        bool flag = false;
        for (i=0; i<array_bp_length; i++) {
            for (j=i+1; j<array_bp_length; j++) {
                if (array[i] > array[j] - 1) {
                    memcpy(array_temp, array, sizeof(int) * MAX);
                    reverse(array_temp, i, j);
                    
                    find_breakpoint(array_temp, array_bp_temp, &array_temp_bp_length);
                    if (min > array_temp_bp_length) {
                        flag = true;
                        x_i = i;
                        x_j = j;
                        min = array_temp_bp_length;
                        memcpy(array_result, array_temp, sizeof(int) * MAX);
                        memcpy(array_bp_result, array_bp_temp, sizeof(int) * MAX);
                    }
                    
                }
            }
        }
        if (flag) {
            for (i=0; i<MAX; i++) {
                if (i > x_i && i < x_j) {
                    printf("---");
                } else if (i == x_i) {
                    printf("^--");
                } else if (i == x_j) {
                    printf("^");
                } else {
                    printf("   ");
                }
            }
            puts("\n");
        }
        
        memcpy(array, array_result, sizeof(int) * MAX);
        
        if (flag) {
            print_breakpoint(array, array_bp_result, &min);
        }
        
        if (!find_reduction(array)) {
            break;
        }
        
        array_bp_length = min;
        min = MAX;
    }

}

int main()
{
    int array2[MAX] = {0, 6, 1, 2, 5, 4, 9, 7, 8, 10, 3, 11};
    sort(array2);
    
    return 0;
}
