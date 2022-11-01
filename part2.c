#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

double mat1[1000][1000], mat2[1000][1000], mat3[1000][1000];
int m=1000, n=1000, p=1000; /*matix dimensions mxn and nxp */


void matmul1(void)
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
}

void matmul2(void)
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
}



int main() {

    clock_t start, end;
    double cpu_time_used;

    FILE* file_1;
    FILE* file_2;
    FILE* file_3;

    file_1 = fopen("data1", "rb");
    file_2 = fopen("data2","rb");
    file_3 = fopen("data3","wb");

    fread(mat1, sizeof(double), sizeof(mat1)/sizeof(double), file_1);
    fread(mat2, sizeof(double), sizeof(mat1)/sizeof(double), file_2);

    start = clock();
    matmul1();
    matmul2();
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("%lf %lf %lf %lf\n", mat3[6][0], mat3[5][3], mat3[5][4], mat3[901][7]);
    printf("matmul1() & matmul2() took %f seconds to execute \n", cpu_time_used);


    fwrite(mat3,sizeof(double),sizeof(mat1)/sizeof(double),file_3);
    fclose(file_1);
    fclose(file_2);
    return 0;
}
