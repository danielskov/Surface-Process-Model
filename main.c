#include "header.h"

void output_erosion(nodetype *nodes,meshtype mesh,char *path,char file[200],FILE *fp,int *counter,char *output_path,model_parameters *parameters);
void d2_diff(nodetype *nodes,model_parameters *parameters);

int main(int argc, char *argv[])
{
  long i;
  double h;
  long nx,ny,nc;
  long npits='\0';
  double dx,dy;
  long n_baselevelnodes; //The number of baselevel nodes
  char file[200];
  FILE *fp=NULL;
  char *output_path = (char*) malloc(500*sizeof(char));
  long *stack; //The stack of nodes to be solved. Created using the FastScape algorithm. Starts from a baselevel node and then moves upstream.
  long *stack2; //The inverse of the stack, that is it starts from the top of the landscape and moves downstream.
  long *baselevel_list;
  int go_on; //Determines whether the model should start from new from the matlab output, or should load the last output in output folder. 0=matlab output, 1=last output
  long *slist;
  long *store;
  double *tmp;
  long *flist;
  long s_flist;
  double step, number_of_outputs, print_modulo;
  long counter;
  long num_landslides=0;
  double time;
  long landslides_since_last=0;
  long old_n_landslides=0;
  char landslide_type;
  double flux_out_modulo;
  double weath_out_modulo;
  double output_number=0;
  long output_burst=0;
  long uplift_change_counter=0;


  int erosionoutputcounter=0;
	
  go_on=0;
  //meshtype *mesh;
  meshtype mesh;
  nodetype *nodes;
  model_parameters *parameters;
  output_path = argv[1];
  clock_t start_time = omp_get_wtime();
  //clock_t start_time=clock();

  /*Read path to working directory*/
  //Getting the current working directory
  char *path;
  char buff[500+1];
  //path = (char*) malloc(500*sizeof(char));	//char buff[500+1];
  path=getcwd(buff,500+1);
	
  /*Uses the first argument input to the terminal as the folder*/
  //path=argv[1];
	
  /*Uses the main folder where the model was developed as working path*/
  path= "/Users/danielss/Dropbox (ICE Research Group)/jbckode/spm_0.96";

  /*Loads the mesh*/
  //mesh = malloc(sizeof(meshtype));
  //mesh=loadmesh(mesh,path,file,fp,go_on);
	
  mesh=loadmesh(path,file,fp,go_on);	
	
  /*Gets parameters from the input mesh*/
  nx=mesh.nx;
  ny=mesh.ny;
  nc=mesh.nc;
  dx=mesh.dx;
  dy=mesh.dy;


  //load_parameters(mesh);
		
  /*allocating memory*/
  stack=(long *) malloc(nc*sizeof(long));
  stack2=(long *) malloc(nc*sizeof(long));
  slist = (long *) malloc(ny*nx*sizeof(long));
  store=(long *) malloc(nx*ny*sizeof(long));
  tmp=(double *) malloc(nx*ny*sizeof(double));
  nodes = (nodetype *) calloc((ny*nx+1),sizeof(nodetype)); //I add one beceause we need an additional node in the computation of delta in get_donorlist()
  parameters = (model_parameters *) malloc(sizeof(model_parameters));
  
  
  /*Initializing the nodes from the input file*/
  initialize_modelparameters(parameters,mesh);
  initialize(nodes,mesh,path,file,fp,go_on,parameters);

  printf("Size of nodetype %lu\n",sizeof(nodetype));
  printf("Size of meshtype %lu\n",sizeof(meshtype));
  printf("Size of modelparameters %lu\n",sizeof(model_parameters));


  /*
  double *saltabr_list;
  double *diff_list;
  double *ero_list;
  double *streampower_list;
  double *rel_sedi_list;



  
  ero_list = (double *) calloc(parameters[0].n_step,sizeof(double));
  saltabr_list = (double *) calloc(parameters[0].n_step,sizeof(double));
  streampower_list = (double *) calloc(parameters[0].n_step,sizeof(double));
  diff_list = (double *) calloc(parameters[0].n_step,sizeof(double));
  rel_sedi_list = (double *) calloc(parameters[0].n_step,sizeof(double));
  */

  //d2_diff(nodes,parameters);
  
  char flex_param=parameters[0].flex_param;
  print_modulo=parameters[0].print_modulo;
  number_of_outputs=parameters[0].number_of_outputs;
  double n_step=parameters[0].n_step;
  landslide_type=parameters[0].landslide_type;
  flux_out_modulo=parameters[0].flux_out_modulo;
  weath_out_modulo=parameters[0].weath_out_modulo;
	
	
  /*Gets the coordinates of the individual nodes*/
  xy(nodes,nx,ny);
  //landslide_distribution_factor(nodes,mesh); //get the probability of an landslide occuring in the node.
	
  
	
  /*Deletes the eventual old log, landslide and n_landslides file in the folder*/
  delete_slides_file(path,file,fp,output_path);
	
  
	
  /*Finds the neighbour for all nodes, and the distance between the neighbours*/	
  get_neighbours(nodes,nx,ny);
	
	
	
  get_distance(nodes,nx,ny,dx,dy);
	
	
  /*Finds baselevel nodes, assigns them the value nodes[i]=1, and returns the number of baselevel nodes*/
  n_baselevelnodes=find_baselevelnodes(nodes,nx,ny);
	
	
	
  printf("Baselevel nodes %ld \n",n_baselevelnodes);
	
  baselevel_list=(long *) malloc(n_baselevelnodes*sizeof(long));
	
  baselevel_lister(nodes,baselevel_list,n_baselevelnodes,nx,ny);
	
  s_flist=2*n_baselevelnodes;
	
  node_uplifts(nodes,nx,ny,npits,parameters);
	
	
  /*Allocates memory for the f_list, which is used in the paralization of the solver*/
  flist=(long *) malloc(s_flist*n_baselevelnodes*sizeof(long));


  /*Is used when determining which step to start at*/
  switch (go_on)
    {
    case (1):
      step=mesh.step;
      break;
    case (0):
      step=0;
      break;
    }
	 
	 
	
  if (n_step<number_of_outputs) {number_of_outputs=n_step;}
  //print_modulo=n_step/number_of_outputs;
	
  counter=0;
  double k_diff_original=parameters[0].k_diff;

  /*Makes a log for the model run*/
  make_log(nodes,mesh,path,file,fp,print_modulo,number_of_outputs,output_path,parameters);
	
	
	
  get_reciever_wo_slope(nodes,nx,ny); //Finds the reciever of node
  npits=n_pits(nodes,nx,ny); //Finds the number of pits
  printf("n_pits: %lu \n",npits);
	
  long *pit_list;
  pit_list=(long *) malloc(nc*sizeof(long));
	
  pit_lister(nodes,nx,ny,pit_list);
	
	
  //for (i=0;i<npits;i++) printf("pit[%ld] = %ld \n",i,pit_list[i]);
	
	
	
  //expli_sed_cap_topsed_new(nodes,stack2,nx,ny,parameters,dx,dy);
  //expli_update_sed(nodes,stack,nx,ny,dx,dy,stack2,1,parameters); //Initializing the sediment in the streams.
	
	
  get_donorlist(nodes,nx,ny,stack,dx,dy,stack2,flist,baselevel_list,n_baselevelnodes,npits,pit_list); //Finds the stack, using the recursive algorithm from the Braun 2013 article
  output_number=write_output(nodes,mesh,path,file,fp,step,print_modulo,number_of_outputs,npits,output_path,landslides_since_last,parameters,output_number); //Writes output
  //flux_out(nodes,mesh,path,file,fp,step,output_path,parameters);
  weath_out(nodes,mesh,path,file,fp,step,output_path,parameters);
	
	
  //for (i=0;i<nx*nx*nx*nx*nx*nx;i++) 	get_reciever_wo_slope(nodes,nx,ny); //Finds the reciever of node
  double stop_uplift_time;
  stop_uplift_time=1.1;
	
  for (h=0;h<n_step;h++)
    {
		
      if (parameters[0].noheightchange=='n') {
	noheightchange_controller(nodes,mesh,path,file,fp,&step,print_modulo,number_of_outputs,output_path,h,n_step,parameters,&output_number,&counter,stack,stack2,pit_list,flist,baselevel_list,n_baselevelnodes,s_flist);
		
      }
      else {



	/*
      if (h>floor(2*n_step/10) && h<(1000+floor(2*n_step/10)))
	{
	  output_erosion(nodes,mesh,path,file,fp,&erosionoutputcounter,output_path,parameters);
	}

      if (h>floor(5*n_step/10) && h<(1000+floor(5*n_step/10)))
	{
	  output_erosion(nodes,mesh,path,file,fp,&erosionoutputcounter,output_path,parameters);
	}

      if (h>floor(8*n_step/10) && h<(1000+floor(8*n_step/10)))
	{
	  output_erosion(nodes,mesh,path,file,fp,&erosionoutputcounter,output_path,parameters);
	}
*/

	
	
	  
	//#pragma omp parallel
	{
	  //#pragma omp single nowait
	  { 
	    if (floor(fmod(counter,flux_out_modulo)==0)) {flux_out(nodes,mesh,path,file,fp,step,output_path,parameters); }
	    //printf ("1 id = %d, h=%g \n", omp_get_thread_num(),h);
				
	  }

    //#pragma omp single nowait
    { 
      //printf ("2 id = %d, \n", omp_get_thread_num());
      if (floor(fmod(counter,print_modulo)==0) /*step%(deltat*print_modulo)==0*/) 
	{
	  landslides_since_last=num_landslides-old_n_landslides;
	  //printf("numlandslides %ld landslides_since_last %ld old_landslides %ld \n",num_landslides,landslides_since_last,old_n_landslides);
	  old_n_landslides=num_landslides;
	  output_number=write_output(nodes,mesh,path,file,fp,step,print_modulo,number_of_outputs,npits,output_path,landslides_since_last,parameters,output_number); //Writes the output number_of_inputs time
	  //printf("Output number %g step %g \n",output_number,step);


	  output_erosion(nodes,mesh,path,file,fp,&erosionoutputcounter,output_path,parameters);

	}
    }		 

    //#pragma omp single
    {
      //printf ("3 id = %d, \n", omp_get_thread_num());
      if (floor(fmod(counter,weath_out_modulo)==0)) {weath_out(nodes,mesh,path,file,fp,step,output_path,parameters);}
    }
  } //Ends the parallel section
  //printf("\n");
}	


	
      transient_changes(parameters,nodes,&print_modulo,&output_burst,n_step,h,&uplift_change_counter,npits,stop_uplift_time,k_diff_original,step);

	
	for (i=0;i<nx*ny;i++)
	  {
	    nodes[i].top_old=nodes[i].topsedi;
	    nodes[i].bed_old=nodes[i].bed;
	  }
		
			
	get_reciever_wo_slope(nodes,nx,ny); //Getting the reciever of the node
	npits=n_pits(nodes,nx,ny); //Finds the number of pits
	if (npits>0) {
	  pit_lister(nodes,nx,ny,pit_list);
	}	
		
	if ((counter%50)==0) {
	  printf("iteration: %2.0f total %2.0f n_landslides %ld deltat %g time %g \n",h,n_step,num_landslides,parameters[0].deltat,step);
	  printf("n_pits: %lu \n",npits);
	} //Outputs the iteration number and total number of landslides to the terminal
	for (i=0;i<nx*ny;i++) {stack[i]=-1;} //Initializing the stack to -1, so that we can find which nodes are not in the stack
	get_donorlist(nodes,nx,ny,stack,dx,dy,stack2,flist,baselevel_list,n_baselevelnodes,npits,pit_list); //Finds the stack, using the recursive algorithm from the Braun 2013 article

	
	expli_solver(nodes,stack,nx,ny,npits,dx,dy,stack2,flist,s_flist,parameters);
		
		
	uplift(nodes,nx,ny,npits,parameters); //Getting the uplift		
	//weathering(nodes,nx,ny,parameters); //Performing weathering
		
	switch (landslide_type)
	  {
	  case 'a':
	    landslide_daniel(nodes,mesh,slist,npits,path,file,fp,output_path,step,&num_landslides,parameters); //Performing landslides
	    break;
	  case 'b':
	    landslide_david(nodes,mesh,slist,npits,path,file,fp,output_path,step,&num_landslides,parameters,h);
	    break;
	  }

		
		
		
		
		
		
	for (i=0;i<nx*ny;i++)
	  {
	    if (nodes[i].b==1 && nodes[i].topsedi!=0)
	      {
		printf("in main. baselevel node has nonzero topsedi thickness i %ld bed %g topsedi %g \n",i,nodes[i].bed,nodes[i].topsedi);
	      }
	  }
		
		

	if (output_burst<150000 && print_modulo!=parameters[0].print_modulo)
	  {
	    output_burst++;
	    //printf("output burst %ld \n",output_burst);
	  }
	else if (print_modulo!=parameters[0].print_modulo){	print_modulo=parameters[0].print_modulo;}
		
		
	     
	//smooth_erosion_handler(nodes,nx,ny,parameters);
	smooth_everything_handler(nodes,nx,ny,parameters);
	
	step+=parameters[0].deltat; //Advances the time
	counter++; //Advances the counter
		
	//
	if (flex_param=='b') {
	  if (h>floor(stop_uplift_time*n_step)) {
		
	    if (fmod(counter,50)==0) {calc_integral_flexure(nodes,nx,ny,dx,dy);}
	  }
	}
		
		
	//Here we perform the flexure or isostasy	
	if (flex_param=='a') {
	  if (h>floor(stop_uplift_time*n_step)){
	    isostasy(nodes,nx,ny);
	  }
	}
	else if (flex_param=='b') {
	  if (h>floor(stop_uplift_time*n_step)){
	    perform_integral_flexure(nodes,nx,ny);
	  }
	}
	else if (flex_param=='c') {
	  if (h>floor(stop_uplift_time*n_step)){
	    flexit(nodes,nx,ny,dx,dy);
	  }
	}
		

    }
	

	
  landslides_since_last=num_landslides-old_n_landslides;
  output_number=write_output(nodes,mesh,path,file,fp,step,print_modulo,number_of_outputs,npits,output_path,landslides_since_last,parameters,output_number); //Writes the final ouput
  n_slides(nodes,path,file,fp,output_path,num_landslides); //Makes the n_slides
  time = omp_get_wtime() - start_time; //Finds the difference between the start time and now
  //time=clock()-start_time;
	
  printf("Time taken %2.2f seconds \n", time); //Prints the time taken to run the model
	
  /*Frees all the allocated memory*/	
  //free(output_path);
  //free(path);
  free(fp);
  free(nodes);
  free(stack);
  free(pit_list);
  free(stack2);
  free (tmp);
  free (store);
  free(slist);
  free(flist);
  free(parameters);
  free(baselevel_list);
  //free(path);
  
  return 0;
}
