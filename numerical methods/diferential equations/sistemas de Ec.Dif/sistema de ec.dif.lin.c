#include <stdio.h>
#include <stdlib.h>

typedef struct Matrices{
    int f;
    int c;
    double **a;
    int e;
} mat;

mat Crea_Matriz(int Filas,int Columnas);
void Libera_Matriz(mat Matriz);
void Lee_Mat(mat A,char n[10]);
void Imprime_Mat(mat A);
mat Suma_Mat(mat A,mat B);
mat Resta_Mat(mat A,mat B);
mat Multiplica_Mat(mat A,mat B);
//
 float fbiprima(float fp, float fx);
 float Euler(float f,float h,float fp);
 float Trapecio(float f, float h,float fp,float fpm1);
//

int main()
{
    double ti=0.0,tf=200.0,h,h1;
    mat A,B,X[2],XE[2],XP[2],M,H,H1;

    double  R1=2,L1=4,R=15,L=10,c=0.9;
    float I2pp[2000],I2p[2000],I2[2000],I1pp[2000],I1p[2000],I1[2000],I3pp[2000],I3p[2000],I3[2000];

    I2pp[0]=0;



    A=Crea_Matriz(2,2);
    B=Crea_Matriz(2,1);
    M=Crea_Matriz(2,1);
    X[0]=Crea_Matriz(2,1);
    XP[0]=Crea_Matriz(2,1);
    H=Crea_Matriz(1,1);
    H1=Crea_Matriz(1,1);

    // Matrices A y B del Modelo
    A.a[0][0]=R/L1;
    A.a[0][1]=-R/L1;
    A.a[1][0]=-R/L;
    A.a[1][1]=R/L;

    B.a[0][0]=0;
    B.a[1][0]=I2pp[0];

    // C.I.
    X[0].a[0][0]=10;
    X[0].a[1][0]=0;

    M = Multiplica_Mat(A,X[0]);
    XP[0] = Suma_Mat(M,B);

    h=(tf-ti)/2000.0;
    h1=h/2.0;
    H.a[0][0]=h;
    H1.a[0][0]=h1;

    //
  I1[0]=0;
  I3[0]=0;
  I2[0]=0;

  I1p[0]= X[0].a[0][0];
  I3p[0]= X[0].a[1][0];
  I2p[0]=3;

  I1pp[0]= XP[0].a[0][0];
  I3pp[0]= XP[0].a[1][0];

    //
    ti=h;
    int i=1;
    while(ti<=tf)
    {
        M = Multiplica_Mat(XP[0],H);
        XE[0]=Suma_Mat(M,X[0]);

		M=Multiplica_Mat(A,XE[0]);
		X[1]=Suma_Mat(M,B);
		X[1]=Suma_Mat(X[1],XP[0]);
		X[1]=Multiplica_Mat(X[1],H1);
		X[1]=Suma_Mat(X[0],X[1]);

		X[0].a[0][0]= X[1].a[0][0];
		X[0].a[1][0]= X[1].a[1][0];/////..sol

		//
        I1p[i]=X[0].a[0][0];
		I3p[i]=X[0].a[1][0];
		//

		XP[1]=Multiplica_Mat(A,X[1]);
		XP[1]=Suma_Mat(XP[1],B);

        XP[0].a[0][0]= XP[1].a[0][0];
		XP[0].a[1][0]= XP[1].a[1][0];  // sol

		//
        I1pp[i]=X[0].a[0][0];
		I3pp[i]=X[0].a[1][0];
		//


        ti=ti+h;
       /////////////

         //predictor
         I2p[i]=Euler(I2p[i-1],h,fbiprima(I2p[i-1],I2[i-1])+I1pp[i-1]);
         I2[i]=Euler(I2[i-1],h,I2p[i-1]);
         //corrector
         I2p[i]=Trapecio(I2p[i-1],h,fbiprima(I2p[i-1],I2[i-1])+I1pp[i-1],fbiprima(I2p[i],I2[i])+I1pp[i]);
         I2[i]=Trapecio(I2[i-1],h,I2p[i-1],I2p[i]);
         I2pp[i]=fbiprima(I2p[i],I2[i])+I1pp[i];
         B.a[1][0]=I2pp[i];
         i++;

    }


    Libera_Matriz(A);
    Libera_Matriz(B);
    Libera_Matriz(M);
    Libera_Matriz(XP[0]);
    Libera_Matriz(X[0]);
    Libera_Matriz(X[1]);
    Libera_Matriz(H);

    return 0;
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
  |      FUNCION QUE LIBERA LOS  ESPACIOS  DE            |
  |      MEMORIA DE UNA MATRIZ                           |
  +------------------------------------------------------+*/
void Libera_Matriz(mat Matriz)
{
    int i;

    for(i=0; i<Matriz.f; i++) {
        free(Matriz.a[i]);
    }

    free(Matriz.a);

    Matriz.a= NULL;
}
/*+------------------------------------------------------+
  |      FUNCION QUE LEE LOS VALORES DE UNA MATRIZ       |
  +------------------------------------------------------+*/
void Lee_Mat(mat A,char n[10])
{
    int i,j;

    for(i=0;i<A.f;i++)
    {
        for(j=0;j<A.c;j++)
        {
            printf("%s[%d][%d]= ",n,i,j);
            scanf("%lf",&A.a[i][j]);
        }
        printf("\n");
    }
}
/*+------------------------------------------------------+
  |      FUNCION QUE IMPRIME LOS VALORES DE UNA MATRIZ       |
  +------------------------------------------------------+*/
void Imprime_Mat(mat A)
{
    int i,j;

    printf("_\n\n");
    for(i=0;i<A.f;i++)
    {
        for(j=0;j<A.c;j++)
        {
            printf("%5.2lf\t",A.a[i][j]);
        }
        printf("\n");
    }
    printf("_\n\n");
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
  |      FUNCION QUE RESTA DOS MATRICES                  |
  +------------------------------------------------------+*/
mat Resta_Mat(mat A,mat B)
{
    mat R;
    int i,j;

    R=Crea_Matriz(A.f,A.c);

    if(A.f!=B.f || A.c!=B.c)
    {
		R.e=-1;
        return R;
    }

    for(i=0;i<A.f;i++)
    {
        for(j=0;j<A.c;j++)
        {
            R.a[i][j]=A.a[i][j]-B.a[i][j];
        }
    }

    return R;
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

///////////
 float fbiprima(float fp, float fx)
{
    return -(0.2*fp)-(0.1111*fx);
}

 float Euler(float f,float h,float fp)
 {
     return f+(h*fp);
 }
 float Trapecio(float f, float h,float fp,float fpm1)
 {
    return f+(h*0.5*(fp+fpm1));
 }





