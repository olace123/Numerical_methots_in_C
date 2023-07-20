#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NE 100//NE= numero de ecuaciones que soporta el programa
void gauss_jordan(float A[NE][NE+1],int n);
void piboteo (float A [NE][NE+1],int n,float *a,int i,int k);
void imprime (float A[NE][NE+1],int n);
int main (void)
{
    float A[NE][NE+1];//matriz del S.E.L
    int i,j,n;//i para las filas y j para las columnas
    printf("numero de ecuaciones: ");
    scanf("%d",&n);
    printf("introduce los datos de la matriz:\n\n");
    for (i=0;i<n;i++)
    {
        for (j=0;j<=n;j++)
        {
            printf("A[%d][%d]: ",i,j);
            scanf("%f",&A[i][j]);
        }
    }
    gauss_jordan(A,n);
    imprime(A,n);
    return 0;
}
void gauss_jordan(float A[NE][NE+1],int n)//n=numero de ecuaciones, A es la matriz previamente leida
{
    int i,j,k;
    float a,b,c;
    for (i=0;i<n;i++)
    {
        a=A[i][i]; //elemento por el que vamos a dividir para hacer 1s la diagonal principal
        for (k=i+1;k<n;k++)
        {
            if (fabs(A[k][i])>fabs(A[i][i])) piboteo(A,n,&a,i,k);
        }
        for (j=0;j<=n;j++)
        {
           A[i][j]= A[i][j]/a;// haciendo unos en la diagonal principal
        }
                 //a continuacion haremos 0s debajo de la diagonal principal
        for (k=i+1;k<n;k++) //recorrido de las filas bajo el elemento A[i][i]
        {
            b=A[k][i];// elemento que vamos a volver 0
            for (j=0;j<=n;j++)//recorrido de las columnas
            {
                A[k][j]= (-A[i][j]*b)+A[k][j];//haciendo ceros bajo la diagonal principal
            }

        }

    }
    for (i=n-1;i>=0;i--)
    {
        for (k=i-1;k>=0;k--)//recorrido de las filas sobre el elemento A[i][i]
        {
            c=A[k][i]; //elemento que vamos a volver 0
            for (j=n;j>=0;j--)
            {
                A[k][j]=A[k][j]+(-A[i][j]*c);//haciendo ceros sobre  la diagonal principal
            }
        }
    }

}
void piboteo (float A [NE][NE+1],int n,float *a,int i,int k)
{
    int j;
    float B[n+1];
    for (j=0;j<=n;j++)
    {
        B[j]=A[i][j];
    }
    for (j=0;j<=n;j++)
    {
      A[i][j]=A[k][j];
      A[k][j]=B[j];
    }
    *a=A[i][i];
}
void imprime (float A[NE][NE+1],int n)
{
    int i,j;
    printf("\n matriz solucion: \n\n");
    for (i=0;i<n;i++)
    {
        printf("\n");
        for (j=0;j<=n;j++)
        {
            printf("%f\t",A[i][j]);

        }
    }
    printf("\n\n");
    printf("soluciones\n");
    for (i=0;i<n;i++)
    {
        printf("S[%d]= %f\n",i,A[i][n]);
    }
     printf("\n");
}
