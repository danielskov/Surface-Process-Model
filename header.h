#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>
#include <omp.h>
#include "limits.h"

#define MAX_NEIGH 9
#define smoother 50

#ifndef HEADER_H_
#define HEADER_H_

/* Structure declarations */
typedef struct
{
  long id, r, di; //node id, node reciever, number of direct donors, 
  long delta, D; //From JB article, From JB article
  long Dij[MAX_NEIGH]; //Array with direct donors, 
  long n_neigh, neigh[MAX_NEIGH], w; //number of neighbours, Array of neighbours, From JB article, 
  long in_stack; //Drainage area to node, Is the node in the stack?
  double drain_area;
  long c; //Catchment number
  long b; //Baselevel or not: Baselevel=1, not baselevel=0; 
  long p; //pit node or not?
  double reciever_slope; //Slope to the reciever
  double bed;
  double erosion,upstream_erosion;
  double distance[MAX_NEIGH], reciever_distance,slope[MAX_NEIGH]; //Height of node, Distance to neighbours, Distance to reciever, slope to neighbours
  double channel_width; //The width of the channel at the point
  double node_uplift; //Opløftet i noden
  double bed_new;
  double fluv,diff; //Used for output. Fluv is sed_incision+stream_power, while diff is the diffusion in the cell
  double stream_power; //Used for output. Is the streampower erosion in the cell.
  double fluv_over_diff; //Used for output. The fraction of fluvial erosion to diffusive erosion.
  double rel_sedi;
  double sediment_capa_sedi,sediment_capa_bed;
  double sediment_thickness,topsedi;
  long x,y;
  long inslide;
  double phi;
  double rfail;
  double landslide_erosion,total_landslide_erosion;
  double topsedi_new, eroding_sediment;
  double moved_sediment;
  double landslide_deposition,fluvial_deposition;
  double distance_to_base;
  double landslide_out;
  double upstream_erosion_old;
  double catchment_landsliding;
  double catchment_erosion,catchment_sediment;
  double total_distance,landslides_since_last;
  double catchment_streampower, catchment_saltabr, saltabr_incision;
  double bedrock_landslide_erosion;
  double catchment_bedrock_landslide_erosion;
  double total_height, catchment_av_height, nodes_in_catchment;
  double total_sediment;
  double total_erosion;
  double total_streampower;
  double total_saltabr;
  double under_taucrit;
  double river;
  double av_donor_height;
  double av_donor_distance;
  double landslide_possibility; //The possibility that a landslide if there would otherwise be a landslide in the node.
  double deflection;
  double weath; //The amount of weathering in the node at the timestep
  double top_old;
  double smooth_erosion_list[smoother]; //An array that stores the erosion in the node in the last 100 timesteps.
  double smooth_erosion; //Array that stores the moving average over the last 100 timesteps.
  double smooth_relsedi_list[smoother]; //An array that stores the erosion in the node in the last 100 timesteps.
  double smooth_relsedi; //Array that stores the moving average over the last 100 timesteps.
  double smooth_diff_list[smoother]; //An array that stores the erosion in the node in the last 100 timesteps.
  double smooth_diff; //Array that stores the moving average over the last 100 timesteps.
  double smooth_saltabr_list[smoother]; //An array that stores the erosion in the node in the last 100 timesteps.
  double smooth_saltabr; //Array that stores the moving average over the last 100 timesteps.
  double smooth_streampower_list[smoother]; //An array that stores the erosion in the node in the last 100 timesteps.
  double smooth_streampower; //Array that stores the moving average over the last 100 timesteps.
  long smooth_counter;
  double diff_erosion; //The erosion of bedrock by hillslope processes, defined in the function diff_change
  double bed_old;
} nodetype;

typedef struct 
{
  long nx;
  long ny;
  long nc;
  double dx;
  double dy;
  double mean_landslide_erate;
  double step;
} meshtype;

