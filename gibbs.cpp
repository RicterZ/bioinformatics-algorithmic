#include <stdio.h>
#include <string.h>

void count(char *s, char c, int length, int *result)
{
    length --;
    while (length >= 0)
    {
        if (s[length] == c) {
            *result = *result + 1;
        };
        length --;
    };
}

int main()
{
    char s[4][9] = {
        // "AATATTTA",
        "AAAATTTA",
        "TCAAGCGT",
        "GTAAACGA",
        "TACTTAAC"
    };

    char f[] = "ACTG";
    int result;
    float result_pro[8][4];
    char temp_s[4];

    for (int j=0; j<8; j++) {
        for (int i=0; i<4; i++) {
            temp_s[i] = s[i][j];
        }
        for (int i=0; i<4; i++) {
            result = 0;
            count(temp_s, f[i], 4, &result);
            result_pro[j][i] = result / 4.0;
        }
    }

    for (int i=0; i<4; i++) {
        printf("      ");
        for (int j=0; j<8; j++) {
            printf("%-6c", s[i][j]);
        }
        printf("\n");
    }
    for (int i=0; i<4; i++) {
        printf("%-6c", f[i]);
        for (int j=0; j<8; j++) {
            printf("%.2f  ", result_pro[j][i]);
        }
        printf("\n");
    }


    float p;
    int index;
    char seq[] = "GTAAACAATATTTATAGC";

    for (int i=0; i<18-8; i++) {
        p = 1.0;
        for (int j=0; j<8; j++) {
            switch (seq[i+j]) {
                case 'A':
                    index = 0;
                    break;
                case 'C':
                    index = 1;
                    break;
                case 'T':
                    index = 2;
                    break;
                case 'G':
                    index = 3;
                    break;
                default:
                    printf("Invalid seq");
                    return 1;
            }
            p = result_pro[j][index] * p;
            printf("%c", seq[i+j]);
        }
        printf("    %f\n", p);
    }

    return 0;
}
