#include "header.h"

void landslide_distribution_factor(nodetype *nodes,meshtype mesh)
{
  long nx=mesh.nx;
  long ny=mesh.ny;
  double sigma=23;
  int i,j;
  double max=0;
  for (i=0;i<nx*ny;i++){
    //nodes[i].landslide_possibility=exp(-(nodes[i].x-nx/4)*(nodes[i].x-nx/4)/(2*sigma*sigma))+exp(-(nodes[i].x-3*nx/4)*(nodes[i].x-3*nx/4)/(2*sigma*sigma));
    nodes[i].landslide_possibility=exp(-((nodes[i].x-nx/4)*(nodes[i].x-nx/4)+(nodes[i].y-ny/4)*(nodes[i].y-ny/4))/(2*sigma*sigma))+exp(-((nodes[i].x-3*nx/4)*(nodes[i].x-3*nx/4)+(nodes[i].y-ny/4)*(nodes[i].y-ny/4))/(2*sigma*sigma));
    //nodes[i].landslide_possibility=exp(-(nodes[i].x-nx/4)*(nodes[i].x-nx/4)/(2*sigma*sigma))+exp(-(nodes[i].y-ny/4)*(nodes[i].y-ny/4)/(2*sigma*sigma))+exp(-(nodes[i].x-3*nx/4)*(nodes[i].x-3*nx/4)/(2*sigma*sigma))+exp(-(nodes[i].y-3*ny/4)*(nodes[i].y-3*ny/4)/(2*sigma*sigma));
    if (nodes[i].landslide_possibility>max) max=nodes[i].landslide_possibility;
  }
	
  for (i=0;i<nx*ny;i++) {nodes[i].landslide_possibility/=2; nodes[i].landslide_possibility+=0.5;};
	
  for (i=0;i<nx;i++) {
    for (j=0;j<ny;j++) {
      printf("%g ",nodes[i*ny+j].landslide_possibility);
    }
    printf("\n");
  }
  printf("\n\n\n\n\n");
}


void nslides_daniel(long i,double hc,nodetype *nodes,long *nsc,long *slist,double failure_slope,model_parameters *parameters)
{
  long ni;
  long j;
  double hp,dist,Hc; 
  //  double xc = nodes[i].x;
  //  double yc = nodes[i].y;
  //double hc = nodes[i].bed;
  //double hc = nodes[i].topsedi;
  //printf("i: %ld n_neigh: %ld \n",i,nodes[i].n_neigh);

  /*loop neighbours*/
  for (j=0;j<nodes[i].n_neigh;j++) {

    /*identify neighbour*/
    ni = nodes[i].neigh[j];
    //	 printf("ni: %ld, inslide: %ld \n",ni,nodes[ni].inslide);
    /*if not allready in slide*/
    if (nodes[ni].inslide == 0) {
      //		printf("i: %ld ni: %ld \n",i,ni);
    
      /*distance to neigbour*/
      dist = nodes[i].distance[j];
			
      /*Critical hillslope height*/
      Hc = hc + (double)tan(M_PI*failure_slope/180)*dist;
      /*Hc = hc + (double)tan(phi0)*dist;*/

      /*Height of cell*/
      //hp = nodes[ni].bed;
      if (parameters[0].do_landslide_deposition=='y')
	{
	  hp = nodes[ni].topsedi;
	}
      else if (parameters[0].do_landslide_deposition=='n')
	{
	  hp = nodes[ni].bed;
	}
      else {
	printf("KAEMPE FEJL I N_LANDSLIDES_DANIEL \n\n\n\n");
	hp=0;
	exit(1);
      }
		
      /*if potentially unstable*/
      if (hp > Hc) {

	/*registre cell*/
	slist[(*nsc)] = ni;
	//slist[nsc] = ni;
	//printf("slist[nsc] %ld \n",slist[*nsc]);
	nodes[ni].inslide = 1;
	nodes[ni].rfail = hp-Hc;

	/*add to number*/
	(*nsc) += 1;
	//nsc += 1;
	/*printf("nsc = %ld\n",(*nsc));*/

	/*increase hillslope height*/
	//if ((*maxH) < hp) (*maxH) = hp;

	/*distance to toe*/
	//dist = sqrt(pow(nodes[ni].x-x0,2.0)+pow(nodes[ni].y-y0,2.0));

	/*increase hillslope angle*/
	//beta = (double)atan((hp-h0)/dist);
	//if ((*maxbeta) < beta) (*maxbeta) = beta;

	/*recursive call*/
	nslides_daniel(ni,Hc,nodes,nsc,slist,failure_slope,parameters);
      }/*if*/

      /*printf("\n");*/

    }/*if*/

  }/*i*/

}

