#include "header.h"

void update_height(nodetype *nodes,long *stack,long nx,long ny,long npits,double dx,double dy,long *stack2,double it_crit,double under_relax_height,long *flist,long s_flist,model_parameters *parameters,int *indi)
{
  long i; //Parameter used in for loops
  long j; //The stack number
  double new; //The old and the new values used in the heigth iteration
  double sediment_capa;
  //double counter=0;
  double ero;
  double split=parameters[0].split;
  double sediment_in_node;	
#pragma omp parallel for default(none) private(i,sediment_capa,new,j,ero,sediment_in_node) shared(indi,nodes,nx,ny,dx,dy,stack,under_relax_height,parameters,split) schedule(static) //if((nx*ny)>(100*100))
  for (i=0;i<nx*ny;i++)
    {
      j=stack[i];
      if (j!=nodes[j].r && nodes[j].in_stack==1 && nodes[j].c>=0/*&& nodes[j].river==1*/) //If it is in the stack and is not a baselevel or pit node
	{	
	  //in_stacks++;
	  sediment_capa=nodes[j].sediment_capa_sedi;
	  sediment_in_node=dx*dy*(nodes[j].topsedi-nodes[j].bed)/parameters[0].deltat;
	  if (sediment_in_node<0)
	  {
		  printf("Sediment in node below zero %g \n",sediment_in_node);
		  exit(1);
	  }
	  new=nodes[j].topsedi;

	  if((sediment_in_node+nodes[j].upstream_erosion)<sediment_capa)
	    {
	      nodes[j].fluv=(1/parameters[0].deltat)*((1-split)*expli_salt_abr(nodes,j,nodes[j].topsedi,parameters)+split*expli_stream_power(nodes,j,nodes[j].topsedi,parameters));
	      if (nodes[j].fluv<0) nodes[j].fluv=0;
	      nodes[j].saltabr_incision=(1/parameters[0].deltat)*(1-split)*expli_salt_abr(nodes,j,nodes[j].topsedi,parameters);
	      if (nodes[j].saltabr_incision<0)
			{
				printf("incision below zero %g \n",nodes[j].saltabr_incision);
				exit(1);
			}
			
			nodes[j].stream_power=(1/parameters[0].deltat)*split*expli_stream_power(nodes,j,nodes[j].topsedi,parameters);
	    }
	  //nodes[j].diff_erosion=diff_change(nodes,parameters,j)/(dx*dy);
	  nodes[j].diff_erosion=nodes[j].diff;

	  long indi2=0;  
	  if ((sediment_in_node+nodes[j].upstream_erosion)<sediment_capa && nodes[j].river==1)
	    {
	      //new=nodes[j].topsedi-(1-split)*expli_salt_abr(nodes,j,nodes[j].topsedi,parameters)-split*expli_stream_power(nodes,j,nodes[j].topsedi,parameters)-diff_change(nodes,parameters,j)*parameters[0].deltat/(dx*dy);
	      new=nodes[j].topsedi-parameters[0].deltat*(nodes[j].fluv+nodes[j].diff_erosion);
	      //nodes[j].diff*parameters[0].deltat/(dx*dy);
	      //new=nodes[j].topsedi-pelletier_sediment_erosion(nodes,j,nodes[j].topsedi,parameters);
	      //printf("Her \n");
	      indi2=1;
	    }
	  else if ((sediment_in_node+nodes[j].upstream_erosion)<sediment_capa && nodes[j].river==0)
	    {
	      //new=nodes[j].topsedi-diff_change(nodes,parameters,j)*parameters[0].deltat/(dx*dy);
	      new=nodes[j].topsedi-nodes[j].diff_erosion*parameters[0].deltat;
	      //printf("Diff erosion %g \n", nodes[j].diff*parameters[0].deltat/(dx*dy));

	    }
	  else {
	    new=nodes[j].topsedi;
	  }

	  
	  if (new<nodes[nodes[j].r].topsedi_new)
	  {
	      printf("Inversion of terrain: topsedi %g new %g re %g saltabr %g stream power %g \n",nodes[j].topsedi,new,nodes[nodes[j].r].topsedi,(1-split)*expli_salt_abr(nodes,j,nodes[j].topsedi,parameters),split*expli_stream_power(nodes,j,nodes[j].topsedi,parameters));
	      (*indi)=1;
	      new=nodes[nodes[j].r].topsedi_new+1e8;
	    }
	  		
	  new=under_relax_height*new+(1-under_relax_height)*nodes[j].topsedi;
		
	  ero=nodes[j].topsedi-new;
	  /*
	  if ((nodes[j].bed-ero)<nodes[nodes[j].r].topsedi)
	  //To make sure that the bedrock of the node doesnt erode under the top of the reciever node	   
	  {
	      ero=nodes[j].bed-nodes[nodes[j].r].topsedi;
	      (*indi)=1;
	      //printf("Ofte?\n");
	    }
	  */
	  if (nodes[j].bed-ero<0) {ero=nodes[j].bed-1e-15; (*indi)=1; printf("Bed erodes under sealevel. Bed %g erosion %g rel sedi %g topsedi %g new %g indi %ld upstream_erision v capa %d \n",nodes[j].bed,ero,nodes[j].upstream_erosion/sediment_capa,nodes[j].rel_sedi,new,indi2,nodes[j].upstream_erosion<sediment_capa);} //The factor 1e-15 is deducted to avoid that we can create a pit
	  if (ero<0) {ero=0; printf("Erosion below zero\n");}
	  nodes[j].bed_new=nodes[j].bed-ero;
	  nodes[j].topsedi_new=nodes[j].topsedi-ero;
	  nodes[j].erosion=ero*dx*dy/parameters[0].deltat; //i m^3/year
	  if (nodes[j].erosion<0) {printf("Negative erosion: %2.8f \n",nodes[j].erosion); printf("node %ld new: %2.2f upper %2.2f, lower: %2.2f \n",j,new,nodes[j].topsedi,nodes[nodes[j].r].topsedi);}
	  //if (nodes[j].erosion>0) {printf("Positive erosion: %2.8f \n",nodes[j].erosion); printf("node %ld new: %2.2f upper %2.2f, lower: %2.2f \n",j,new,nodes[j].topsedi,nodes[nodes[j].r].topsedi);}		
			
	}
    }
}

