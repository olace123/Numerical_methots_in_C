#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define NE 100
#define NP 1000

void GaussJordan(float a[NE][NE+1],int n);
void piboteo (float a [NE][NE+1],int n,float *A,int i,int k);
void Imprime(float a[NE][NE+1],int n);
void ForMat(float a[NE][NE+1],float xi[NP],float yi[NP],int np, int n);

void FormaPol(float A[NP],char p[NP],int g);

int main(void)
{
	FILE *pun, *pgnu;

	int np,g,r,i;
	float xi[NP],yi[NP],A[NE],a[NE][NE+1],x,fx;
	char p[1000];

	pun=fopen("Puntos.txt","w");
	pgnu=popen("C:/gnuplot/bin/gnuplot.exe","w");

	printf("Numero de puntos= ");
	scanf("%d",&np);

	for(i=0;i<np;i++)
	{
		printf("(X%d,Y%d)= ",i+1,i+1);
		scanf("%f %f",&xi[i],&yi[i]);
		fprintf(pun,"%f\t%f\n",xi[i],yi[i]);
	}

	printf("Grado del polinomio= ");
	scanf("%d",&g);
	printf("\n\n");

    ForMat(a,xi,yi,np,g);
    printf("sistema de ecuaciones a resolver:\n");
	Imprime(a,g);
	GaussJordan(a,g);
	printf("sistema resuelto\n");
	Imprime(a,g);

	for(i=0;i<=g;i++)
	{
		A[i]=a[i][g+1];
	}

	FormaPol(A,p,g);


	printf("\n\nPolinomio:\n");
	printf("%s",p);

	fclose(pun);
	fprintf(pgnu,"load \"configuracion.gp\" \n");
    fprintf(pgnu,"plot %s,\"Puntos.txt\" using  1:2 w p \n",p);
    fprintf(pgnu,"pause 60\n");
    pclose(pgnu);

    printf("\n\nQuiere interpolar (1=si/0=No): ");
    scanf("%d",&r);
    if(r==1)
    {
    	printf("Dame el valor de x= ");
    	scanf("%f",&x);
    	fx=0;
    	for(i=0;i<=g;i++)
    	{
    		fx= fx + A[i]*pow(x,i);
    	}
    	printf("El valor de la interpolacion es= %5.4f",fx);
    }
	return 0;
}

void GaussJordan(float a[NE][NE+1],int n)
{
	int i,j,k;
	float A,B;

	for(i=0;i<=n;i++)
	{
		A=a[i][i];
		for (k=i+1;k<=n;k++)
        {
            if (fabs(a[k][i])>fabs(a[i][i])) piboteo(a,n,&A,i,k);
        }
		for(j=0;j<=n+1;j++)
		{
			a[i][j]=a[i][j]/A;
		}
		for(k=i+1;k<=n;k++)
		{
			B=a[k][i];
			for(j=0;j<=n+1;j++)
			{
				a[k][j]=a[k][j]-a[i][j]*B;
			}
		}
		for(k=i-1;k>=0;k--)
		{
			B=a[k][i];
			for(j=0;j<=n+1;j++)
			{
				a[k][j]=a[k][j]-a[i][j]*B;
			}
		}
	}
}
void piboteo (float a [NE][NE+1],int n,float *A,int i,int k)
{
    int j;
    float B[n+1];
    for (j=0;j<=n+1;j++)
    {
        B[j]=a[i][j];
    }
    for (j=0;j<=n+1;j++)
    {
      a[i][j]=a[k][j];
      a[k][j]=B[j];
    }
    *A=a[i][i];
}
void Imprime(float a[NE][NE+1],int n)
{
	int i,j;

	for(i=0;i<=n;i++)
	{
		for(j=0;j<=n+1;j++)
		{
			printf("%5.4f\t",a[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void ForMat(float a[NE][NE+1],float xi[NP],float yi[NP],int np, int n)
{
    int i,j,k;
    float s;

    for(i=0;i<=n;i++)
	{
		for(j=0;j<=n+1;j++)
		{
			s=0;
			if(j!=n+1)
			{
				for(k=0;k<np;k++)
				{
					s= s + pow(xi[k],i+j);
					a[i][j]= s;
				}
			}
			else
			{
				s=0;
				for(k=0;k<np;k++)
				{
					s= s + yi[k]*pow(xi[k],i);
					a[i][j]= s;
				}
			}
		}
	}
}

void FormaPol(float A[NE],char p[NP],int g)
{
	int i;
	char a[NP];
	for(i=0;i<=g;i++)
	{
		sprintf(a,"%5.4f*(x**%d)",A[i],i);
		strcat(p,a);
		if(i<g)
		{
			if(A[i+1]>=0)
			{
				strcat(p,"+");
			}
		}
	}
}
