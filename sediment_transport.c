#include "header.h"


long lowest_donor(nodetype *nodes,long sedi_node)
{
  long i;
  long h=sedi_node;
  double tmp=INT_MAX;
  long tmp_node,lowest_donor;
  tmp_node=-1;
  for (i=0;i<nodes[h].di;i++)
    {
      if (tmp>nodes[nodes[h].Dij[i]].topsedi)
	{
	  tmp=nodes[nodes[h].Dij[i]].topsedi;
	  tmp_node=nodes[h].Dij[i];
	}
    }
  if (nodes[h].di==0 || tmp_node==-1) {tmp_node=0; printf("problemer i lowest donor script \n"); exit(1);}
  lowest_donor=tmp_node;
  return lowest_donor;
}


long lowest_neighbour_above_new(nodetype *nodes,long sedi_node)
{
  long i;
  long h=sedi_node;
  double tmp=INT_MAX;
  long tmp_node,lowest_above_neigh;
  tmp_node=-1;
  for (i=0;i<nodes[h].n_neigh;i++)
    {
      if (tmp>nodes[nodes[h].neigh[i]].topsedi && nodes[nodes[h].neigh[i]].topsedi>nodes[h].topsedi)
	{
	  tmp=nodes[nodes[h].neigh[i]].topsedi;
	  tmp_node=nodes[h].neigh[i];
	}
    }
  if (tmp_node==-1) {printf("Problem in lowest neighbour above new \n"); exit(1);}
  lowest_above_neigh=tmp_node;
  return lowest_above_neigh;
}

void alluviate(nodetype *nodes,long *stack,long h,double deposition,long u,model_parameters *parameters)
{
  long g,i;
  double topsedi;
  double small_factor; //This is the height below the donor node that cannot be alluviated over

  /*
    ++u; u=2;
    if (u==1) {topsedi=nodes[h].topsedi;}
    //This is done because the alluviating firstly moved downstream, thus updating the topsedi. We should thus only use the old topsedi for the first node
    else {topsedi=nodes[h].topsedi;}
  */
	
  topsedi=nodes[h].topsedi;
	
  if (nodes[h].di==0) {nodes[h].topsedi+=deposition; if (deposition>2000) {printf("Large deposition on hilltope, %4.2f \n",deposition);}/*printf("u% ld deposition: %5.2f topsedi before %6.2f, topsedi now %6.2f upstream erosion %5.2f, sediment capa %5.2f erosion %5.2f \n",u,deposition,nodes[h].topsedi,nodes[h].topsedi,nodes[h].upstream_erosion*2,nodes[h].sediment_capa_sedi*2,nodes[h].erosion*2);*/}
  else {
    g=lowest_donor(nodes,h); /*I'm using the lowest donor, and not just the lowest neighbour, to avoid mixing sediments from different catchmetns*/
    small_factor=parameters[0].sedimentation_angle*nodes[g].reciever_distance; /*The sedimentation angle reflects the maximum angle the deposits can have, in [meters/meter]*/
    //g=lowest_neighbour_above_new(nodes,h);
    if ((topsedi+deposition)<(nodes[g].topsedi-small_factor)) {
      nodes[h].topsedi=topsedi+deposition;
      nodes[h].fluvial_deposition=deposition;
      deposition=0;
      for (i=0;i<nodes[h].di;i++) {if (nodes[h].topsedi>nodes[nodes[h].Dij[i]].topsedi) {printf("u: %ld deposition %4.3f, di: %ld g: %ld Dij: %ld \n ",u,deposition,nodes[h].di,g,nodes[h].Dij[i]); printf("node: %ld, donor: %ld, n_donors %ld, node height new %8.4f, node h before %8.4f, donor h %8.4f, Dij h %8.4f \n",h,g,nodes[h].di,nodes[h].topsedi,nodes[h].topsedi,nodes[g].topsedi,nodes[nodes[h].Dij[i]].topsedi);
	  exit(1);}}
    }
    else if ((topsedi)>(nodes[g].topsedi-small_factor)){
      if (topsedi>(nodes[g].topsedi)) printf("Problemer i alluviate 1, topsedi %6.4f u: %ld ts n %6.4f g h %6.4f g old %6.4f \n",topsedi,u,nodes[h].topsedi,nodes[g].topsedi,nodes[g].topsedi);
      //printf("node: %ld, donor: %ld, n_donors %ld \n",h,g,nodes[h].di);
      alluviate(nodes,stack,g,deposition,u,parameters);
    }
    else {
      deposition-=(nodes[g].topsedi-small_factor-topsedi);
      nodes[h].fluvial_deposition=(nodes[g].topsedi-small_factor-topsedi);
      //printf("h %ld ,depo %5.3f \n ",h,nodes[h].fluvial_deposition);
      nodes[h].topsedi=nodes[g].topsedi-small_factor;
      for (i=0;i<nodes[h].di;i++) {if (nodes[h].topsedi>nodes[nodes[h].Dij[i]].topsedi) printf("Problemer i alluviate 2 \n");}
      alluviate(nodes,stack,g,deposition,u,parameters);
    }
  }	
}
//The alluviate function has been made so that the alluviation will continuisly go up a distinct catchment. This function should be improved, so that the sediment would deposit in the overall lowest neighbour upstream from the initially alluviating node



