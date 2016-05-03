/*In out*/

#include <sys/stat.h>
#include "header.h"
#include <dirent.h>


void initialize_modelparameters(model_parameters *parameters,meshtype mesh)
{
parameters[0].U=4e-3; //Uplift
//parameters[0].U=0; //Uplift
//parameters[0].K_stream=0.7e-5; //Fluvial erosion constant
parameters[0].K_stream=5e-4; //Fluvial erosion constant
parameters[0].n=1; //Slope exponent
parameters[0].M=0.5; //drainage exponents
parameters[0].n_diff=1; //diffusion exponent
parameters[0].deltat=1; //Time step
parameters[0].K_s=1e-3; //Constant from Sklaar Dietrich model
parameters[0].K_t=1e-0; //Constant related to the maximum sediment load
parameters[0].k_w=8e-4; //Constant related to the width of a channel
//parameters[0].k_diff=1e3*5e-5; //diffusion constant used without sediment
parameters[0].k_diff=100*0.0000694557; //diffusion constant used without sediment
	//The diffusion parameter has been chosen as 0.0000694557 such that a hillslope with an angle of S_c=tan(30*M_PI/180) has a diffusion of 4e-3 m/year*dx*dy
	//printf("%g  %g \n",S_c,tan(30*M_PI/180));
parameters[0].split=0.0; //The split between Saltation-Abrasion and Stream-Power models. 1=full stream power. 0=full saltation abrasion
parameters[0].bare_rock_weath=1e-5; //The weathering rate on bare bedrock
parameters[0].max_weath=0*1.0e-10; //The maximum weathering rate
parameters[0].R_star=1; //The sediment thickness that corresponds to maximum weathering
parameters[0].R_scale=1; //Scaling factor used in calculating the weathering rate
parameters[0].porosity=0; //The porosity of the weathered layer on top the bedrock
parameters[0].sedimentation_angle=0.02; //This is the angle that sediment will be sedimented with at a minimum. The angle is in [meters/meter]
parameters[0].landslide_angle=0.01; //This is the angle that landslides will deposit with. Unit is [meters/meter]
parameters[0].n_step=700000; //The number of steps that the model should run
parameters[0].n_landslide_pa=0*2.0; //The number of landslides per year
parameters[0].flux_out_modulo=1000; //Determines how many timesteps there is between each addition to the flux out file
parameters[0].weath_out_modulo=1; //Determines how many timesteps there is between each addition to the flux out file
parameters[0].do_fluvial_deposition='n'; //Determines whether rivers can deposit sediment or not
parameters[0].do_landslide_deposition='n';  //Determines whether landslides will move sediment, or just free it as sediment but not move it
parameters[0].landslide_type='a';  //Determines whether landslides will move sediment, or just free it as sediment but not move it
parameters[0].uplift_type='b'; //Determines the type of uplift. The available types at the moment are uniform uplift, called by 'a', and a tilting uplift, called by 'b', sideways uplift by 'c', mix of sideways uplift and tilting uplift by 'd' and a mix of sideways uplift the other way and tilting uplift by 'e'.
parameters[0].number_of_outputs=5;
if (parameters[0].number_of_outputs>parameters[0].n_step) {parameters[0].number_of_outputs=parameters[0].n_step;}
parameters[0].print_modulo=parameters[0].n_step/parameters[0].number_of_outputs;
parameters[0].bisection_it_crit=1e-4;
parameters[0].noheightchange='n'; //This paramters determines whether there should be any height change in the model. 'y' means that there will be height change in the model, while 'n' means that there will be no height change in the model.


parameters[0].k_sed=1.21e0; //Parameter that scales the sediment carrying capacity in the streams.
parameters[0].k_tau=1;
//parameters[0].tau_crit=27.1*parameters[0].k_tau; //tau_crit is scaled so that a channel with 80000m^2 and a slope of 50% will initiate a channel. A^(1/3)*S^(2/3)=27.1 when A=80000 and S=0.5
parameters[0].tau_crit=31.75*parameters[0].k_tau; //tau_crit is scaled so that a channel with 200000m^2 and a slope of 40% will initiate a channel. A^(1/3)*S^(2/3)=31,75 when A=200000 and S=0.4
//parameters[0].tau_crit=8E190*parameters[0].k_tau; //tau_crit is scaled so that a channel with 200000m^2 and a slope of 40% will initiate a channel. A^(1/3)*S^(2/3)=8 when A=200000 and S=0.05
//parameters[0].tau_crit=0*parameters[0].k_tau; //tau_crit is scaled so that a channel with 80000m^2 and a slope of 50% will initiate a channel. A^(1/3)*S^(2/3)=27.1 when A=80000 and S=0.5
//parameters[0].tau_crit=64*parameters[0].k_tau; //tau_crit is scaled so that a channel with 80000m^2 and a slope of 50% will initiate a channel. A^(1/3)*S^(2/3)=64 when A=5*200*200 and S=0.57*2

parameters[0].nx=mesh.nx;
parameters[0].ny=mesh.ny;
parameters[0].dx=mesh.dx;
parameters[0].dy=mesh.dy;
}


