#include <stdio.h>
#include <stdlib.h>
#define NE 100//NE= numero de ecuaciones que soporta el programa
void gauss(float A[NE][NE+1],int n);
void imprime (float A[NE][NE+1],int n);
void sustinversa(float A[NE][NE+1],int n);
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
    gauss(A,n);
    imprime(A,n);
    sustinversa(A,n);
    return 0;
}
void gauss(float A[NE][NE+1],int n)//n=numero de ecuaciones, A es la matriz previamente leida
{
    int i,j,k;
    float a,b;
    for (i=0;i<n;i++)
    {
        a=A[i][i]; //elemento por el que vamos a dividir para hacer 1 la diagonal principal
        for (j=0;j<=n;j++)
        {
           A[i][j]= A[i][j]/a;// haciendo unos en la diagonal principal
        }
                 //a continuacion haremos 0s debajo de la diagonal principal
        for (k=i+1;k<n;k++) //recorrido de las filas
        {
            b=A[k][i];// elemento que vamos a volver 0
            for (j=0;j<=n;j++)//recorrido de las columnas
            {
                A[k][j]= (-A[i][j]*b)+A[k][j];//haciendo ceros bajo la diagonal principal
            }

        }
    }

}
void imprime (float A[NE][NE+1],int n)
{
    int i,j;
    printf("\n matriz escalonada: \n\n");
    fflush(stdin);
    for (i=0;i<n;i++)
    {
        printf("\n");
        for (j=0;j<=n;j++)
        {
            printf("%f\t",A[i][j]);

        }
    }
}
void sustinversa(float A[NE][NE+1],int n)// n es el numero de ecuaciones
{
    int i,j;
    A[n-1][n-1]=A[n-1][n];//esta es el valor de la ultima variable
    for (i=n-2;i>=0;i--)
    {
        A[i][i]=A[i][n];//igualamos la variable al termino independiente y a continuacion terminamos de despejar
        for (j=n-1;j>i;j--)
        {
           A[i][i]=A[i][i]+(-A[i][j]*A[j][j]);//A[j][j] = valor de la varible anterior (ya encontrada)
        }
    }

    printf("\n\n soluciones:\n\n");// las soluciones quedaran guardadas en la diagonal principal
    for (i=0;i<n;i++)
    {
        printf("A[%d][%d]=%f\n",i,i,A[i][i]);
    }


}