long lowest_donor2(nodetype *nodes,long sedi_node)
{
  long i;
  long h=sedi_node;
  double tmp=INT_MAX;
  long tmp_node,lowest_donor;
  tmp_node=-1;
  for (i=0;i<nodes[h].di;i++)
    {
      if (tmp>nodes[nodes[h].Dij[i]].topsedi_new && nodes[h].Dij[i]!=h) //The first term finds if the node is below the current lowest node. The second node makes sure that the node is not itself.
	{
	  tmp=nodes[nodes[h].Dij[i]].topsedi_new;
	  tmp_node=nodes[h].Dij[i];
	}
    }
	
	
	
   
  if (nodes[h].di==0 || tmp_node==-1) {
    printf("problemer i lowest donor script i %ld reciever %ld number donors %ld height %g pit? %ld tmp_node %ld  \n",h,nodes[h].r,nodes[h].di,nodes[h].topsedi_new,nodes[h].p,tmp_node);

    for (i=0;i<nodes[h].di;i++) {printf("donor[i]=%ld donor[i].topsedi=%g \n",nodes[h].Dij[i],nodes[nodes[h].Dij[i]].topsedi_new);}
		
    tmp=INT_MAX;
    tmp_node=-1;
    for (i=0;i<nodes[h].di;i++)
      {
	printf("tmp %g donor topsedi %g donor %ld  sedinode %ld \n",tmp,nodes[nodes[h].Dij[i]].topsedi_new,nodes[h].Dij[i],h);
	if (tmp>nodes[nodes[h].Dij[i]].topsedi_new && nodes[h].Dij[i]!=h) //The first term finds if the node is below the current lowest node. The second node makes sure that the node is not itself.
	  {
	    printf("INSIDE \n\n\n");
	    tmp=nodes[nodes[h].Dij[i]].topsedi_new;
	    tmp_node=nodes[h].Dij[i];
	  }
      }
		
    exit(1);}
  lowest_donor=tmp_node;
  return lowest_donor;
}



