// Blanca Berbel Fdez
// Creation date: 28/12/2021
// Last modification: 24/02/2025

//////////////////////////////////////////////////////////
//														//
//			CPG (SIEC configuration, KK model)		 	//
//														//
//////////////////////////////////////////////////////////

// CPG X-Y and Z, electrically coupled to X : SIEC configuration
// Code to explore a range of electrical conductance value


// System libraries
# include <math.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>


// Program parameter access constants
# define PARAMETERS		4  		// Number of parameters passed to the program
# define ENTRY		    1  		// File with initial conditions
# define G_FIN			2  		// Electrical conductance end value
# define G_PASO			3  		// Electrical conductance increase step
# define TIME			4  		// Simulation time


// Model variable constants
# define DIM			25 		// Number of variables	

// Access constants to model variables
# define Vm_X           0  		// Membrane potential of neuron X
# define Ca_X		    1  		// Calcium concentration in neuron X
# define mB_X		    2  		// Gating variable for X
# define hB_X		    3
# define mNaTTX_X	    4
# define hNaTTX_X	    5
# define nKTEA_X	    6
# define mCa_X		    7

# define Vm_Y		    8  		// Ídem for neuron Y
# define Ca_Y		    9
# define mB_Y		    10
# define hB_Y		    11
# define mNaTTX_Y	    12
# define hNaTTX_Y	    13
# define nKTEA_Y	    14
# define mCa_Y          15


# define Vm_Z		    16  	// Ídem for neuron Z
# define Ca_Z		    17
# define mB_Z		    18
# define hB_Z		    19
# define mNaTTX_Z	    20
# define hNaTTX_Z	    21
# define nKTEA_Z	    22
# define mCa_Z 	        23
# define ms_YX          24  	// Slow current from Y to X


// Model constants
# define VNa            40.0
# define VK	            -70.0
# define VB             -58.0
# define VCa            150.0
# define Cm             0.02
# define ks		        50.0
# define ro		        0.002
# define kBeta	        15000.0
# define beta		    0.00004
# define cte	        808.3108459
# define g_XY_f      	0.0255  // Fast-chemical conductance
# define g_YX_s         0.0155  // Slow-chemical conductance
# define E_syn          -65.0
# define V_f            -44.7 					
# define s_f            0.31
# define V_s            -49.0
# define s_s            1.0
# define K1_s           0.6  		
# define K2_s           0.27 		


// Global variables 
static double V0 = 0.0;  
static double Ca0 = 0.0;  
static double gK_cbm = 0.0;  	// ** All neurons are set according to KK parameters for the chaotic bursting regime.
static double gNaV_cbm = 0.0;
static double gNa_cbm = 0.0;
static double gB_cbm = 0.0;
static double gNaTTX_cbm = 0.0;
static double gKTEA_cbm = 0.0;
static double gCa_cbm = 0.0;
static double gCa_Ca_cbm = 0.0;
static double g_ZX = 0.0;  		// Electrical conductance variable from Z to X
static double g_XZ = 0.0;  		// Electrical conductance variable from X to Z


// Function definition
void kk_model(double, double *, double *);
void set_parameters(char *);
void set_conditions(double *, double *);
double intey(double, double, double *);


