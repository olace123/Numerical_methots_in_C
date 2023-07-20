#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void trapecio (double a,double b, int np);
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
    trapecio(a,b,np);
}
void trapecio (double a,double b, int np)
{
    double h,AT;
    int i;
    AT=0;
    h=(b-a)/np;
    printf("%lf\n",h);
    for (i=0;i<np;i++)
    {
        AT=AT+(fx(a+i*h)+fx(a+(i+1)*h));
    }
    AT=AT*(h/2);
    printf("\n AREA TOTAL= %f \n",AT);

}
double fx(double x)
{
   return pow(x,2);
}