void alluviate2(nodetype *nodes,long *stack,long h,double deposition,long u,model_parameters *parameters) //The alluviate2 function works on topsedi_new instead of topsedi. This means that the alluviation will have an actual effect, as 
{
  long g,i;
  double topsedi;
  double small_factor; //This is the height below the donor node that cannot be alluviated over

  /*
    ++u; u=2;
    if (u==1) {topsedi=nodes[h].topsedi;}
    //This is done because the alluviating firstly moved downstream, thus updating the topsedi. We should thus only use the old topsedi for the first node
    else {topsedi=nodes[h].topsedi;}
  */
  u++;
  //if (u>1) printf("u %ld depo %g \n",u,deposition);
	
  topsedi=nodes[h].topsedi_new;
	
  if (nodes[h].di==0) {nodes[h].topsedi_new+=deposition; if (deposition>2) {printf("Large deposition on hilltope, %g node %ld \n",deposition,h);} deposition=0; /*printf("u% ld deposition: %5.2f topsedi before %6.2f, topsedi now %6.2f upstream erosion %5.2f, sediment capa %5.2f erosion %5.2f \n",u,deposition,nodes[h].topsedi,nodes[h].topsedi,nodes[h].upstream_erosion*2,nodes[h].sediment_capa_sedi*2,nodes[h].erosion*2);*/}
  else {
   g=lowest_donor2(nodes,h); /*I'm using the lowest donor, and not just the lowest neighbour, to avoid mixing sediments from different catchmetns*/
    small_factor=parameters[0].sedimentation_angle*nodes[g].reciever_distance; /*The sedimentation angle reflects the maximum angle the deposits can have, in [meters/meter]*/
    //g=lowest_neighbour_above_new(nodes,h);
    if ((topsedi+deposition)<(nodes[g].topsedi_new-small_factor)) {
      nodes[h].topsedi_new=topsedi+deposition;
      nodes[h].fluvial_deposition=deposition;
      deposition=0;
      for (i=0;i<nodes[h].di;i++) {if (nodes[h].topsedi_new>nodes[nodes[h].Dij[i]].topsedi_new) {printf("u: %ld deposition %4.3f, di: %ld g: %ld Dij: %ld \n ",u,deposition,nodes[h].di,g,nodes[h].Dij[i]); printf("node: %ld, donor: %ld, n_donors %ld, node height new %8.4f, node h before %8.4f, donor h %8.4f, Dij h %8.4f \n",h,g,nodes[h].di,nodes[h].topsedi_new,nodes[h].topsedi,nodes[g].topsedi_new,nodes[nodes[h].Dij[i]].topsedi_new);
	  exit(1);}}
    }
    else if ((topsedi)>(nodes[g].topsedi_new-small_factor)){
      if (topsedi>(nodes[g].topsedi_new)) printf("Problemer i alluviate 1, node %ld donor %ld ts n %6.4f g h %6.4f \n",h,g,nodes[h].topsedi_new,nodes[g].topsedi_new);
      //printf("node: %ld, donor: %ld, n_donors %ld \n",h,g,nodes[h].di);
      alluviate2(nodes,stack,g,deposition,u,parameters);
    }
    else {
      deposition-=(nodes[g].topsedi_new-small_factor-topsedi);
      nodes[h].fluvial_deposition=(nodes[g].topsedi_new-small_factor-topsedi);
      //printf("h %ld ,depo %5.3f \n ",h,nodes[h].fluvial_deposition);
      nodes[h].topsedi_new=nodes[g].topsedi_new-small_factor;
      for (i=0;i<nodes[h].di;i++) {if (nodes[h].topsedi_new>nodes[nodes[h].Dij[i]].topsedi_new) printf("Problemer i alluviate 2 \n");}
      alluviate2(nodes,stack,g,deposition,u,parameters);
    }
  }	
}
//The alluviate function has been made so that the alluviation will continuisly go up a distinct catchment. This function should be improved, so that the sediment would deposit in the overall lowest neighbour upstream from the initially alluviating node




