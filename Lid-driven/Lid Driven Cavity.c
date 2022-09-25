#include <stdio.h>				/*Re = 400; Beta = 1 and velocity of lid =1*/
#include <math.h>				/*above terms are considered and simplified formula was written in the code*/
#include <stdlib.h>
int main()
{
	int i,j,c,m=129,n=129; /*c=count;m and n are number of grid points*/					
	double x[m],y[n],es=0,er=1,dx,dy,l=128,xi1[m][n],xi2[m][n],w1[m][n],w2[m][n],tol,sumn=0,sumd=0,u[65][j],v[i][65];
	dx= 1/l;								/*x[m]andy[n] to get grid points*/			
	dy=dx;									/*es - error sum; er - error; dx,dy-length of one grid*/
	tol= 1/pow(10,5);						/*xi - stream finction; w - vorticity function*/
	printf("%lf\t%lf\t%lf\t %lf\t",es,er,dx,dy);/*tol - to limit error; u,v- centre live velocities*/
	for(i=1;i<=m;i++)		/*intial guess*/
	{
		for(j=1;j<=n;j++)
		{
			xi1[i][j] = 0; 			/*stream function is zero every where*/
			if(i==1 || i==m)		/*voritcity conditions */
			{
				w1[i][j] = 0;
			}
			else
			{
				if(j==n)
				{
					w1[i][j] = -2/dy;
				}
				else
				{
					w1[i][j] = 0;					
				}
			}
		}
	}
	for(i=1;i<=m;i++) /*storing values on xi1 and w1 into xi2 and w2*/
	{
		for(j=1;j<=n;j++)
		{
			xi2[i][j] = xi1[i][j];
			w2[i][j] = w1[i][j];
		}
	}
	while (er > tol)	/*for updating values of xi and w using iteration*/
	{
 		for(c=1;c<=10;c++)		/*iterations of */
 		{
		
 			for (i = 2; i < m; i++)
 			{
 				for (j = 2; j < n; j++)		/*using simplified xi formula*/
 				{
 					xi2[i][j] =0.25*(xi2[i+1][j]+xi2[i-1][j]+xi2[i][j+1]+xi2[i][j-1]+(dx*dx*w1[i][j]));
 				}
 			}
 		}
 		for (j = 2; j < n; j++) /*updating boundary condition of vorticity function at top lid and bottom wall*/
 		{
 			w1[1][j] = (-2 * xi2[2][j]) / (dx * dx);
 			w2[1][j] = w1[1][j];
 			w1[129][j] = (-2 * xi2[128][j]) / (dx * dx);
			w2[129][j] = w1[129][j];
 		}
 		for (i = 2; i < m; i++) /*updating boundary condition of vorticity function at left and right walls*/
 		{
 			w1[i][1] = (-2 * xi2[i][2]) / (dy * dy);
 			w2[i][1] = w1[i][1];
 			w1[i][129] = ((-2 * xi2[i][128]) - (2 * dy * 1)) /(dy * dy);
 			w2[i][129] = w1[i][129];
 		}
 		for(c=1;c<=2;c++) /*updating values of vorticity function*/
 		{ 
 			for (i = 2; i < m; i++)
 			{
 				for (j = 2; j < n; j++) /*using simplified w formula*/
 				{
 					w2[i][j] =0.25*(w1[i+1][j]+w2[i-1][j]+((w1[i][j+1]+w2[i][j-1]))-(100*(w1[i+1][j]-w2[i-1][j])*(xi1[i][j+1]-xi1[i][j-1]))+(100*(w1[i][j+1]-w2[i][j-1])*(xi1[i+1][j]-xi1[i-1][j])));
 				}
 			}
 		}
 		for (i = 1; i <= m; i++) /*evaluation of error*/
 		{
 			for (j = 1; j <= n; j++)
 			{
 				sumn = sumn + fabs((w2[i][j] - w1[i][j]));
				sumd = sumd + fabs(w2[i][j]);
 			}
 		}
 		es = es + (sumn / sumd);
 		for (i = 1; i <= m; i++) /*updating xi and w values*/
 		{
 			for (j = 1; j <= n; j++)
 			{
 				xi1[i][j] = xi2[i][j];
				w1[i][j] = w2[i][j]; 
 			}
 		}
 		er = es;	
 		es = 0;		
 		sumn = 0;
 		sumd = 0;
	}
	FILE *xy,*uvel,*vvel,*xi,*sf,*U,*V; /*opening text files to plot velocities and stream functions */
	xy=fopen("coordinate.txt","w");
	xi=fopen("stream_func.txt","w");
	sf=fopen("stream_function.txt","w");
	uvel=fopen("u_vel_central.txt","w");
	U=fopen("U_velocity.txt","w");
	vvel=fopen("v_vel_central.txt","w");
	V=fopen("V_velocity.txt","w");
	fprintf(xy,"x\ty\n");				/*headers in text file*/
	fprintf(uvel,"x\ty\tu\n");
	fprintf(vvel,"x\ty\tv\n");
	fprintf(xi,"x\ty\txi");
	x[1]=0;								/*coordinates of grid*/
	x[129]=1;
	y[1]=0;
	y[129]=1;
	for(i=2;i<m;i++)
	{
		for(j=2;j<n;j++)
		{
			x[i]=x[i-1]+dx;
			y[j]=y[j-1]+dy;
		}
	}
	for(i=1;i<=m;i++)
	{
		for(j=1;j<=n;j++)
		{
			fprintf(xy,"%lf\t%lf\n",x[i],y[j]);
		}
	}
	for(i = 1; i <= m; i++)				/*stream function*/
	{
		for(j = 1; j < n; j++)
 		{
 			fprintf(xi,"%lf \t %lf \t %lf \n",x[i],y[j],xi1[i][j]);
 			fprintf(sf,"%lf \t %lf \t %lf \n",x[i],y[j],xi1[i][j]);
 		}
	}
	for(j=1;j<=n;j++)			/*verticle centre line velocity u*/
	{
		if(j==1)
		{
			u[65][j]=0;
			fprintf(uvel,"%f\t%f\t%f\n",x[65],y[j],u[65][j]);
			fprintf(U,"%f\t%f\n",u[65][j],y[j]);
		}
		else if(j==n)
		{
			u[65][j]=1;
			fprintf(uvel,"%f\t%f\t%f\n",x[65],y[j],u[65][j]);
			fprintf(U,"%f\t%f\n",u[65][j],y[j]);
		}
		else
		{ 
			u[65][j] = (xi1[65][j+1]-xi1[65][j-1])/(2*dy);
			fprintf(uvel,"%f\t%f\t%f\n",x[65],y[j],u[65][j]);
			fprintf(U,"%f\t%f\n",u[65][j],y[j]);
		}
	}
	for(i=1;i<=m;i++)				/*horizontal centre line velocity v*/
	{
		if(i==1 || i==m)
		{
			v[i][65]=0;
			fprintf(vvel,"%f\t%f\t%f\n",x[i],y[65],v[i][65]);
			fprintf(V,"%f\t%f\n",x[i],v[i][65]);
		}
		else
		{ 
			v[i][65] = (-xi1[i+1][65]+xi1[i-1][65])/(2*dx);
			fprintf(vvel,"%f\t%f\t%f\n",x[i],y[65],v[i][65]);
			fprintf(V,"%f\t%f\n",x[i],v[i][65]);
		}
	}
	return 0;
}