void save_parameters(nodetype *nodes,long nx,long ny,model_parameters *parameters)
{
  /*These outputs are given with the old values to make the output represent the force that resulted in the lowering*/
  double split=parameters[0].split;
  double sediment_capa;
  int j;
	
#pragma omp parallel for default(none) private(j,sediment_capa) shared(nodes,nx,ny,parameters,split)
  for (j=0;j<nx*ny;j++) 
    {
	
      sediment_capa=nodes[j].sediment_capa_sedi;
	
	
      if (nodes[j].upstream_erosion<sediment_capa && nodes[j].in_stack==1 && nodes[j].under_taucrit==0)
	{
	  nodes[j].fluv=(1/parameters[0].deltat)*((1-split)*expli_salt_abr(nodes,j,nodes[j].topsedi,parameters)+split*expli_stream_power(nodes,j,nodes[j].topsedi,parameters));
	  if (nodes[j].fluv<0) nodes[j].fluv=0;
	  nodes[j].saltabr_incision=(1/parameters[0].deltat)*(1-split)*expli_salt_abr(nodes,j,nodes[j].topsedi,parameters);
	  nodes[j].stream_power=(1/parameters[0].deltat)*split*expli_stream_power(nodes,j,nodes[j].topsedi,parameters);
	  //nodes[j].diff=0;
	}
      else
	{
	  nodes[j].fluv=0;
	  nodes[j].stream_power=0;
	  nodes[j].saltabr_incision=0;
	  //nodes[j].diff=sediment_capa;
	  //printf("%fluv: %5.2e \n",nodes[j].fluv);
	}
    }
}



