#include "header.h"

void transient_changes(model_parameters *parameters, nodetype *nodes,double *print_modulo,long *output_burst,long n_step,long h,long *uplift_change_counter,long npits,double stop_uplift_time,double k_diff_original,double step)
{
	
	//parameters[0].k_sed=100*1.21e0

  /*  
  if (npits==0 && (*uplift_change_counter)<505001)
    {
      (*uplift_change_counter)+=1;
      if ((*uplift_change_counter)==50001)
	{
	  parameters[0].split=0.1;
	  (*output_burst)=0;
	  (*print_modulo)=100;
	}
      if ((*uplift_change_counter)==120000)
	{
	  parameters[0].split=0.01;
	  (*output_burst)=0;
	  (*print_modulo)=100;
	}
      if((*uplift_change_counter)==200000)
	{
	  parameters[0].split=0.0;
	  (*output_burst)=0;
	  (*print_modulo)=100;
	}
    }
  */

  /*
  if (h==floor(0.1*n_step))
    {
      parameters[0].U=0;
      //(*output_burst)=0;
      //(*print_modulo)=200;
    }
  */


  /*
  if (h>floor(1*n_step/10))
    {
      parameters[0].k_diff=k_diff_original+0.5*k_diff_original*sin((h%1000)*2.0*M_PI/1000.0);
      //(*output_burst)=0;
      //(*print_modulo)=200;
    }
  */

  /*    
      if (h==floor(0.1*n_step/10))
	{
	  parameters[0].k_diff=0.5*k_diff_original;
	  //parameters[0].k_diff_sed_change=0.5;
	  //(*output_burst)=0;
	  //(*print_modulo)=1000;
	  //printf("1 \n");
	}
  */
      /*     
      if (h==floor(5*n_step/10))
	{
	  parameters[0].k_diff=1*k_diff_original;
	  //parameters[0].k_diff_sed_change=1.0;
	  (*output_burst)=0;
	  (*print_modulo)=100;
	  //printf("4 \n");
	}
      if (h==floor(8*n_step/10))
	{
	  parameters[0].k_diff=1.5*k_diff_original;
	  //parameters[0].k_diff_sed_change=1.5;
	  (*output_burst)=0;
	  (*print_modulo)=100;
	  //printf("7 \n");
	}
      */
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

  
	//parameters[0].uplift_type='f';
	//node_uplifts(nodes,nx,ny,npits,parameters);

	//if (h>(floor(0.1*n_step))) {parameters[0].K_s=250*1e-5; parameters[0].split=0.0;}
		
	//if (h>(floor(0.7*n_step))) {parameters[0].max_weath=5.0*1e-5; print_modulo=5; if(burst_starter_1=='y') {output_burst=0; burst_starter_1='n';}}
		
	//double stop_uplift_time=1.2;
	if (h==(floor(stop_uplift_time*n_step))) {parameters[0].U=0; /*print_modulo=1; if(burst_starter_1=='y') {output_burst=0; burst_starter_1='n';}*/}







		
	//Used for 1to10
	//parameters[0].max_weath=1e-6;
	//if (h>(floor(0.5*n_step))) {parameters[0].max_weath=1e-5; print_modulo=5; if(burst_starter_1=='y') {output_burst=0; burst_starter_1='n';}}
		
		
	//Used for 1to100
	//parameters[0].max_weath=1e-6;
	//if (h>(floor(0.5*n_step))) {parameters[0].max_weath=1e-4; print_modulo=5; if(burst_starter_1=='y') {output_burst=0; burst_starter_1='n';}}
		
		
	//Used for 100to10
	//parameters[0].max_weath=1e-4;
	//if (h>(floor(0.5*n_step))) {parameters[0].max_weath=1e-5; print_modulo=5; if(burst_starter_1=='y') {output_burst=0; burst_starter_1='n';}}
		
	//Used for 100to1
	//parameters[0].max_weath=1e-4;
	//if (h>(floor(0.5*n_step))) {parameters[0].max_weath=1e-6; print_modulo=5; if(burst_starter_1=='y') {output_burst=0; burst_starter_1='n';}}
		
		
	//parameters[0].k_diff=100*0.0000694557;
	//if (h>(floor(0.2*n_step))) {parameters[0].k_diff=0.0000694557; print_modulo=5;}
	//if (h>(floor(0.6*n_step))) {parameters[0].k_diff=100*100*0.0000694557; print_modulo=5;}
		
		


}
