#ifdef HAVE_MALLOC_H
# include<malloc.h>
#endif
#include "header.h"

#define FREE_ARG char*
#define NR_END 1
#define PI 3.141592653589793

float *vector(nl,nh)
long nh,nl;
/* allocate a float vector with subscript range v[nl..nh] */
{
        float *v;

        v=(float *)malloc((unsigned int) ((nh-nl+1+NR_END)*sizeof(float)));
        return v-nl+NR_END;
}

int *ivector(nl,nh)
long nh,nl;
/* allocate an int vector with subscript range v[nl..nh] */
{
        int *v;

        v=(int *)malloc((unsigned int) ((nh-nl+1+NR_END)*sizeof(int)));
        return v-nl+NR_END;
}

float **matrix(nrl,nrh,ncl,nch)
int nrl,nrh,ncl,nch;
/* allocate a float matrix with subscript range m[nrl..nrh][ncl..nch] */
{
    int i;
    float **m;

        /*allocate pointers to rows */
        m=(float **) malloc((unsigned) (nrh-nrl+1)*sizeof(float*));
    m -= nrl;

   /*allocate rows and set pointers to them */
      for(i=nrl;i<=nrh;i++) {
                      m[i]=(float *) malloc((unsigned) (nch-ncl+1)*sizeof(float)
);
            m[i] -= ncl;
    }
      /* return pointer to array of pointers to rows */
      return m;
}

#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr

void fourn(float data[], int nn[], int ndim, int isign)
{
	int idim;
	unsigned long i1,i2,i3,i2rev,i3rev,ip1,ip2,ip3,ifp1,ifp2;
	unsigned long ibit,k1,k2,n,nprev,nrem,ntot;
	float tempi,tempr;
	double theta,wi,wpi,wpr,wr,wtemp;

	for (ntot=1,idim=1;idim<=ndim;idim++)
		ntot *= nn[idim];
	nprev=1;
	for (idim=ndim;idim>=1;idim--) {
		n=nn[idim];
		nrem=ntot/(n*nprev);
		ip1=nprev << 1;
		ip2=ip1*n;
		ip3=ip2*nrem;
		i2rev=1;
		for (i2=1;i2<=ip2;i2+=ip1) {
			if (i2 < i2rev) {
				for (i1=i2;i1<=i2+ip1-2;i1+=2) {
					for (i3=i1;i3<=ip3;i3+=ip2) {
						i3rev=i2rev+i3-i2;
						SWAP(data[i3],data[i3rev]);
						SWAP(data[i3+1],data[i3rev+1]);
					}
				}
			}
			ibit=ip2 >> 1;
			while (ibit >= ip1 && i2rev > ibit) {
				i2rev -= ibit;
				ibit >>= 1;
			}
			i2rev += ibit;
		}
		ifp1=ip1;
		while (ifp1 < ip2) {
			ifp2=ifp1 << 1;
			theta=isign*6.28318530717959/(ifp2/ip1);
			wtemp=sin(0.5*theta);
			wpr = -2.0*wtemp*wtemp;
			wpi=sin(theta);
			wr=1.0;
			wi=0.0;
			for (i3=1;i3<=ifp1;i3+=ip1) {
				for (i1=i3;i1<=i3+ip1-2;i1+=2) {
					for (i2=i1;i2<=ip3;i2+=ifp2) {
						k1=i2;
						k2=k1+ifp1;
						tempr=(float)wr*data[k2]-(float)wi*data[k2+1];
						tempi=(float)wr*data[k2+1]+(float)wi*data[k2];
						data[k2]=data[k1]-tempr;
						data[k2+1]=data[k1+1]-tempi;
						data[k1] += tempr;
						data[k1+1] += tempi;
					}
				}
				wr=(wtemp=wr)*wpr-wi*wpi+wr;
				wi=wi*wpr+wtemp*wpi+wi;
			}
			ifp1=ifp2;
		}
		nprev *= n;
	}
}
#undef SWAP