long lowest_neighbour_above(nodetype *nodes,long sedi_node)
{
  long i;
  long h=sedi_node;
  double tmp=INT_MAX;
  long tmp_node,lowest_above_neigh;
  tmp_node=h;
  for (i=0;i<nodes[h].n_neigh;i++)
    {
      if (tmp>nodes[nodes[h].neigh[i]].topsedi && nodes[nodes[h].neigh[i]].topsedi>nodes[h].topsedi)
	{
	  tmp=nodes[nodes[h].neigh[i]].topsedi;
	  tmp_node=nodes[h].neigh[i];
	}
    }
  lowest_above_neigh=tmp_node;
  return lowest_above_neigh;
}


double beta_calc(nodetype *nodes,long failnode,double *maxH)
{
  long i;
  double beta,dist=1;
  long h=failnode;
  double tmp=nodes[h].topsedi;
  //long tmp_node=h;
  //long highest_above_neigh;
  for (i=0;i<nodes[h].n_neigh;i++)
    {
      if (tmp<nodes[nodes[h].neigh[i]].topsedi && nodes[nodes[h].neigh[i]].inslide==0)
	{
	  tmp=nodes[nodes[h].neigh[i]].topsedi;
	  //tmp_node=nodes[h].neigh[i];
	  dist=nodes[h].distance[i];
	}
    }
  //highest_above_neigh=tmp_node;
  *maxH=tmp;
  beta=(tmp-nodes[h].topsedi)/(dist);
  //printf("beta: %4.3f \n",beta);
  return beta;
}

void move_sediment(nodetype *nodes,double dHH,long i,long dx,long dy,model_parameters *parameters)
{
  long g;
	
  g=lowest_neighbour_above(nodes,i);
	
	
  double slope=parameters[0].landslide_angle*nodes[g].reciever_distance;
	
  //printf("dHH: %6.3f i: %ld own: %5.2f, above %5.2f, slope %4.2f \n",dHH,i,nodes[i].topsedi,nodes[g].topsedi,slope);	
	
  if (nodes[i].b==1) {nodes[i].landslide_out=dx*dy*dHH/parameters[0].deltat; /*printf("dHH: %6.3f i: %ld own: %5.2f, above %5.2f, slope %4.2f \n",dHH,i,nodes[i].topsedi,nodes[g].topsedi,slope);	*/ dHH=0;}
  else if (g==i) {move_sediment(nodes,dHH,nodes[i].r,dx,dy,parameters);} //This if the node have no nodes above, the sediment is then just passed on	
  else if (nodes[i].topsedi>=nodes[g].topsedi-slope)
    {
      move_sediment(nodes,dHH,nodes[i].r,dx,dy,parameters);
    }
  else {
    if (dHH>nodes[g].topsedi-slope-nodes[i].topsedi) {	
      //printf("topsedi %6.4f, number of donors %ld g old %6.4f, dHH %4.3f \n",nodes[i].topsedi,nodes[i].di,nodes[g].topsedi,dHH);
			
      dHH-=nodes[g].topsedi-slope-nodes[i].topsedi;
      nodes[i].landslide_deposition+=nodes[g].topsedi-slope-nodes[i].topsedi;
      //if(nodes[g].topsedi-slope-nodes[i].topsedi>2) printf("1! Large deposition node %ld amount %g n donors %ld \n",i,nodes[g].topsedi-slope-nodes[i].topsedi,nodes[i].di);
			
      nodes[i].topsedi=nodes[g].topsedi-slope;
			
      //	printf("i% ld, g %ld topsedi %6.4f, g old %6.4f dHH: %5.3f \n",i,g,nodes[i].topsedi,nodes[g].topsedi,dHH);
      if (nodes[i].topsedi>nodes[g].topsedi) printf("1 \n");			
      move_sediment(nodes,dHH,nodes[i].r,dx,dy,parameters);

    }
    else {
      nodes[i].topsedi+=dHH;
      nodes[i].landslide_deposition+=dHH;
      //if(dHH>2) printf("2! Large deposition node %ld amount %g n donors %ld \n",i,dHH,nodes[i].di);
      dHH=0;
      if (nodes[i].topsedi>nodes[g].topsedi) printf("2 \n");
    }
	
  }
}