//void loadmesh(meshtype *mesh, char* path, char file[200], FILE *fp,int go_on)
meshtype loadmesh(char* path, char file[200], FILE *fp,int go_on)
{
	meshtype mesh;
	
	if (go_on==0)
	{
   	sprintf(file,"%s/meshdata.input",path); /*filename*/
		printf("File path: %s/meshdata.input \n",path);
   	if ((fp = fopen(file,"rb")) == NULL) { //Opens the file as a binary for reading in fp
     		printf("Cannot open file : %s/meshdata.input\n",path);
     		exit(1);
   	}
	}
	else if (go_on==1)
	{	
		char last_file[200];
		char tmp_file[200];
		char tmp_file2[200];
		FILE *fp2=NULL;
		int i;
				
		system("bash last_file.sh");
	   sprintf(tmp_file,"%s/output/last_file",path); //filename
		printf("file: %s \n",tmp_file);
		
	   fp2 = fopen(tmp_file,"rb");
	   fread(last_file,22*sizeof(char),1,fp2); //The 22 chars are from ./output+14numbers
		printf("last_file: %s \n",last_file);
		for (i=0;i<20;i++)
		{
			tmp_file2[i]=last_file[i+2];
		}
		printf("last_file: %s \n",tmp_file2);
		sprintf(file,"%s/output/%s",path,tmp_file2);
		printf("file: %s \n",file);
   	if ((fp = fopen(file,"rb")) == NULL) { //Opens the file in fp
     		printf("Cannot open file : %s\n",file);
     		exit(1);
   	}
		fclose(fp2);
		free(fp2);
   }
	else
	{
		printf("Go_on has been assigned a wrong value. Please assign it to either 0 or 1 in the main.c file");
		exit(1);
	}
	
   fread(&mesh.nx,sizeof(long),1,fp);  //Finds nx
	printf("nx: %ld \n",mesh.nx);
	fread(&mesh.ny,sizeof(long),1,fp);  //Finds ny
	printf("ny: %ld \n",mesh.ny);
	mesh.nc=mesh.nx*mesh.ny;
	fread(&mesh.dx,sizeof(double),1,fp);  //Finds dx
	printf("dx: %f \n",mesh.dx);
	fread(&mesh.dy,sizeof(double),1,fp);  //Finds dy
	printf("dy: %f \n",mesh.dy);
	fread(&mesh.step,sizeof(double),1,fp);  //Finds the step number
	printf("step: %5.0e \n",mesh.step);
	fclose(fp);

//	return mesh;
	return mesh;

}    /*This function reads the mesh from an input file. This input file can either be a file generated from matlab, but can also be a former output file from the model.*/

