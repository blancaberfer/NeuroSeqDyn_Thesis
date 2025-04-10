// Blanca Berbel Fdez
// Creation date: 28/12/2021
// Last modification: 17/12/2024


// System libraries
# include <math.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>


// Program parameter access constants
# define PARAMETROS		5		// Number of parameters passed to the program
# define ENTRADA		1		// File with initial conditions
# define G_INI			2		// Electrical conductance initial value
# define G_FIN			3       // Electrical conductance end value
# define G_Ds			4		// Electrical conductance increase step
# define TIME			5		// Simulation time


// Model variable constants
# define DIM			44       	// Number of variables

// Access constants to model variables
# define Vm_LP          0
# define Ca_LP		    1
# define mB_LP		    2
# define hB_LP		    3
# define mNaTTX_LP	    4
# define hNaTTX_LP	    5
# define nKTEA_LP	    6
# define mCa_LP		    7
# define Vm_PY		    8
# define Ca_PY		    9
# define mB_PY		    10
# define hB_PY		    11
# define mNaTTX_PY	    12
# define hNaTTX_PY	    13
# define nKTEA_PY	    14
# define mCa_PY		    15
# define Vm_AB		    16
# define Ca_AB		    17
# define mB_AB		    18
# define hB_AB		    19
# define mNaTTX_AB	    20
# define hNaTTX_AB	    21
# define nKTEA_AB	    22
# define mCa_AB		    23
# define Vm_PD1		    24
# define Ca_PD1		    25
# define mB_PD1		    26
# define hB_PD1		    27
# define mNaTTX_PD1	    28
# define hNaTTX_PD1	    29
# define nKTEA_PD1	    30
# define mCa_PD1	    31
# define Vm_PD2		    32
# define Ca_PD2		    33
# define mB_PD2		    34
# define hB_PD2		    35
# define mNaTTX_PD2	    36
# define hNaTTX_PD2	    37
# define nKTEA_PD2	    38
# define mCa_PD2 	    39
# define ms_PD1LP       40
# define ms_PD2LP       41
# define ms_PD1PY       42
# define ms_PD2PY       43


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
# define g_ABLP_f       0.0446  
# define g_ABPY_f       0.0556
# define g_LPPD1_f      0.0211 
# define g_LPPD2_f      0.0269   
# define g_LPPY_f       0.0398
# define g_PYLP_f       0.0311
# define g_PD1LP_s      0.0015	
# define g_PD1PY_s      0.0023
# define g_PD2LP_s      0.0033
# define g_PD2PY_s      0.0028
# define E_syn          -65.0
# define V_f            -44.7
# define s_f            0.31
# define s_s            1.0
# define V_s            -49.0
# define K1_LP          1.0
# define K2_LP          0.01
# define K1_PY          1.0
# define K2_PY          0.0275


// Global variables
static double V0 = 0.0; 
static double Ca0 = 0.0; 
static double gK_r = 0.0;   
static double gNaV_r = 0.0;
static double gNa_r = 0.0;
static double gB_r = 0.0;
static double gNaTTX_r = 0.0;
static double gKTEA_r = 0.0;
static double gCa_r = 0.0;
static double gCa_Ca_r = 0.0;
static double gK_cm = 0.0;
static double gNaV_cm = 0.0;
static double gNa_cm = 0.0;
static double gB_cm = 0.0;
static double gNaTTX_cm = 0.0;
static double gKTEA_cm = 0.0;
static double gCa_cm = 0.0;
static double gCa_Ca_cm = 0.0;
static double gK_cbm = 0.0;
static double gNaV_cbm = 0.0;
static double gNa_cbm = 0.0;
static double gB_cbm = 0.0;
static double gNaTTX_cbm = 0.0;
static double gKTEA_cbm = 0.0;
static double gCa_cbm = 0.0;
static double gCa_Ca_cbm = 0.0;
static double g_ABPD1 = 0.0;
static double g_PD1AB = 0.0;
static double g_ABPD2 = 0.0;
static double g_PD2AB = 0.0;
static double g_PD1PD2 = 0.0;
static double g_PD2PD1 = 0.0;


// Function definition
void funcion(double, double *, double *);
void set_parameters(char *);
void set_conditions(double *, double *);
double intey(double, double, double *);


