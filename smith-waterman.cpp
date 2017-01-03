#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50

void print_lcs(char path[MAX][MAX], int array[MAX][MAX], char *seq, int i, int j)
{
    if (i == 0 || j == 0 || array[i][j] == 0) {
        return;
    }
    if (path[i][j] == '\\') {
        print_lcs(path, array, seq, i-1, j-1);
        printf("|");
    } else {
        if (path[i][j] == '|') {
            print_lcs(path, array, seq, i-1, j);
        } else {
            print_lcs(path, array, seq, i, j-1);
            printf("-");
        }
    }
}

void print_seq(int array[MAX][MAX], char path[MAX][MAX], char *ori, char *seq, int max, int len_t, int len_s)
{
    int i, j, x, y, t, m = 0, space = 0;
    char *s = new char[MAX];
    for (i=len_t-1; i>=0; i--) {
        for (j=len_s-1; j>=0; j--) {
            if (array[i][j] == max) {
                x = i;
                y = j;
                while (array[x][y] != 0) {
                    x --;
                    y --;
                    m ++;
                }
                if (i > j) {
                    for (t=0; t<i-j;t++) {
                        printf(" ");
                    }
                }
                puts(ori);
                if (i > j) {
                    space = i - m;
                } else {
                    space = j - m;
                }
                for (t=0; t<space; t++) {
                    printf(" ");
                }
                print_lcs(path, array, seq, i, j);
                puts("");
                if (j > i) {
                    for (t=0; t<j-i;t++) {
                        printf(" ");
                    }
                }
                puts(seq);
                return;
            }
        }
    }
}

int main()
{
    int i, j;

    //char s[] = "GTCGGACATTAATCACTTACAT";
    //char t[] = "CCGACATAGTGAGGGGTTT";
    char s[] = "GTCGGAACGGGGGTTTTACAT";
    char t[] = "CCGACATAGTGAGGGGTTT";
    int len_s = strlen(s) + 1;
    int len_t = strlen(t) + 1;
    int max, score;

    int array[MAX][MAX];
    char path[MAX][MAX];

    for (i=0; i<len_s; i++) {
        array[0][i] = 0;
        path[0][i] = ' ';
    }
    for (i=0; i<len_t; i++) {
        array[i][0] = 0;
        path[i][0] = ' ';
    }
    for (i=1; i<len_t; i++) {
        for (j=1; j<len_s; j++) {
            path[i][j] = ' ';
            if (t[i-1] == s[j-1]) {
                score = 1;
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
            if (array[i][j] < 0) {
                array[i][j] = 0;
            }
        }
    }
    for (i=0; i<len_s; i++) {
        if (i > 0) {
            printf("%3c ", s[i-1]);
        } else {
            printf("      ");
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
            printf("%2c%d ", path[i][j], array[i][j]);
        }
        puts("");
    }

    max = 0;
    for (i=len_t-1; i>=0; i--) {
        for (j=len_s-1; j>=0; j--) {
            if (array[i][j] > max) {
                max = array[i][j];
            }
        }
    }
    puts("\nResult:");
    //printf("%s\n", s);
    print_seq(array, path, s, t, max, len_t, len_s);
    //printf("%s\n", t);
    return 0;
}
