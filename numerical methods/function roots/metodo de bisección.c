#include <stdio.h>
#include <math.h>
float f(float x);
void Escribir(FILE *funcion1,float xr,float ii,float dd);

int main ()
{
    FILE *pgnu,*funcion1,*Error;
    funcion1=fopen("funcion1.txt","w");
    float a,b,error,xr[1000],er;
    xr[0]=0;
    int c,C=0;
    printf("introduzca el limite inferior del intervalo: ");
    scanf("%f",&a);
    printf("introduzca el limite superior del intervalo: ");
    scanf("%f",&b);
    printf("introduzca el error: ");
    scanf("%f",&error);
    printf("introduzca el numero de veces a repetir la operación: ");
    scanf("%f",&c);
    do
    {
        C=C+1;
        xr[C]=(a+b)/2.0;
        er=fabs(xr[C]-xr[C-1])/2.0;
        if( (f(a)*f(xr[C]))<0) b=xr[C];
        else a=xr[C];
    }

      while (C<c&&er>error);
      printf("La raiz es:%f\n",xr[C]);
      if(f(xr[C])>0.5||f(xr[C])<-0.5) {printf("error, alguna condicion para el metodo no se cumple");}
      Escribir(funcion1,xr[C],xr[C]-10,xr[C]+10);
      pgnu=popen("C:/gnuplot/bin/gnuplot.exe","w");
      fprintf(pgnu,"plot \"funcion1.txt\" using 1:2 w l \n");
        fprintf(pgnu,"pause 10\n");
      pclose(pgnu);
      return 0;
}

 float f(float x)
 {
     float y;
     y=2*x+12;
     return y;
 }
 void Escribir(FILE *funcion1,float xr,float ii,float dd)
 {
     int np=100,i;//np=numero de particiones, dp=distancia de la particion
     float dp;
     dp=fabs((dd-ii)/np);
     fprintf(funcion1,"xr\t fx\n");
     for (i=0;i<np;i++)
     {
         fprintf(funcion1,"%f\t %f\n",ii+i*dp,f(ii+i*dp));
     }

    fclose(funcion1);

 }


