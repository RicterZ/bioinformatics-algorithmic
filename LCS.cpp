#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 20

void print_lcs(char path[MAX][MAX], char *seq, int i, int j)
{

    if (i == 0 || j == 0) {
        return;
    }
    if (path[i][j] == '\\') {
        print_lcs(path, seq, i-1, j-1);
        printf("%c", seq[i-1]);
    } else {
        if (path[i][j] == '|') {
            print_lcs(path, seq, i-1, j);
        } else {
            print_lcs(path, seq, i, j-1);
            printf("-");
        }
    }
}

int main()
{
    int i, j;

    char s[] = "ATCAGAACTGGGATC";
    char t[] = "ATCGGATTCGGTC";
    //char s[] = "ACTTCG";
    //char t[] = "ACTAG";
    int len_s = strlen(s) + 1;
    int len_t = strlen(t) + 1;
    int max, score;

    int array[MAX][MAX];
    char path[MAX][MAX];

    for (i=1; i<len_s; i++) {
        array[0][i] = array[0][i-1] - 2;
    }
    for (i=1; i<len_t; i++) {
        array[i][0] = array[i-1][0] - 2;
    }
    for (i=1; i<len_t; i++) {
        for (j=1; j<len_s; j++) {
            if (i == 0 && j == 0) {
                array[i][j] = 0;
            } else if (i == 0) {
                array[i][j] = array[i][j-1] - 2;
            } else if (j == 0) {
                array[i][j] = array[i-1][j] - 2;
            } else {
                if (t[i-1] == s[j-1]) {
                    score = 3;
                } else {
                    score = -1;
                }
                if (array[i-1][j] > array[i][j-1]) {
                    
                    max = array[i-1][j] - 2;
                } else {
                    max = array[i][j-1] - 2;
                }
                if (max < array[i-1][j-1] + score) {
                    max = array[i-1][j-1] + score;
                }

                array[i][j] = max;
                if (array[i][j] == array[i-1][j] - 2) {
                    path[i][j] = '|';
                } else if (array[i][j] == array[i][j-1] - 2) {
                    path[i][j] = '-';
                } else {
                    path[i][j] = '\\';
                }

            }
        }
    }
    for (i=0; i<len_s; i++) {
        if (i > 0) {
            printf("%4c ", s[i-1]);
        } else {
            printf("       ");
        }
    }

    puts("");
    for (i=0; i<len_t; i++) {
        if (i > 0) {
            printf("%c ", t[i-1]);
        } else {
            printf("  ");
        }
        for (j=0; j<len_s; j++) {
            printf("%4d ", array[i][j]);
        }
        puts("");
    }

    puts("\nResult:");
    puts(s);
    print_lcs(path, t, len_t-1, len_s-1);
    puts("");
    return 0;
}