typedef struct
{
  double U; //Uplift
  double K_stream; //Fluvial erosion constant
  double n; //Slope exponent
  double M; //drainage exponent
  double n_diff; //diffusion exponent
  double deltat; //Time step
  double deltat_next_time; //The timestep in the next iteration
  double K_s; //Constant from Sklaar Dietrich model
  double K_t; //Constant related to the maximum sediment load
  double k_w; //Constant related to the width of a channel
  double k_diff; //diffusion constant used without sediment
  double k_diff_sed_change; //If I want to alter the efficiency of sediment transport by diffusion
  double S_c; //The critical hillslope angle in percent
  double split; //The split between Saltation-Abrasion and Stream-Power models. 1=full stream power. 0=full saltation abrasion
  double bare_rock_weath; //The weathering rate on bare bedrock
  double max_weath; //The maximum weathering rate
  double R_star; //The sediment thickness that corresponds to maximum weathering
  double R_scale; //Scaling factor used in calculating the weathering rate
  double porosity; //The porosity of the weathered layer on top the bedrock
  double sedimentation_angle; //This is the angle that sediment will be sedimented with at a minimum. The angle is in [meters/meter]
  double landslide_angle; //This is the angle that landslides will deposit with. Unit is [meters/meter]
  double n_step; //The number of steps that the model should run
  double n_landslide_pa; //The number of landslides per year
  double flux_out_modulo; //Determines how many timesteps there is between each addition to the flux out file
  char do_fluvial_deposition; //Determines whether rivers can deposit sediment or not
  char do_landslide_deposition;  //Determines whether landslides will move sediment, or just free it as sediment but not move it
  char landslide_type;  //Determines whether landslides will move sediment, or just free it as sediment but not move it
  char uplift_type; //Determines the type of uplift. The available types at the moment are uniform uplift, called by 'a', and a tilting uplift, called by 'b', sideways uplift by 'c', mix of sideways uplift and tilting uplift by 'd' and a mix of sideways uplift the other way and tilting uplift by 'e'.
  long number_of_outputs;
  double print_modulo;
  double bisection_it_crit;
  double tau_crit;
  double k_tau;
  double k_sed;
  char humped_weathering;
  double weath_out_modulo; //Parameter that determines the amount of timesteps between each output to from the weath_out function.
  long nx,ny;
  double dx,dy;
  char noheightchange; //This parameter determines whether the bedrock height in the model should be updated or be static.
  char flex_param;
  long burst_starter_1;
} model_parameters;


typedef struct
{
  double n_landslides;
  double landslides;
} landslidetype;

/* Prototype functions */

/*Functions.c*/
long find_baselevelnodes(nodetype *nodes,long nx,long ny);
void xy(nodetype *nodes,long nx,long ny);
void get_neighbours(nodetype *nodes,long nx,long ny);
void get_distance(nodetype *nodes,long nx,long ny,double dx, double dy);
void get_slope(nodetype *nodes,long nx,long ny);
void get_slope_new_heights(nodetype *nodes,long nx,long ny);
void get_reciever(nodetype *nodes,long nx,long ny);
void get_reciever_wo_slope(nodetype *nodes,long nx,long ny);
void get_reciever_new_heights(nodetype *nodes,long nx,long ny);
long n_pits(nodetype *nodes,long nx,long ny);
void add_to_stack(long l,nodetype *nodes,long *stack,long a,double dist);
void get_donorlist(nodetype *nodes,long nx,long ny, long *stack,double dx,double dy,long *stack2,long *flist,long *baselevel_list,long n_baselevelnodes,long n_pits,long *pit_list);
void remove_recur(long l,nodetype *nodes,long a);
void drain_recur(long l,nodetype *nodes,double height,long drainplus,long a);
long pit_remover(nodetype *nodes,long nx,long ny,long *store,double *tmp);
void node_uplifts(nodetype *nodes,long nx,long ny,long npits,model_parameters *parameters);
void uplift(nodetype *nodes,long nx,long ny,long npits,model_parameters *parameters);
void weathering(nodetype *nodes,long nx,long ny,model_parameters *parameters);
	
