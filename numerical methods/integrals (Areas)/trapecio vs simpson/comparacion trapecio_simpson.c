#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double trapecio (double a,double b, int np,double *h);
double simpson(double a, double b, int np);
double f(double x);
int main ()
{
    FILE *d,*gnu;
    d=fopen("comparacion.txt","w");
    double a,b,h,AT,AS;
    int np,op;
    printf ("introduce el intervalo [a,b] de la funcion:\n");
    printf ("a= ");scanf ("%lf",&a);
    printf ("b= ");scanf("%lf",&b);
    fprintf(d,"f(x)=x*x\n");
 do{
    printf("introduce el numero de particiones para el intervalo: ");
    scanf("%d",&np);
    // AREA
    AT=trapecio(a,b,np,&h);
    AS=simpson(a,b,np);
    fprintf(d,"\t\th:\t%lf\tAtrapecio:\t%lf\tAsimpson:\t%lf\n",h,AT,AS);
    printf("\ndesea modificar el numero de particiones ? (SI=1,NO=0)");
    scanf("%d",&op);
   }
    while (op==1);
    fclose(d);
    gnu=popen("C:/gnuplot/bin/gnuplot.exe","w");
    fprintf(gnu,"plot [%f:%f][0:%f] x*x with boxes\n",a,b,(b-a)*(b-a));
    fprintf(gnu,"pause 10\n");
    fprintf(gnu,"load\"configuracion.gp\"\n");
    fprintf(gnu,"plot\"comparacion.txt\" using 2:4 w l,\"comparacion.txt\" using 2:6 w l \n");
    fprintf(gnu,"pause 10\n");
    pclose(gnu);
    return 0;
}
double trapecio (double a,double b, int np,double *h)
{
    double AT;
    int i;
    np=np*2;
    AT=0;
    *h=(b-a)/np;
    for (i=0;i<np;i++)
    {
        AT=AT+(f(a+i*(*h))+f(a+(i+1)*(*h)));
    }
    AT=AT*(*h/2);
    printf("AREA (TRAPECIO)=%lf\n ",AT);
     return AT;

}
double simpson(double a, double b, int np)
{
    int i;
    double AS,h;
    AS=0;
    h=(b-a)/(2*np);
    for (i=0;i<=2*(np-1);i=i+2)
    {
        AS=AS+(f(a+i*h)+4*f(a+(i+1)*h)+f(a+(i+2)*h));

    }
    AS=AS*(h/3);
    printf("AREA (SIMPSON)=%lf\n ",AS);
    return AS;
}
double f(double x)
{
   return pow(x,2);
}

