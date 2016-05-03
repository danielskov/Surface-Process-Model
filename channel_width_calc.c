#include "header.h"


double channel_width_calc(nodetype *nodes,long i,model_parameters *parameters)
{
  double channel_width;
  channel_width=parameters[0].k_w*pow(nodes[i].drain_area,0.5);
  return channel_width;
}
