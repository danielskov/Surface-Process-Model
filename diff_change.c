#include "header.h"

double diff_change(nodetype *nodes,model_parameters *parameters,long j)
{

  double diff_change;

  //diff_change=(nodes[j].diff-nodes[nodes[j].r].diff)/nodes[j].reciever_slope;
  diff_change=(nodes[j].diff-nodes[nodes[j].r].diff)/nodes[j].reciever_distance;


  diff_change=nodes[j].diff;
  
  if (diff_change<0)
    diff_change=0;
  
  return diff_change;
}
