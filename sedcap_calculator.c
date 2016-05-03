#include "header.h"

void expli_sed_cap_topsed_new(nodetype *nodes,long *stack2,long nx,long ny,model_parameters *parameters,double dx, double dy)
{
  /*This function finds the sediment capacity for all nodes in the grid. The function uses the stack2 to make sure that a once initiated stream stays a stream further downstream*/
  double sediment_capa=0;
  int indi=0;
	
  long j,h;
  	
  //#pragma omp parallel for default(none) private(j,sediment_capa,indi,h) shared(nodes,nx,ny,dx,dy,parameters,stack2)
  for (j=0;j<nx*ny;j++)
    {
      h=stack2[j];
		
      if ((parameters[0].k_tau*pow(nodes[h].drain_area,1.0/3)*pow(nodes[h].reciever_slope,2.0/3)-parameters[0].tau_crit)>0 /*|| nodes[h].river==1*/)
	{
	  sediment_capa=parameters[0].k_sed*pow(nodes[h].drain_area,0.5)*pow(parameters[0].k_tau*pow(nodes[h].drain_area,1.0/3)*pow((nodes[h].topsedi-nodes[nodes[h].r].topsedi)/nodes[h].reciever_distance,2.0/3)-parameters[0].tau_crit,3.0/2);
	  //sediment_capa=parameters[0].k_sed*pow(nodes[h].drain_area,0.5)*pow(parameters[0].k_tau*pow(nodes[h].drain_area,1.0/3)*pow(nodes[h].reciever_slope,2.0/3)-parameters[0].tau_crit,3.0/2);		
	  //sediment_capa=parameters[0].k_sed*pow(nodes[h].drain_area,0.5)*pow(parameters[0].k_tau*pow(nodes[h].drain_area,1.0/3)*pow(nodes[h].reciever_slope,2.0/3),3.0/2);		
	  nodes[h].river=1;
	  nodes[nodes[h].r].river=1;
	  indi=0;
	  nodes[h].under_taucrit=0;
	  //printf("node %ld flod drainage area %g sediment capa %g \n",h,nodes[h].drain_area,sediment_capa);
	}
      else if (nodes[h].river==1)
	{
	  indi=1;
	  sediment_capa=0;
	  nodes[nodes[h].r].river=1;
	  nodes[h].under_taucrit=0;
	}
      else
	{
	  indi=2;
	  nodes[h].river=0;
	  nodes[h].under_taucrit=1;
	  sediment_capa=0;
	  //sediment_capa=dx*dy*parameters[0].k_diff*(-nodes[nodes[h].r].topsedi+nodes[h].topsedi)/(nodes[h].reciever_distance);
	  //sediment_capa=nodes[h].diff*parameters[0].k_diff_sed_change*dx*dy; //expli_diffusion_calc(nodes,h,nodes[h].topsedi,parameters);
	  //nodes[h].diff=sediment_capa/(dx*dy*parameters[0].deltat);
	  if (sediment_capa<0) {printf("Det noget pis sed capa %g indi %d \n",sediment_capa,indi); sediment_capa=0; }
	}
	
      if (sediment_capa<0) {printf("Det noget pis sed capa %g indi %d \n",sediment_capa,indi); sediment_capa=0; }
      //if (sediment_capa>0 && indi==2) {printf("Det er bedre %g indi %d \n",sediment_capa,indi); sediment_capa=0; }
		
      //if (indi==1 && sediment_capa>0) printf("Det kan lykkes \n");
      //printf("sedi capa %g indi %d frac %g \n",sediment_capa,indi,pow((nodes[h].topsedi-nodes[nodes[h].r].topsedi)/nodes[h].reciever_distance,2.0/3));
		
      //printf("j %ld node %ld fluv transport %g  diff %g \n",j,h,sediment_capa,nodes[h].diff);

      //printf("fluvial transport %g diff transport %g \n",nodes[h].sediment_capa_sedi,nodes[h].diff);
      nodes[h].sediment_capa_sedi=sediment_capa+dx*dy*nodes[h].diff*parameters[0].k_diff_sed_change;
      //nodes[h].sediment_capa_sedi=sediment_capa;	
		
		
    }
	
	
	
  //	for (j=0;j<nx*ny;j++)
  //	{
  //		if (nodes[j].sediment_capa_sedi==0 && j>nx) printf("indi %ld j %ld sediment capa %g \n",indi,j,nodes[j].sediment_capa_sedi);
  //	}
	
	
	
  //sediment_capa=fluv_trans+diff_trans;
	
  //These lines are to give an overview, by splitting up the equation. For better perfomance, use the line above and outcomment the lines below.
  /*
    double K_t=parameters[0].K_t;
    double drain_area_w_expo=pow(nodes[i].drain_area,(1.5));
    double slope=pow((nodes[i].topsedi-nodes[nodes[i].r].topsedi)/nodes[i].reciever_distance,1);
    sediment_capa=K_t*drain_area_w_expo*slope;
  */
  //return sediment_capa;
}






double expli_sed_cap_bed(nodetype *nodes, long i,model_parameters *parameters)
{
  double sediment_capa;
  double K_t=parameters[0].K_t;
  sediment_capa=K_t*pow(nodes[i].drain_area,(1.5))*pow((nodes[i].bed-nodes[nodes[i].r].bed)/nodes[i].reciever_distance,1);
  //printf("Sedimet_capa: %2.6f \n",sediment_capa);
  return sediment_capa;
}
