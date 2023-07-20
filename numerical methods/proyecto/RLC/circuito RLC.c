 #include <stdio.h>
 #include <stdlib.h>
 #define NP 10000
  float fbiprima(float fp, float fx);
  float Euler(float f,float h,float fp);
  float Trapecio(float f, float h,float fp,float fpm1);
 int main()
 {
     float xi,f_xi,xf,h,x[NP],fx[NP],fp[NP];
     int i,np;
     FILE *puntos,*pgnu;
     printf("xi= ");
     scanf("%f",&xi);
     printf("f_xi= ");
     scanf("%f",&f_xi);
     printf("xf= ");
     scanf("%f",&xf);
     printf("fp_xi= ");
     scanf("%f",&fp[0]);
     printf("numero de particiones= ");
     scanf("%d",&np);
     h=(xf-xi)/np;
     x[0]=xi;
     fx[0]=f_xi;
     for(i=1;i<np;i++)
     {
         x[i]=x[i-1]+h;
         //predictor
         fp[i]=Euler(fp[i-1],h,fbiprima(fp[i-1],fx[i-1]));
         fx[i]=Euler(fx[i-1],h,fp[i-1]);
         //corrector
         fp[i]=Trapecio(fp[i-1],h,fbiprima(fp[i-1],fx[i-1]),fbiprima(fp[i],fx[i]));
         fx[i]=Trapecio(fx[i-1],h,fp[i-1],fp[i]);
     }
     puntos=fopen("puntos.txt","w");
     fprintf(puntos,"\nt\t\tI\t\tfp");
     for (i=0;i<np;i++)
     {
         fprintf(puntos,"\n%f\t%f\t%f",x[i],fx[i],fp[i]);
     }
     fclose(puntos);
     pgnu=popen("C:/gnuplot/bin/gnuplot.exe","w");
     fprintf(pgnu,"plot \"puntos.txt\" using 1:2 w l\n");
     fprintf(pgnu,"pause 15\n");
     pclose(pgnu);

 }

 float fbiprima(float fp, float fx)
{
    return -(0.5*fp)-(5*fx);
}

 float Euler(float f,float h,float fp)
 {
     return f+(h*fp);
 }
 float Trapecio(float f, float h,float fp,float fpm1)
 {
    return f+(h*0.5*(fp+fpm1));
 }











