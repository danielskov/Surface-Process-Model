
/*
  double expli_sed_cap_topsed(nodetype *nodes,long i,model_parameters *parameters,double dx, double dy)
  {
  double sediment_capa;
  int indi=0;
	
  //sediment_capa=parameters[0].K_t*pow(nodes[i].drain_area,(1.5))*pow((nodes[i].topsedi-nodes[nodes[i].r].topsedi)/nodes[i].reciever_distance,1);
	
  //double fluv_trans;
  //double diff_trans;
	
  //printf("whole %g drain_area %g slope %g \n",pow(nodes[i].drain_area,1.0/3)*pow((nodes[i].topsedi-nodes[nodes[i].r].topsedi)/nodes[i].reciever_distance,2.0/3),nodes[i].drain_area,(nodes[i].topsedi-nodes[nodes[i].r].topsedi)/nodes[i].reciever_distance);
  if ((parameters[0].k_tau*pow(nodes[i].drain_area,1.0/3)*pow((nodes[i].topsedi-nodes[nodes[i].r].topsedi)/nodes[i].reciever_distance,2.0/3)-parameters[0].tau_crit)>0)
  {
  sediment_capa=parameters[0].k_sed*pow(nodes[i].drain_area,0.5)*pow(parameters[0].k_tau*pow(nodes[i].drain_area,1.0/3)*pow((nodes[i].topsedi-nodes[nodes[i].r].topsedi)/nodes[i].reciever_distance,2.0/3)-parameters[0].tau_crit,3.0/2);
  //printf("plus %g minus %g \n",parameters[0].k_tau*pow(nodes[i].drain_area,1.0/3)*pow((nodes[i].topsedi-nodes[nodes[i].r].topsedi)/nodes[i].reciever_distance,2.0/3),parameters[0].tau_crit);
  //printf("slope: %g drain_area %g \n",(nodes[i].topsedi-nodes[nodes[i].r].topsedi)/nodes[i].reciever_distance,nodes[i].drain_area);
  nodes[i].river=1;
  }
  else
  {
  indi=1;
  nodes[i].under_taucrit=1;
  nodes[i].river=0;
  //sediment_capa=0;
			
  // if (nodes[i].di>0)
  // {
  // 	sediment_capa=dx*dy*parameters[0].k_diff*pow((-nodes[i].av_donor_height-nodes[nodes[i].r].topsedi+2*nodes[i].topsedi)/(pow((nodes[i].reciever_distance+nodes[i].av_donor_distance)/2,2)),parameters[0].n_diff);
  // }
  // else {
  // 	sediment_capa=dx*dy*parameters[0].k_diff*pow((-2*nodes[nodes[i].r].topsedi+2*nodes[i].topsedi)/(pow(nodes[i].reciever_distance,2)),parameters[0].n_diff);
  // }
  sediment_capa=dx*dy*parameters[0].k_diff*(-nodes[nodes[i].r].topsedi+nodes[i].topsedi)/(nodes[i].reciever_distance);
		
		
		
		
  //sediment_capa=dx*dy*parameters[0].k_diff*pow((nodes[i].topsedi+nodes[nodes[nodes[i].r].r].topsedi-2*nodes[nodes[i].r].topsedi)/(pow(nodes[i].reciever_distance,2)),parameters[0].n_diff);
  //if (sediment_capa<=0) {printf("Det noget pis sed capa %g indi %d \n",sediment_capa,indi); sediment_capa=0; }
  //nodes[i].diff=sediment_capa/(dx*dy);
  //printf("sediment capa: %g i %ld \n",nodes[i].diff,i);
  }
  if (sediment_capa<=0) {printf("Det noget pis sed capa %g indi %d \n",sediment_capa,indi); sediment_capa=0; }
	
	
  //if (indi==1 && sediment_capa>0) printf("Det kan lykkes \n");
	
	

	
  //sediment_capa=fluv_trans+diff_trans;
	
  //These lines are to give an overview, by splitting up the equation. For better perfomance, use the line above and outcomment the lines below.
	
  //double K_t=parameters[0].K_t;
  //double drain_area_w_expo=pow(nodes[i].drain_area,(1.5));
  //double slope=pow((nodes[i].topsedi-nodes[nodes[i].r].topsedi)/nodes[i].reciever_distance,1);
  //sediment_capa=K_t*drain_area_w_expo*slope;
	
  return sediment_capa;
  }
*/



