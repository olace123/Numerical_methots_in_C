#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NP 10000
float Euler(float h,float f_xi,float xi);
float Trapecio(float h,float f_xi,float xi,float xim1);
float fp(float x);
int main(void)
{
    float h,xi,f_xi,xf,x[NP],ft[NP],fe[NP];
    int i,np;
    FILE *puntos,*pgnu;
    printf("xi= ");scanf("%f",&xi);// x inicial
    printf("f_xi= ");scanf("%f",&f_xi);//f(x) inicial
    printf("xf= ");scanf("%f",&xf);// valor de la fucion que se desea obtener
    printf("np= ");scanf("%d",&np);//numero de particiones de xi a xf
    h=(xf-xi)/np;//distancia entre las particiones (entre mas se aproxime a 0 mejor)
    // condiciones inciales
    x[0]=xi;
    fe[0]=f_xi;
    ft[0]=f_xi;
        for (i=1;i<np;i++)
    {
        x[i]=x[i-1]+h;
        fe[i]=Euler(h,fe[i-1],x[i-1]);
        ft[i]=Trapecio(h,ft[i-1],x[i-1],x[i]);
    }
    puntos=fopen("puntos.txt","w");
    fprintf(puntos,"\nx\t\tf(e)\t\tf(t)");
    for (i=0;i<np;i++)
    {
       fprintf(puntos,"\n%f\t%f\t%f",x[i],fe[i],ft[i]);
    }
    fclose(puntos);
    pgnu=popen("C:/gnuplot/bin/gnuplot.exe","w");
    fprintf(pgnu,"plot \"puntos.txt\" usin 1:2 w l,\"puntos.txt\" usin 1:3 w l\n");
    fprintf(pgnu,"pause 15\n");
    pclose(pgnu);
    return 0;
}
float Euler(float h,float f_xi,float xi)
{
    return f_xi+h*fp(xi);
}
float Trapecio(float h,float f_xi,float xi,float xim1)
{
    return f_xi+h*0.5*(fp(xi)+fp(xim1));
}
float fp(float x)
{
    return 3*x+1;
}