// Main program
int main (int argc, char ** argv)
{

    double time_max, time; 
    double inct=1e-4; 
	
	// Variables for conductances
	double g_PD1PD2_ini, g_PD1PD2_max, g_Ds; 

	// Counter for saving data
	int punto = 0; 

	// Integer numbers for spikes
	int stopLP = 0, contLP = 0, stopPY = 0, contPY = 0, stopAB = 0, contAB = 0 ,stopPD1 = 0, contPD1 = 0, stopPD2 = 0, contPD2 = 0; 

    // Vectors with model variables
    double variables[DIM], variables_ant[DIM], variables_act[DIM], variables_sig[DIM]; 

    // Output and input data files
    FILE * salida, * spikes_LP, * spikes_PY, * spikes_AB, * spikes_PD1, * spikes_PD2;

    char nombrearchivoV[80], nombrearchivoAB[80], nombrearchivoLP[80], nombrearchivoPD1[80], nombrearchivoPD2[80], nombrearchivoPY[80];

    if (argc != PARAMETROS + 1)
    {
		puts("Parámetros en script_komendantov");
		exit(0);
    }

    time_max = atof(argv[TIME]);
    g_PD1PD2_ini = atof(argv[G_INI]);
	g_PD1PD2_max = atof(argv[G_FIN]);
	g_Ds = atof(argv[G_Ds]);

	set_parameters(argv[ENTRADA]);

	// Loop to iterate with different conductances

	for(g_PD1PD2 = g_PD1PD2_ini; g_PD1PD2 <= g_PD1PD2_max; g_PD1PD2 += g_Ds)
	{

		g_PD2PD1 = g_PD1PD2;  // ** In this configuration, the current is symmetrical between all neurons in the pacemaker group. **
		g_ABPD1 = g_PD1PD2;
		g_PD1AB = g_PD1PD2;
		g_ABPD2 = g_PD1PD2;
		g_PD2AB = g_PD1PD2;

		// Same initial conditions for each conductance value
		set_conditions(variables, variables_ant);	
		
		// Name and open files for each conductance
		sprintf(nombrearchivoV, "V_g_%.4f_g_%.4f", g_PD1PD2, g_PD2PD1);       // File for saving potential values
		sprintf(nombrearchivoLP, "S_LP_g_%.4f_g_%.4f", g_PD1PD2, g_PD2PD1);   // File for storing LP spikes 
		sprintf(nombrearchivoPY, "S_PY_g_%.4f_g_%.4f", g_PD1PD2, g_PD2PD1);   // File for storing PY spikes
		sprintf(nombrearchivoAB, "S_AB_g_%.4f_g_%.4f", g_PD1PD2, g_PD2PD1);   // File for storing AB spikes
		sprintf(nombrearchivoPD1, "S_PD1_g_%.4f_g_%.4f", g_PD1PD2, g_PD2PD1); // File for storing PD1 spikes
		sprintf(nombrearchivoPD2, "S_PD2_g_%.4f_g_%.4f", g_PD1PD2, g_PD2PD1); // File for storing PD2 spikes

		if ( (salida = fopen(nombrearchivoV, "r")) ) {    // ** We ensure the simulation hasn't been done before for that conductance value.  **
			fclose(salida);
			printf("Existe para %lf\n", g_PD1PD2);
		}
		else
		{		
			salida = fopen(nombrearchivoV, "w");
			spikes_LP = fopen(nombrearchivoLP, "w");
			spikes_PY = fopen(nombrearchivoPY, "w");
			spikes_AB = fopen(nombrearchivoAB, "w");
			spikes_PD1 = fopen(nombrearchivoPD1, "w");
			spikes_PD2 = fopen(nombrearchivoPD2, "w");
			

			time = 0.0;
			intey(time, inct, variables);

			variables_act[Vm_LP] = variables[Vm_LP];
			variables_act[Vm_PY] = variables[Vm_PY];
			variables_act[Vm_AB] = variables[Vm_AB];
			variables_act[Vm_PD1] = variables[Vm_PD1];
			variables_act[Vm_PD2] = variables[Vm_PD2];		

			time += inct;
			intey(time, inct, variables);

			variables_sig[Vm_LP] =  variables[Vm_LP];
			variables_sig[Vm_PY] =  variables[Vm_PY];
			variables_sig[Vm_AB] =  variables[Vm_AB];
			variables_sig[Vm_PD1] =  variables[Vm_PD1];
			variables_sig[Vm_PD2] =  variables[Vm_PD2];
	
			for(time = 0.0; time < time_max; time += inct)
			{
				variables_ant[Vm_LP] =  variables_act[Vm_LP];
				variables_ant[Vm_PY] =  variables_act[Vm_PY];	
				variables_ant[Vm_AB] =  variables_act[Vm_AB];
				variables_ant[Vm_PD1] =  variables_act[Vm_PD1];
				variables_ant[Vm_PD2] =  variables_act[Vm_PD2];

				variables_act[Vm_LP] = variables_sig[Vm_LP];
				variables_act[Vm_PY] = variables_sig[Vm_PY];
				variables_act[Vm_AB] = variables_sig[Vm_AB];
				variables_act[Vm_PD1] = variables_sig[Vm_PD1];
				variables_act[Vm_PD2] = variables_sig[Vm_PD2];
				
				intey(time, inct, variables);
				
				punto += 1;			
		
				if (punto==5)
				{
					fprintf(salida, "%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\n", time, variables[Vm_LP], variables[Vm_PY], variables[Vm_AB], variables[Vm_PD1], variables[Vm_PD2]); 
					punto = 0;
				}
		
				variables_sig[Vm_LP] = variables[Vm_LP];
				variables_sig[Vm_PY] = variables[Vm_PY];
				variables_sig[Vm_AB] = variables[Vm_AB];
				variables_sig[Vm_PD1] = variables[Vm_PD1];
				variables_sig[Vm_PD2] = variables[Vm_PD2];
			
				if (variables_act[Vm_LP] > 0)
				{
					if (((variables_act[Vm_LP] - variables_ant[Vm_LP]) > 0) && ((variables_sig[Vm_LP] - variables_act[Vm_LP]) < 0))
					{
						if (contLP == 0)
						{
							fprintf(spikes_LP, "%d\n", 1);
							contLP ++;
						}
						if (stopLP == 0)
						{
							fprintf (spikes_LP, "\n%.3f\t%.3f\t%d\t%d\n", time, variables_act[Vm_LP], 1, 0);
							stopLP = 1;
						}
						else
						{
							fprintf (spikes_LP, "\n%.3f\t%.3f\t%d\t%d\n", time, variables_act[Vm_LP], 0, 0);
						}
					}
				}

				if (variables_act[Vm_LP] < -50)
				{
					stopLP = 0;
					contLP = 0;
				}

				if (variables_act[Vm_PY] > 0)
				{
					if (((variables_act[Vm_PY] - variables_ant[Vm_PY]) > 0) && ((variables_sig[Vm_PY] - variables_act[Vm_PY]) < 0))
					{	
						if (contPY == 0)
						{
							fprintf(spikes_PY, "%d\n", 1);
							contPY ++;
						}
						if (stopPY == 0)
						{
							fprintf (spikes_PY, "\n%.3f\t%.3f\t%d\t%d\n", time, variables_act[Vm_PY], 1, 0);
							stopPY = 1;
						}
						else
						{
							fprintf (spikes_PY, "\n%.3f\t%.3f\t%d\t%d\n", time, variables_act[Vm_PY], 0, 0);
						}
					}
				}
		
				if (variables_act[Vm_PY] < -50)
				{
					stopPY = 0;
					contPY = 0;
				}

				if (variables_act[Vm_AB] > 0)
				{
					if (((variables_act[Vm_AB] - variables_ant[Vm_AB]) > 0) && ((variables_sig[Vm_AB] - variables_act[Vm_AB]) < 0))
					{
						if (contAB == 0)
						{
							fprintf(spikes_AB, "%d\n", 1);
							contAB ++;
						}
						if (stopAB == 0)
						{
							fprintf (spikes_AB, "\n%.3f\t%.3f\t%d\t%d\n", time, variables_act[Vm_AB], 1, 0);
							stopAB = 1;
						}
						else
						{
							fprintf (spikes_AB, "\n%.3f\t%.3f\t%d\t%d\n", time, variables_act[Vm_AB], 0, 0);
						}
					}
				}
				if (variables_act[Vm_AB] < -50)
				{
					stopAB = 0;
					contAB = 0;
				}	

				if (variables_act[Vm_PD1] > 0)
				{
					if (((variables_act[Vm_PD1] - variables_ant[Vm_PD1]) > 0) && ((variables_sig[Vm_PD1] - variables_act[Vm_PD1]) < 0))
					{
						if (contPD1 == 0)
						{
							fprintf(spikes_PD1, "%d\n", 1);
							contPD1 ++;
						}
						if (stopPD1 == 0)
						{
							fprintf (spikes_PD1, "\n%.3f\t%.3f\t%d\t%d\n", time, variables_act[Vm_PD1], 1, 0);
							stopPD1 = 1;
						}
						else
						{
							fprintf (spikes_PD1, "\n%.3f\t%.3f\t%d\t%d\n", time, variables_act[Vm_PD1], 0, 0);
						}
					}
				}
				if (variables_act[Vm_PD1] < -50)
				{
					stopPD1 = 0;
					contPD1 = 0;
				}	

				if (variables_act[Vm_PD2] > 0)
				{
					if (((variables_act[Vm_PD2] - variables_ant[Vm_PD2]) > 0) && ((variables_sig[Vm_PD2] - variables_act[Vm_PD2]) < 0))
					{
						if (contPD2 == 0)
						{
							fprintf(spikes_PD2, "%d\n", 1);
							contPD2 ++;
						}
						if (stopPD2 == 0)
						{
							fprintf (spikes_PD2, "\n%.3f\t%.3f\t%d\t%d\n", time, variables_act[Vm_PD2], 1, 0);
							stopPD2 = 1;
						}
						else
						{
							fprintf (spikes_PD2, "\n%.3f\t%.3f\t%d\t%d\n", time, variables_act[Vm_PD2], 0, 0);
						}
					}
				}
				if (variables_act[Vm_PD2] < -50)
				{
					stopPD2 = 0;
					contPD2 = 0;
				}
				fflush(salida);
				fflush(spikes_LP);
				fflush(spikes_PY);
				fflush(spikes_AB);
				fflush(spikes_PD1);
				fflush(spikes_PD2);		
			}
			fclose(salida);
		 	fclose(spikes_LP);
			fclose(spikes_PY);
			fclose(spikes_AB);
			fclose(spikes_PD1);
			fclose(spikes_PD2);
		}
		
	}			
	exit(1);
}