/*inout.c*/
//void load_parameters(meshtype *mesh);
meshtype loadmesh(char* path, char file[200], FILE *fp,int go_on);
//void loadmesh(meshtype mesh, char* path, char file[200], FILE *fp,int go_on);
void initialize_modelparameters(model_parameters *parameters,meshtype mesh);
void initialize(nodetype *nodes,meshtype mesh,char *path,char file[200],FILE *fp,int go_on,model_parameters *parameters);
double write_output(nodetype *nodes,meshtype mesh,char *path,char file[200],FILE *fp,double step,double print_modulo,double number_of_outputs,long npits,char *output_path,long landslides_since_last,model_parameters *parameters,double output_number);
void output_landslides(nodetype *nodes,meshtype mesh,char *path,char file[200],FILE *fp,double step,long i,double landslide_size,long catchment,char *output_path,long nodes_in_landslide,long *num_landslides);
void n_slides(nodetype *nodes,char *path,char file[200],FILE *fp,char *output_path,long num_landslides);
void delete_slides_file(char *path,char file[200],FILE *fp,char *output_path);
void flux_out(nodetype *nodes,meshtype mesh,char *path,char file[200],FILE *fp,double step,char *output_path,model_parameters *parameters);
void make_log(nodetype *nodes,meshtype mesh,char *path,char file[200],FILE *fp,double print_modulo,double number_of_outputs,char *output_path,model_parameters *parameters);
void weath_out(nodetype *nodes,meshtype mesh,char *path,char file[200],FILE *fp,double step,char *output_path,model_parameters *parameters); //Function that outputs averages of weathering, fluvial erosion and movement of sediment by diffusion and fluvial processes.
/*solver.c*/

//void newton_raphson(nodetype *nodes,long *stack,long nx,long ny,long i);
//void solve_eq(nodetype *nodes,long *stack,long nx,long ny,long npits,double dx,double dy);

/*Sediment_solver*/
double update_sed(nodetype *nodes,long *stack,long nx,long ny,double dx,double dy,long *stack2,double under_relax_sed,model_parameters *parameters);
double fluvial_incision_sed_calc(nodetype *nodes,long j,double node_height,model_parameters *parameters);
double fluvial_stream_power_calc(nodetype *nodes,long j,double node_height,model_parameters *parameters);
double diffusion_calc(nodetype *nodes,long j,double node_height,model_parameters *parameters);
double sediment_capacity_calc_topsed(nodetype *nodes,long i,model_parameters *parameters);
double sediment_capacity_calc_bed(nodetype *nodes, long i,model_parameters *parameters);
double newt_raphs_denominator_with_fluv_and_diff(nodetype *nodes,long j,double node_height,model_parameters *parameters);
double newt_raphs_denominator_with_fluv_without_diff(nodetype *nodes,long j,double node_height,model_parameters *parameters);
double newt_raphs_denominator_without_fluv_with_diff(nodetype *nodes,long j,double node_height,model_parameters *parameters);
double channel_width_calc(nodetype *nodes,long i,model_parameters *parameters);
double newton_raphson(nodetype *nodes,long j,double sediment_capa,double old,long lol,double* converge_crit,double under_relax_height,model_parameters *parameters);
double bisection(nodetype *nodes,long j,double sediment_capa,double it_crit,double* taeller,model_parameters *parameters);
void iterator(nodetype *nodes,long *stack,long nx,long ny,long npits,double dx,double dy,long *stack2,long *flist,long s_flist,model_parameters *parameters);
void alluviate(nodetype *nodes,long *stack,long h,double deposition,long u,model_parameters *parameters);
long lowest_donor(nodetype *nodes,long sedi_node);
void sediment_transport(nodetype *nodes,long *stack,long nx,long ny,double dx,double dy,long *stack2,long npits,model_parameters *parameters);
void sediment_transport2(nodetype *nodes,long *stack,long nx,long ny,double dx,double dy,long *stack2,long npits,model_parameters *parameters,int *indi);
void sediment_transport3(nodetype *nodes,long *stack,long nx,long ny,double dx,double dy,long *stack2,long npits,model_parameters *parameters,int *indi);



