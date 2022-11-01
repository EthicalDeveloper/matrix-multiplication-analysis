#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

double mat1[1000][1000], mat2[1000][1000], mat3[1000][1000];
int m=1000, n=1000, p=1000; /*matix dimensions mxn and nxp */


void* matmul1(void * arg)
{
    int i,j,k,l;
    double sum=0;
    int s =0, e = 500;
    for (i = s; i < e; i++) {
        for (j = 0; j < p; j++) {
            for (k = 0; k < n; k++) {
                sum = sum + mat1[i][k]*mat2[k][j];
            }
            mat3[i][j] = sum;
            sum = 0;
        }
    }
    pthread_exit(NULL);
}


void* matmul2(void * arg)
{
    int i,j,k,l;
    double sum=0;
    int s = 500, e = 1000;
    for (i = s; i < e; i++) {
        for (j = 0; j < p; j++) {
            for (k = 0; k < n; k++) {
                sum = sum + mat1[i][k]*mat2[k][j];
            }
            mat3[i][j] = sum;
            sum = 0;
        }
    }
    pthread_exit(NULL);
}




int main() {

    clock_t start, end;
    double cpu_time_used;
    pthread_t tid1;
    pthread_t tid2;

    pthread_create(&tid1, NULL, matmul1, NULL);
    pthread_create(&tid2, NULL, matmul2, NULL);


    FILE* file_1;
    FILE* file_2;
    FILE* file_3;

    file_1 = fopen("data1", "rb");
    file_2 = fopen("data2","rb");
    file_3 = fopen("data3","wb");

    fread(mat1, sizeof(double), sizeof(mat1)/sizeof(double), file_1);
    fread(mat2, sizeof(double), sizeof(mat1)/sizeof(double), file_2);

    start = clock();
    pthread_create(&tid1, NULL, matmul1, NULL);
    pthread_create(&tid2, NULL, matmul2, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("%lf %lf %lf %lf\n", mat3[6][0], mat3[5][3], mat3[5][4], mat3[901][7]);
    printf("matmul1() & matmul2() took %f seconds to execute \n", cpu_time_used);


    fwrite(mat3,sizeof(double),sizeof(mat1)/sizeof(double),file_3);
    fclose(file_1);
    fclose(file_2);
    return 0;
}
