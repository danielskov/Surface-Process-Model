#include "header.h"

double expli_diffusion_calc(nodetype *nodes,long j,double node_height,model_parameters *parameters)
{
  double diffusion;
	
  double S_c=tan(30*M_PI/180);
  double lineratization_start=0.99;
  double diff_parameters=0.0000694557; 
  diff_parameters=parameters[0].k_diff;
  //The diffusion parameter has been chosen as 0.0000694557 such that a hillslope with an angle of S_c=tan(30*M_PI/180) has a diffusion of 4e-3 m/year*dx*dy
  //printf("%g  %g \n",S_c,tan(30*M_PI/180));
		
  if (nodes[j].di<0) {
    //diffusion=parameters[0].k_diff*(-nodes[j].av_donor_height-nodes[nodes[j].r].topsedi+2*node_height)/(pow((nodes[j].av_donor_distance+nodes[j].reciever_distance)/2,2));
    if (nodes[j].reciever_slope<lineratization_start*S_c) {
      diffusion=(diff_parameters)*nodes[j].reciever_slope/(1-(fabs(nodes[j].reciever_slope)/S_c)*(fabs(nodes[j].reciever_slope)/S_c));
    }
    else if(nodes[j].reciever_slope>=lineratization_start*S_c && nodes[j].reciever_slope<S_c)
      {
	diffusion=(diff_parameters)*lineratization_start*S_c/(1-(lineratization_start)*(lineratization_start))+diff_parameters*S_c*S_c*(S_c*S_c+(lineratization_start*S_c)*(lineratization_start*S_c))/((lineratization_start*S_c*lineratization_start*S_c-S_c*S_c)*(lineratization_start*S_c*lineratization_start*S_c-S_c*S_c))*(nodes[j].reciever_slope-lineratization_start*S_c);
	//This linerization when the slope is above lineratization_start is to ensure stability. The derivation of the equation KS_c^2(S_c^2+S^2)/(S^2-S_c^2)^2 can be found in a Latex document in a subsection named "Derivation of linerization of non-linear diffusion"
      }
    else {
      diffusion=(nodes[j].topsedi-(S_c*nodes[j].reciever_distance+nodes[nodes[j].r].topsedi))*(parameters[0].dx*parameters[0].dy);
    }
  }
  else {
    //diffusion=parameters[0].k_diff*(-2*nodes[nodes[j].r].topsedi+2*node_height)/(pow(nodes[j].reciever_distance,2));
    if (nodes[j].reciever_slope<lineratization_start*S_c) {
      diffusion=(diff_parameters)*nodes[j].reciever_slope/(1-(fabs(nodes[j].reciever_slope)/S_c)*(fabs(nodes[j].reciever_slope)/S_c));
      //printf("Ellers %g \n",diffusion);
      //if (diffusion>3000) printf("large diffusion %g \n\n",diffusion);
    }
    else if(nodes[j].reciever_slope>=lineratization_start*S_c && nodes[j].reciever_slope<2e8*S_c)
      {
	diffusion=(diff_parameters)*lineratization_start*S_c/(1-(lineratization_start)*(lineratization_start))+(nodes[j].reciever_slope-lineratization_start*S_c)*diff_parameters*S_c*S_c*(S_c*S_c+(lineratization_start*S_c)*(lineratization_start*S_c))/((lineratization_start*S_c*lineratization_start*S_c-S_c*S_c)*(lineratization_start*S_c*lineratization_start*S_c-S_c*S_c));
	//This linerization when the slope is above lineratization_start is to ensure stability. The derivation of the equation KS_c^2(S_c^2+S^2)/(S^2-S_c^2)^2 can be found in a Latex document in a subsection named "Derivation of linerization of non-linear diffusion"
      }
    else {
      diffusion=(nodes[j].topsedi-(S_c*nodes[j].reciever_distance+nodes[nodes[j].r].topsedi));
      printf("Diffusion Calc Very High %g topsedi %g reciveer topsedi %g S_c*distance %g diffusion in meters %g \n",diffusion,nodes[j].topsedi,nodes[nodes[j].r].topsedi,S_c*nodes[j].reciever_distance,(nodes[j].topsedi-(S_c*nodes[j].reciever_distance+nodes[nodes[j].r].topsedi)));
    }
  }
	
	
  if (diffusion<0) diffusion=0;
  nodes[j].diff=diffusion;
	
  //printf("Diffusion %g \n",diffusion);
	
  diffusion*=parameters[0].dx*parameters[0].dy;
	
	
  /*
    double i;
    double slope;
    int indi=0;
    for (i=0;i<1000;i++) {
    slope=(i/1000.0)*(S_c+0.1);
    if (slope<lineratization_start*S_c) {
    diffusion=(diff_parameters)*slope/(1-(fabs(slope)/S_c)*(fabs(slope)/S_c));
    //printf("Ellers %g \n",diffusion);
    //printf("large diffusion %g \n\n",diffusion);
    indi=1;
    }
    else if(slope>=lineratization_start*S_c && slope<2*S_c)
    {
    diffusion=(diff_parameters)*lineratization_start*S_c/(1-(lineratization_start)*(lineratization_start))+(slope-lineratization_start*S_c)*diff_parameters*S_c*S_c*(S_c*S_c+(lineratization_start*S_c)*(lineratization_start*S_c))/((lineratization_start*S_c*lineratization_start*S_c-S_c*S_c)*(lineratization_start*S_c*lineratization_start*S_c-S_c*S_c));
    //printf("Diffusion %g \n",diffusion);
    indi=2;
    }
    else {
    diffusion=(300-(300.0-(S_c*200.0+(300-slope*parameters[0].dx))))*(parameters[0].dx*parameters[0].dy);
    indi=3;
    }
	
    printf("slope %g diffusion %g indi %d \n",slope,diffusion,indi);
    if (indi==3) printf("diffusion %g topsedi %g reciveer topsedi %g S_c*distance %g diffusion in meters %g \n",diffusion,300.0,(300-slope*parameters[0].dx),S_c*200.0,(300.0-(S_c*200.0+(300-slope*parameters[0].dx))));
	
    }
  */
	
  return diffusion;
}


