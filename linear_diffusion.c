#include "header.h"

void d2_diff(nodetype *nodes,model_parameters *parameters)
{
  int i,j;

  long nx=parameters[0].nx;
  long ny=parameters[0].ny;
  double inv_dx=1/parameters[0].dx;
  double inv_dy=1/parameters[0].dy;
  double inv_dx_square=1/(parameters[0].dx*parameters[0].dx);
  double inv_dy_square=1/(parameters[0].dy*parameters[0].dy);
  double sum1,sum2;
  double k_diff=parameters[0].k_diff;

#pragma omp parallel for default(none) private(i,j,sum1,sum2) shared(nodes,nx,ny,inv_dx,inv_dy,k_diff,inv_dx_square,inv_dy_square)
  for (i=1;i<ny-1;i++)
    {
      for (j=1;j<nx-1;j++)
	{
	  sum1=-nodes[i*nx+j-1].topsedi+2*nodes[i*nx+j].topsedi-nodes[i*nx+j+1].topsedi; //Højre venstre
	  sum2=-nodes[i*nx+j-1*nx].topsedi+2*nodes[i*nx+j].topsedi-nodes[i*nx+j+nx].topsedi; //Op ned
	  nodes[i*nx+j].diff=k_diff*(sum1*inv_dx_square+sum2*inv_dy_square);


	}

      //Left side
      sum1=-2*nodes[i*nx+0+1].topsedi+2*nodes[i*nx+0].topsedi; //Højre venstre
      sum2=-nodes[i*nx+0-1*nx].topsedi+2*nodes[i*nx+0].topsedi-nodes[i*nx+0+nx].topsedi; //Op ned
      nodes[i*nx+0].diff=k_diff*(sum1*inv_dx_square+sum2*inv_dy_square);



      

      //Right side
      sum1=-2*nodes[i*nx+(nx-1)-1].topsedi+2*nodes[i*nx+(nx-1)].topsedi; //Højre venstre
      sum2=-nodes[i*nx+(nx-1)-1*nx].topsedi+2*nodes[i*nx+(nx-1)].topsedi-nodes[i*nx+(nx-1)+nx].topsedi; //op ned
      nodes[i*nx+(nx-1)].diff=k_diff*(sum1*inv_dx_square+sum2*inv_dy_square);
    }


  for (j=1;j<nx-1;j++)
    {
      //Bund
      sum1=-nodes[j+1].topsedi+2*nodes[j].topsedi-nodes[j-1].topsedi; //Højre venstre
      sum2=2*nodes[j].topsedi-2*nodes[j+nx].topsedi; //op ned
      nodes[j].diff=parameters[0].k_diff*(sum1*inv_dx_square+sum2*inv_dy_square);

      //Top
      sum1=-nodes[(ny-1)*nx+j+1].topsedi+2*nodes[(ny-1)*nx+j].topsedi-nodes[(ny-1)*nx+j-1].topsedi; //Højre venstre
      sum2=2*nodes[(ny-1)*nx+j].topsedi-2*nodes[(ny-1)*nx+j-nx].topsedi;
      nodes[(ny-1)*nx+j].diff=parameters[0].k_diff*(sum1*inv_dx_square+sum2*inv_dy_square);
    }


  //Nederste venstre
  nodes[0].diff=2*parameters[0].k_diff*((nodes[0].topsedi-nodes[1].topsedi)*inv_dx_square+(nodes[0].topsedi-nodes[nx].topsedi)*inv_dy_square);

  //Nederste højre
  nodes[nx-1].diff=2*parameters[0].k_diff*((nodes[nx-1].topsedi-nodes[nx-2].topsedi)*inv_dx_square+(nodes[nx-1].topsedi-nodes[nx-1+nx].topsedi)*inv_dy_square);

  //Øverste venstre
  nodes[(ny-1)*nx].diff=2*parameters[0].k_diff*((nodes[(ny-1)*nx].topsedi-nodes[(ny-1)*nx+1].topsedi)*inv_dx_square+(nodes[(ny-1)*nx].topsedi-nodes[(ny-1)*nx-nx].topsedi)*inv_dy_square);

  //Øverste højre
  nodes[(ny-1)*nx+nx-1].diff=2*parameters[0].k_diff*((nodes[(ny-1)*nx+nx-1].topsedi-nodes[(ny-1)*nx+nx-2].topsedi)*inv_dx_square+(nodes[(ny-1)*nx+nx-1].topsedi-nodes[(ny-1)*nx-1].topsedi)*inv_dy_square);


  //printf("nv %ld, nh %ld ov %ld oh %ld \n",0,nx-1,(ny-1)*nx,(ny-1)*nx+nx-1);
  //printf("%g %g %g %g \n",nodes[0].diff,nodes[99].diff,nodes[9900].diff,nodes[9999].diff);
  
  for (i=0;i<nx*ny;i++)
    {
      if (nodes[i].diff<0)
	nodes[i].diff=0;
      //printf("diff %g \n",nodes[i].diff);
    }
  
}