void initialize(nodetype *nodes,meshtype mesh,char *path,char file[200],FILE *fp,int go_on,model_parameters *parameters)
{
	long i,j;
	long nx=mesh.nx;
	long ny=mesh.ny;
	
   if (go_on==0)
	{
   	sprintf(file,"%s/meshdata.input",path); /*filename*/
		printf("%s/meshdata.input \n",path);
   	if ((fp = fopen(file,"rb")) == NULL) { //Opens the file in fp
     		printf("Cannot open file : %s/meshdata.input\n",path);
     		exit(1);
   	}
	}
	else if (go_on==1)
	{	
		char last_file[200];
		char tmp_file[200];
		char tmp_file2[200];
		system("bash last_file.sh");
	   sprintf(tmp_file,"%s/output/last_file",path); //filename
		printf("file: %s \n",tmp_file);
		FILE *fp2=NULL;
	   fp2 = fopen(tmp_file,"rb");
	   fread(last_file,22*sizeof(char),1,fp2); //The 22 chars are from ./output+14numbers
		printf("last_file: %s \n",last_file);
		int i;
		for (i=0;i<20;i++)
		{
			tmp_file2[i]=last_file[i+2];
		}
		printf("last_file: %s \n",tmp_file2);
		sprintf(file,"%s/output/%s",path,tmp_file2);
		printf("file: %s \n",file);
   	if ((fp = fopen(file,"rb")) == NULL) { //Opens the file in fp
     		printf("Cannot open file : %s\n",file);
     		exit(1);
   	}
		fclose(fp2);
		free(fp2);
   }
	else
	{
		printf("Go_on has been assigned a wrong value. Please assign it to either 0 or 1 in the main.c file");
		exit(1);
	}
	
	if (go_on==1)
	{
	fread(&nodes[0].bed,3*sizeof(long),1,fp); //This is done to skip the first two ints (nx and ny) in the stream, how is this done more elegantly?
	fread(&nodes[0].bed,6*sizeof(double),1,fp); //This is done to skip the first two ints (nx and ny) in the stream, how is this 
	}
	else if (go_on==0)
	{
		fread(&nodes[0].bed,2*sizeof(long),1,fp); //This is done to skip the first two ints (nx and ny) in the stream, how is this done more elegantly?
		fread(&nodes[0].bed,3*sizeof(double),1,fp); //This is done to skip the first two ints (nx and ny) in the stream, how is this done more elegantly?
	}
	else
	{
		printf("problem: go_on parameter not assigned to either 0 or 1 \n");
		exit(1);
	}
	for (i=0;i<nx*ny;i++) {
		if (parameters[0].noheightchange=='n') {
			fread(&nodes[i].bed,sizeof(double),1,fp); fread(&nodes[i].topsedi,sizeof(double),1,fp); nodes[i].bed=nodes[i].topsedi; nodes[i].sediment_thickness=nodes[i].topsedi-nodes[i].bed;
		}
		else {
			fread(&nodes[i].bed,sizeof(double),1,fp); fread(&nodes[i].topsedi,sizeof(double),1,fp); nodes[i].sediment_thickness=nodes[i].topsedi-nodes[i].bed;
		}
	}
	
#pragma omp parallel for default(none) private(i,j) shared(nx,ny,nodes) //if((nx*ny)>(100*100))
	for (i=0;i<nx*ny;i++) {
		nodes[i].erosion=0;
		nodes[i].total_landslide_erosion=0;
		nodes[i].catchment_landsliding=0;
		nodes[i].catchment_sediment=0;
		nodes[i].catchment_erosion=0;
		nodes[i].upstream_erosion=0;
		nodes[i].sediment_capa_sedi=0;
		nodes[i].sediment_capa_bed=0;
		//nodes[i].sediment_thickness=0;
		nodes[i].inslide=0;
		nodes[i].landslide_erosion=0;
		nodes[i].landslide_deposition=0;
		nodes[i].fluvial_deposition=0;
		nodes[i].upstream_erosion_old=0;
		nodes[i].total_distance=0;
		nodes[i].landslides_since_last=0;
 		nodes[i].total_distance=0;
 		nodes[i].landslides_since_last=0;
 		nodes[i].catchment_streampower=0;
 		nodes[i].catchment_saltabr=0;
		nodes[i].catchment_bedrock_landslide_erosion=0;
		nodes[i].total_height=0;
		nodes[i].catchment_av_height=0;
		nodes[i].nodes_in_catchment=0;
		nodes[i].total_sediment=0;
		nodes[i].total_erosion=0;
		nodes[i].total_streampower=0;
		nodes[i].total_saltabr=0;
		for (j=0;j<100;j++) {nodes[i].smooth_erosion_list[j]=0;}
		nodes[i].smooth_erosion=0;
		nodes[i].smooth_counter=0;		
	}
	fclose(fp);
} /*Initializes the bed topography, as well as the topography of the top of the sediment*/


void make_log(nodetype *nodes,meshtype mesh,char *path,char file[200],FILE *fp,double print_modulo,double number_of_outputs,char *output_path,model_parameters *parameters)
{
   char file_path[400];
	time_t ltime; /* calendar time */
	
   /*create output file*/
   //sprintf(file,"%s/output/output%09ld.dat",path,step);
   if (output_path!=NULL)
   {
 	  sprintf(file_path,"%s/output/%s",path,output_path);
 	  sprintf(file,"%s/log.txt",file_path);
   		mkdir(file_path,0777); /* The 0777 is to allow the path to be created and read by all users*/
 	}
 	else {
  	  sprintf(file,"%s/output/log.txt",path);
 	}
		
   if ((fp = fopen(file,"w+")) == NULL) {
     printf("could not open file for writing, %s, file %s \n",path,file);
     exit(1);
   }
	else {
		ltime=time(NULL); /* get current cal time */	
		fprintf(fp,"Time stamp %s",asctime(localtime(&ltime)));
    	fprintf(fp,"U: %g \n",parameters[0].U);
   	fprintf(fp,"K_stream %g \n",parameters[0].K_stream);
    	fprintf(fp,"n: %g \n",parameters[0].n);
    	fprintf(fp,"M: %g \n",parameters[0].M);
   	fprintf(fp,"n_diff %g \n",parameters[0].n_diff);
    	fprintf(fp,"deltat: %g \n",parameters[0].deltat);
    	fprintf(fp,"K_s: %g \n",parameters[0].K_s);
   	fprintf(fp,"K_t %g \n",parameters[0].K_t);
    	fprintf(fp,"k_w: %g \n",parameters[0].k_w);
    	fprintf(fp,"k_diff: %g \n",parameters[0].k_diff);
   	fprintf(fp,"split %g \n",parameters[0].split);
    	fprintf(fp,"bare_rock_weath: %g \n",parameters[0].bare_rock_weath);
    	fprintf(fp,"max_weath: %g \n",parameters[0].max_weath);
   	fprintf(fp,"R_star %g \n",parameters[0].R_star);
    	fprintf(fp,"R_scale: %g \n",parameters[0].R_scale);
   	fprintf(fp,"porosity %g \n",parameters[0].porosity);
    	fprintf(fp,"sedimentation_angle: %g \n",parameters[0].sedimentation_angle);
    	fprintf(fp,"landslide_angle: %g \n",parameters[0].landslide_angle);
   	fprintf(fp,"n_step %g \n",parameters[0].n_step);
    	fprintf(fp,"n_landslide_pa: %g \n",parameters[0].n_landslide_pa);
    	fprintf(fp,"number of outputs: %ld \n",parameters[0].number_of_outputs);
    	fprintf(fp,"print_modulo: %g \n",parameters[0].print_modulo);
    	fprintf(fp,"flux_out_modulo: %g \n",parameters[0].flux_out_modulo);
		fprintf(fp,"do fluvial deposition %c \n",parameters[0].do_fluvial_deposition);
		fprintf(fp,"do landslide deposition %c \n",parameters[0].do_landslide_deposition);
		fprintf(fp,"landslide_type  %c, (a=daniel, b=david) \n",parameters[0].landslide_type);
		fprintf(fp,"uplift type %c \n",parameters[0].uplift_type);
		fprintf(fp,"bisection it crit lowering %g \n",parameters[0].bisection_it_crit);
		fprintf(fp,"tau crit %g \n",parameters[0].tau_crit);
		fprintf(fp,"k tau %g \n",parameters[0].k_tau);
		fprintf(fp,"k sed %g \n",parameters[0].k_sed);
		
		
		fclose(fp);
	}
	
}/*This file creates a log of the global parameters used in the model. Additional things that should be built into this log includes: Sedimentation is on for rivers/landslides. Number of outputs.*/


