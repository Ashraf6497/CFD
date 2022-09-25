#include<stdio.h>
#include<conio.h>
int main()
{
	int i,j,m=21,n=41,p,q,r,s,count;
	float T1[m][n],T2[m][n],x,y;
	/*file opening*/
	FILE *tm;
	tm = fopen("time_marching.txt","w");
	/*initial condition*/
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
	/*storing into other variable*/
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
	/*to count number of iterations*/
	for(count=1;count<10000000;count++)
	{
		y=0;
	/*defining problem terms*/	
		for(i=1;i<m-1;i++)
		{
			p = i+1;
			q = i-1;
			for(j=1;j<n-1;j++)
			{
				r = j+1;
				s = j-1;
	/*using the formula of time marching*/			
				T1[i][j] = 0.25 * (T1[p][j] + T1[q][j] + T1[i][r] + T1[i][s]);
	/*error calculating*/			
				x = T1[i][j] - T2[i][j];
				if(x<0)
				{
					x = 0-x;
				}
				y = y+x;
				T2[i][j] = T1[i][j];
			}
		}
		if(y>0.01)
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
	/*writing in to the text file*/
	fprintf(tm,"i\t\tj\t\tT (Time Marching)\n");
	for(j=0;j<n;j++)
	{
		i = 10;
		fprintf(tm,"%d\t\t%d\t\t%f\n",i+1,j+1,T1[i][j]);
	}
	fprintf(tm,"number of iterations is %d",count);
	getch ();
	return 0;
}
