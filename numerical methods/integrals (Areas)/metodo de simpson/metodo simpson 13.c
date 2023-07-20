#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void simpson(double a, double b, int np);
double fx(double x);
int main ()
{
    double a,b,h,AT;
    int np;
    printf ("introduce el intervalo [a,b] de la funcion:\n");
    printf ("a= ");scanf ("%lf",&a);
    printf ("b= ");scanf("%lf",&b);
    printf("introduce el numero de particiones para el intervalo: ");
    scanf("%d",&np);
    // AREA
    simpson (a,b,np);
}
void simpson(double a, double b, int np)
{
    int i;
    double AT,h;
    AT=0;
    h=(b-a)/(2*np);
    for (i=0;i<=2*(np-1);i=i+2)
    {
        AT=AT+(fx(a+i*h)+4*fx(a+(i+1)*h)+fx(a+(i+2)*h));

    }
    AT=AT*(h/3);
    printf("\n AREA TOTAL= %lf \n",AT);
}
double fx(double x)
{
   return pow(x,2);
}