void landslide_daniel(nodetype *nodes,meshtype mesh,long *slist,long npits,char *path,char file[200],FILE *fp,char *output_path,long step,long *num_landslides,model_parameters *parameters)	
{
  long i,j;
  long ti,ni;
  long nsc;
  double HH,Hc,dH,maxbeta,phi,Pf,ran;
  double dH_sum;
  double maxH;
  //double x0,y0;
  double h0;
  double Atot,Vtot,newsedi,Vmean;
  //char move_sed = 'y';
  //if (npits!=0) move_sed= 'n';

  double gamma = 4*6e4/(2000*9.82); //Is 4*Cohesion/(rho*g) from equation 14 in Densmore 1998

  double dx = mesh.dx;
  double dy = mesh.dy;
  long nx = mesh.nx;
  long ny = mesh.ny;
  double area = dx*dy;
  double sediment_thickness;
  double failure_slope;
  
  
  /*initialize*/
#pragma omp parallel for default(none) shared(nodes,nx,ny) private(i) //if((nx*ny)>(100*100))
  for (i=0;i<ny*nx;i++)
    {
      nodes[i].inslide = 0;
      nodes[i].landslide_deposition=0;
      nodes[i].rfail = 0.0;
      nodes[i].phi=17; //In degrees, remember to convert it to degrees whenever used
      //nodes[i].phi=26+8*(double)rand()/(double)RAND_MAX;
      nodes[i].landslide_erosion=0;
      nodes[i].landslide_out=0;
      nodes[i].bedrock_landslide_erosion=0;
    }

  /*mean landslide volume*/
  Vmean = 0.0;

  /*loop some random cells*/
  
  
  //printf("1a \n");
  
  
  
  ran = (double)rand()/(double)RAND_MAX;
  int numbers_picked;
  numbers_picked=parameters[0].n_landslide_pa*parameters[0].deltat*ran+ran; /*This determines how many landslides there are per year. The equation has the for number_of_landslides_per_year*x+x, where x varies between 0 and 1*/
  if (numbers_picked<0) {numbers_picked=0;}
  for (i=0;i<numbers_picked;i++) 
    {
      /*random double between 0 and 1*/
      ran = (double)rand()/(double)RAND_MAX;

      /*random integer between 1 and ny*nx*/
      ti = (long)floor(ran*(double)ny*nx);

      /*if not allready in slide*/
      if ((ti>=0)&&(ti<ny*nx)&&nodes[ti].inslide == 0 && nodes[ti].in_stack==1) {

      	nsc = 0;
	//x0 = nodes[ti].x;
      	//y0 = nodes[ti].y;
      	//h0 = nodes[ti].bed;
	h0 = nodes[ti].topsedi;
      	maxH = h0;
      	maxbeta = 0.0;
      	phi = nodes[ti].phi*M_PI/180.0;
			
	maxbeta=beta_calc(nodes,ti,&maxH);
	//printf("maxbeta: %3.3f \n ",maxbeta);
	//exit(1);
	Hc = gamma*sin(maxbeta)*cos(phi)/(1.0-cos(maxbeta-phi));
	failure_slope = 0.5*(maxbeta*180/M_PI + phi*180/M_PI);

	if (failure_slope>70) {failure_slope=70;}
	/*Hillslope height*/
	HH = maxH - h0;
	/*Critical height*/
	Hc = gamma*sin(maxbeta)*cos(phi)/(1.0-cos(maxbeta-phi));

	/*Propability*/
	Pf = HH/Hc;
	/*pick random number between 0 and 1*/
	ran = (double)rand()/(double)RAND_MAX;
	/*if failure*/
	if (ran < Pf && failure_slope>10 && phi<maxbeta) {
	  /*recursive call*/
	  nslides_daniel(ti,h0,nodes,&nsc,slist,failure_slope,parameters);
	  dH_sum=0;
	  for (j=0;j<nsc;j++) {dH_sum+=nodes[slist[j]].rfail;}
	  //if (dH_sum>500) printf("BIG LANDSLIDE: failure slope: %4.2f maxbeta %5.2f dHsum %6.2f Pf %5.4f, HH %4.3f, Hc %4.3f h0 %4.3f nsc %ld \n ",failure_slope,maxbeta*180/M_PI,dH_sum,Pf,HH,Hc,h0,nsc);
	  Atot = 0.0;
	  Vtot = 0.0;

	  /*loop unstable cells and collect material*/
	  if (dH_sum>30)
	    {
	      switch (parameters[0].do_landslide_deposition)
		{
		case ('n'):
		  for (j=0;j<nsc;j++) {
	    
		    /*identify cell*/
		    ni = slist[j];

		    /*distance to cell*/
		    /*mdist = sqrt(pow(cells[ni][nj].x-x0,2.0)+pow(cells[ni][nj].y-y0,2.0));*/

		    /*Excess height*/
		    /*dH = cells[ni][nj].topsedi - (h0+(double)tan(theta)*mdist);*/
		    dH = nodes[ni].rfail;
			
		    sediment_thickness=nodes[ni].topsedi-nodes[ni].bed;
		    /*erosion*/
		    //if (dH > 0.1) {
	   		
		    if (dH > sediment_thickness) {
		      newsedi = dH - sediment_thickness;
		      //	  dH_sum+=newsedi;
		      nodes[ni].bed -=newsedi;
		      if (nodes[ni].bed<0) {newsedi=newsedi+nodes[ni].bed; nodes[ni].bed=0; printf("Landslides daniel 1 her? \n");}
		      nodes[ni].total_landslide_erosion += newsedi;
		      nodes[ni].landslide_erosion = newsedi;
		      //printf("landslide \n");
		      nodes[ni].bedrock_landslide_erosion+=newsedi;
		      if (nodes[ni].in_stack==1 && nodes[ni].c>=0) 
			{
			  nodes[nodes[ni].c].catchment_bedrock_landslide_erosion+=newsedi;
			  nodes[nodes[ni].c].catchment_landsliding+=newsedi;
			  nodes[nodes[ni].c].total_distance+=nodes[ni].distance_to_base;
			  nodes[nodes[ni].c].landslides_since_last++;
			}
		      Atot += area;
		      Vtot += area*dH;
		    }/*if erosion*/

		    //}
		    Vmean += Vtot;
		
		  }/*loop unstable cells*/
		  break;
		case ('y'):
		  //dH_sum=0;
		  for (j=0;j<nsc;j++) {
					
		    ni = slist[j];
		    dH=nodes[ni].rfail;
		    //dH_sum+=dH;
		    sediment_thickness=nodes[ni].topsedi-nodes[ni].bed;
		    if (dH >= sediment_thickness)
		      {
			newsedi = dH - sediment_thickness;
			nodes[ni].bed -=newsedi;
			if (nodes[ni].bed<0) {newsedi=newsedi+nodes[ni].bed; nodes[ni].bed=0; printf("Landslides daniel 2 her? \n");}
			nodes[ni].topsedi=nodes[ni].bed;
			nodes[ni].total_landslide_erosion += dH;
			nodes[ni].landslide_erosion = dH;
			nodes[ni].bedrock_landslide_erosion+=newsedi;
			if (nodes[ni].in_stack==1 && nodes[ni].c>=0) 
			  {
			    nodes[nodes[ni].c].catchment_bedrock_landslide_erosion+=newsedi;
			    nodes[nodes[ni].c].catchment_landsliding+=newsedi;
			    nodes[nodes[ni].c].total_distance+=nodes[ni].distance_to_base;
			    nodes[nodes[ni].c].landslides_since_last++;
			  }
			Atot += area;
			Vtot += area*dH;
		      }/*if erosion*/
		    else if (dH<sediment_thickness) {
		      nodes[ni].topsedi-=dH;
		      nodes[ni].total_landslide_erosion +=dH;
		      nodes[ni].landslide_erosion=dH;
		      if (nodes[ni].in_stack==1 && nodes[ni].c>=0)
			{
			  nodes[nodes[ni].c].catchment_landsliding+=dH;
			  nodes[nodes[ni].c].total_distance+=nodes[ni].distance_to_base;
			  nodes[nodes[ni].c].landslides_since_last++;
			}
		    }
		  }
		  move_sediment(nodes,dH_sum,ti,dx,dy,parameters);
		  break;
		}/*End switch*/
	      if (step>200) {
		if (dH_sum > 30) {
		  output_landslides(nodes,mesh,path,file,fp,step,ti,dH_sum,nodes[ti].c,output_path,nsc,num_landslides);
		}
	      }
	    }
	}/*if failure*/
      	/*if nsc > 0*/

      }/*if not in slide*/
    }
}/*landslide*/