/*=======================================*/
/* Functions for Variable Initialization */
/*=======================================*/

void set_parameters(char * entrada)
{
	FILE * puntero; 

	puntero = fopen(entrada, "r");

	if (puntero == NULL) 
	{
		printf("Error al abrir el fichero con los datos de entrada.\n");
		exit(0);
	}
	else
	{
		if (fscanf(puntero, "%lf", &V0) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &Ca0) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gK_r) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gNa_r) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gNaV_r) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gB_r) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gNaTTX_r) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gKTEA_r) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gCa_r) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gCa_Ca_r) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
				if (fscanf(puntero, "%lf", &gK_cm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gNa_cm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gNaV_cm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gB_cm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gNaTTX_cm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gKTEA_cm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gCa_cm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gCa_Ca_cm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
				if (fscanf(puntero, "%lf", &gK_cbm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gNa_cbm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gNaV_cbm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gB_cbm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gNaTTX_cbm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gKTEA_cbm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gCa_cbm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
		if (fscanf(puntero, "%lf", &gCa_Ca_cbm) == -100)
		{
			fprintf(stderr, "Incorrect value\n");
		}
	}
	
	fclose(puntero);

   return;

}

void set_conditions(double * variables, double * variables_ant) 
{	
	variables_ant[Vm_LP] = V0; 
	variables[Vm_LP] = V0 + ((double) rand()/RAND_MAX);
    variables[Ca_LP] = Ca0;

    variables_ant[Vm_PY] = V0;
    variables[Vm_PY] = V0 + ((double) rand()/RAND_MAX);
    variables[Ca_PY] = Ca0;

    variables_ant[Vm_AB] = V0;
    variables[Vm_AB] = V0 + ((double) rand()/RAND_MAX);
    variables[Ca_AB] = Ca0;

	variables_ant[Vm_PD1] = V0;
    variables[Vm_PD1] = V0 + ((double) rand()/RAND_MAX);
    variables[Ca_PD1] = Ca0;

    variables_ant[Vm_PD2] = V0;
    variables[Vm_PD2] = V0 + ((double) rand()/RAND_MAX);
    variables[Ca_PD2] = Ca0;
	
    variables[mB_LP] = 1.0 / (1.0 + exp(0.4 * (variables[Vm_LP] + 34.0)));
    variables[hB_LP] = 1.0 / (1.0 + exp(-0.55 * (variables[Vm_LP] + 43.0)));
    variables[mNaTTX_LP] = 1.0 / (1.0 + exp(-0.4 * (variables[Vm_LP] + 31.0)));
    variables[hNaTTX_LP] = 1.0 / (1.0 + exp(0.25 * (variables[Vm_LP] + 45.0)));
    variables[nKTEA_LP] = 1.0 / (1.0 + exp(-0.18 * (variables[Vm_LP] + 25.0)));
    variables[mCa_LP] = 1.0 / (1.0 + exp(-0.2 * variables[Vm_LP]));

    variables[mB_PY] = 1.0 / (1.0 + exp(0.4 * (variables[Vm_PY] + 34.0)));
    variables[hB_PY] = 1.0 / (1.0 + exp(-0.55 * (variables[Vm_PY] + 43.0)));
    variables[mNaTTX_PY] = 1.0 / (1.0 + exp(-0.4 * (variables[Vm_PY] + 31.0)));
    variables[hNaTTX_PY] = 1.0 / (1.0 + exp(0.25 * (variables[Vm_PY] + 45.0)));
    variables[nKTEA_PY] = 1.0 / (1.0 + exp(-0.18 * (variables[Vm_PY] + 25.0)));
    variables[mCa_PY] = 1.0 / (1.0 + exp(-0.2 * variables[Vm_PY]));

    variables[mB_AB] = 1.0 / (1.0 + exp(0.4 * (variables[Vm_AB] + 34.0)));
    variables[hB_AB] = 1.0 / (1.0 + exp(-0.55 * (variables[Vm_AB] + 43.0)));
    variables[mNaTTX_AB] = 1.0 / (1.0 + exp(-0.4 * (variables[Vm_AB] + 31.0)));
    variables[hNaTTX_AB] = 1.0 / (1.0 + exp(0.25 * (variables[Vm_AB] + 45.0)));
    variables[nKTEA_AB] = 1.0 / (1.0 + exp(-0.18 * (variables[Vm_AB] + 25.0)));
    variables[mCa_AB] = 1.0 / (1.0 + exp(-0.2 * variables[Vm_AB]));

    variables[mB_PD1] = 1.0 / (1.0 + exp(0.4 * (variables[Vm_PD1] + 34.0)));
    variables[hB_PD1] = 1.0 / (1.0 + exp(-0.55 * (variables[Vm_PD1] + 43.0)));
    variables[mNaTTX_PD1] = 1.0 / (1.0 + exp(-0.4 * (variables[Vm_PD1] + 31.0)));
    variables[hNaTTX_PD1] = 1.0 / (1.0 + exp(0.25 * (variables[Vm_PD1] + 45.0)));
    variables[nKTEA_PD1] = 1.0 / (1.0 + exp(-0.18 * (variables[Vm_PD1] + 25.0)));
    variables[mCa_PD1] = 1.0 / (1.0 + exp(-0.2 * variables[Vm_PD1]));

    variables[mB_PD2] = 1.0 / (1.0 + exp(0.4 * (variables[Vm_PD2] + 34.0)));
    variables[hB_PD2] = 1.0 / (1.0 + exp(-0.55 * (variables[Vm_PD2] + 43.0)));
    variables[mNaTTX_PD2] = 1.0 / (1.0 + exp(-0.4 * (variables[Vm_PD2] + 31.0)));
    variables[hNaTTX_PD2] = 1.0 / (1.0 + exp(0.25 * (variables[Vm_PD2] + 45.0)));
    variables[nKTEA_PD2] = 1.0 / (1.0 + exp(-0.18 * (variables[Vm_PD2] + 25.0)));
    variables[mCa_PD2] = 1.0 / (1.0 + exp(-0.2 * variables[Vm_PD2]));

    variables[ms_PD1LP] = K1_LP/(K1_LP+K2_LP*(1.0+exp(s_s*(V_s-variables[Vm_PD1]))));
    variables[ms_PD2LP] = K1_LP/(K1_LP+K2_LP*(1.0+exp(s_s*(V_s-variables[Vm_PD2]))));
    variables[ms_PD1PY] = K1_PY/(K1_PY+K2_PY*(1.0+exp(s_s*(V_s-variables[Vm_PD1]))));
    variables[ms_PD2PY] = K1_PY/(K1_PY+K2_PY*(1.0+exp(s_s*(V_s-variables[Vm_PD2]))));

   return;
}


/*======================================*/
/* Calculation functions of the model   */
/*======================================*/

void funcion(double tiempo, double * x, double * fvec)
{
	double IK_LP, INa_LP, INaV_LP, IB_LP, INaTTX_LP, IKTEA_LP, ICa_LP, ICa_Ca_LP;
	double IK_PY, INa_PY, INaV_PY, IB_PY, INaTTX_PY, IKTEA_PY, ICa_PY, ICa_Ca_PY;
	double IK_AB, INa_AB, INaV_AB, IB_AB, INaTTX_AB, IKTEA_AB, ICa_AB, ICa_Ca_AB;
    double IK_PD1, INa_PD1, INaV_PD1, IB_PD1, INaTTX_PD1, IKTEA_PD1, ICa_PD1, ICa_Ca_PD1;
    double IK_PD2, INa_PD2, INaV_PD2, IB_PD2, INaTTX_PD2, IKTEA_PD2, ICa_PD2, ICa_Ca_PD2;
    double I_e_AB, I_e_PD1, I_e_PD2;
    double I_f_LP, I_f_PY, I_f_PD1, I_f_PD2;
    double I_s_LP, I_s_PY;

	INaV_LP = gNaV_cm * (1.0 / (1.0 + exp(-0.2 * (x[Vm_LP] + 45.0)))) * (x[Vm_LP] - VNa);
	IK_LP = gK_cm * (x[Vm_LP] - VK);
	INa_LP = gNa_cm * (x[Vm_LP] - VNa);
	IB_LP = gB_cm * x[mB_LP] * x[hB_LP] * (x[Vm_LP] - VB);
	INaTTX_LP = gNaTTX_cm * x[mNaTTX_LP] * x[mNaTTX_LP] * x[mNaTTX_LP] * x[hNaTTX_LP] * (x[Vm_LP] - VNa);
	IKTEA_LP = gKTEA_cm * x[nKTEA_LP] * x[nKTEA_LP] * x[nKTEA_LP] * x[nKTEA_LP] * (x[Vm_LP] - VK);
	ICa_LP = gCa_cm * x[mCa_LP] * x[mCa_LP] * (x[Vm_LP] - VCa);
	ICa_Ca_LP = gCa_Ca_cm * (x[Vm_LP] - VCa) / ((1.0 + exp (-0.06 *(x[Vm_LP] + 45.0))) * (1.0 + exp(kBeta * (x[Ca_LP] - beta))));
	I_f_LP = (g_PYLP_f*(x[Vm_LP]-E_syn)) / (1.0 + exp(s_f*(V_f-x[Vm_PY]))) + (g_ABLP_f*(x[Vm_LP]-E_syn)) / (1.0 + exp(s_f*(V_f-x[Vm_AB])));
	I_s_LP = g_PD1LP_s * x[ms_PD1LP] * (x[Vm_LP] - E_syn) + g_PD2LP_s * x[ms_PD2LP] * (x[Vm_LP] - E_syn);

	INaV_PY = gNaV_cm * (1.0 / (1.0 + exp(-0.2 * (x[Vm_PY] + 45.0)))) * (x[Vm_PY] - VNa);
	IK_PY = gK_cm * (x[Vm_PY] - VK);
	INa_PY = gNa_cm * (x[Vm_PY] - VNa);
	IB_PY = gB_cm * x[mB_PY] * x[hB_PY] * (x[Vm_PY] - VB);
	INaTTX_PY = gNaTTX_cm * x[mNaTTX_PY] * x[mNaTTX_PY] * x[mNaTTX_PY] * x[hNaTTX_PY] * (x[Vm_PY] - VNa);
	IKTEA_PY = gKTEA_cm * x[nKTEA_PY] * x[nKTEA_PY] * x[nKTEA_PY] * x[nKTEA_PY] * (x[Vm_PY] - VK);
	ICa_PY = gCa_cm * x[mCa_PY] * x[mCa_PY] * (x[Vm_PY] - VCa);
	ICa_Ca_PY = gCa_Ca_cm * (x[Vm_PY] - VCa) / ((1.0 + exp (-0.06 *(x[Vm_PY] + 45.0))) * (1.0 + exp(kBeta * (x[Ca_PY] - beta))));
	I_f_PY =  (g_LPPY_f*(x[Vm_PY]-E_syn)) / (1.0 + exp(s_f*(V_f-x[Vm_LP]))) + (g_ABPY_f*(x[Vm_PY]-E_syn)) / (1.0 + exp(s_f*(V_f-x[Vm_AB])));
	I_s_PY =  g_PD1PY_s * x[ms_PD1PY] * (x[Vm_PY] - E_syn) + g_PD2PY_s * x[ms_PD2PY] * (x[Vm_PY] - E_syn);

	INaV_AB = gNaV_r * (1.0 / (1.0 + exp(-0.2 * (x[Vm_AB] + 45.0)))) * (x[Vm_AB] - VNa);
	IK_AB = gK_r * (x[Vm_AB] - VK);
	INa_AB = gNa_r * (x[Vm_AB] - VNa);
	IB_AB = gB_r * x[mB_AB] * x[hB_AB] * (x[Vm_AB] - VB);
	INaTTX_AB = gNaTTX_r * x[mNaTTX_AB] * x[mNaTTX_AB] * x[mNaTTX_AB] * x[hNaTTX_AB] * (x[Vm_AB] - VNa);
	IKTEA_AB = gKTEA_r * x[nKTEA_AB] * x[nKTEA_AB] * x[nKTEA_AB] * x[nKTEA_AB] * (x[Vm_AB] - VK);
	ICa_AB = gCa_r * x[mCa_AB] * x[mCa_AB] * (x[Vm_AB] - VCa);
	ICa_Ca_AB = gCa_Ca_r * (x[Vm_AB] - VCa) / ((1.0 + exp (-0.06 *(x[Vm_AB] + 45.0))) * (1.0 + exp(kBeta * (x[Ca_AB] - beta))));
	I_e_AB = g_PD1AB * (x[Vm_AB] - x[Vm_PD1]) + g_PD2AB * (x[Vm_AB] - x[Vm_PD2] );

	INaV_PD1 = gNaV_cm * (1.0 / (1.0 + exp(-0.2 * (x[Vm_PD1] + 45.0)))) * (x[Vm_PD1] - VNa);
	IK_PD1 = gK_cm * (x[Vm_PD1] - VK);
	INa_PD1 = gNa_cm * (x[Vm_PD1] - VNa);
	IB_PD1 = gB_cm * x[mB_PD1] * x[hB_PD1] * (x[Vm_PD1] - VB);
	INaTTX_PD1 = gNaTTX_cm * x[mNaTTX_PD1] * x[mNaTTX_PD1] * x[mNaTTX_PD1] * x[hNaTTX_PD1] * (x[Vm_PD1] - VNa);
	IKTEA_PD1 = gKTEA_cm * x[nKTEA_PD1] * x[nKTEA_PD1] * x[nKTEA_PD1] * x[nKTEA_PD1] * (x[Vm_PD1] - VK);
	ICa_PD1 = gCa_cm * x[mCa_PD1] * x[mCa_PD1] * (x[Vm_PD1] - VCa);
	ICa_Ca_PD1 = gCa_Ca_cm * (x[Vm_PD1] - VCa) / ((1.0 + exp (-0.06 *(x[Vm_PD1] + 45.0))) * (1.0 + exp(kBeta * (x[Ca_PD1] - beta))));
	I_e_PD1 = g_PD2PD1 * (x[Vm_PD1] -  x[Vm_PD2]) + g_ABPD1 * (x[Vm_PD1] - x[Vm_AB]);
	I_f_PD1 =  (g_LPPD1_f * (x[Vm_PD1]- E_syn)) / (1.0 + exp(s_f*(V_f-x[Vm_LP])));

	INaV_PD2 = gNaV_cbm * (1.0 / (1.0 + exp(-0.2 * (x[Vm_PD2] + 45.0)))) * (x[Vm_PD2] - VNa);
	IK_PD2 = gK_cbm * (x[Vm_PD2] - VK);
	INa_PD2 = gNa_cbm * (x[Vm_PD2] - VNa);
	IB_PD2 = gB_cbm * x[mB_PD2] * x[hB_PD2] * (x[Vm_PD2] - VB);
	INaTTX_PD2 = gNaTTX_cbm * x[mNaTTX_PD2] * x[mNaTTX_PD2] * x[mNaTTX_PD2] * x[hNaTTX_PD2] * (x[Vm_PD2] - VNa);
	IKTEA_PD2 = gKTEA_cbm * x[nKTEA_PD2] * x[nKTEA_PD2] * x[nKTEA_PD2] * x[nKTEA_PD2] * (x[Vm_PD2] - VK);
	ICa_PD2 = gCa_cbm * x[mCa_PD2] * x[mCa_PD2] * (x[Vm_PD2] - VCa);
	ICa_Ca_PD2 = gCa_Ca_cbm * (x[Vm_PD2] - VCa) / ((1.0 + exp (-0.06 *(x[Vm_PD2] + 45.0))) * (1.0 + exp(kBeta * (x[Ca_PD2] - beta))));
	I_e_PD2 = g_PD1PD2 * (x[Vm_PD2] - x[Vm_PD1]) + g_ABPD2 * (x[Vm_PD2] - x [Vm_AB]);
  	I_f_PD2 =  (g_LPPD2_f * (x[Vm_PD2]- E_syn)) / (1.0 + exp(s_f*(V_f-x[Vm_LP])));

	fvec[Vm_LP] = - (INaTTX_LP + IKTEA_LP + IK_LP + INa_LP + INaV_LP + IB_LP + ICa_LP + ICa_Ca_LP + I_s_LP + I_f_LP) / Cm; 
	fvec[Ca_LP] = ro * ((-ICa_LP / cte) - (ks * x[Ca_LP]));
	fvec[mB_LP] = (1.0 / (1.0 + exp(0.4 * (x[Vm_LP] + 34.0))) - x[mB_LP]) / 0.05;
	fvec[hB_LP] = (1.0 / (1.0 + exp(-0.55 * (x[Vm_LP] + 43.0))) - x[hB_LP]) / 1.5;
	fvec[mNaTTX_LP] = (1.0 / (1.0 + exp(-0.4 * (x[Vm_LP] + 31.0))) - x[mNaTTX_LP]) / 0.0005;
	fvec[hNaTTX_LP] = (1.0 / (1.0 + exp(0.25 * (x[Vm_LP] + 45.0))) - x[hNaTTX_LP]) / 0.01;
	fvec[nKTEA_LP] = (1.0 / (1.0 + exp(-0.18 * (x[Vm_LP] + 25.0))) - x[nKTEA_LP]) / 0.015;
	fvec[mCa_LP] = (1.0 / (1.0 + exp(-0.2 * x[Vm_LP])) - x[mCa_LP]) / 0.01;
	fvec[ms_PD1LP] = ((K1_LP*(1.0-x[ms_PD1LP]))/(1.0+exp(s_s*(V_s-x[Vm_PD1])))) - K2_LP*x[ms_PD1LP];
	fvec[ms_PD2LP] = ((K1_LP*(1.0-x[ms_PD2LP]))/(1.0+exp(s_s*(V_s-x[Vm_PD2])))) - K2_LP*x[ms_PD2LP];

	fvec[Vm_PY] =  - (INaTTX_PY + IKTEA_PY + IK_PY + INa_PY + INaV_PY + IB_PY + ICa_PY + ICa_Ca_PY + I_s_PY + I_f_PY) / Cm;
	fvec[Ca_PY] = ro * ((-ICa_PY / cte) - (ks * x[Ca_PY]));
	fvec[mB_PY] = (1.0 / (1.0 + exp(0.4 * (x[Vm_PY] + 34.0))) - x[mB_PY]) / 0.05;
	fvec[hB_PY] = (1.0 / (1.0 + exp(-0.55 * (x[Vm_PY] + 43.0))) - x[hB_PY]) / 1.5;
	fvec[mNaTTX_PY] = (1.0 / (1.0 + exp(-0.4 * (x[Vm_PY] + 31.0))) - x[mNaTTX_PY]) / 0.0005;
	fvec[hNaTTX_PY] = (1.0 / (1.0 + exp(0.25 * (x[Vm_PY] + 45.0))) - x[hNaTTX_PY]) / 0.01;
	fvec[nKTEA_PY] = (1.0 / (1.0 + exp(-0.18 * (x[Vm_PY] + 25.0))) - x[nKTEA_PY]) / 0.015;
	fvec[mCa_PY] = (1.0 / (1.0 + exp(-0.2 * x[Vm_PY])) - x[mCa_PY]) / 0.01;
	fvec[ms_PD1PY] = ((K1_PY*(1.0-x[ms_PD1PY]))/(1.0+exp(s_s*(V_s-x[Vm_PD1])))) - K2_PY*x[ms_PD1PY];
	fvec[ms_PD2PY] = ((K1_PY*(1.0-x[ms_PD2PY]))/(1.0+exp(s_s*(V_s-x[Vm_PD2])))) - K2_PY*x[ms_PD2PY];

	fvec[Vm_AB] = - (INaTTX_AB + IKTEA_AB + IK_AB + INa_AB + INaV_AB + IB_AB + ICa_AB + ICa_Ca_AB + I_e_AB) / Cm;
	fvec[Ca_AB] = ro * ((-ICa_AB / cte) - (ks * x[Ca_AB]));
	fvec[mB_AB] = (1.0 / (1.0 + exp(0.4 * (x[Vm_AB] + 34.0))) - x[mB_AB]) / 0.05;
	fvec[hB_AB] = (1.0 / (1.0 + exp(-0.55 * (x[Vm_AB] + 43.0))) - x[hB_AB]) / 1.5;
	fvec[mNaTTX_AB] = (1.0 / (1.0 + exp(-0.4 * (x[Vm_AB] + 31.0))) - x[mNaTTX_AB]) / 0.0005;
	fvec[hNaTTX_AB] = (1.0 / (1.0 + exp(0.25 * (x[Vm_AB] + 45.0))) - x[hNaTTX_AB]) / 0.01;
	fvec[nKTEA_AB] = (1.0 / (1.0 + exp(-0.18 * (x[Vm_AB] + 25.0))) - x[nKTEA_AB]) / 0.015;
	fvec[mCa_AB] = (1.0 / (1.0 + exp(-0.2 * x[Vm_AB])) - x[mCa_AB]) / 0.01;

	fvec[Vm_PD1] = - (INaTTX_PD1 + IKTEA_PD1 + IK_PD1 + INa_PD1 + INaV_PD1 + IB_PD1 + ICa_PD1 + ICa_Ca_PD1 + I_f_PD1 + I_e_PD1) / Cm; 
	fvec[Ca_PD1] = ro * ((-ICa_PD1 / cte) - (ks * x[Ca_PD1]));
	fvec[mB_PD1] = (1.0 / (1.0 + exp(0.4 * (x[Vm_PD1] + 34.0))) - x[mB_PD1]) / 0.05;
	fvec[hB_PD1] = (1.0 / (1.0 + exp(-0.55 * (x[Vm_PD1] + 43.0))) - x[hB_PD1]) / 1.5;
	fvec[mNaTTX_PD1] = (1.0 / (1.0 + exp(-0.4 * (x[Vm_PD1] + 31.0))) - x[mNaTTX_PD1]) / 0.0005;
	fvec[hNaTTX_PD1] = (1.0 / (1.0 + exp(0.25 * (x[Vm_PD1] + 45.0))) - x[hNaTTX_PD1]) / 0.01;
	fvec[nKTEA_PD1] = (1.0 / (1.0 + exp(-0.18 * (x[Vm_PD1] + 25.0))) - x[nKTEA_PD1]) / 0.015;
	fvec[mCa_PD1] = (1.0 / (1.0 + exp(-0.2 * x[Vm_PD1])) - x[mCa_PD1]) / 0.01;

	fvec[Vm_PD2] = - (INaTTX_PD2 + IKTEA_PD2 + IK_PD2 + INa_PD2 + INaV_PD2 + IB_PD2 + ICa_PD2 + ICa_Ca_PD2 + I_f_PD2 + I_e_PD2) / Cm;
	fvec[Ca_PD2] = ro * ((-ICa_PD2 / cte) - (ks * x[Ca_PD2]));
	fvec[mB_PD2] = (1.0 / (1.0 + exp(0.4 * (x[Vm_PD2] + 34.0))) - x[mB_PD2]) / 0.05;
	fvec[hB_PD2] = (1.0 / (1.0 + exp(-0.55 * (x[Vm_PD2] + 43.0))) - x[hB_PD2]) / 1.5;
	fvec[mNaTTX_PD2] = (1.0 / (1.0 + exp(-0.4 * (x[Vm_PD2] + 31.0))) - x[mNaTTX_PD2]) / 0.0005;
	fvec[hNaTTX_PD2] = (1.0 / (1.0 + exp(0.25 * (x[Vm_PD2] + 45.0))) - x[hNaTTX_PD2]) / 0.01;
	fvec[nKTEA_PD2] = (1.0 / (1.0 + exp(-0.18 * (x[Vm_PD2] + 25.0))) - x[nKTEA_PD2]) / 0.015;
	fvec[mCa_PD2] = (1.0 / (1.0 + exp(-0.2 * x[Vm_PD2])) - x[mCa_PD2]) / 0.01;

    return;
}


/*================================================*/
/* Integration routine, 6th order runge kutta     */
/*================================================*/

double intey(double tiempo, double inc_integracion, double *variables) //2
{
	double apoyo[DIM],retorno[DIM],variables_hat[DIM];
	double k[6][DIM];
	double u=0.0;
	int j;

	funcion(tiempo,variables,retorno);
	
	for(j=0;j<DIM;++j) k[0][j]=inc_integracion*retorno[j];
	for(j=0;j<DIM;++j) apoyo[j]=variables[j]+k[0][j]*.2;

	funcion(tiempo+inc_integracion/5,apoyo,retorno);

	for(j=0;j<DIM;++j) k[1][j]=inc_integracion*retorno[j];
	for(j=0;j<DIM;++j) apoyo[j]=variables[j]+k[0][j]*.075+k[1][j]*0.225;

	funcion(tiempo+inc_integracion*0.3,apoyo,retorno);
	
	for(j=0;j<DIM;++j) k[2][j]=inc_integracion*retorno[j];
	for(j=0;j<DIM;++j) apoyo[j]=variables[j]+k[0][j]*.3-k[1][j]*0.9+k[2][j]*1.2;
	
	funcion(tiempo+inc_integracion*0.6,apoyo,retorno);
  
	for(j=0;j<DIM;++j) k[3][j]=inc_integracion*retorno[j];
	for(j=0;j<DIM;++j) apoyo[j]=variables[j]+k[0][j]*0.075+k[1][j]*0.675-k[2][j]*0.6+k[3][j]*0.75;

	funcion(tiempo+inc_integracion*0.9,apoyo,retorno);
	
	for(j=0;j<DIM;++j) k[4][j]=inc_integracion*retorno[j];
	for(j=0;j<DIM;++j) apoyo[j]=variables[j]+k[0][j]*0.660493827160493+k[1][j]*2.5-k[2][j]*5.185185185185185+k[3][j]*3.888888888888889-k[4][j]*0.864197530864197;
  
	funcion(tiempo+inc_integracion,apoyo,retorno);

	for(j=0;j<DIM;++j) k[5][j]=inc_integracion*retorno[j];
	for(j=0;j<DIM;++j) variables_hat[j]=variables[j]+k[0][j]*0.1049382716049382+k[2][j]*0.3703703703703703+k[3][j]*0.2777777777777777+k[4][j]*0.2469135802469135;
	for(j=0;j<DIM;++j) variables[j]+=k[0][j]*0.098765432098765+k[2][j]*0.396825396825396+k[3][j]*0.231481481481481+k[4][j]*0.308641975308641-k[5][j]*0.035714285714285;

	for(j=0;j<DIM;++j) u+=fabs(variables[j]-variables_hat[j]);
  
	return u; 

}
