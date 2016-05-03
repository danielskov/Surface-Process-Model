#include "header.h"

double expli_stream_power(nodetype *nodes,long j,double node_height,model_parameters *parameters)
{
  double fluv_stream_power;
	
	
  fluv_stream_power=(nodes[j].channel_width/parameters[0].dx)*parameters[0].K_stream*parameters[0].deltat*pow(nodes[j].drain_area,parameters[0].M)*pow(nodes[j].reciever_slope,parameters[0].n);
	
	
  if (node_height<nodes[nodes[j].r].topsedi) printf("node %ld reciever %ld h1 %g h1_2 %g h2 %g \n",j,nodes[j].r,nodes[j].topsedi,node_height,nodes[nodes[j].r].topsedi);
	
  //These lines are to give an overview, by splitting up the equation. For better perfomance, use the line above and outcomment the lines below.
	
  // double M=parameters[0].M;
  // double n=parameters[0].n;
  // double K_stream=parameters[0].K_stream;
  // double deltat=parameters[0].deltat;
  // double drain_area_w_exponent=pow(nodes[j].drain_area,M);
  // double slope_w_exponent=pow((node_height-nodes[nodes[j].r].topsedi)/nodes[j].reciever_distance,n);
  //
  // fluv_stream_power=K_stream*deltat*drain_area_w_exponent*slope_w_exponent;
	
  return fluv_stream_power;
}