void nslides_david(long i,nodetype *nodes,long *nsc,long *slist,double x0,double y0,double h0,double *maxH,double *maxbeta,model_parameters *parameters)
{
  long ni;
  long j;
  double hp,dist,Hc,beta; 
  //  double xc = nodes[i].x;
  //  double yc = nodes[i].y;
  //double hc = nodes[i].bed;
  double hc = nodes[i].topsedi;
  
  //printf("i: %ld n_neigh: %ld \n",i,nodes[i].n_neigh);

  /*loop neighbours*/
  for (j=0;j<nodes[i].n_neigh;j++) {

    /*identify neighbour*/
    ni = nodes[i].neigh[j];
    //	 printf("ni: %ld, inslide: %ld \n",ni,nodes[ni].inslide);
    /*if not allready in slide*/
    if (nodes[ni].inslide == 0) {
      //		printf("i: %ld ni: %ld \n",i,ni);
    
      /*distance to neigbour*/
      dist = nodes[i].distance[j];
			
      /*Critical hillslope height*/
      Hc = hc + (double)tan(nodes[i].phi*M_PI/180.0)*dist;
      /*Hc = hc + (double)tan(phi0)*dist;*/

      /*Height of cell*/
      //hp = nodes[ni].bed;
      if (parameters[0].do_landslide_deposition=='y')
	{
	  hp = nodes[ni].topsedi;
	}
      else if (parameters[0].do_landslide_deposition=='n')
	{
	  hp = nodes[ni].bed;
	}
      else {
	printf("KAEMPE FEJL I N_LANDSLIDES_DAVID \n\n\n\n");
	hp=0;
	exit(1);
      }

      /*if potentially unstable*/
      if (hp > Hc) {

	/*registre cell*/
	slist[(*nsc)] = ni;
	//printf("slist[nsc] %ld \n",slist[*nsc]);
	nodes[ni].inslide = 1;
	nodes[ni].rfail = hp-Hc;

	/*add to number*/
	(*nsc) += 1;
	/*printf("nsc = %ld\n",(*nsc));*/

	/*increase hillslope height*/
	if ((*maxH) < hp) (*maxH) = hp;

	/*distance to toe*/
	dist = sqrt(pow(nodes[ni].x-x0,2.0)+pow(nodes[ni].y-y0,2.0));

	/*increase hillslope angle*/
	beta = (double)atan((hp-h0)/dist);
	if ((*maxbeta) < beta) (*maxbeta) = beta;

	/*recursive call*/
	nslides_david(ni,nodes,nsc,slist,x0,y0,h0,maxH,maxbeta,parameters);
      }/*if*/

      /*printf("\n");*/

    }/*if*/

  }/*i*/
}
  

