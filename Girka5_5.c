#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Программа сперва получает на вход N, после - число m такое, что N*m - длина стороны матрицы
//При одинаковых наборах данных время работы 1 нити - 0.429 с, N нитей - 0.133 с, N = 30

int *a;
int *b;
int *c;
int N, m;

void* MatMult (int* arg) {
    int i, j, k, tmp;
    for (i = 0; i < m; i++) {
        for (j = 0; j < N * m; j++) {
            tmp = 0;
            for (k = 0; k < N * m; k++) {
                tmp += a[k + (*arg * m + i) * N * m] * b[j + k * N * m];
            }
            c[j + (*arg * m + i) * N * m] = tmp;
       }
    }
}

void printC (int N, int m) {
    int i, j;
    for (i = 0; i < N * m; i++) {
        for (j = 0; j < N * m; j++) {
            printf("%d ", c[j + N*m*i]);
        }
        printf("\n");
    }
}

int main() {
    int i, sizeVector, result;
    pthread_t thid;
    scanf("%d %d", &N, &m);
    sizeVector = N*m*N*m;
    a = (int*) calloc(sizeVector, sizeof(int));
    b = (int*) calloc(sizeVector, sizeof(int));
    c = (int*) calloc(sizeVector, sizeof(int));
    for (i = 0; i <  sizeVector; i++) {
        a[i] = i;
        b[i] = i;
    }
    for (i = 0; i < N; i++) {
        result = pthread_create(&thid, (pthread_attr_t *)NULL, MatMult, &i);
        if (result != 0) {
                        printf ("Thread error\n");
                        exit(-1);
                }
    }
    pthread_join(thid, (void **)NULL);
    printC(N, m);
    free(a);
    free(b);
    free(c);
}
