#include <stdio.h>
#include <stdlib.h>
#define NP 100
void lagrange (float X[NP],float Y[NP],int np);
int main ()
{
    float X[NP],Y[NP];
    int i,np;
    printf ("numero de puntos:\n");
    scanf("%d",&np);
    printf ("introduce los datos:\n");
    for (i=0;i<np;i++)
    {
        printf("X[%d] Y[%d]: ",i+1,i+1);
        scanf("%f %f",&X[i],&Y[i]);
    }
    lagrange (X,Y,np);
}
void lagrange (float X[NP],float Y[NP],int np)
{
    int i,j;
    float s,m,x;
    printf ("Valor de X para el que desea interpolar: ");
    scanf("%f",&x);
    s=0;
    for (i=0;i<np;i++)
    {
         m=1;
        for (j=0;j<np;j++)
        {
            if (i!=j) m=m*((x-X[j])/(X[i]-X[j]));
        }
         s=s+Y[i]*m;
    }
    printf("\nvalor de fx: %f\n",s);
}
