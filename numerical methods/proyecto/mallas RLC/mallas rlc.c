#include <stdio.h>
#include <stdlib.h>
typedef struct Matrices{
    int f;
    int c;
    double **a;
    int e;
} mat;

mat Crea_Matriz(int Filas,int Columnas);
mat Suma_Mat(mat A,mat B);
mat Multiplica_Mat(mat A,mat B);

int main()
{
    int np,i;
    float ti,tf,h;//INTERVALO DE TIEMPO EN EL QUE SE GRAFICARÁ LA FUNCIÓN [TI,TF]
    FILE *puntos,*pgnu;
    puntos=fopen("puntos.txt","w");
    printf("ti= ");
    scanf("%f",&ti);
    printf("tf= ");
    scanf("%f",&tf);
    printf("np= ");//NUMERO DE PARTICIONES DEL INTERVALO
    scanf("%d",&np);
    h=(tf-ti)/np;//h  ES EL INCREMENTO EN X
    //..... A continuacion se crean las matrices
    mat X[np],XP[np],A,B,M;
    A=Crea_Matriz(2,2);
    B=Crea_Matriz(2,1);
    for (i=0;i<np;i++);
    {
       X[i]=Crea_Matriz(2,1);
       XP[i]=Crea_Matriz(2,1);
    }
    //MATRICES A Y B DEL MODELO
    double  K1=0.08,R=0.7,L=0.5,J=0.5,D=0.005,Va=100,Tc=0.8;
    A.a[0][0]=-R/L;
    A.a[0][1]=-K1/J;
    A.a[1][0]=K1/J;
    A.a[1][1]=-D/J;
    B.a[0][0]=Va/L;
    B.a[1][0]=-Tc/J;

    //.......CI
    X[0].a[0][0]=0;
    X[0].a[1][0]=0;
    fflush(stdout);
    M=Multiplica_Mat(A,X[0]);
    XP[0]=Suma_Mat(M,B);
    //....
    fprintf(puntos,"\n t \t\t i(t) \t\t w(t) \t\t ip(t) \t\t wp(t)");
    fprintf(puntos,"\n %f \t %f \t %f \t %f \t %f",ti,X[0].a[0][0],X[0].a[1][0],XP[0].a[0][0],XP[0].a[1][0]);
    fclose(puntos);

}
/*+------------------------------------------------------+
  |      FUNCION QUE CREA UNA MATRIZ DINAMICA            |
  +------------------------------------------------------+*/
mat Crea_Matriz(int Filas,int Columnas)
{
    mat matriz;
    int i;

    matriz.a = (double **)malloc (Filas*sizeof(double *));

    for(i=0;i<Filas;i++)
	{
		matriz.a[i] = (double *) malloc (Columnas*sizeof(double));
	}

	if (matriz.a == NULL)
	{
		matriz.e=-1;
        return matriz;
	}
	else
        matriz.e = 0;

	matriz.f=Filas;
	matriz.c=Columnas;

	return matriz;
}
/*+------------------------------------------------------+
  |      FUNCION QUE SUMA DOS MATRICES                   |
  +------------------------------------------------------+*/
mat Suma_Mat(mat A,mat B)
{
    mat S;
    int i,j;

    S=Crea_Matriz(A.f,A.c);

    if(A.f!=B.f || A.c!=B.c)
    {
		S.e=-1;
        return S;
    }

    for(i=0;i<A.f;i++)
    {
        for(j=0;j<A.c;j++)
        {
            S.a[i][j]=A.a[i][j]+B.a[i][j];
        }
    }

    return S;
}

/*+------------------------------------------------------+
  |      FUNCION QUE MULTIPLICA DOS MATRICES             |
  +------------------------------------------------------+*/
mat Multiplica_Mat(mat A,mat B)
{
    mat M;
    int i,j,k;

    M=Crea_Matriz(A.f,B.c);

    if(A.c!=B.f)
    {
		M.e=-1;
        return M;
    }

    for(i=0;i<A.f;i++){
        for(j=0;j<B.c;j++){
            M.a[i][j]=0.0;
            for(k=0;k<A.c;k++){
                    M.a[i][j]=M.a[i][j]+A.a[i][k]*B.a[k][j];
            }
        }
    }

    return M;
}