double write_output(nodetype *nodes,meshtype mesh,char *path,char file[200],FILE *fp,double step,double print_modulo,double number_of_outputs, long pits,char *output_path,long landslides_since_last,model_parameters *parameters,double output_number)
{
  long i;
  long nx = mesh.nx;
  long ny = mesh.ny;
  double dx = mesh.dx;
  double dy = mesh.dy;
  char file_path[400];
  double total_height=0;
  double av_height=0;
  double max_height=0;
  double total_incision=0;
  double av_incision=0;

  /*create output file*/
  //sprintf(file,"%s/output/output%09ld.dat",path,step);
  /*
  if (output_path!=NULL)
  {
	  sprintf(file_path,"%s/output/%s",path,output_path);
	  sprintf(file,"%s/output%014.2f",file_path,step);
  		mkdir(file_path,0777); //The 0777 is to allow the path to be created and read by all users
	}
	else {
 	  sprintf(file,"%s/output/output%014.2f",path,step);
	}
	*/
  
   if (output_path!=NULL)
   {
  	  sprintf(file_path,"%s/output/%s",path,output_path); 
		
		
	  
 
 	  sprintf(file,"%s/output%014.2f",file_path,output_number);
     mkdir(file_path,0777); /* The 0777 is to allow the path to be created and read by all users*/
 	}
 	else {
  	  sprintf(file,"%s/output/output%014.2f",path,step);
 	}
    
  
  
  if ((fp = fopen(file,"wb")) == NULL) {
    printf("could not open file for writing, %s, file %s \n",path,file);
    exit(1);
  }
  else
  {
	  
	for (i=0;i<nx*ny;i++)
	{
		total_height+=nodes[i].topsedi;
		if (nodes[i].topsedi>max_height)
		{
			max_height=nodes[i].topsedi;
		}
	}
	av_height=total_height/(nx*ny);
	 
	total_incision=0;
	
	for (i=0;i<nx*ny;i++)
	{
		total_incision+=nodes[i].saltabr_incision;
	}
	av_incision=total_incision/(dx*dy);
	
	
	  
    	fwrite(&nx,sizeof(long),1,fp);
   	fwrite(&ny,sizeof(long),1,fp);
    	fwrite(&dx,sizeof(double),1,fp);
   	fwrite(&dy,sizeof(double),1,fp);
		fwrite(&step,sizeof(double),1,fp);
  	  	if (step==0)
  	 {
	printf("size int %ld \n",sizeof(int));
	printf("size long %ld \n",sizeof(long));
	printf("size double %ld \n",sizeof(double));
 		}
		fwrite(&print_modulo,sizeof(double),1,fp);
		fwrite(&number_of_outputs,sizeof(double),1,fp);
		fwrite(&parameters[0].deltat,sizeof(double),1,fp);
	fwrite(&pits,sizeof(long),1,fp);
	fwrite(&av_height,sizeof(long),1,fp);
	fwrite(&max_height,sizeof(long),1,fp);
	fwrite(&av_incision,sizeof(double),1,fp);
	fwrite(&landslides_since_last,sizeof(long),1,fp);
	for (i=0;i<ny*nx;i++) fwrite(&nodes[i].bed,sizeof(double),1,fp);
	for (i=0;i<ny*nx;i++) fwrite(&nodes[i].topsedi,sizeof(double),1,fp);
	for (i=0;i<ny*nx;i++) fwrite(&nodes[i].id,sizeof(long),1,fp);
	for (i=0;i<ny*nx;i++) fwrite(&nodes[i].r,sizeof(long),1,fp);
	for (i=0;i<ny*nx;i++) fwrite(&nodes[i].drain_area,sizeof(double),1,fp);
	for (i=0;i<ny*nx;i++) fwrite(&nodes[i].reciever_distance,sizeof(double),1,fp);
	for (i=0;i<ny*nx;i++) fwrite(&nodes[i].erosion,sizeof(double),1,fp);
	for (i=0;i<ny*nx;i++) fwrite(&nodes[i].fluv,sizeof(double),1,fp);
	for (i=0;i<ny*nx;i++) fwrite(&nodes[i].diff,sizeof(double),1,fp);
	for (i=0;i<ny*nx;i++) fwrite(&nodes[i].fluv_over_diff,sizeof(double),1,fp);
	for (i=0;i<ny*nx;i++) fwrite(&nodes[i].rel_sedi,sizeof(double),1,fp);
	for (i=0;i<ny*nx;i++) fwrite(&nodes[i].sediment_capa_sedi,sizeof(double),1,fp);
	for (i=0;i<ny*nx;i++) fwrite(&nodes[i].stream_power,sizeof(double),1,fp);
	for (i=0;i<ny*nx;i++) fwrite(&nodes[i].channel_width,sizeof(double),1,fp);
	for (i=0;i<ny*nx;i++) fwrite(&nodes[nodes[i].r].bed,sizeof(double),1,fp);
	for (i=0;i<ny*nx;i++) fwrite(&nodes[nodes[nodes[i].r].r].bed,sizeof(double),1,fp);
	for (i=0;i<ny*nx;i++) fwrite(&nodes[i].upstream_erosion,sizeof(double),1,fp);
	for (i=0;i<nx*ny;i++) fwrite(&nodes[i].landslide_erosion,sizeof(double),1,fp);
	for (i=0;i<nx*ny;i++) fwrite(&nodes[i].reciever_slope,sizeof(double),1,fp);
	for (i=0;i<nx*ny;i++) fwrite(&nodes[i].moved_sediment,sizeof(double),1,fp);
	for (i=0;i<nx*ny;i++) fwrite(&nodes[i].landslide_deposition,sizeof(double),1,fp);
	for (i=0;i<nx*ny;i++) fwrite(&nodes[i].fluvial_deposition,sizeof(double),1,fp);
	for (i=0;i<nx*ny;i++) fwrite(&nodes[i].in_stack,sizeof(long),1,fp);
	for (i=0;i<nx*ny;i++) fwrite(&nodes[i].total_landslide_erosion,sizeof(double),1,fp);
	for (i=0;i<nx*ny;i++) fwrite(&nodes[i].river,sizeof(double),1,fp);
	for (i=0;i<nx*ny;i++) fwrite(&nodes[i].sediment_thickness,sizeof(double),1,fp);
	for (i=0;i<nx*ny;i++) fwrite(&nodes[i].deflection,sizeof(double),1,fp);
	for (i=0;i<nx*ny;i++) fwrite(&nodes[i].smooth_erosion,sizeof(double),1,fp);
	fclose(fp);
	//free(file_path);
  }
  
  
  
  for (i=0;i<nx*ny;i++) {
	  if (fabs((nodes[i].topsedi-nodes[i].bed)-nodes[i].sediment_thickness)>1e-5) printf("Inout sedthick!=topsedi-bed sedthick %g topsedi %g bed %g topsedi-bed %g node %ld \n",nodes[i].sediment_thickness,nodes[i].topsedi,nodes[i].bed,nodes[i].topsedi-nodes[i].bed,i);
  }
  
  output_number++;
  return output_number;
} /*Writes output to a new file marked with the timestep number*/

