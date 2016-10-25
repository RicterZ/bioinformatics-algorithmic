#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// stone number + 1
#define MAX_X 11
#define MAX_Y 11

void print_table(char table[MAX_X][MAX_Y]) {
    int i, j;
    for (i=0; i<MAX_X; i++) {
        for (j=0; j<MAX_X; j++) {
            printf("%c ", table[i][j]);
        }
        printf("\n");
    }
}

void init_table(char table[MAX_X][MAX_Y]) {
    int i, j;
    table[0][0] = '0';
    for (i=0; i<MAX_X; i++) {
        for (j=0; j<MAX_Y; j++) {
            if (i == 0 && j > 0) {
                if (table[i][j - 1] == '0') {
                    table[i][j] = '1';
                } else if (table[i][j - 1] == '1') {
                    table[i][j] = '0';
                }
                continue;
            }
            if (j == 0 && i > 0) {
                if (table[i - 1][j] == '0') {
                    table[i][j] = '1';
                } else if (table[i - 1][j] == '1') {
                    table[i][j] = '0';
                }
                continue;
            }
            table[i][j] = (table[i - 1][j] == '0' || table[i][j - 1] == '0' || table[i - 1][j - 1] == '0') ? '1' : '0';
        }
    }
}

void computer_turn(char table[MAX_X][MAX_Y], int *i, int *j) {
    int choice;
    if (table[*i][*j] == '0') {
        if (*j == 0) {
            *i = *i - 1;
        } else if (*i == 0) {
            *j = *j - 1;
        } else {
            choice = rand() % 3;
            if (choice == 0) {
                *i = *i - 1;
            } else if (choice == 1) {
                *j = *j - 1;
            } else {
                *i = *i - 1;
                *j = *j - 1;
            }
        }
    } else {
        if (*i == 0) {
            *j = *j - 1;
        } else if (*j == 0) {
            *i = *i - 1;
        } else {
            // mistake
            choice = rand() % 100;
            if (choice > 20) {
                if (*i % 2 == 0) {
                    *j = *j - 1;
                } else if (*j % 2 == 0) {
                    *i = *i - 1;
                } else {
                    *i = *i - 1;
                    *j = *j - 1;
                }
            } else {
                puts("Computer made a mistake");
                choice = rand() % 100;
                if (choice > 66) {
                    *i = *i - 1;
                } else if (choice < 33) {
                    *j = *j - 1;
                } else {
                    *i = *i - 1;
                    *j = *j - 1;
                }
            }
        }
    }
}

int main() {
    int i = MAX_X - 1, j = MAX_Y - 1, tmp_i, tmp_j;
    int x, y, choice;
    char *str_win = "Win", *str_lose = "Lose";

    srand((unsigned)time(0));
    int upper_hand = rand() % 100;

    char table[MAX_X][MAX_Y];
    memset(table, '2', MAX_X * MAX_Y);

    // 0: must lose point
    // 1: must win point
    // 2: init status
    init_table(table);
    // print_table(table);

    while (1) {
        tmp_i = i;
        tmp_j = j;
        puts("-------------------");
        printf("Stone status: %d %d\n", i, j);

       if (i == 0 && j == 0) {
           printf("You %s\n", upper_hand % 2 == 0 ? str_win : str_lose);
           break;
        }

        if (upper_hand % 2 == 0) {
            // computer turn
            computer_turn(table, &i, &j);
            printf("< Computer turn: %d %d\n", tmp_i - i, tmp_j - j);
        } else {
            // your turn
            if (i == 0 && j == 0) {
                printf("You %s\n", upper_hand % 2 != 0 ? str_win : str_lose);
                break;
            }

            while (1) {
                printf("> Your turn: ");
                scanf("%d %d", &x, &y);

                if (x > 1 || x < 0 || y > 1 || y < 0) {
                    continue;
                }
                if ((i == 0 && x != 0) || (j == 0 && y != 0)) {
                    continue;
                }
                if (x == 0 && y == 0) {
                    continue;
                }
                break;
            }
            i -= x;
            j -= y;
        }
        upper_hand --;
    }
    return 0;
}

