#include<stdio.h>
#include<conio.h>
int main()
{
	int i,j,m=21,n=41,p,q,r,s,count;
	float T1[m][n],T2[m][n],x,y;
	FILE *gs;
	gs = fopen("gauss_seidel.txt","w");
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			if(j==0)
			{
				T1[i][j] = 100;
			}
			else
			{
				T1[i][j] = 0;
			}
		}
	}
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			T2[i][j] = T1[i][j];
			printf("%f\t",T1[i][j]);	
		}
		printf("\n");
	}
	printf("\n\n");
	for(count=1;count<10000000;count++)
	{
		y=0;
		for(i=1;i<m-1;i++)
		{
			p = i+1;
			q = i-1;
			for(j=1;j<n-1;j++)
			{
				r = j+1;
				s = j-1;
				T1[i][j] = 0.25 * (T1[p][j] + T1[q][j] + T1[i][r] + T1[i][s]);
				x = T1[i][j] - T2[i][j];
				if(x<0)
				{
					x = 0-x;
				}
				y = y+x;
				T2[i][j] = T1[i][j];
			}
		}
		if(y>0.1)
		{
			continue;	
		}
		else
		{
			break;
		}	
	}
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%f\t",T1[i][j]);
		}
		printf("\n");
	}
	printf("\n\n number of iterations is %d \n\n\n",count);
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			fprintf(gs,"%d\t\t%d\t\t%f\n",i+1,j+1,T1[i][j]);
		}
	}
	getch ();
	return 0;
	}