void expli_diffusion_calc_new(nodetype *nodes,model_parameters *parameters)
{
  double diffusion;
  //printf("%g  %g \n",S_c,tan(30*M_PI/180));
  int j;
  double lineratization_start=0.99;
  double dxdy=parameters[0].dx*parameters[0].dy;
  double diff_parameters=parameters[0].k_diff;
  double S_c=parameters[0].S_c;
  //printf("k diff %g \n",diff_parameters);
  for (j=0;j<parameters[0].nx*parameters[0].ny;j++)
    {
	
      if (nodes[j].di<0) {
	//diffusion=parameters[0].k_diff*(-nodes[j].av_donor_height-nodes[nodes[j].r].topsedi+2*node_height)/(pow((nodes[j].av_donor_distance+nodes[j].reciever_distance)/2,2));
	if (nodes[j].reciever_slope<lineratization_start*S_c) {
	  diffusion=(diff_parameters)*nodes[j].reciever_slope/(1-(fabs(nodes[j].reciever_slope)/S_c)*(fabs(nodes[j].reciever_slope)/S_c));
	}
	else if(nodes[j].reciever_slope>=lineratization_start*S_c && nodes[j].reciever_slope<S_c)
	  {
	    diffusion=(diff_parameters)*lineratization_start*S_c/(1-(lineratization_start)*(lineratization_start))+diff_parameters*S_c*S_c*(S_c*S_c+(lineratization_start*S_c)*(lineratization_start*S_c))/((lineratization_start*S_c*lineratization_start*S_c-S_c*S_c)*(lineratization_start*S_c*lineratization_start*S_c-S_c*S_c))*(nodes[j].reciever_slope-lineratization_start*S_c);
	    //This linerization when the slope is above lineratization_start is to ensure stability. The derivation of the equation KS_c^2(S_c^2+S^2)/(S^2-S_c^2)^2 can be found in a Latex document in a subsection named "Derivation of linerization of non-linear diffusion"
	  }
	else {
	  diffusion=(nodes[j].topsedi-(S_c*nodes[j].reciever_distance+nodes[nodes[j].r].topsedi))*(parameters[0].dx*parameters[0].dy);
	}
      }
      else {
	//diffusion=parameters[0].k_diff*(-2*nodes[nodes[j].r].topsedi+2*node_height)/(pow(nodes[j].reciever_distance,2));
	if (nodes[j].reciever_slope<lineratization_start*S_c) {
	  diffusion=(diff_parameters)*nodes[j].reciever_slope/(1-(fabs(nodes[j].reciever_slope)/S_c)*(fabs(nodes[j].reciever_slope)/S_c));
	  //printf("Ellers %g \n",diffusion);
	  //if (diffusion>3000) printf("large diffusion %g \n\n",diffusion);
	}
	else if(nodes[j].reciever_slope>=lineratization_start*S_c && nodes[j].reciever_slope<2e8*S_c)
	  {
	    diffusion=(diff_parameters)*lineratization_start*S_c/(1-(lineratization_start)*(lineratization_start))+(nodes[j].reciever_slope-lineratization_start*S_c)*diff_parameters*S_c*S_c*(S_c*S_c+(lineratization_start*S_c)*(lineratization_start*S_c))/((lineratization_start*S_c*lineratization_start*S_c-S_c*S_c)*(lineratization_start*S_c*lineratization_start*S_c-S_c*S_c));
	    //This linerization when the slope is above lineratization_start is to ensure stability. The derivation of the equation KS_c^2(S_c^2+S^2)/(S^2-S_c^2)^2 can be found in a Latex document in a subsection named "Derivation of linerization of non-linear diffusion"
	  }
	else {
	  diffusion=(nodes[j].topsedi-(S_c*nodes[j].reciever_distance+nodes[nodes[j].r].topsedi));
	  printf("Diffusion Calc Very High %g topsedi %g reciveer topsedi %g S_c*distance %g diffusion in meters %g \n",diffusion,nodes[j].topsedi,nodes[nodes[j].r].topsedi,S_c*nodes[j].reciever_distance,(nodes[j].topsedi-(S_c*nodes[j].reciever_distance+nodes[nodes[j].r].topsedi)));
	}
      }
	
	
      if (diffusion<0) diffusion=0;
	
      // if (diffusion>nodes[j].sediment_thickness) {
      // 		diffusion=nodes[j].sediment_thickness; }
      //
      // 	nodes[j].topsedi-=diffusion;
      // 	nodes[j].sediment_thickness-=diffusion;
      //
	
	
      nodes[j].diff=diffusion*dxdy;
    }
  //diffusion*=parameters[0].dx*parameters[0].dy;
}