void sediment_transport2(nodetype *nodes,long *stack,long nx,long ny,double dx,double dy,long *stack2,long npits,model_parameters *parameters,int *indi)
{		
  long i;
  long h; //The current position in the inversed stack, that is stack2
  double deposition;
  double lower_boundary;
  //char do_fluvial_deposition='n';
	
  //if (npits!=0) {do_deposition='n';}
  long u;
	
	
  for (i=0;i<nx*ny;i++) 
    {
      nodes[i].upstream_erosion_old=nodes[i].upstream_erosion;
      nodes[i].upstream_erosion=nodes[i].erosion;
      nodes[i].fluvial_deposition=0;
    }
		
		
		
	
  for (i=0;i<nx*ny;i++) //Looping through the nodes
    {
      h=stack2[i];
      if (nodes[h].r!=h && nodes[h].in_stack==1 && nodes[h].b!=1 && nodes[h].c>=0) //Only nodes that are in the stack and are not pits or baselevel nodes are looped
	{
	  if ((nodes[h].topsedi_new+parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy))>nodes[h].bed_new && (nodes[h].topsedi_new+parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy))>nodes[nodes[h].r].topsedi_new) //If the erosion or deposition doesn't lower the top of the sediment below the top of the bedrock
	    {
	      if (parameters[0].do_fluvial_deposition=='n' && nodes[h].river==1) { //This is when we have no fluvial deposition
		if (nodes[h].upstream_erosion<nodes[h].sediment_capa_sedi) //If the sediment capacity is larger than the upstream erosion we pick up sediment
		  {
		    nodes[h].topsedi_new=nodes[h].topsedi_new+parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy); //The top of the sediment pile is lowered by the difference between sediment capacity and  the upstream erosion
		    nodes[h].moved_sediment=-(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy); //The amount of sediment that is picked up in the node is calculated as the difference between the amount of sediment in the stream (upstream erosion) before and after picking up the sediment
		    nodes[h].upstream_erosion=nodes[h].sediment_capa_sedi; //The upstream erosion is set to sediment capacity, as it is moving sediment on full capacity
		    if (nodes[h].upstream_erosion>nodes[h].sediment_capa_sedi) {nodes[h].upstream_erosion=nodes[h].sediment_capa_sedi;} //This should never happen, as we just assign upstream erosion to be equal to the sediment capacity just one line above
		  }
		else { //If the amount of sediment entering the node equals or exceeds the carriyng capacity, and there is no deposition, no sediment is picked up, and the sediment entering the node just passes on to the next node.
		  //nodes[h].upstream_erosion+=nodes[h].topsedi_new+parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy);
		  nodes[h].moved_sediment=0; //The moved sediment is assigned to zero, as zero sediment is picked up in the node.
		}
	      }
	      else if (parameters[0].do_fluvial_deposition=='y' || nodes[h].river==0){ //This is when we have fluvial deposition
		if (nodes[h].upstream_erosion<=nodes[h].sediment_capa_sedi) //Handles the case where we have erosion to above the bedrock level
		  {
		    nodes[h].topsedi_new=nodes[h].topsedi_new+parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy); //The top of the sediment pile is lowered by the difference between sediment capacity and the upstream erosion
		    nodes[h].moved_sediment=-(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy); //The amount of sediment that is picked up in the node is calculated as the difference between the amount of sediment in the stream (upstream erosion) before and after picking up the sediment
		    nodes[h].upstream_erosion=nodes[h].sediment_capa_sedi; //The upstream erosion is set to sediment capacity, as it is moving sediment on full capacity
		    if (nodes[h].topsedi_new>nodes[h].topsedi) {printf("Den går da opad i deposit \n");}
		    //printf("Formentlig mest her \n");
		  }
		else //Handles the case where we have deposition
		  {
		    u=0;
		    deposition=parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy); //Calculates the height of the pile of sediment that has to be deposited
		    //printf("deposition: %8.3f \n",deposition);
		    nodes[h].moved_sediment=0;
		    nodes[h].upstream_erosion=nodes[h].sediment_capa_sedi;
		    //printf("tit her? deposition %g \n",deposition);
		    alluviate2(nodes,stack,h,deposition,u,parameters);
		    if (nodes[h].topsedi_new<nodes[h].bed_new) {nodes[h].topsedi_new=nodes[h].bed_new; printf("Alluvial Sediment transport, bed above topsedi \n");}
						
		  }
	      }
	      else {
		printf("Wrong allocation of do_fluvial_deposition parameter. Should be either 'y' or 'n'. This error message is in sediment_transport2 function\n"); exit(1);
	      }
				
	    }
	  else if ((nodes[h].topsedi_new+parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy))<=nodes[h].bed_new ||
		   (nodes[h].topsedi_new+parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy))<=nodes[nodes[h].r].topsedi_new) //Used when the erosion will remove all sediment in the node
	    {
				
				
	      if (nodes[h].bed_new<=nodes[nodes[h].r].topsedi_new) {
		lower_boundary=nodes[nodes[h].r].topsedi_new+1e-1; 
		if (lower_boundary>nodes[h].topsedi_new) {
		  lower_boundary=nodes[nodes[h].r].topsedi_new+1e-2;} 
		if (lower_boundary>nodes[h].topsedi_new) {
		  lower_boundary=(nodes[nodes[h].r].topsedi_new+nodes[h].topsedi_new)/2; printf("Lower boundary problem, sediment_transport \n"); /* printf("Lower boundary for sediment transport is low node %ld sediment_thickness %g drainage network %ld sediment capa %g drain area %g topsedi %g r_topsedi %g \n",h,nodes[h].sediment_thickness,nodes[h].c,nodes[h].sediment_capa_sedi,nodes[h].drain_area/(500.0*500.),nodes[h].topsedi,nodes[nodes[h].r].topsedi); */}
		(*indi)=1;
	      }
	      else {lower_boundary=nodes[h].bed_new;}
				
				
	      //lower_boundary=nodes[h].bed_new;
				
				
	      if (lower_boundary==0) {lower_boundary=(nodes[nodes[h].r].topsedi_new+nodes[h].topsedi_new)/2; printf("lower boundary problem 2");} //The lower boundary thus becomes the mean of the nodes height and the recievers height
	      nodes[h].upstream_erosion=nodes[h].upstream_erosion+(nodes[h].topsedi_new-lower_boundary)*dx*dy/parameters[0].deltat;
							
	      nodes[h].topsedi_new=lower_boundary;
	      nodes[h].moved_sediment=(nodes[h].topsedi-nodes[h].topsedi_new)/parameters[0].deltat;
	      //if (nodes[h].topsedi_new>nodes[h].topsedi) {printf("Den går da opad sed trans indi %ld i: h %ld low_bound %4.2f \n",indi,h,lower_boundary);}
	      if (nodes[h].topsedi_new<nodes[h].bed_new) {nodes[h].topsedi_new=nodes[h].bed_new; printf("Other Sediment transport, bed above topsedi \n");}
						
	    }
	  else
	    {
	      printf("MAYOR ALERT \n");
	      exit(1);
	    }
	  if (nodes[h].topsedi_new<nodes[h].bed_new) {nodes[h].topsedi_new=nodes[h].bed_new; printf("Sediment transport, bed above topsedi \n");}
			
			
	  if (nodes[h].upstream_erosion<0) {printf("Sediment transport, Upstream erosion below zero, nodes[%ld].upstream_erosion=%g \n",h,nodes[h].upstream_erosion); nodes[h].upstream_erosion=0; }
			
	  nodes[nodes[h].r].upstream_erosion=nodes[nodes[h].r].upstream_erosion+nodes[h].upstream_erosion;
			
	  if (nodes[h].sediment_capa_sedi!=0) {
	    nodes[h].rel_sedi=(nodes[h].upstream_erosion/(nodes[h].sediment_capa_sedi));
	  }
	  else {
	    nodes[h].rel_sedi=1;
	  }
		
		//printf("upstream erosion %g \n",nodes[h].upstream_erosion);
			
	  if (nodes[h].river==0) {nodes[h].diff=nodes[h].moved_sediment;}
			
	  //nodes[h].sediment_thickness=nodes[h].topsedi_new-nodes[h].bed_new;
	}
    }
  //exit(1);
}
/*topsedi new is used everywhere in this function as we are now starting after the point where the incision has happened*/




