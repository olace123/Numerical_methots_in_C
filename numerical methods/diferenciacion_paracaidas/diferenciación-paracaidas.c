#include <stdio.h>
int main ()
{
  float dt,v[200],m,g=9.8,c;
  int i;
  v[0]=0;
  printf("masa del objeto:");scanf("%f",&m);
  printf("coeficiente de friccion:");scanf("%f",&c);
  printf("diferencial del tiempo:");scanf("%f",&dt);

  FILE *velocidad;
  velocidad=fopen("velocidad.txt","w");
 // fprintf(velocidad,"segundos  velocidad\n\n");
  for (i=1;i<200;i++)
  {
      v[i]=((m*g-c*v[i-1])*dt/m)+v[i-1];
      fprintf(velocidad,"%f\t %f\n",i*dt,v[i]);
  }
  fclose(velocidad);

  FILE *pgnu;
  pgnu=popen("C:/gnuplot/bin/gnuplot.exe","w");
   fprintf(pgnu,"plot \"velocidad.txt\" using 1:2 w l \n");
  fprintf(pgnu,"pause 10 \n");
  pclose(pgnu);

}
