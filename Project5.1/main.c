#include <conio.h>
#include <malloc.h>
#include <stdio.h>
#include <time.h>

int creating_array(int n) {
    printf("Enter the numbers of desired numbers: ");
    if (scanf_s("%d", &n) != 1 || n <= 0) {
        printf("Data is incorrect\n");
        n = -1;
    }
    return n;
}

void printf_array(int* a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void shift_left(int* a, int* n, int j) {
      for (int k = j; k < *n - 1; ++k){
        a[k] = a[k + 1];
      }
      (*n)--;
}



int main() {
    srand(time(NULL));
    do {
        scanf_s("%*[^\n]");
        int* a;
        int n = 0;
        n = creating_array(n);
        if (n == -1) {
            continue;
        }

        a = (int*)malloc(n * sizeof(int));
       
        puts("Press 1 to enter elements independetly, press 0 to enter elements randomly");
        char option1 = _getch();
        if (option1 == '0') {
            for (int i = 0; i < n; ++i) {
               a[i] = rand() % 21 - 10;
               printf("%d ", a[i]);
            }
        }
        else if (option1 == '1') {
            for (int i = 0; i < n; ++i) {
                if (scanf_s("%d", &a[i]) != 1) {
                    printf("Data is incorrect\n");
                    free(a);
                    return 0;
                }
            }
        }
        else {
            printf("Data is incorrect\n");
            free(a);
            continue;
        }

        printf("\n");
       
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (a[i] == a[j]) {
                    shift_left(a, &n, j);
                    j--;
                }
            }
        }

        printf_array(a, n);

        free(a);
    } while (puts("Contiue - 1, Exit - 0"), _getch() == '1');

    return 0;
}

/* 
1 1 2 2, n = 4, i = 0, j = 1
1 2 2 x, n = 3, i = 0, j = 1
1 2 2 x, n = 3, i = 0, j = 2
1 2 2 x, n = 3, i = 0, j = 3

1 2 2 x, n = 3, i = 1, j = 2
1 2 x x, n = 2, i = 1, j = 2
*/

/*
n = 4
1 0 
2 1 3
3 -4 -4 5
4 1 2
*/