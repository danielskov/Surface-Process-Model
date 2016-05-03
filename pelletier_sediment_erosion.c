#include "header.h"

double pelletier_sediment_erosion(nodetype *nodes,long j,double node_height,model_parameters *parameters)
{
  double fluvial_incision;
  double pelletier_erosion_constant=1e-2;
  fluvial_incision=(nodes[j].channel_width/parameters[0].dx)*(parameters[0].deltat*pelletier_erosion_constant*sqrt(nodes[j].upstream_erosion)/nodes[j].channel_width)*nodes[j].reciever_slope;

  /*
    if (nodes[j].c>-1) {
    printf("fluvial incision %g node %ld sediment flux %g \n ",fluvial_incision,j,nodes[j].upstream_erosion);
    }
  */

  return fluvial_incision;	
}