void landslide_david(nodetype *nodes,meshtype mesh,long *slist,long npits,char *path,char file[200],FILE *fp,char *output_path,long step,long *num_landslides,model_parameters *parameters,long h)
{	
  long i,j;
  long ti,ni;
  long nsc;
  double HH,Hc,dH,maxbeta,phi,Pf,ran;
  double dH_sum;
  double maxH,x0,y0,h0;
  double Atot,Vtot,newsedi,Vmean;
  
  double gamma = 4*6e4/(2000*9.82); //Is 4*Cohesion/(rho*g) from equation 14 in Densmore 1998

  double dx = mesh.dx;
  double dy = mesh.dy;
  long nx = mesh.nx;
  long ny = mesh.ny;
  //long Nc=nx*ny;
  double area = dx*dy;
  double sediment_thickness;
  
  
  /*initialize*/
  for (i=0;i<ny*nx;i++)
    {
      nodes[i].inslide = 0;
      nodes[i].landslide_deposition=0;
      nodes[i].rfail = 0.0;
      nodes[i].phi=32;
      //nodes[i].phi=28+8*(double)rand()/(double)RAND_MAX;
      nodes[i].landslide_erosion=0;
      nodes[i].landslide_out=0;
      nodes[i].bedrock_landslide_erosion=0;
    }

  /*mean landslide volume*/
  Vmean = 0.0;

  /*loop some random cells*/
  
  ran = (double)rand()/(double)RAND_MAX;
  int numbers_picked;
  numbers_picked=parameters[0].n_landslide_pa*parameters[0].deltat*ran+ran; /*This determines how many landslides there are per year. The equation has the for number_of_landslides_per_year*x+x, where x varies between 0 and 1*/
  if (numbers_picked<0) {numbers_picked=0;}
  
  //numbers_picked=ceil(Nc/2000);
  //if (h>(0.3*parameters[0].n_step)) {numbers_picked=0;}
  
  
  for (i=0;i<numbers_picked;i++) 
    {
      if (nodes[i].in_stack==1)
	{

	  /*random double between 0 and 1*/
	  ran = (double)rand()/(double)RAND_MAX;

	  /*random integer between 1 and ny*nx*/
	  ti = (long)floor(ran*(double)ny*nx);

	  /*if not allready in slide*/
	  if ((ti>=0)&&(ti<ny*nx)&&nodes[ti].inslide == 0) {

	    nsc = 0;
	    x0 = nodes[ti].x;
	    y0 = nodes[ti].y;
	    //h0 = nodes[ti].bed;
	    h0 = nodes[ti].topsedi;
	    maxH = h0;
	    maxbeta = 0.0;
	    phi = nodes[ti].phi*M_PI/180.0;
	    //printf("ti: %ld \n",ti);
	    /*recursive call*/
	    nslides_david(ti,nodes,&nsc,slist,x0,y0,h0,&maxH,&maxbeta,parameters);

	    /*printf("nsc = %ld\n",nsc);*/


	    //printf("aher \n");
	    /*if potential for slide*/
	    if (nsc > 0) {
	
	      /*Hillslope height*/
	      HH = maxH - h0;

	      /*Critical height*/
	      Hc = gamma*sin(maxbeta)*cos(phi)/(1.0-cos(maxbeta-phi));

	      /*Propability*/
	      Pf = HH/Hc;
	      /*Pf = HH/Hc + kt*(time - lastslide[tp]);*/

	      /*pick random number between 0 and 1*/
	      ran = (double)rand()/(double)RAND_MAX;

	      /*if failure*/
	      if (ran < Pf  /*&& ran<nodes[ti].landslide_possibility*/) {
				
		dH_sum=0;
		for (j=0;j<nsc;j++) {dH_sum+=nodes[slist[j]].rfail;}
		/*critical angle*/
		/*theta = 0.5*(maxbeta + phi0);*/
		//		printf("bher \n");

		Atot = 0.0;
		Vtot = 0.0;
		/*loop unstable cells and collect material*/
		switch (parameters[0].do_landslide_deposition)
		  {
		  case ('n'):
		    for (j=0;j<nsc;j++) {
	    
		      /*identify cell*/
		      ni = slist[j];

		      /*distance to cell*/
		      /*mdist = sqrt(pow(cells[ni][nj].x-x0,2.0)+pow(cells[ni][nj].y-y0,2.0));*/

		      /*Excess height*/
		      /*dH = cells[ni][nj].topsedi - (h0+(double)tan(theta)*mdist);*/
		      dH = nodes[ni].rfail+0.001*(RAND_MAX/2-rand())/RAND_MAX; //Adding a bit of roughness to the fault surface
		      //				printf("cher \n");
			
		      sediment_thickness=nodes[ni].topsedi-nodes[ni].bed;
		      /*erosion*/
		      if (dH > 0.1) {
	   		
			if (dH > sediment_thickness) {
			  newsedi = dH - sediment_thickness;
			  nodes[ni].bed -=newsedi;
			  if (nodes[ni].bed<0) {newsedi=newsedi+nodes[ni].bed; nodes[ni].bed=0; printf("Landslides david 1 her? \n");}
			  nodes[ni].total_landslide_erosion += newsedi;
			  nodes[ni].landslide_erosion = newsedi/parameters[0].deltat;
			  nodes[ni].bedrock_landslide_erosion+=newsedi;
			  if (nodes[ni].in_stack==1 && nodes[ni].c>=0) 
			    {
			      nodes[nodes[ni].c].catchment_bedrock_landslide_erosion+=newsedi;
			      nodes[nodes[ni].c].catchment_landsliding+=newsedi;
			      nodes[nodes[ni].c].total_distance+=nodes[ni].distance_to_base;
			      nodes[nodes[ni].c].landslides_since_last++;
			    }
			  //printf("landslide \n");
			  Atot += area;
			  Vtot += area*dH;
			  //		  			printf("dher \n");
								  
			}/*if erosion*/
		      }
		      Vmean += Vtot;
		    }/*loop unstable cells*/
		    break;
		  case ('y'):
					
		    dH_sum=0;
		    for (j=0;j<nsc;j++) {
					
		      ni = slist[j];
		      dH=nodes[ni].rfail;
		      dH_sum+=dH;
		      sediment_thickness=nodes[ni].topsedi-nodes[ni].bed;

		      if (dH >= sediment_thickness) {
			newsedi = dH - sediment_thickness;
			nodes[ni].bed -=newsedi;
			if (nodes[ni].bed<0) {newsedi=newsedi+nodes[ni].bed; nodes[ni].bed=0; printf("Landslides david 2 her? \n");}
			nodes[ni].topsedi=nodes[ni].bed;
			nodes[ni].total_landslide_erosion += newsedi;
			nodes[ni].landslide_erosion = newsedi/parameters[0].deltat;
			nodes[ni].bedrock_landslide_erosion+=newsedi;
			if (nodes[ni].in_stack==1 && nodes[ni].c>=0) 
			  {
			    nodes[nodes[ni].c].catchment_bedrock_landslide_erosion+=newsedi;
			    nodes[nodes[ni].c].catchment_landsliding+=newsedi;
			    nodes[nodes[ni].c].total_distance+=nodes[ni].distance_to_base;
			    nodes[nodes[ni].c].landslides_since_last++;
			  }
			//printf("landslide \n");
			Atot += area;
			Vtot += area*dH;
		      }/*if erosion*/
		      else if (dH<sediment_thickness) {
			nodes[ni].topsedi-=dH;
			nodes[ni].total_landslide_erosion +=dH;
			nodes[ni].landslide_erosion=dH/parameters[0].deltat;
			if (nodes[ni].in_stack==1 && nodes[ni].c>=0) 
			  {
			    nodes[nodes[ni].c].catchment_landsliding+=dH;
			    nodes[nodes[ni].c].total_distance+=nodes[ni].distance_to_base;
			    nodes[nodes[ni].c].landslides_since_last++;
			  }
		      }
		    }
		    if (nodes[ti].in_stack==1) {
		      move_sediment(nodes,dH_sum,ti,dx,dy,parameters);
		    }			
		    break;
		  }/*End switch*/
		//if (step>200) {
		if (dH_sum > 3) {
		  output_landslides(nodes,mesh,path,file,fp,step,ti,dH_sum,nodes[ti].c,output_path,nsc,num_landslides);
		}
		//}
	      }/*if failure*/
	    }/*if nsc > 0*/

	  }/*if not in slide*/
	}
    }/*i*/
  //mesh.mean_landslide_erate = Vmean/(mesh.L*mesh.H*dt);
}/*landslide*/