void output_landslides(nodetype *nodes,meshtype mesh,char *path,char file[200],FILE *fp,double step,long i,double landslide_size,long catchment,char *output_path,long nodes_in_landslide,long *num_landslides)
{
   long nx = mesh.nx;
   long ny = mesh.ny;
   double dx = mesh.dx;
   double dy = mesh.dy;
   char file_path[400];

	/*Adds a landslide to the total number of landslides*/
	*num_landslides+=1;
	//printf("numlandslides %ld \n",*num_landslides);
   /*create output file*/
   //sprintf(file,"%s/output/output%09ld.dat",path,step);
   if (output_path!=NULL)
   {
 	  sprintf(file_path,"%s/output/%s",path,output_path);
 	  sprintf(file,"%s/landslides",file_path);
 		mkdir(file_path,0777); /* The 0777 is to allow the path to be created and read by all users*/
 	}
 	else {
  	  sprintf(file,"%s/output/landslides",path);
 	}
 
   if ((fp = fopen(file,"a")) == NULL) {
     printf("could not open file for writing, %s, file %s \n",path,file);
     exit(1);
   }
   else
   {
		
  	fwrite(&nx,sizeof(long),1,fp);
 	fwrite(&ny,sizeof(long),1,fp);
  	fwrite(&dx,sizeof(double),1,fp);
 	fwrite(&dy,sizeof(double),1,fp);
	fwrite(&step,sizeof(double),1,fp);
	fwrite(&i,sizeof(long),1,fp);
	fwrite(&catchment,sizeof(long),1,fp);
	fwrite(&landslide_size,sizeof(double),1,fp);
	fwrite(&nodes_in_landslide,sizeof(long),1,fp);
	fwrite(&nodes[i].topsedi,sizeof(double),1,fp);
	fwrite(&nodes[i].distance_to_base,sizeof(double),1,fp);
	fclose(fp);
	}
} /*Outputs the landslides that happened in this timestep*/