void flexit(nodetype *nodes,long nx,long ny,long dx,long dy)
{    float alpha,fact,*w,delrho;
     long i,j;
     int *nn;
         
			
			
			
	  /*
  	fftw_complex *in,out;
  	fftw_plan plan_backward;
  	fftw_plan plan_forward;
  	
  	nyh=(ny/2)+1;

  	in =fftw_malloc(sizeof(fftw_complex)*nx*ny);
	out =fftw_malloc(sizeof(fftw_complex)*nx*nyh);
  	plan_forward=fftw_plan_dft_r2c_2d(nx*ny,in,out,FFTW_FORWARD,FFTW_ESTIMATE);	
	
	
  	in2 = ( double * ) malloc ( sizeof ( double ) * nx * ny );

  	  plan_backward = fftw_plan_dft_c2r_2d ( nx, ny, out, in2, FFTW_ESTIMATE );

  	  fftw_execute ( plan_backward );
	
  	printf ( "\n" );
  	  printf ( "  Recovered input data divided by NX * NY:\n" );
  	  printf ( "\n" );

  	  for ( i = 0; i < nx; i++ )
  	  {
  	    for ( j = 0; j < ny; j++ )
  	    {
  	      printf ( "  %4d  %4d  %12f\n",  
  	        i, j, in2[i*ny+j] / ( double ) ( nx * ny ) );
  	    }
  	  }
	  */
	  
  	/*
  	  Free up the allocated memory.
  	*/
	  
	  /*
  	  fftw_destroy_plan ( plan_forward );
  	  fftw_destroy_plan ( plan_backward );

  	  free ( in );
  	  free ( in2 );
  	  fftw_free ( out );
		*/	
			
			
			
			
     alpha=50.0;  /* (4D/((rho_m-rho_c)*g))^0.25, in units of multiples of delta */
     delrho=0.27; /* (rho_m-rho_c)/rho_c */
     nn=ivector(1,2);
     nn[1]=nx;
     nn[2]=ny;
	  
	  for(i=0;i<nx*ny;i++) nodes[i].deflection=0;
	  
	  /*nodes[nx*ny/2+nx/2].erosion=1E3;
	   nodes[nx*ny/2+1+nx/2].erosion=1E3;
		 nodes[nx*ny/2+2+nx/2].erosion=1E3;
		  nodes[nx*ny/2+3+nx/2].erosion=1E3;
		 */ 
     w=vector(1,2*nx*ny);
     for (j=1;j<=ny;j++) {
      for (i=1;i<=nx;i++)
       {w[2*(i-1)*ny+2*j-1]=(nodes[(j-1)*nx+(i-1)].top_old-nodes[(j-1)*nx+(i-1)].topsedi);
        w[2*(i-1)*ny+2*j]=0.0;}}

		  /*
	 	 for(i=0;i<nx*ny;i++)
	 		 {
	 			 if (nodes[i].erosion>0) printf("%g \n",nodes[i].erosion);
	 		 }
	  */
	  
	  fourn(w,nn,2,1);
	  
     w[1]*=1/delrho;
     w[2]*=1/delrho;
     for (j=1;j<=ny/2;j++)
      {fact=1/(delrho+4*delrho*pow(alpha*j*PI/(ny),4.0));
       w[2*j+1]*=fact;
       w[2*j+2]*=fact;
       w[2*ny-2*j+1]*=fact;
       w[2*ny-2*j+2]*=fact;}
     for (i=1;i<=nx/2;i++)
      {fact=1/(delrho+4*delrho*pow(alpha*i*PI/(nx),4.0));
       w[2*i*ny+1]*=fact;
       w[2*i*ny+2]*=fact;
       w[2*nx*ny-2*i*ny+1]*=fact;
       w[2*nx*ny-2*i*ny+2]*=fact;}
     for (i=1;i<=nx/2;i++)
      for (j=1;j<=ny/2;j++)
       {fact=1/(delrho+4*delrho*pow(alpha*sqrt((PI*PI*i*i)/(nx*nx)+
         (PI*PI*j*j)/(ny*ny)),4.0));
        w[2*i*ny+2*j+1]*=fact;
        w[2*i*ny+2*j+2]*=fact;
        w[2*i*ny+2*ny-2*j+1]*=fact;
        w[2*i*ny+2*ny-2*j+2]*=fact;
        w[2*nx*ny-2*(i-1)*ny-
          2*(ny-j)+1]*=fact;
        w[2*nx*ny-2*(i-1)*ny-
          2*(ny-j)+2]*=fact;
        w[2*nx*ny-2*ny-
          2*(i-1)*ny+2*(ny-j)+1]*=fact;         
		w[2*nx*ny-2*ny-
          2*(i-1)*ny+2*(ny-j)+2]*=fact;}
     fourn(w,nn,2,-1);
	  for (j=1;j<=ny;j++) {
      for (i=1;i<=nx;i++) {
			nodes[(j-1)*nx+(i-1)].deflection=w[2*(i-1)*ny+2*j-1]/(nx*ny);
	 }}
	 
	 /*
	printf("deflection start \n");
	 for(i=0;i<nx*ny;i++)
		 {
			 if (nodes[i].deflection!=0) {
				 printf("deflec %g \n",nodes[i].deflection);
				 printf("ero %g \n",nodes[i].top_old-nodes[i].topsedi);
			 }
		 }
		 printf("deflection slut \n");
		*/
	 
	 
	 for (i=nx;i<nx*ny;i++)
	 {
		 nodes[i].bed+=nodes[i].deflection;
		 nodes[i].topsedi+=nodes[i].deflection;
	 }
	 

}
