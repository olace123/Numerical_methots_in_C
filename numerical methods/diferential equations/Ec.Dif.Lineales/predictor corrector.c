#include <stdio.h>
#include <stdlib.h>
#define NP 10000
float Euler(float h,float f_xi,float xi);
float fp(float x,float f_xi);
float Trapecio(float h,float f_xi,float xi,float fxim1,float xim1);
int main(void)
{
    float h,xi,xf,x[NP],f[NP],f_xi;
    int i,np;
    FILE *puntos,*pgnu;
    printf("xi= ");scanf("%f",&xi);// x inicial
    printf("f_xi= ");scanf("%f",&f_xi);//f(x) inicial
    printf("xf= ");scanf("%f",&xf);// valor de la fucion que se desea obtener
    printf("np= ");scanf("%d",&np);//numero de particiones de xi a xf
    h=(xf-xi)/np;//distancia entre las particiones (entre mas se aproxime a 0 mejor)
    // condiciones inciales
    x[0]=xi;
    f[0]=f_xi;
    for (i=1;i<np;i++)
    {
        x[i]=x[i-1]+h;
        f[i]=Euler(h,f[i-1],x[i-1]);
        f[i]=Trapecio(h,f[i-1],x[i-1],f[i],x[i]);
    }
    puntos=fopen("puntos.txt","w");
    fprintf(puntos,"\nx\t\tf(x)\t\tfprima(x)");
    for (i=0;i<np;i++)
    {
       fprintf(puntos,"\n%f\t%f\t%f",x[i],f[i],fp(x[i],f[i]));
    }
    fclose(puntos);
    pgnu=popen("C:/gnuplot/bin/gnuplot.exe","w");
    fprintf(pgnu,"plot \"puntos.txt\" usin 1:2 w l\n");
    fprintf(pgnu,"pause 15\n");
    pclose(pgnu);

    return 0;
}

float Euler(float h,float f_xi,float xi)
{
    return f_xi+h*fp(xi,f_xi);
}
float fp(float x,float f_xi)
{
    return 3*x+f_xi;
}
float Trapecio(float h,float f_xi,float xi,float fxim1,float xim1)
{
    return f_xi+h*0.5*(fp(xi,f_xi)+fp(xim1,fxim1));
}
