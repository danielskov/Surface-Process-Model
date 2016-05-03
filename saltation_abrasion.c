#include "header.h"


double expli_salt_abr(nodetype *nodes,long j,double node_height,model_parameters *parameters)
{	
  double fluvial_incision;
  fluvial_incision=(nodes[j].channel_width/parameters[0].dx)*(parameters[0].deltat*parameters[0].K_s*(nodes[j].upstream_erosion/nodes[j].channel_width))*pow(nodes[j].drain_area,-0.88/3)*pow(nodes[j].reciever_slope,-1.76/3)*(1-nodes[j].upstream_erosion/nodes[j].sediment_capa_sedi);

  
  
  //These lines are to give an overview, by splitting up the equation. For better perfomance, use the line above and outcomment the lines below.
  /*
    double deltat=parameters[0].deltat;
    double K_s=parameters[0].K_s;
    double upstream_erosion=nodes[j].upstream_erosion;
    double channel_width=nodes[j].channel_width;
    double drain_area_w_exponent=pow(nodes[j].drain_area,-0.88/3);
    double slope_w_exponent=pow((node_height-nodes[nodes[j].r].topsedi)/nodes[j].reciever_distance,-1.76/3);
    double sediment_capa=nodes[j].sediment_capa_sedi;
	
    fluvial_incision=(deltat*K_s*(upstream_erosion/channel_width))*drain_area_w_exponent*slope_w_exponent*(1-upstream_erosion/sediment_capa);
  */

  if (fluvial_incision<0) {
    fluvial_incision=0;
    //printf("fluvial incision %g node %ld relsedi %g upstream erosion %g \n ",fluvial_incision,j,nodes[j].upstream_erosion/nodes[j].sediment_capa_sedi,nodes[j].upstream_erosion);
  }


  
  /*
    if (nodes[j].c>-1) {
    printf("fluvial incision %g node %ld relsedi %g \n ",fluvial_incision,j,nodes[j].upstream_erosion/nodes[j].sediment_capa_sedi);
    }
  */
	
  return fluvial_incision;	
}

