#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define COIN_COUNT 6

int main()
{

    unsigned int money;
    printf("Please input the change: ");
    scanf("%d", &money);

    int *money_array = new int[money+1];
    memset(money_array, 0, sizeof(int) * (money+1));

    int i, j, k, min_count, used_coin_index;

    int coin[COIN_COUNT] =       {  1,   5,  10,  20,  50, 100};
    int coin_store[COIN_COUNT] = { 100, 100, 100,100,100,100};

    int **coin_cost = new int*[money+1];
    for(i=0; i<money+1; i++) {
        coin_cost[i] = new int[COIN_COUNT];
        memset(coin_cost[i], 0, sizeof(int) * COIN_COUNT);
    }

    money_array[1] = 1;
    for (i=1; i<=money; i++) {
        min_count = i;
        used_coin_index = 0;
        for (j=0; j<COIN_COUNT; j++) {
            if (coin[j] <= i) {
                if (coin_store[j] <= 0 || coin_cost[i-coin[j]][j] + 1 > coin_store[j]) {
                    continue;
                }
                if (1 + money_array[i-coin[j]] < min_count) {
                    min_count = 1 + money_array[i-coin[j]];
                    used_coin_index = j;
                }
            }
        }
        for (k=0; k<COIN_COUNT; k++) {
            coin_cost[i][k] = coin_cost[i-coin[used_coin_index]][k];
        }
        coin_cost[i][used_coin_index] += 1;
        money_array[i] = min_count;
    }

    for (i=0; i<COIN_COUNT; i++) {
        if (coin_cost[money][i] > coin_store[i]) {
            puts("Can't change");
            return 0;
        }
    }

    for (i=0; i<COIN_COUNT; i++) {
        if (coin_cost[money][i] != 0) {
            printf("%3d CNY: %d\n", coin[i], coin_cost[money][i]);
        }
    }

    // free
    free(money_array);
    for(i=0; i<money+1; i++) {
        free(coin_cost[i]);
    }
    free(coin_cost);
    return 0;
}