void sediment_transport3(nodetype *nodes,long *stack,long nx,long ny,double dx,double dy,long *stack2,long npits,model_parameters *parameters,int *indi)
{		
  long i;
  long h; //The current position in the inversed stack, that is stack2
  double deposition;
  double lower_boundary;
  //char do_fluvial_deposition='n';
	
  //if (npits!=0) {do_deposition='n';}
  //long u;
  int g;
	
  for (i=0;i<nx*ny;i++) 
    {
      nodes[i].upstream_erosion=nodes[i].erosion;
      nodes[i].fluvial_deposition=0;
    }
		
		
		
	
  for (i=0;i<nx*ny;i++) //Looping through the nodes
    {
      h=stack2[i];
      if (nodes[h].r!=h && nodes[h].in_stack==1 && nodes[h].b!=1 && nodes[h].c>=0) //Only nodes that are in the stack and are not pits or baselevel nodes are looped
	{
	  if ((nodes[h].topsedi_new+parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy))>nodes[h].bed_new && (nodes[h].topsedi_new+parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy))>nodes[nodes[h].r].topsedi_new) //If the erosion or deposition doesn't lower the top of the sediment below the top of the bedrock
	    {
	      if (parameters[0].do_fluvial_deposition=='n' && nodes[h].river==1) { //This is when we have no fluvial deposition
		if (nodes[h].upstream_erosion<nodes[h].sediment_capa_sedi) //If the sediment capacity is larger than the upstream erosion we pick up sediment
		  {
		    nodes[h].topsedi_new=nodes[h].topsedi_new+parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy); //The top of the sediment pile is lowered by the difference between sediment capacity and  the upstream erosion
		    nodes[h].moved_sediment=-(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy); //The amount of sediment that is picked up in the node is calculated as the difference between the amount of sediment in the stream (upstream erosion) before and after picking up the sediment
		    nodes[h].upstream_erosion=nodes[h].sediment_capa_sedi; //The upstream erosion is set to sediment capacity, as it is moving sediment on full capacity
		    if (nodes[h].upstream_erosion>nodes[h].sediment_capa_sedi) {nodes[h].upstream_erosion=nodes[h].sediment_capa_sedi;} //This should never happen, as we just assign upstream erosion to be equal to the sediment capacity just one line above
		  }
		else { //If the amount of sediment entering the node equals or exceeds the carriyng capacity, and there is no deposition, no sediment is picked up, and the sediment entering the node just passes on to the next node.
		  //nodes[h].upstream_erosion+=nodes[h].topsedi_new+parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy);
		  nodes[h].moved_sediment=0; //The moved sediment is assigned to zero, as zero sediment is picked up in the node.
		}
	      }
	      else if (parameters[0].do_fluvial_deposition=='y' || nodes[h].river==0){ //This is when we have fluvial deposition
		if (nodes[h].upstream_erosion<=nodes[h].sediment_capa_sedi) //Handles the case where we have erosion to above the bedrock level
		  {
		    nodes[h].topsedi_new=nodes[h].topsedi_new+parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy); //The top of the sediment pile is lowered by the difference between sediment capacity and the upstream erosion
		    nodes[h].moved_sediment=-(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy); //The amount of sediment that is picked up in the node is calculated as the difference between the amount of sediment in the stream (upstream erosion) before and after picking up the sediment
		    nodes[h].upstream_erosion=nodes[h].sediment_capa_sedi; //The upstream erosion is set to sediment capacity, as it is moving sediment on full capacity
		    if (nodes[h].topsedi_new>nodes[h].topsedi) {printf("Den går da opad i deposit \n");}
		    //printf("Formentlig mest her \n");
		  }
		else //Handles the case where we have deposition
		  {
		    //u=0;
		    deposition=parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy); //Calculates the height of the pile of sediment that has to be deposited
		    //printf("deposition: %8.3f \n",deposition);

		    //printf("node %ld sediment capa %g upstream_erosion %g donors %ld deposition %g \n",h,nodes[h].sediment_capa_sedi,nodes[h].upstream_erosion,nodes[h].di,deposition);

		    if (deposition/parameters[0].deltat>5)
		      {
			printf("large deposition %g deltat %g úpstream erosion %g sedicapa %g dx %g dy %g deltat %g \n",deposition,parameters[0].deltat,nodes[h].upstream_erosion,nodes[h].sediment_capa_sedi,dx,dy,parameters[0].deltat);
			(*indi)=1;
		      }
		    
		    if (nodes[h].di>0) {
		    g=lowest_donor2(nodes,h);
		    }
		    else {
		      g=h;
		    }

		    double min_factor=1e-5; //The height below the lowest donor that the node can maximally deposit to
		    if ((nodes[h].topsedi_new+deposition)<(nodes[g].topsedi_new-min_factor) && nodes[h].topsedi_new<(nodes[g].topsedi_new-min_factor)) {
		      nodes[h].topsedi_new+=deposition;
		      nodes[h].upstream_erosion=nodes[h].sediment_capa_sedi;
		    }
		    else if (nodes[h].topsedi_new>(nodes[g].topsedi_new-min_factor))
		      {
			//printf("2 \n");
		      }
		    else {
		      deposition=nodes[g].topsedi_new-min_factor-nodes[h].topsedi_new;
		      nodes[h].upstream_erosion-=deposition*dx*dy/parameters[0].deltat;
		      nodes[h].topsedi_new=nodes[g].topsedi_new-min_factor;
		      //printf("3 \n");
		      //printf("large deposition %g deltat %g úpstream erosion %g sedicapa %g dx %g dy %g deltat %g \n",deposition,parameters[0].deltat,nodes[h].upstream_erosion,nodes[h].sediment_capa_sedi,dx,dy,parameters[0].deltat);
		      (*indi)=1;
		    }
			 

		    nodes[h].moved_sediment=0;
		    //nodes[h].upstream_erosion=nodes[h].sediment_capa_sedi;
		    //printf("tit her? deposition %g \n",deposition);
		    //alluviate2(nodes,stack,h,deposition,u,parameters);
		    if (nodes[h].topsedi_new<nodes[h].bed_new) {nodes[h].topsedi_new=nodes[h].bed_new; printf("Alluvial Sediment transport, bed above topsedi \n");}
						
		  }
	      }
	      else {
		printf("Wrong allocation of do_fluvial_deposition parameter. Should be either 'y' or 'n'. This error message is in sediment_transport2 function\n"); exit(1);
	      }
				
	    }
	  else if ((nodes[h].topsedi_new+parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy))<=nodes[h].bed_new ||
		   (nodes[h].topsedi_new+parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy))<=nodes[nodes[h].r].topsedi_new) //Used when the erosion will remove all sediment in the node
	    {
				
				
	      if (nodes[h].bed_new<=nodes[nodes[h].r].topsedi_new) {
		lower_boundary=nodes[nodes[h].r].topsedi_new+1e-1; 
		if (lower_boundary>nodes[h].topsedi_new) {
		  lower_boundary=nodes[nodes[h].r].topsedi_new+1e-2;} 
		if (lower_boundary>nodes[h].topsedi_new) {
		  lower_boundary=(nodes[nodes[h].r].topsedi_new+nodes[h].topsedi_new)/2; printf("Lower boundary problem, sediment_transport \n"); /* printf("Lower boundary for sediment transport is low node %ld sediment_thickness %g drainage network %ld sediment capa %g drain area %g topsedi %g r_topsedi %g \n",h,nodes[h].sediment_thickness,nodes[h].c,nodes[h].sediment_capa_sedi,nodes[h].drain_area/(500.0*500.),nodes[h].topsedi,nodes[nodes[h].r].topsedi); */}
		(*indi)=1;
	      }
	      else {lower_boundary=nodes[h].bed_new;}
				
				
	      //lower_boundary=nodes[h].bed_new;
				
				
	      if (lower_boundary==0) {lower_boundary=(nodes[nodes[h].r].topsedi_new+nodes[h].topsedi_new)/2; printf("lower boundary problem 2");} //The lower boundary thus becomes the mean of the nodes height and the recievers height
	      nodes[h].upstream_erosion=nodes[h].upstream_erosion+(nodes[h].topsedi_new-lower_boundary)*dx*dy/parameters[0].deltat;
							
	      nodes[h].topsedi_new=lower_boundary;
	      nodes[h].moved_sediment=(nodes[h].topsedi-nodes[h].topsedi_new)/parameters[0].deltat;
	      //if (nodes[h].topsedi_new>nodes[h].topsedi) {printf("Den går da opad sed trans indi %ld i: h %ld low_bound %4.2f \n",indi,h,lower_boundary);}
	      if (nodes[h].topsedi_new<nodes[h].bed_new) {nodes[h].topsedi_new=nodes[h].bed_new; printf("Other Sediment transport, bed above topsedi \n");}
						
	    }
	  else
	    {
	      printf("MAYOR ALERT \n");
	      exit(1);
	    }
	  if (nodes[h].topsedi_new<nodes[h].bed_new) {nodes[h].topsedi_new=nodes[h].bed_new; printf("Sediment transport, bed above topsedi \n");}
			
			
	  if (nodes[h].upstream_erosion<0) {printf("Sediment transport, Upstream erosion below zero, nodes[%ld].upstream_erosion=%g \n",h,nodes[h].upstream_erosion); nodes[h].upstream_erosion=0; }
			
	  nodes[nodes[h].r].upstream_erosion=nodes[nodes[h].r].upstream_erosion+nodes[h].upstream_erosion;
			
	  if (nodes[h].sediment_capa_sedi!=0) {
	    nodes[h].rel_sedi=(nodes[h].upstream_erosion_old/(nodes[h].sediment_capa_sedi));
	  }
	  else {
	    nodes[h].rel_sedi=1;
	  }
		
		//printf("upstream erosion %g \n",nodes[h].upstream_erosion);
			
	  if (nodes[h].river==0) {nodes[h].diff=nodes[h].moved_sediment;}
			
	  //nodes[h].sediment_thickness=nodes[h].topsedi_new-nodes[h].bed_new;
	}
    }
  //exit(1);



}
/*topsedi new is used everywhere in this function as we are now starting after the point where the incision has happened*/