// Main program
int main (int argc, char ** argv)
{

    double time_max, time; 
    double inct=1e-4;  

    // Variables for conductances
	double g_max, d_g;  

	// Counter for saving data
	int point = 0;

	// Integer numbers for spikes
	int stopX = 0, contX = 0, stopY = 0, contY = 0, int stopZ = 0, contZ = 0;

	// Vectors with model variables
	double variables[DIM], variables_pre[DIM], variables_now[DIM], variables_aft[DIM];

    // Output and input data files
    FILE * salida, * spikes_X, * spikes_Y, * spikes_Z;

    char namefileV[80], namefileX[80], namefileY[80], namefileZ[80];

    if (argc != PARAMETERS + 1)
    {
		puts("Parámetros en script_komendantov");
		exit(0);
    }

    time_max = atof(argv[TIME]);
    g_max = atof(argv[G_FIN]);
    d_g = atof(argv[G_PASO]);

	set_parameters(argv[ENTRY]);
	
	// Loop to iterate with different conductances, starting at zero conductance
	
	for (g_ZX = 0.0000; g_ZX <= g_max; g_ZX = g_ZX + d_g)
	{	

		g_XZ = g_ZX;  // ** Symmetric gap junction

		// Same initial conditions for each conductance value
		set_conditions(variables, variables_pre); 

		sprintf(namefileV, "V_gZX_%.4f", g_ZX);		// File for saving potential values
		sprintf(namefileX, "S_X_gZX_%.4f", g_ZX);	// File for storing X spikes 
		sprintf(namefileY, "S_Y_gZX_%.4f", g_ZX);	// File for storing Y spikes 
		sprintf(namefileZ, "S_Z_gZX_%.4f", g_ZX);	// File for storing Z spikes 

		salida = fopen(namefileV, "w");
		spikes_X = fopen(namefileX, "w"); 
		spikes_Y = fopen(namefileY, "w");
		spikes_Z = fopen(namefileZ, "w");

		if (salida == NULL)
		{
			printf("Error creating output files.\n");
			exit(0);
		}
		else
		{	

			time = 0.0;
			intey(time, inct, variables);

	    	variables_now[Vm_X] = variables[Vm_X];
	    	variables_now[Vm_Y] = variables[Vm_Y];
	    	variables_now[Vm_Z] = variables[Vm_Z];		
	    	

			time += inct;
			intey(time, inct, variables);

	    	variables_aft[Vm_X] =  variables[Vm_X];
	    	variables_aft[Vm_Y] =  variables[Vm_Y];
	    	variables_aft[Vm_Z] =  variables[Vm_Z];
	    
	    	
			for(time = 0.0; time < time_max; time += inct)
			{
				variables_pre[Vm_X] =  variables_now[Vm_X];
				variables_pre[Vm_Y] =  variables_now[Vm_Y];
				variables_pre[Vm_Z] =  variables_now[Vm_Z];
				

				variables_now[Vm_X] = variables_aft[Vm_X];
				variables_now[Vm_Y] = variables_aft[Vm_Y];
				variables_now[Vm_Z] = variables_aft[Vm_Z];
				
				intey(time, inct, variables);

				point += 1; 
				
				if (point == 5)
				{	
					fprintf(salida, "%.4f\t%.4f\t%.4f\t%.4f\n", time, variables[Vm_X], variables[Vm_Y], variables[Vm_Z]); 
					point = 0; 
				}
					
	    		variables_aft[Vm_X] = variables[Vm_X];
	    		variables_aft[Vm_Y] = variables[Vm_Y];
	    		variables_aft[Vm_Z] = variables[Vm_Z];
	
				if (variables_now[Vm_X] > 0)
				{
					if (((variables_now[Vm_X] - variables_pre[Vm_X]) > 0) && ((variables_aft[Vm_X] - variables_now[Vm_X]) < 0))
					{
						if (contX == 0)
						{
							fprintf(spikes_X, "%d\n", 1);
							contX ++;
						}
						if (stopX == 0)
						{
							fprintf (spikes_X, "\n%.4f\t%.4f\t%d\t%d\n", time, variables_now[Vm_X], 1, 0);
							stopX = 1;
						}
						else
						{
							fprintf (spikes_X, "\n%.4f\t%.4f\t%d\t%d\n", time, variables_now[Vm_X], 0, 0);
						}
					}
				}
	
				if (variables_now[Vm_X] < -50)
				{
					stopX = 0;
					contX = 0;
				}	

				if (variables_now[Vm_Y] > 0)
				{
					if (((variables_now[Vm_Y] - variables_pre[Vm_Y]) > 0) && ((variables_aft[Vm_Y] - variables_now[Vm_Y]) < 0))
					{
						if (contY == 0)
						{
							fprintf(spikes_Y, "%d\n", 1);
							contY ++;
						}
						if (stopY == 0)
						{
							fprintf (spikes_Y, "\n%.4f\t%.4f\t%d\t%d\n", time, variables_now[Vm_Y], 1, 0);
							stopY = 1;
						}
						else
						{
							fprintf (spikes_Y, "\n%.4f\t%.4f\t%d\t%d\n", time, variables_now[Vm_Y], 0, 0);
						}
					}
				}
				if (variables_now[Vm_Y] < -50)
				{
					stopY = 0;
					contY = 0;
				}	

				if (variables_now[Vm_Z] > 0)
				{
					if (((variables_now[Vm_Z] - variables_pre[Vm_Z]) > 0) && ((variables_aft[Vm_Z] - variables_now[Vm_Z]) < 0))
					{
						if (contZ == 0)
						{
							fprintf(spikes_Z, "%d\n", 1);
							contZ ++;
						}
						if (stopZ == 0)
						{
							fprintf (spikes_Z, "\n%.4f\t%.4f\t%d\t%d\n", time, variables_now[Vm_Z], 1, 0);
							stopZ = 1;
						}
						else
						{
							fprintf (spikes_Z, "\n%.4f\t%.4f\t%d\t%d\n", time, variables_now[Vm_Z], 0, 0);
						}
					}
				}
				if (variables_now[Vm_Z] < -50)
				{
					stopZ = 0;
					contZ = 0;
				}
				fflush(salida);		
				fflush(spikes_X);
				fflush(spikes_Y);
				fflush(spikes_Z);
			}
			fclose(salida);
			fclose(spikes_X);
			fclose(spikes_Y);
			fclose(spikes_Z);
		}
	}
	exit(1);
}