void flux_out(nodetype *nodes,meshtype mesh,char *path,char file[200],FILE *fp,double step,char *output_path,model_parameters *parameters)
{
   long nx = mesh.nx;
	long ny=mesh.ny;
   char file_path[400];
	long i;
	double av_distance;
  	/*create output file*/
   //sprintf(file,"%s/output/output%09ld.dat",path,step);
   if (output_path!=NULL)
   {
 	  sprintf(file_path,"%s/output/%s",path,output_path);
 	  sprintf(file,"%s/fluxout",file_path);
 		mkdir(file_path,0777); /* The 0777 is to allow the path to be created and read by all users*/
 	}
 	else {
  	  sprintf(file,"%s/output/fluxout",path);
 	}
 
   if ((fp = fopen(file,"a")) == NULL) {
     printf("could not open file for writing, %s, file %s \n",path,file);
     exit(1);
   }
   else
   {
  	  if (step==0)
  	  {
 		  fwrite(&parameters[0].n_step,sizeof(double),1,fp);
		  fwrite(&parameters[0].flux_out_modulo,sizeof(double),1,fp);
 		}
 	 	fwrite(&step,sizeof(double),1,fp);
 		for (i=0;i<nx;i++) fwrite(&nodes[i].landslide_out,sizeof(double),1,fp);
		for (i=0;i<nx;i++) fwrite(&nodes[i].upstream_erosion,sizeof(double),1,fp);
 		for (i=0;i<nx;i++) fwrite(&nodes[i].catchment_landsliding,sizeof(double),1,fp);
 		for (i=0;i<nx;i++) fwrite(&nodes[i].catchment_erosion,sizeof(double),1,fp);
 		for (i=0;i<nx;i++) fwrite(&nodes[i].catchment_sediment,sizeof(double),1,fp);
 		
		for (i=0;i<nx;i++) {
			if (nodes[i].landslides_since_last>0)
			{
				av_distance=(nodes[i].total_distance/nodes[i].landslides_since_last); 
			}
			else
			{
				av_distance=0;
			}
			fwrite(&av_distance,sizeof(double),1,fp);
		}
 		for (i=0;i<nx;i++) fwrite(&nodes[i].catchment_streampower,sizeof(double),1,fp);
 		for (i=0;i<nx;i++) fwrite(&nodes[i].catchment_saltabr,sizeof(double),1,fp);
 		for (i=0;i<nx;i++) fwrite(&nodes[i].catchment_bedrock_landslide_erosion,sizeof(double),1,fp);
		for (i=0;i<nx*ny;i++)
		{
			if (nodes[i].in_stack==1 && nodes[i].c>=0)
			{
				nodes[nodes[i].c].total_height+=nodes[i].topsedi;
				//printf("total height %7.3f, catchment %ld i: %ld \n",nodes[nodes[i].c].total_height,nodes[i].c,i);
				nodes[nodes[i].c].nodes_in_catchment++;
			}
		}
		for (i=0;i<nx;i++)
		{
			nodes[i].catchment_av_height=nodes[i].total_height/nodes[i].nodes_in_catchment;
			//printf("av height %7.3f total height %7.3f \n",nodes[i].catchment_av_height,nodes[i].total_height);
		}
		for (i=0;i<nx;i++) fwrite(&nodes[i].catchment_av_height,sizeof(double),1,fp);
 		fwrite(&nodes[0].total_erosion,sizeof(double),1,fp);
		fwrite(&nodes[0].total_streampower,sizeof(double),1,fp);
 		fwrite(&nodes[0].total_saltabr,sizeof(double),1,fp);
 		fwrite(&nodes[0].total_sediment,sizeof(double),1,fp);
	fclose(fp);
 	}
	
#pragma omp parallel for default(none) private(i) shared(nx,ny,nodes) //if((nx*ny)>(100*100))
  	for (i=0;i<nx*ny;i++)
 	{
		nodes[i].total_height=0;
		nodes[i].catchment_av_height=0;
		nodes[i].nodes_in_catchment=0;
 		nodes[i].total_distance=0;
 		nodes[i].landslides_since_last=0;
 		nodes[i].catchment_sediment=0;
 		nodes[i].catchment_erosion=0;
 		nodes[i].catchment_streampower=0;
 		nodes[i].catchment_saltabr=0;
		nodes[i].catchment_landsliding=0;
		nodes[i].catchment_bedrock_landslide_erosion=0;
		nodes[0].total_sediment=0;
		nodes[0].total_erosion=0;
		nodes[0].total_streampower=0;
		nodes[0].total_saltabr=0;
 	}
} /*Gives the flux out of the catchment, as well as the landsliding in the individual catchments*/