double expli_update_sed(nodetype *nodes,long *stack,long nx,long ny,double dx,double dy,long *stack2,double under_relax_sed,model_parameters *parameters)
{		
  long i;
  long h; //The current position in the inversed stack, that is stack2
  double new_sed=0;
  double lower_boundary;
  double new_sediment=0;
	
#pragma omp parallel for default(none) shared(nodes,nx,ny) private(i) //if((nx*ny)>(100*100))
  for (i=0;i<nx*ny;i++) {
    nodes[i].upstream_erosion_old=nodes[i].upstream_erosion;
    nodes[i].upstream_erosion=nodes[i].erosion;
  }
  //#pragma omp parallel for default(none) shared(nodes,nx,ny) private(i) //if((nx*ny)>(100*100))
  for (i=0;i<nx*ny;i++) //Looping through the nodes
    {
		
      h=stack2[i]; //We are using stack 2, as we are summing up the sediment from the top of the hills all the way to the baselevel nodes.
		
      if (nodes[h].r!=h && nodes[h].in_stack==1 && nodes[h].b!=1 && nodes[h].c>=0) //Only nodes that are in the stack and are not pits or baselevel nodes are looped
	{
	  if ((nodes[h].topsedi+parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy))>nodes[h].bed && 
	      (nodes[h].topsedi+parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy))>nodes[nodes[h].r].topsedi) //If the erosion or deposition doesn't lower the top of the sediment below the top of the bedrock
	    {		
	      if (nodes[h].upstream_erosion<nodes[h].sediment_capa_sedi) //Picking up sediment
		{
		  //					nodes[h].topsedi=nodes[h].topsedi+parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy);
		  //nodes[h].upstream_erosion=nodes[h].sediment_capa_sedi;
		  new_sediment=nodes[h].sediment_capa_sedi;
		}
	      else { /*This is where the deposition is in the transport_sediment function*/
		//nodes[h].upstream_erosion=nodes[h].sediment_capa_sedi;
					
		switch (parameters[0].do_fluvial_deposition)
		  {
		  case 'y':
		    new_sediment=nodes[h].sediment_capa_sedi;
		    break;
		  case 'n':
		    if (nodes[h].river==1) {
		      new_sediment=nodes[h].upstream_erosion;
		    }
		    else {
		      new_sediment=nodes[h].sediment_capa_sedi;
		    }
		    break;
		  }
		if (nodes[h].upstream_erosion<0) {nodes[h].upstream_erosion=0; new_sediment=0;}
	      }
	    }
	  else if ((nodes[h].topsedi+parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy))<=nodes[h].bed ||
		   (nodes[h].topsedi+parameters[0].deltat*(nodes[h].upstream_erosion-nodes[h].sediment_capa_sedi)/(dx*dy))<=nodes[nodes[h].r].topsedi) //Used when the erosion will remove all sediment in the node
	    {
	      if (nodes[h].bed<nodes[nodes[h].r].topsedi)
		{
		  if (nodes[h].bed<nodes[nodes[h].r].topsedi) {
		    lower_boundary=nodes[nodes[h].r].topsedi+1e-1; } 
		  if (lower_boundary>nodes[h].topsedi) {
		    lower_boundary=nodes[nodes[h].r].topsedi+1e-2;} 
		  if (lower_boundary>nodes[h].topsedi) {
		    lower_boundary=(nodes[nodes[h].r].topsedi+nodes[h].topsedi)/2;  /*printf("her\n");*/}
		}
	      else {lower_boundary=nodes[h].bed;}
	      //nodes[h].upstream_erosion=nodes[h].upstream_erosion+(nodes[h].topsedi-lower_boundary)*dx*dy/parameters[0].deltat;
	      new_sediment=nodes[h].upstream_erosion+(nodes[h].topsedi-lower_boundary)*dx*dy/parameters[0].deltat;
	      //				nodes[h].topsedi=lower_boundary;
	    }
	  else
	    {
	      new_sediment=0;
	      printf("MAYOR ALERT \n");
	      exit(1);
	    }
			
	  nodes[h].upstream_erosion=under_relax_sed*new_sediment+(1-under_relax_sed)*nodes[h].upstream_erosion_old;
						
	  if (nodes[h].upstream_erosion<0) {nodes[h].upstream_erosion=0;}

	  nodes[nodes[h].r].upstream_erosion=nodes[nodes[h].r].upstream_erosion+nodes[h].upstream_erosion;
	}
    }
	
#pragma omp parallel for default(none) shared(nx,ny,nodes) private(i) reduction(+:new_sed)	
  for (i=0;i<nx*ny;i++) {new_sed+=fabs(nodes[i].upstream_erosion);}
  new_sed*=parameters[0].deltat/dx*dy;
  return new_sed;

}