/*=======================================*/
/* Functions for Variable Initialization */
/*=======================================*/

void set_parameters(char * initial_parameters)
{
	FILE * pointer; 

	pointer = fopen(initial_parameters, "r");

	if (pointer == NULL) 
	{
		printf("Error to open the file with the initial entry parameter.\n");
		exit(0);
	}
	else
	{
		if (fscanf(pointer, "%lf", &V0) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(pointer, "%lf", &Ca0) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(pointer, "%lf", &gK_cbm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(pointer, "%lf", &gNa_cbm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(pointer, "%lf", &gNaV_cbm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(pointer, "%lf", &gB_cbm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(pointer, "%lf", &gNaTTX_cbm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(pointer, "%lf", &gKTEA_cbm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(pointer, "%lf", &gCa_cbm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(pointer, "%lf", &gCa_Ca_cbm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
	}
	
	fclose(pointer);

   return;

}

void set_conditions(double * variables, double * variables_pre) 
{	
	variables_pre[Vm_X] = V0; 
	variables[Vm_X] = V0 + ((double) rand()/RAND_MAX);
    variables[Ca_X] = Ca0;

	variables_pre[Vm_Y] = V0;
    variables[Vm_Y] = V0 + ((double) rand()/RAND_MAX);
    variables[Ca_Y] = Ca0;

    variables_pre[Vm_Z] = V0;
    variables[Vm_Z] = V0 + ((double) rand()/RAND_MAX);
    variables[Ca_Z] = Ca0;

	
    variables[mB_X] = 1.0 / (1.0 + exp(0.4 * (variables[Vm_X] + 34.0)));
    variables[hB_X] = 1.0 / (1.0 + exp(-0.55 * (variables[Vm_X] + 43.0)));
    variables[mNaTTX_X] = 1.0 / (1.0 + exp(-0.4 * (variables[Vm_X] + 31.0)));
    variables[hNaTTX_X] = 1.0 / (1.0 + exp(0.25 * (variables[Vm_X] + 45.0)));
    variables[nKTEA_X] = 1.0 / (1.0 + exp(-0.18 * (variables[Vm_X] + 25.0)));
    variables[mCa_X] = 1.0 / (1.0 + exp(-0.2 * variables[Vm_X]));

    variables[mB_Y] = 1.0 / (1.0 + exp(0.4 * (variables[Vm_Y] + 34.0)));
    variables[hB_Y] = 1.0 / (1.0 + exp(-0.55 * (variables[Vm_Y] + 43.0)));
    variables[mNaTTX_Y] = 1.0 / (1.0 + exp(-0.4 * (variables[Vm_Y] + 31.0)));
    variables[hNaTTX_Y] = 1.0 / (1.0 + exp(0.25 * (variables[Vm_Y] + 45.0)));
    variables[nKTEA_Y] = 1.0 / (1.0 + exp(-0.18 * (variables[Vm_Y] + 25.0)));
    variables[mCa_Y] = 1.0 / (1.0 + exp(-0.2 * variables[Vm_Y]));

    variables[mB_Z] = 1.0 / (1.0 + exp(0.4 * (variables[Vm_Z] + 34.0)));
    variables[hB_Z] = 1.0 / (1.0 + exp(-0.55 * (variables[Vm_Z] + 43.0)));
    variables[mNaTTX_Z] = 1.0 / (1.0 + exp(-0.4 * (variables[Vm_Z] + 31.0)));
    variables[hNaTTX_Z] = 1.0 / (1.0 + exp(0.25 * (variables[Vm_Z] + 45.0)));
    variables[nKTEA_Z] = 1.0 / (1.0 + exp(-0.18 * (variables[Vm_Z] + 25.0)));
    variables[mCa_Z] = 1.0 / (1.0 + exp(-0.2 * variables[Vm_Z]));

    variables[ms_YX] = K1_s/(K1_s+K2_s*(1.0+exp(s_s*(V_s-variables[Vm_Y]))));  

   return;
}


/*======================================*/
/* Calculation functions of the model   */
/*======================================*/

void kk_model(double tiempo, double * x,double * fvec)
{

	double IK_X, INa_X, INaV_X, IB_X, INaTTX_X, IKTEA_X, ICa_X, ICa_Ca_X;
	double IK_Y, INa_Y, INaV_Y, IB_Y, INaTTX_Y, IKTEA_Y, ICa_Y, ICa_Ca_Y;
	double IK_Z, INa_Z, INaV_Z, IB_Z, INaTTX_Z, IKTEA_Z, ICa_Z, ICa_Ca_Z;
    double I_f_XY; 
    double I_s_YX;
    double I_elec_XZ, I_elec_ZX; 

	INaV_X = gNaV_cbm * (1.0 / (1.0 + exp(-0.2 * (x[Vm_X] + 45.0)))) * (x[Vm_X] - VNa);
	IK_X = gK_cbm * (x[Vm_X] - VK);
	INa_X = gNa_cbm * (x[Vm_X] - VNa);
	IB_X = gB_cbm * x[mB_X] * x[hB_X] * (x[Vm_X] - VB);
	INaTTX_X = gNaTTX_cbm * x[mNaTTX_X] * x[mNaTTX_X] * x[mNaTTX_X] * x[hNaTTX_X] * (x[Vm_X] - VNa);
	IKTEA_X = gKTEA_cbm * x[nKTEA_X] * x[nKTEA_X] * x[nKTEA_X] * x[nKTEA_X] * (x[Vm_X] - VK);
	ICa_X = gCa_cbm * x[mCa_X] * x[mCa_X] * (x[Vm_X] - VCa);
	ICa_Ca_X = gCa_Ca_cbm * (x[Vm_X] - VCa) / ((1.0 + exp (-0.06 *(x[Vm_X] + 45.0))) * (1.0 + exp(kBeta * (x[Ca_X] - beta))));
	I_s_YX = g_YX_s * x[ms_YX] * (x[Vm_X] - E_syn);

	I_elec_XZ = g_XZ * (x[Vm_Z] -  x[Vm_X]); 

	INaV_Y = gNaV_cbm * (1.0 / (1.0 + exp(-0.2 * (x[Vm_Y] + 45.0)))) * (x[Vm_Y] - VNa);
	IK_Y = gK_cbm * (x[Vm_Y] - VK);
	INa_Y = gNa_cbm * (x[Vm_Y] - VNa);
	IB_Y = gB_cbm * x[mB_Y] * x[hB_Y] * (x[Vm_Y] - VB);
	INaTTX_Y = gNaTTX_cbm * x[mNaTTX_Y] * x[mNaTTX_Y] * x[mNaTTX_Y] * x[hNaTTX_Y] * (x[Vm_Y] - VNa);
	IKTEA_Y = gKTEA_cbm * x[nKTEA_Y] * x[nKTEA_Y] * x[nKTEA_Y] * x[nKTEA_Y] * (x[Vm_Y] - VK);
	ICa_Y = gCa_cbm * x[mCa_Y] * x[mCa_Y] * (x[Vm_Y] - VCa);
	ICa_Ca_Y = gCa_Ca_cbm * (x[Vm_Y] - VCa) / ((1.0 + exp (-0.06 *(x[Vm_Y] + 45.0))) * (1.0 + exp(kBeta * (x[Ca_Y] - beta))));
	I_f_XY =  (g_XY_f * (x[Vm_Y]- E_syn)) / (1.0 + exp(s_f*(V_f-x[Vm_X])));
	

	INaV_Z = gNaV_cbm * (1.0 / (1.0 + exp(-0.2 * (x[Vm_Z] + 45.0)))) * (x[Vm_Z] - VNa);
	IK_Z = gK_cbm * (x[Vm_Z] - VK);
	INa_Z = gNa_cbm * (x[Vm_Z] - VNa);
	IB_Z = gB_cbm * x[mB_Z] * x[hB_Z] * (x[Vm_Z] - VB);
	INaTTX_Z = gNaTTX_cbm * x[mNaTTX_Z] * x[mNaTTX_Z] * x[mNaTTX_Z] * x[hNaTTX_Z] * (x[Vm_Z] - VNa);
	IKTEA_Z = gKTEA_cbm * x[nKTEA_Z] * x[nKTEA_Z] * x[nKTEA_Z] * x[nKTEA_Z] * (x[Vm_Z] - VK);
	ICa_Z = gCa_cbm * x[mCa_Z] * x[mCa_Z] * (x[Vm_Z] - VCa);
	ICa_Ca_Z = gCa_Ca_cbm * (x[Vm_Z] - VCa) / ((1.0 + exp (-0.06 *(x[Vm_Z] + 45.0))) * (1.0 + exp(kBeta * (x[Ca_Z] - beta)))); 

  	I_elec_ZX = g_ZX * (x[Vm_X] - x[Vm_Z]);


	fvec[Vm_X] = - (INaTTX_X + IKTEA_X + IK_X + INa_X + INaV_X + IB_X + ICa_X + ICa_Ca_X + I_s_YX + I_elec_ZX)/ Cm;
	fvec[Ca_X] = ro * ((-ICa_X / cte) - (ks * x[Ca_X]));
	fvec[mB_X] = (1.0 / (1.0 + exp(0.4 * (x[Vm_X] + 34.0))) - x[mB_X]) / 0.05;
	fvec[hB_X] = (1.0 / (1.0 + exp(-0.55 * (x[Vm_X] + 43.0))) - x[hB_X]) / 1.5;
	fvec[mNaTTX_X] = (1.0 / (1.0 + exp(-0.4 * (x[Vm_X] + 31.0))) - x[mNaTTX_X]) / 0.0005;
	fvec[hNaTTX_X] = (1.0 / (1.0 + exp(0.25 * (x[Vm_X] + 45.0))) - x[hNaTTX_X]) / 0.01;
	fvec[nKTEA_X] = (1.0 / (1.0 + exp(-0.18 * (x[Vm_X] + 25.0))) - x[nKTEA_X]) / 0.015;
	fvec[mCa_X] = (1.0 / (1.0 + exp(-0.2 * x[Vm_X])) - x[mCa_X]) / 0.01;
	

	fvec[Vm_Y] = - (INaTTX_Y + IKTEA_Y + IK_Y + INa_Y + INaV_Y + IB_Y + ICa_Y + ICa_Ca_Y + I_f_XY) / Cm; 
	fvec[Ca_Y] = ro * ((-ICa_Y / cte) - (ks * x[Ca_Y]));
	fvec[mB_Y] = (1.0 / (1.0 + exp(0.4 * (x[Vm_Y] + 34.0))) - x[mB_Y]) / 0.05;
	fvec[hB_Y] = (1.0 / (1.0 + exp(-0.55 * (x[Vm_Y] + 43.0))) - x[hB_Y]) / 1.5;
	fvec[mNaTTX_Y] = (1.0 / (1.0 + exp(-0.4 * (x[Vm_Y] + 31.0))) - x[mNaTTX_Y]) / 0.0005;
	fvec[hNaTTX_Y] = (1.0 / (1.0 + exp(0.25 * (x[Vm_Y] + 45.0))) - x[hNaTTX_Y]) / 0.01;
	fvec[nKTEA_Y] = (1.0 / (1.0 + exp(-0.18 * (x[Vm_Y] + 25.0))) - x[nKTEA_Y]) / 0.015;
	fvec[mCa_Y] = (1.0 / (1.0 + exp(-0.2 * x[Vm_Y])) - x[mCa_Y]) / 0.01;

	fvec[ms_YX] = ((K1_s*(1.0-x[ms_YX]))/(1.0+exp(s_s*(V_s-x[Vm_Y])))) - K2_s*x[ms_YX];

	fvec[Vm_Z] = - (INaTTX_Z + IKTEA_Z + IK_Z + INa_Z + INaV_Z + IB_Z + ICa_Z + ICa_Ca_Z + I_elec_XZ) / Cm;
	fvec[Ca_Z] = ro * ((-ICa_Z / cte) - (ks * x[Ca_Z]));
	fvec[mB_Z] = (1.0 / (1.0 + exp(0.4 * (x[Vm_Z] + 34.0))) - x[mB_Z]) / 0.05;
	fvec[hB_Z] = (1.0 / (1.0 + exp(-0.55 * (x[Vm_Z] + 43.0))) - x[hB_Z]) / 1.5;
	fvec[mNaTTX_Z] = (1.0 / (1.0 + exp(-0.4 * (x[Vm_Z] + 31.0))) - x[mNaTTX_Z]) / 0.0005;
	fvec[hNaTTX_Z] = (1.0 / (1.0 + exp(0.25 * (x[Vm_Z] + 45.0))) - x[hNaTTX_Z]) / 0.01;
	fvec[nKTEA_Z] = (1.0 / (1.0 + exp(-0.18 * (x[Vm_Z] + 25.0))) - x[nKTEA_Z]) / 0.015;
	fvec[mCa_Z] = (1.0 / (1.0 + exp(-0.2 * x[Vm_Z])) - x[mCa_Z]) / 0.01;

    return;
}


/*================================================*/
/* Integration routine, 6th order runge kutta     */
/*================================================*/

double intey(double tiempo, double inc_integracion, double *variables) 
{
	double apoyo[DIM],retorno[DIM],variables_hat[DIM];
	double k[6][DIM];
	double u=0.0;
	int j;

	kk_model(tiempo,variables,retorno);
	
	for(j=0;j<DIM;++j) k[0][j]=inc_integracion*retorno[j];
	for(j=0;j<DIM;++j) apoyo[j]=variables[j]+k[0][j]*.2;

	kk_model(tiempo+inc_integracion/5,apoyo,retorno);

	for(j=0;j<DIM;++j) k[1][j]=inc_integracion*retorno[j];
	for(j=0;j<DIM;++j) apoyo[j]=variables[j]+k[0][j]*.075+k[1][j]*0.225;

	kk_model(tiempo+inc_integracion*0.3,apoyo,retorno);
	
	for(j=0;j<DIM;++j) k[2][j]=inc_integracion*retorno[j];
	for(j=0;j<DIM;++j) apoyo[j]=variables[j]+k[0][j]*.3-k[1][j]*0.9+k[2][j]*1.2;
	
	kk_model(tiempo+inc_integracion*0.6,apoyo,retorno);
  
	for(j=0;j<DIM;++j) k[3][j]=inc_integracion*retorno[j];
	for(j=0;j<DIM;++j) apoyo[j]=variables[j]+k[0][j]*0.075+k[1][j]*0.675-k[2][j]*0.6+k[3][j]*0.75;

	kk_model(tiempo+inc_integracion*0.9,apoyo,retorno);
	
	for(j=0;j<DIM;++j) k[4][j]=inc_integracion*retorno[j];
	for(j=0;j<DIM;++j) apoyo[j]=variables[j]+k[0][j]*0.660493827160493+k[1][j]*2.5-k[2][j]*5.185185185185185+k[3][j]*3.888888888888889-k[4][j]*0.864197530864197;
  
	kk_model(tiempo+inc_integracion,apoyo,retorno);

	for(j=0;j<DIM;++j) k[5][j]=inc_integracion*retorno[j];
	for(j=0;j<DIM;++j) variables_hat[j]=variables[j]+k[0][j]*0.1049382716049382+k[2][j]*0.3703703703703703+k[3][j]*0.2777777777777777+k[4][j]*0.2469135802469135;
	for(j=0;j<DIM;++j) variables[j]+=k[0][j]*0.098765432098765+k[2][j]*0.396825396825396+k[3][j]*0.231481481481481+k[4][j]*0.308641975308641-k[5][j]*0.035714285714285;
	for(j=0;j<DIM;++j) u+=fabs(variables[j]-variables_hat[j]);

	return u; 

}