void weath_out(nodetype *nodes,meshtype mesh,char *path,char file[200],FILE *fp,double step,char *output_path,model_parameters *parameters)
{
   long nx = mesh.nx;
	long ny=mesh.ny;
	long dx=mesh.dx;
	long dy=mesh.dy;
   char file_path[400];
	long i;
  	/*create output file*/
   //sprintf(file,"%s/output/output%09ld.dat",path,step);
   if (output_path!=NULL)
   {
 	  sprintf(file_path,"%s/output/%s",path,output_path);
 	  sprintf(file,"%s/weathout",file_path);
 		mkdir(file_path,0777); /* The 0777 is to allow the path to be created and read by all users*/
 	}
 	else {
  	  sprintf(file,"%s/output/weathout",path);
 	}
 
   if ((fp = fopen(file,"a")) == NULL) {
     printf("could not open file for writing, %s, file %s \n",path,file);
     exit(1);
   }
   else
   {
		double mean_weath=0;
		double mean_erosion=0;
		double mean_diff=0;
		double mean_moved_fluvial_sediment=0;
		double mean_topsedi=0;
		double mean_bed=0;
		double river_nodes=0;
		double mean_sedimentthickness=0;
		double mean_saltabr_fraction=0;
		long counter_fluv=0;
		long counter_diff=0;
		long counter_saltabr=0;
		long total_counter=0;
		
  	  if (step==0)
  	  {
 		 fwrite(&parameters[0].n_step,sizeof(double),1,fp);
		 fwrite(&parameters[0].weath_out_modulo,sizeof(double),1,fp);
   	// fwrite(&step,sizeof(double),1,fp);
  	 	// fwrite(&mean_weath,sizeof(double),1,fp);
  	 	// fwrite(&mean_erosion,sizeof(double),1,fp);
  	 	// fwrite(&mean_diff,sizeof(double),1,fp);
  	 	// fwrite(&mean_moved_fluvial_sediment,sizeof(double),1,fp);
	 }
	 else {		
		

		
		for (i=0;i<nx*ny;i++)
		{
			if (nodes[i].b!=1) {
				mean_weath+=nodes[i].weath;
				mean_topsedi+=nodes[i].topsedi;
				mean_bed+=nodes[i].bed;
				mean_sedimentthickness+=nodes[i].sediment_thickness;
				total_counter++;
				if (nodes[i].river==1 && nodes[i].b!=1) {
					mean_erosion+=nodes[i].erosion;
					mean_moved_fluvial_sediment+=nodes[i].moved_sediment;
					if (nodes[i].saltabr_incision+nodes[i].stream_power>0) {
						mean_saltabr_fraction+=nodes[i].saltabr_incision/(nodes[i].saltabr_incision+nodes[i].stream_power);
						counter_saltabr++;
					}
					counter_fluv++;
					river_nodes++;
				}
				else if(nodes[i].river==0 && nodes[i].b!=1) {
					mean_diff+=nodes[i].diff;
					counter_diff++;
				}
			}
		}
		mean_weath/=total_counter;
		mean_topsedi/=total_counter;
		mean_bed/=total_counter;
		mean_sedimentthickness/=total_counter;
		mean_erosion/=(counter_fluv*dx*dy);
		mean_saltabr_fraction/=(counter_saltabr);
		mean_diff/=counter_diff;
		mean_moved_fluvial_sediment/=counter_fluv;
		
 	 	fwrite(&step,sizeof(double),1,fp);
		fwrite(&mean_weath,sizeof(double),1,fp);
 	 	fwrite(&mean_erosion,sizeof(double),1,fp);
 	 	fwrite(&mean_diff,sizeof(double),1,fp);
 	 	fwrite(&mean_moved_fluvial_sediment,sizeof(double),1,fp);
		fwrite(&mean_topsedi,sizeof(double),1,fp);
		fwrite(&mean_sedimentthickness,sizeof(double),1,fp);
		fwrite(&river_nodes,sizeof(double),1,fp);
		fwrite(&mean_bed,sizeof(double),1,fp);
		//fwrite(&mean_saltabr_fraction,sizeof(double),1,fp);
		
		//printf("mean saltabr_fraction %g \n",mean_saltabr_fraction);
		
		
		/*printf("step %g \n",step);
		printf("mean weath %g \n",mean_weath);
		printf("mean erosion %g \n",mean_erosion);
		printf("mean diff %g \n",mean_diff);
		printf("mean moved fluvial sediment %g \n",mean_moved_fluvial_sediment);
		printf("mean topsedi %g \n",mean_topsedi);
		printf("mean sedithick %g \n",mean_sedimentthickness);*/
		
		
	}
		
		
		fclose(fp);
 	}
}



