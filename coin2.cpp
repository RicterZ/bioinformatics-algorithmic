#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define COIN_COUNT 6

int main()
{

    unsigned int money, temp, i;
    printf("Please input the change: ");
    scanf("%d", &money);

    int coin[COIN_COUNT] =       {  1,   5,  10,  20,  50, 100};
    int coin_num[COIN_COUNT] = {0};

    temp = money;
    for (i=COIN_COUNT; i>0; i--) {
        if (temp >= coin[i-1]) {
            coin_num[i-1] = temp / coin[i-1];
            temp -= coin_num[i-1] * coin[i-1];
        }
    }

    for (i=0; i<COIN_COUNT; i++) {
        if (coin_num[i] != 0) {
            printf("%3d CNY: %d\n", coin[i], coin_num[i]);
        }
    }
    return 0;
}
