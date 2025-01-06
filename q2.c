#include <stdio.h>
#include <stdlib.h>

void filter(int **array, int m, int n, int **fil, int k, int **result);

int main() {
    int m;

    do {
        printf("Enter the image matrices row size:\n");
        scanf("%d", &m);
    }while (m < 2);

    int n;

    do {
        printf("Enter the image matrices column size:\n");
        scanf("%d", &n);
    }while (n < 2);

    int k;

    do {
        printf("Enter the filter matrix size:\n");
        scanf("%d", &k);
    }while (k < 2);

    int **matrix = malloc(m * sizeof(int *)); //0 1 2 0 3 4 5 2 6 7 1 1 1 2 3 4
    int **fil = malloc(k * sizeof(int *));    //0 1 0 2 3 1 0 1 2
    int **result = malloc((m - k + 1) * sizeof(int *));

    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(n * sizeof(int));
    }

    for (int i = 0; i < k; i++) {
        fil[i] = malloc(k * sizeof(int));
    }

    for (int i = 0; i < n - k + 1; i++) {
        result[i] = malloc((n - k + 1) * sizeof(int));
    }

    printf("Enter the image matrices values with spaces between.\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
            if (matrix[i][j] < 0 || matrix[i][j] > 255) {
                printf("Gray pixel value can not be negative or bigger than 255. Try again.\n");
                j--;
            }
        }
    }

    printf("Enter the filter matrices values with spaces between.\n");
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            scanf("%d", &fil[i][j]);
        }
    }

    filter(matrix, m, n, fil, k, result);

    for (int i = 0; i < m - k + 1; i++) {
        for (int j = 0; j < n - k + 1; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }

    for (int i = 0; i < k; i++) {
        free(fil[i]);
    }

    for (int i = 0; i < n - k + 1; i++) {
        free(result[i]);
    }

    free(matrix);
    free(fil);
    free(result);

    return 0;
}

void filter(int **array, int m, int n, int **fil, int k, int **result) {
    int sum = 0;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            sum += fil[i][j];
        }
    }

    for (int i = 0; i < m - k + 1; i++) {
        for (int j = 0; j < n - k + 1; j++) {
            int temp = 0;

            for (int g = 0; g < k; g++) {
                for (int f = 0; f < k; f++) {
                    temp += array[g + i][f + j] * fil[g][f];
                }
            }

            result[i][j] = temp / sum;
        }
    }
}
