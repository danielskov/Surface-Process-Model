/*Functions to be used in model*/
#include "header.h"
#include <omp.h>
#define PI 3.141592653589793

/*
double ber(double r)
{
	double x,z;
	
	x=pow(pow(r/8.0,2),2);
	z=1.0+x*(-64.0+x*(113.77777774+x*(-32.36345652+x*(2.64191397 + x*(-0.08349609+x*(0.00122552 + x*(-0.00000901)))))));
	return z;
}

double bei(double r)
{
	double x,y,z;
	y=pow(r/8.0,2);
	x=pow(y,2);
	z=y*(16.0+x*(-113.77777774 +
		x*(72.81777742+x*(-10.56765779 +
			x*(0.52185615+x*(-0.01103667+
				x*0.00011346))))));
	return z;
}

double kei(double r)
{
	
	double x,y,z;
	
	if(r==0) r=1e-50;
	y=pow(r/8.0,2);
	x=pow(y,2);
	z=(-log(0.50*r)*bei(r))-(0.25*M_PI*ber(r))+
		y*(6.76454936+x*(-142.91827687 +
			x*(124.23569650+x*(-21.30060904+
				x*(1.17509064+x*(-0.02695875+
					x*0.00029532))))));
	return z;
}
*/


double ber(double r)
{ double x,z;
x = pow(pow(r/8.0,2),2);
z = 1.0 + x * (-64.0 + x * (113.77777774 +
x * (-32.36345652 + x * ( 2.64191397 +
x * ( -0.08349609 + x * ( 0.00122552 +
x * -0.00000901))))));
return z;
}

double bei(double r)
{
double x,y,z;
y = pow(r/8.0,2);
x = pow(y,2);
z = y * (16.0 + x * (-113.77777774 +
x * (72.81777742 + x * ( -10.56765779 +
x * ( 0.52185615 + x * ( -0.01103667 +
x * 0.00011346))))));
return z;
}


double kei(double r)
{
double x,y,z;
if (r == 0) r = 1e-50;
y = pow(r/8.0,2);
x = pow(y,2);
z = (-log(0.50 * r) * bei(r)) - (0.25*PI*ber(r)) +
	y * ( 6.76454936 + x * (-142.91827687 +
	x * (124.23569650 + x * ( -21.30060904 +
	x * ( 1.17509064 + x * ( -0.02695875 +
	x * 0.00029532))))));
	return z;
	}


void calc_integral_flexure(nodetype *nodes,long nx,long ny,long dx,long dy)
{
	int i,j;
	
	double rho_c=2600.0;
	double rho_m=3300.0;
	
	//double rho_contrast=rho_c/(rho_m-rho_c);
	
	double rho_contrast=rho_c/rho_m;
	
	double alpha=1;
	
	double constant=sqrt(2)/alpha;
	
	double distance;
	long k=0;
	
	double dxx=dx;
	double dyy=dy;
	double constant2=nx*ny/(1000.0);
	
	//#pragma omp parallel for default(none) private(i,j,k,distance) shared(dxx,dyy,nx,ny,nodes,constant,rho_contrast) 
	for (i=nx;i<nx*ny;i++)
	{
		nodes[i].deflection=0;
		k=0;
		for (j=0;j<nx*ny;j++)
		{
			distance=sqrt((dxx/1000)*(dxx/1000)*(nodes[i].x-nodes[j].x)*(nodes[i].x-nodes[j].x)+(dyy/1000)*(dyy/1000)*(nodes[i].y-nodes[j].y)*(nodes[i].y-nodes[j].y));
			
			if ((distance*constant)<10.3) {
			nodes[i].deflection+=(nodes[j].topsedi-nodes[j].top_old)*kei(distance*constant);
			k++;
			//printf("kei %g \n",kei(distance*constant));
			//if (i==j) printf("kei own %g ero %g \n",(nodes[j].topsedi-nodes[j].top_old)*kei(distance*constant),nodes[i].top_old-nodes[i].topsedi);
			}		
		}
		nodes[i].deflection*=rho_contrast;
		nodes[i].deflection*=constant2/k;
		//printf("k %ld  \n",k);
	}
	
	//printf("k: %ld of nx*ny %ld \n",k,nx*ny);
	
	double mean_deflec=0;
	double mean_erosion=0;
	
	
	printf("deflection start \n");
	 for(i=0;i<nx*ny;i++)
		 {
			 if (nodes[i].deflection!=0) {
				 printf("deflec %g \n",nodes[i].deflection);
				 printf("ero %g \n",nodes[i].top_old-nodes[i].topsedi);
				 mean_deflec+=nodes[i].deflection;
				 mean_erosion+=nodes[i].top_old-nodes[i].topsedi;
			 }
		 }
		 printf("deflection slut mean deflec %g mean erosion %g mean_erosion*rho_c/rho_m %g \n",mean_deflec,mean_erosion,mean_erosion*rho_contrast);
		 
 	//printf("kl %ld total %ld \n",kl,nx*ny*nx*ny);
 

}
	
	
	
void perform_integral_flexure(nodetype *nodes, long nx,long ny)
{
	long i;

	
   for (i=nx;i<nx*ny;i++)
   {
  	 //if (nodes[i].top_old-nodes[i].topsedi!=0){
  	 //printf("deflec %g ero %g \n",nodes[i].deflection,nodes[i].top_old-nodes[i].topsedi);}
  	 nodes[i].bed+=nodes[i].deflection;
  	 nodes[i].topsedi+=nodes[i].deflection;
   }
}