void expli_solver(nodetype *nodes,long *stack,long nx,long ny,long npits,double dx,double dy,long *stack2,long *flist,long s_flist,model_parameters *parameters)
{
  double under_relax_height=1;
  double it_crit=1e-1; //The convergence criterion in the heigth iteration
  long i;
	
#pragma omp parallel for default(none) private(i) shared(nx,ny,nodes,parameters) //if((nx*ny)>(100*100))
  for (i=0;i<nx*ny;i++)
    {
      nodes[i].bed_new=nodes[i].bed;
      nodes[i].topsedi_new=nodes[i].topsedi;
      nodes[i].fluv=0;
      nodes[i].diff=0;
      nodes[i].fluv_over_diff=0;
      nodes[i].rel_sedi=0;
      nodes[i].stream_power=0;
      nodes[i].channel_width=channel_width_calc(nodes,i,parameters);
      nodes[i].moved_sediment=0;
      nodes[i].saltabr_incision=0;
      nodes[i].under_taucrit=0;
      nodes[i].river=0;
      nodes[i].diff_erosion=0;
    }

  int indi=1;
  int indi2=0;
  int it_counter=0;

  
  //expli_diffusion_calc_new(nodes,parameters);
  //printf("Her \n");
  //d2_diff(nodes,parameters);
  d2_nonlin_diff(nodes,parameters,&indi2);
  expli_sed_cap_topsed_new(nodes,stack2,nx,ny,parameters,dx,dy);
  
  //update_height(nodes,stack,nx,ny,npits,dx,dy,stack2,it_crit,under_relax_height,flist,s_flist,parameters);
  //expli_update_sed(nodes,stack,nx,ny,dx,dy,stack2,under_relax_sed,parameters);

  parameters[0].deltat=parameters[0].deltat_next_time;

#pragma omp parallel for default(none) private(i) shared(nx,ny,nodes)
  for (i=0;i<nx*ny;i++) {
    nodes[i].upstream_erosion=nodes[i].upstream_erosion_old;
  }
  
  while (indi!=0) {
    
#pragma omp parallel for default(none) private(i) shared(nx,ny,nodes) //if((nx*ny)>(100*100))   
    for (i=0;i<nx*ny;i++) {
    nodes[i].bed_new=nodes[i].bed;
    nodes[i].topsedi_new=nodes[i].topsedi;
    //nodes[i].upstream_erosion=nodes[i].upstream_erosion_old;
  }

    indi=0;
    update_height(nodes,stack,nx,ny,npits,dx,dy,stack2,it_crit,under_relax_height,flist,s_flist,parameters,&indi);
    

    double min_deltat=0.1;
    sediment_transport3(nodes,stack,nx,ny,dx,dy,stack2,npits,parameters,&indi); //This one always uses the new topsedi values

    
  if (indi==1)
      {
	if (parameters[0].deltat/1.1>min_deltat){
	  parameters[0].deltat/=1.1;
	  indi2=1;
	}
	else {
	  parameters[0].deltat=min_deltat;
	  indi=0;
	  indi2=1;
	}
	//printf("Halving deltat \n");
      }

    if (indi2==0) {
      //courant_crit(nodes,parameters,&indi);
      int max_deltat=20;
      if( parameters[0].deltat*1.01<max_deltat)
	parameters[0].deltat_next_time=parameters[0].deltat*1.01;
      else
	parameters[0].deltat_next_time=max_deltat;
    }
    else{
      parameters[0].deltat_next_time=parameters[0].deltat;
    }
    
    //parameters[0].deltat_next_time=1;
    it_counter++;
    //printf("indi %d \n",indi);
}
//save_parameters(nodes,nx,ny,parameters);


#pragma omp parallel for default(none) private(i) shared(nx,ny,nodes) //if((nx*ny)>(100*100))
for (i=0;i<nx*ny;i++) {
nodes[i].sediment_thickness=nodes[i].topsedi_new-nodes[i].bed_new;
//if(nodes[i].sediment_thickness>0.05) printf("Sediment thickness %g fluvial deposition %g \n",nodes[i].sediment_thickness,nodes[i].fluvial_deposition);
nodes[i].bed=nodes[i].bed_new;
nodes[i].topsedi=nodes[i].topsedi_new;
nodes[i].upstream_erosion_old=nodes[i].upstream_erosion;
nodes[i].fluv_over_diff=nodes[i].fluv/(nodes[i].diff+1e-18);
if (nodes[i].in_stack==1 && nodes[i].c>=0)
  {
    nodes[nodes[i].c].catchment_sediment+=nodes[i].sediment_thickness;
    nodes[nodes[i].c].catchment_erosion+=nodes[i].erosion;
    nodes[nodes[i].c].catchment_streampower+=nodes[i].stream_power;
    nodes[nodes[i].c].catchment_saltabr+=nodes[i].saltabr_incision;
    nodes[0].total_sediment+=nodes[i].sediment_thickness;
    nodes[0].total_erosion+=nodes[i].erosion;
    nodes[0].total_streampower+=nodes[i].stream_power;
    nodes[0].total_saltabr+=nodes[i].saltabr_incision;
  }
}
	
	
}



