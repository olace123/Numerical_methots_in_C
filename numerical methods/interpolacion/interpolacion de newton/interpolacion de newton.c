#include <stdio.h>
#include <string.h>
#define NP 100
void Bs(int np, float x[NP], float y[NP]);
void formpol(char p[800],float x[NP],float y[NP],int np);
void interpolar(float x[NP],float y[NP],int np);

int main(void)
{
	int i, j, I,np;
	float x[NP], y[NP];
	char p[800]="\0";
	FILE *pgnu, *pun;
	pun=fopen("Puntos.txt","w");
	pgnu=popen("C:/gnuplot/bin/gnuplot.exe","w");

	printf("np= ");
	scanf("%d",&np);

	for(i=0;i<np;i++)
	{
		printf("x[%d]=",i);
		scanf("%f",&x[i]);
		printf("y[%d]=",i);
		scanf("%f",&y[i]);
		fprintf(pun,"%f\t%f\n",x[i],y[i]);
	}

	fclose(pun);

	Bs(np,x,y);
	formpol(p,x,y,np);
	printf("\np(x)=%s\n\n",p);

    fprintf(pgnu,"plot %s,\"Puntos.txt\" using  1:2 w p \n",p);
    fprintf(pgnu,"pause 15\n");
    pclose(pgnu);

	interpolar(x,y,np);
	return 0;
}
void Bs(int np, float x[NP], float y[NP])
{
	int i,j;
	for(j=1;j<np;j++)
	{
		for(i=np-1;i>=j;i--)
		{
			y[i]=(y[i]-y[i-1])/(x[i]-x[i-j]);
		}
	}
}

void formpol(char p[800], float x[NP],float y[NP],int np)
{
	int i,j;
	char cd[800]="\0";

	sprintf(cd,"%f",y[0]);
	strcat(p,cd);

	for(i=1;i<np;i++)
	{
		if(y[i]<0)
		{
            sprintf (cd,"%f", y[i]);
            strcat (p,cd);
            for (j=1;j<=i;j++)
            {
                if(x[j-1]<0)
                {
                    sprintf (cd,"%f",-x[j-1]);
                    strcat(p,"*(x+");
                    strcat(p, cd);
                    strcat(p, ")");
                }
                else
                {
                    sprintf (cd,"%f",x[j-1]);
                    strcat(p,"*(x-");
                    strcat(p, cd);
                    strcat(p, ")");
                }
            }
		}
		else
		{
            sprintf (cd,"+%f", y[i]);
            strcat (p,cd);
            for (j=1;j<=i;j++)
            {
                if(x[j-1]<0)
                {
                    sprintf (cd,"%f",-x[j-1]);
                    strcat(p,"*(x+");
                    strcat(p, cd);
                    strcat(p, ")");
                }
                else
                {
                    sprintf (cd,"%f",x[j-1]);
                    strcat(p,"*(x-");
                    strcat(p, cd);
                    strcat(p, ")");
                }
            }
		}
    }
}
void interpolar(float x[NP],float y[NP],int np)
{
	int I,i,j;
	float s,m,X;
	printf("Quiere interpolar? (SI=1,NO=0) ");
	scanf("%d",&I);
	if(I==1)
	{
		printf("\nX: ");
		scanf("%f",&X);
		s=y[0];
		for(i=1;i<np;i++)
		{
			m=y[i];
			for(j=0;j<i;j++)
			{
				m=m*(X-x[j]);
			}
			s=s+m;
		}
	printf("\nP(%f)=%0.3f",X,s);
	printf("\n\n");
	}
}
