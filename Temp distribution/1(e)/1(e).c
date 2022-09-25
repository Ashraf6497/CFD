#include<stdio.h>
#include<conio.h>
#include<math.h>
int main()
{
	int i,j,n;
	float x,y,pi=3.1428571,sum = 0,T[21][41];
	/*opening text file*/
	FILE *ana;
	ana = fopen("analytic_sol.txt","w");
	/*initial conditions*/
	for(i=0;i<21;i++)
	{
		for(j=0;j<41;j++)
		{
			if(j==0)
			{
				T[i][j] = 100;
			}
			else
			{
				T[i][j] = 0;
			}
		}
	}
	/*defining problem terms*/
	for(i=1;i<20;i++)
	{
		for(j=1;j<40;j++)
		{
			x = 0.05 * i;
			y = 0.05 * j;
			sum = 0;
			for(n=1;n<=110;n++)
			{
	/*applying formula*/			
				sum = sum + (((1-pow(-1,n))/(n*pi)) * ((sinh(n*pi*(2-y)))/(sinh(2*pi*n))) * (sin(n*pi*x)));
			}
			T[i][j] = 100 * 2 * sum;
		}
	}
	printf("\n\n");
	/*writing in the output text file*/
	fprintf(ana,"i\t\tj\t\tT (analytical)\n");
	for(j=0;j<41;j++)
	{
		i=10;
		fprintf(ana,"%d\t\t%d\t\t%f\n",i+1,j+1,T[i][j]);
	}
	getch();
	return 0;
}