void delete_slides_file(char *path,char file[200],FILE *fp,char *output_path)
{
   char file_path[400];
	
	
	
	//Here I create the folder if it doesn't exist
   if (output_path!=NULL)
   {
	  sprintf(file_path,"%s/output/%s",path,output_path);
 	  mkdir(file_path,0777); /* The 0777 is to allow the path to be created and read by all users*/
 	}
 		
	
	
	//Here I empty the folder
   sprintf(file_path,"%s/Output/%s",path,output_path);
	DIR *theFolder = opendir(file_path);
   struct dirent *next_file;
   char filepath[256];
	
   while ( (next_file = readdir(theFolder)) != NULL )
   {
       // build the path for each file in the folder
	    sprintf(filepath, "%s/%s", file_path,next_file->d_name);
       remove(filepath);
		 
   }
	
	
	
   if (output_path!=NULL)
   {
 	  sprintf(file_path,"%s/output/%s",path,output_path);
 	  sprintf(file,"%s/landslides",file_path);
 	  mkdir(file_path,0777); /* The 0777 is to allow the path to be created and read by all users*/
 	}
 	else {
  	  sprintf(file,"%s/output/landslides",path);
 	}
 
   if ((fp = fopen(file,"w")) == NULL) {
     printf("could not open file for writing in delete slides file, %s, file %s \n",path,file);
     exit(1);
   }
   else
   {
  	fclose(fp);
	}
	
	
   /*Deleting old fluxout file*/
	
   if (output_path!=NULL)
   {
 	  sprintf(file_path,"%s/output/%s",path,output_path);
 	  sprintf(file,"%s/fluxout",file_path);
 		mkdir(file_path,0777); /* The 0777 is to allow the path to be created and read by all users*/
 	}
 	else {
  	  sprintf(file,"%s/output/fluxout",path);
 	}
 
   if ((fp = fopen(file,"w")) == NULL) {
     printf("could not open file for writing in delete slides file, %s, file %s \n",path,file);
     exit(1);
   }
   else
   {
  	fclose(fp);
	}
	
	
   /*Deleting old fluxout file*/
	
   if (output_path!=NULL)
   {
 	  sprintf(file_path,"%s/output/%s",path,output_path);
 	  sprintf(file,"%s/weathout",file_path);
 		mkdir(file_path,0777); /* The 0777 is to allow the path to be created and read by all users*/
 	}
 	else {
  	  sprintf(file,"%s/output/weathout",path);
 	}
 
   if ((fp = fopen(file,"w")) == NULL) {
     printf("could not open file for writing in delete slides file, %s, file %s \n",path,file);
     exit(1);
   }
   else
   {
  	fclose(fp);
	}
	
   /*Deleting old n_landslides file*/
	
	
	if (output_path!=NULL)
   {
 	  sprintf(file_path,"%s/output/%s",path,output_path);
 	  sprintf(file,"%s/n_landslides",file_path);
 	}
 	else {
  	  sprintf(file,"%s/output/landslides",path);
 	}
 
   if ((fp = fopen(file,"w+")) == NULL) {
     printf("could not open file for writing, %s, file %s \n",path,file);
     exit(1);
   }
   else
   {
  	fclose(fp);
	}

}/*This file erases the content of the old landslides and fluxout files in the folder*/

void n_slides(nodetype *nodes,char *path,char file[200],FILE *fp,char *output_path,long num_landslides)
{
   char file_path[400];

   /*create output file*/
   //sprintf(file,"%s/output/output%09ld.dat",path,step);
   if (output_path!=NULL)
   {
 	  sprintf(file_path,"%s/output/%s",path,output_path);
 	  sprintf(file,"%s/n_landslides",file_path);
   		mkdir(file_path,0777); /* The 0777 is to allow the path to be created and read by all users*/
 	}
 	else {
  	  sprintf(file,"%s/output/landslides",path);
 	}
 
   if ((fp = fopen(file,"a")) == NULL) {
     printf("could not open file for writing, %s, file %s \n",path,file);
     exit(1);
   }
   else
   {
  	fwrite(&num_landslides,sizeof(long),1,fp);
	fclose(fp);
	}
} /*Outputs the number of slides that from the model*/
