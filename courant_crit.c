#include "header.h"


void courant_crit(nodetype *nodes,model_parameters *parameters,int *indi)
{
  double stream_crit=200e8;
  double saltabr_crit=200e8;
  double pel_crit=200e9;
  double pelletier_erosion_constant=1e-2;
  int j;
  double dx=parameters[0].dx;
  double dy=parameters[0].dy;
  double dxdymin=dx;
  if (dxdymin>dy)
    dxdymin=dy;
	
  for (j=0;j<parameters[0].nx*parameters[0].ny;j++)
    {
      if (nodes[j].reciever_distance>0)
	{
	  //printf("node %ld width %g, drain area %g stream crit %g \n",j,nodes[j].channel_width,nodes[j].drain_area,(nodes[j].channel_width/parameters[0].dx)*parameters[0].K_stream*parameters[0].deltat*pow(nodes[j].drain_area,parameters[0].M));
	  if ((nodes[j].reciever_distance/((nodes[j].channel_width/parameters[0].dx)*parameters[0].K_stream*parameters[0].deltat*pow(nodes[j].drain_area,parameters[0].M)))<stream_crit)
	    {
	      stream_crit=nodes[j].reciever_distance/((nodes[j].channel_width/parameters[0].dx)*parameters[0].K_stream*parameters[0].deltat*pow(nodes[j].drain_area,parameters[0].M));
	      //printf("stream_crit %g node %j \n",stream_crit,j);
	    }	
	  if ((nodes[j].reciever_distance/((nodes[j].channel_width/parameters[0].dx)*(parameters[0].deltat*pelletier_erosion_constant*sqrt(nodes[j].upstream_erosion)/nodes[j].channel_width)))<pel_crit)
	    pel_crit=nodes[j].reciever_distance/((nodes[j].channel_width/parameters[0].dx)*(parameters[0].deltat*pelletier_erosion_constant*sqrt(nodes[j].upstream_erosion)/nodes[j].channel_width));
	  if (nodes[j].upstream_erosion<nodes[j].sediment_capa_sedi && (nodes[j].reciever_distance/((nodes[j].channel_width/parameters[0].dx)*(parameters[0].deltat*parameters[0].K_s*(nodes[j].upstream_erosion/nodes[j].channel_width))*pow(nodes[j].drain_area,-0.88/3)*(1-nodes[j].upstream_erosion/nodes[j].sediment_capa_sedi)))<saltabr_crit)
	    saltabr_crit=nodes[j].reciever_distance/((nodes[j].channel_width/parameters[0].dx)*(parameters[0].deltat*parameters[0].K_s*(nodes[j].upstream_erosion/nodes[j].channel_width))*pow(nodes[j].drain_area,-0.88/3)*(1-nodes[j].upstream_erosion/nodes[j].sediment_capa_sedi));
	}
    }



  //printf("node %ld width %g, drain area %g stream crit %g \n",i,nodes[i].channel_width,nodes[i].drain_area,stream_crit);

  if ((dxdymin/stream_crit)>1000) {
    //printf("node %ld width %g, drain area %g stream crit %g \n",i,nodes[i].channel_width,nodes[i].drain_area,stream_crit);
    //exit(1);
  }
	
  double upstreamsum=0;
  double drainsum=0;
  for (j=0;j<parameters[0].nx;j++)
    {
      upstreamsum+=nodes[j].upstream_erosion;
      drainsum+=nodes[j].drain_area;
    }


  //printf("streamcrit %g pelcrit %g saltabrcrit %g \n",stream_crit,pel_crit,saltabr_crit);	
  double deltat_old=parameters[0].deltat;
  //parameters[0].deltat=stream_crit;

  if (parameters[0].deltat>saltabr_crit)
    {
      printf("herinde crit %g deltat %g \n", saltabr_crit,parameters[0].deltat);
      parameters[0].deltat=saltabr_crit;
	   
      (*indi)=2;
    }
  else {
    parameters[0].deltat=saltabr_crit;
  }
	  

  if ((parameters[0].deltat/deltat_old)>1.1) {
    parameters[0].deltat=deltat_old*1.1;
  }
	
  if (parameters[0].deltat>10)
    {
      parameters[0].deltat=10;
    }
	
  //if (parameters[0].deltat>100)
  //	parameters[0].deltat=100;
	
  //printf("deltat %g upstreamsum %g drainsum %g salabr crit %g \n",parameters[0].deltat,upstreamsum,drainsum,saltabr_crit);
	
}