/*explicit solver*/
double expli_update_sed(nodetype *nodes,long *stack,long nx,long ny,double dx,double dy,long *stack2,double under_relax_sed,model_parameters *parameters);
double expli_salt_abr(nodetype *nodes,long j,double node_height,model_parameters *parameters);
double expli_stream_power(nodetype *nodes,long j,double node_height,model_parameters *parameters);
double expli_diffusion_calc(nodetype *nodes,long j,double node_height,model_parameters *parameters);
double expli_sed_cap_topsed(nodetype *nodes,long i,model_parameters *parameters,double dx, double dy);
void expli_sed_cap_topsed_new(nodetype *nodes,long *stack2,long nx,long ny,model_parameters *parameters,double dx, double dy);
double expli_sediment_capacity_calc_bed(nodetype *nodes, long i,model_parameters *parameters);
double expli_newt_raphs_denominator_with_fluv_and_diff(nodetype *nodes,long j,double node_height,model_parameters *parameters);
double expli_newt_raphs_denominator_with_fluv_without_diff(nodetype *nodes,long j,double node_height,model_parameters *parameters);
double expli_newt_raphs_denominator_without_fluv_with_diff(nodetype *nodes,long j,double node_height,model_parameters *parameters);
double channel_width_calc(nodetype *nodes,long i,model_parameters *parameters);
double expli_newton_raphson(nodetype *nodes,long j,double sediment_capa,double old,long lol,double* converge_crit,double under_relax_height,model_parameters *parameters);
double expli_bisection(nodetype *nodes,long j,double sediment_capa,double it_crit,double* taeller,model_parameters *parameters);
void update_height(nodetype *nodes,long *stack,long nx,long ny,long npits,double dx,double dy,long *stack2,double it_crit,double under_relax_height,long *flist,long s_flist,model_parameters *parameters,int *indi);
void expli_solver(nodetype *nodes,long *stack,long nx,long ny,long npits,double dx,double dy,long *stack2,long *flist,long s_flist,model_parameters *parameters);
void alluviate(nodetype *nodes,long *stack,long h,double deposition,long u,model_parameters *parameters);
long lowest_donor(nodetype *nodes,long sedi_node);
//void sediment_transport(nodetype *nodes,long *stack,long nx,long ny,double dx,double dy,long *stack2,long npits,model_parameters *parameters);



/*Noheightchange*/
void noheightchange_controller(nodetype *nodes,meshtype mesh,char *path,char file[200],FILE *fp,double *step,double print_modulo,double number_of_outputs,char *output_path,double h,double n_step,model_parameters *parameters,double *output_number,long *counter,long *stack,long *stack2,long *pit_list,long *flist,long *baselevel_list,long n_baselevelnodes,long s_flist);
void expli_solver_noheightchange(nodetype *nodes,long *stack,long nx,long ny,long npits,double dx,double dy,long *stack2,long *flist,long s_flist,model_parameters *parameters);
void weathering_noheightchange(nodetype *nodes,long nx,long ny,model_parameters *parameters);

/*Landslides*/
void landslide_distribution_factor(nodetype *nodes,meshtype mesh);
void landslide_daniel(nodetype *nodes,meshtype mesh,long *slist,long npits,char *path,char file[200],FILE *fp,char *output_path,long step,long *num_landslides,model_parameters *parameters);
void nslides_daniel(long i,double hc,nodetype *nodes,long *nsc,long *slist,double failure_slope,model_parameters *parameters);
void nslides_david(long i,nodetype *nodes,long *nsc,long *slist,double x0,double y0,double h0,double *maxH,double *maxbeta,model_parameters *parameters);
void landslide_david(nodetype *nodes,meshtype mesh,long *slist,long npits,char *path,char file[200],FILE *fp,char *output_path,long step,long *num_landslides,model_parameters *parameters,long h);
void move_sediment(nodetype *nodes,double dHH,long i,long dx,long dy,model_parameters *parameters);
long lowest_neighbour_above(nodetype *nodes,long sedi_node);


/*flexflex*/
void flexit(nodetype *nodes,long nx,long ny,long dx,long dy);



/*blandet godt*/
void baselevel_lister(nodetype *nodes,long *baselevel_list,long n_baselevelnodes,long nx,long ny);
void calc_integral_flexure(nodetype *nodes,long nx,long ny,long dx,long dy);
void perform_integral_flexure(nodetype *nodes, long nx,long ny);
void pit_lister(nodetype *nodes,long nx,long ny,long *pit_list);
void isostasy(nodetype *nodes,long nx,long ny);
void transient_changes(model_parameters *parameters, nodetype *nodes,double *print_modulo,long *output_burst,long n_step,long h,long *uplift_change_counter,long npits,double stop_uplift_time,double k_diff_original,double step);
void smooth_everything_handler(nodetype *nodes,long nx,long ny,model_parameters *parameters);


#endif
