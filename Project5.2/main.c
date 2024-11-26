#include <malloc.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>

int enter_number(int* n) {
    if (scanf_s("%d", n) != 1 || *n <= 0) {
        printf("Data is incorrect\n");
        return 0;
    }
    return 1;
}

int enter_independently(int** a, int* b, int i) {
        for (int j = 0; j < b[i]; ++j) {
            if (scanf_s("%d", &a[i][j]) != 1) {
                printf("Data is not correct, try more");
                return 0;
            }
            if (a[i][j] == 100) {
                b[i] = j + 1;
                break;
            }
        }
        return 1;
}

void enter_random(int** a, int* b, int i) {
        for (int j = 0; j < b[i]; ++j) {
            a[i][j] = rand() % 21 - 10;
            printf("%d ", a[i][j]);
        }
        printf("\n");
}
       
void printf_array(int** a, int* b, int i){ 
    for (int j = 0; j < b[i]; ++j) {
        printf("%d ", a[i][j]);
    }
    printf("\n");
}

void delete_negative(int** a, int* b, int i) {
    for (int j = 0; j < b[i]; ++j) {
        if (a[i][j] < 0) {
            for (int k = j; k < b[i] - 1; ++k) {
                a[i][k] = a[i][k + 1];
            }
            b[i]--;
            j--;
        }
    }
}

int main() {
    srand(time(NULL));
    int n = 0, m = 0;

    do {
        scanf_s("%*[^\n]");

        printf("Enter the numbers of desired rows for the set: ");
        if(!enter_number(&n)) {
            continue;
        }
        int** a = (int**)malloc(n * sizeof(int*));  // выделяем память под количество строк
        if (!a) {
            printf("Memory allocation failed");
            continue;
        }
        int* b = (int*)malloc(n * sizeof(int));  //  выделяем память для запоминания кол-ва элементов в каждой строке
        if (!b) {
            printf("Memory allocation failed");
            continue;
        }

        int i = 0;
        for (i = 0; i < n; ++i) { //задаем подмассивы каждого элемента
            printf("Enter the number of desired elements for the %d row: ", i+1);
            if(!enter_number(&m)){
                break;
            }
            b[i] = m;
            if (!b[i]) {
                printf("Memory allocation failed");
                for (int k = 0; k < i; ++k) {
                    free(a[k]);
                }
                free(a);
                break;
            }
        }
        if (i != n) {
            continue;
        }

        for (int i = 0; i < n; ++i) {
            a[i] = (int*)malloc(b[i] * sizeof(int)); //выделение памяти для подмассива
            if (!a[i]) {
                printf("Memory allocation failed");
                for (int k = 0; k < i; ++k) {
                    free(a[k]);
                }
                free(a);
                break;
            }

            puts(" Do you want to enter the data yourself or randomly?\n Please, press 0 - for independently, 1 - for randomly.");
            char option_1 = _getch();
            if (option_1 == '0') {
                if (!enter_independently(a, b, i)) {
                    printf("Data is not correct, please, try again\n");
                    break;
                }
            }
            else if (option_1 == '1') {
                enter_random(a, b, i);
            }
            else {
                printf("Data is incorrect\n");
                break;
            }

            delete_negative(a, b, i);

            scanf_s("%*[^\n]");
        }

        printf("\nResult:\n");
        for (int i = 0; i < n; ++i) {
            printf_array(a, b, i);
        }
       

        for (int i = 0; i < n; ++i) {
            free(a[i]);
        }
        free(b);
        free(a);

    } while (puts("Contiue - 1, Exit - 0"), _getch() == '1');

    return 0;
}
