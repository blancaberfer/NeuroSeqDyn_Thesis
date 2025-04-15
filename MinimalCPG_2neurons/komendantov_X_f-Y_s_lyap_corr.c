// Blanca Berbel Fdez
// Creation date: 28/12/2021
// Last modification: 09/02/2023

// Program to calculate Lyapunov coefficients in given situation.
// Case collected here: asymmetrical circuit with fast and slow current, from the study of X with
// values 1.0, 0.4 (first case reflected on the chapter). Furthermore, the currents are saved so
// that their shape can be investigated.

// System libraries
#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

// Program parameter access constants
#define PARAMETROS 3 // Number of parameters passed to the program
#define ENTRADA 1    // File with initial conditions
#define TIME 2       // Simulation time
#define LYAPUNOV 3   // Set to '1' for calculation, '0' not to calculate Lyapunov coefficients.

// Model variable constants
#define DIM 17 // Number of variables

// Access constants to model variables
#define Vm_X 0
#define Ca_X 1
#define mB_X 2
#define hB_X 3
#define mNaTTX_X 4
#define hNaTTX_X 5
#define nKTEA_X 6
#define mCa_X 7
#define Vm_Y 8
#define Ca_Y 9
#define mB_Y 10
#define hB_Y 11
#define mNaTTX_Y 12
#define hNaTTX_Y 13
#define nKTEA_Y 14
#define mCa_Y 15
#define ms_YX 16

// Model contants
#define VNa 40.0
#define VK -70.0
#define VB -58.0
#define VCa 150.0
#define Cm 0.02
#define ks 50.0
#define ro 0.002
#define kBeta 15000.0
#define beta 0.00004
#define cte 808.3108459
#define E_syn -65.0
#define V_s -49.0
#define V_f -44.7
#define g_XY_f 0.0255 // Fast-chemical conductance
#define g_YX_s 0.0155 // Slow-chemical conductance
#define s_s 1.0
#define s_f 0.31
#define K1_X 1.10
#define K2_X 0.4

// Global variables
static double V0 = 0.0;
static double Ca0 = 0.0;
static double gK_cbm =
    0.0; // ** All neurons are set according to KK parameters for the chaotic bursting regime.
static double gNaV_cbm = 0.0;
static double gNa_cbm = 0.0;
static double gB_cbm = 0.0;
static double gNaTTX_cbm = 0.0;
static double gKTEA_cbm = 0.0;
static double gCa_cbm = 0.0;
static double gCa_Ca_cbm = 0.0;

// Currents variables
static double IK_X, INa_X, INaV_X, IB_X, INaTTX_X, IKTEA_X, ICa_X, ICa_Ca_X;
static double IK_Y, INa_Y, INaV_Y, IB_Y, INaTTX_Y, IKTEA_Y, ICa_Y, ICa_Ca_Y;
static double I_s_X;
static double I_f_Y;

// Function definition
void funcion(double, double *, double *);
void set_parameters(char *);
void set_conditions(double *, double *);
double intey(double, double, double *);

// Lyapunov's functions
double modulo(double *);
double escalar(double *, double *);
void ortonormal(double y[DIM][DIM], double *);
void compone(double vector[DIM][DIM], double yy[DIM + 1][DIM], double);
void obtiene(double vector[DIM][DIM], double y[DIM + 1][DIM]);

// Main program
int main(int argc, char **argv) {
    double time_max, time;
    double inct = 1e-4;

    // Counter for saving data
    int punto = 0;

    // Integer numbers for spikes
    int stopX = 0, contX = 0, contY = 0, stopY = 0;

    // Vectors with model variables
    double variables[DIM + 1][DIM], variables_ant[DIM], variables_act[DIM], variables_sig[DIM];

    // Output and input data files
    FILE *salida, *spikes_X, *spikes_Y, *s_lyapunov, *s_corrientes_X, *s_corrientes_Y,
        *s_corrientes_con;

    char nombrearchivoV[80], nombrearchivoX[80], nombrearchivoY[80], nombrearchivoLyap[80],
        nombrearchivoCorr_X[80], nombrearchivoCorr_Y[80], nombrearchivoCorr_con[80];

    // Variables required for the calculation of coefficients.
    short conLyapunov = 0;
    double vector[DIM][DIM], distancia[DIM], exponentes[DIM + 1], eal = 1e-6;
    double u = 0.0;

    // Integer numbers for loops
    int i, j, k;

    if (argc != PARAMETROS + 1) {
        puts("Parámetros en script_komendantov");
        exit(0);
    }

    time_max = atof(argv[TIME]);
    conLyapunov = atoi(argv[LYAPUNOV]);
    set_parameters(argv[ENTRADA]);

    set_conditions(variables[0], variables_ant);

    sprintf(nombrearchivoV, "V_lyap_K1_1.10_K2_0.40");
    sprintf(nombrearchivoX, "S_X_lyap_K1_1.10_K2_0.40");
    sprintf(nombrearchivoY, "S_Y_lyap_K1_1.10_K2_0.40");
    sprintf(nombrearchivoLyap, "Coef_lyap_K1_1.10_K2_0.40");
    sprintf(nombrearchivoCorr_X, "Corr_X_K1_1.10_K2_0.40");
    sprintf(nombrearchivoCorr_Y, "Corr_Y_K1_1.10_K2_0.40");
    sprintf(nombrearchivoCorr_con, "Corr_con_K1_1.10_K2_0.40");

    salida = fopen(nombrearchivoV, "w");
    spikes_X = fopen(nombrearchivoX, "w");
    spikes_Y = fopen(nombrearchivoY, "w");
    s_lyapunov = fopen(nombrearchivoLyap, "w");
    s_corrientes_X = fopen(nombrearchivoCorr_X, "w");
    s_corrientes_Y = fopen(nombrearchivoCorr_Y, "w");
    s_corrientes_con = fopen(nombrearchivoCorr_con, "w");

    if (salida == NULL) {
        printf("Error creating output files.\n");
        exit(0);
    } else {
        if (conLyapunov) {
            // Initial conditions
            for (i = 0; i < DIM; i++) {
                for (j = 0; j < DIM; j++) {
                    if (i == j)
                        vector[i][j] = 1.0;
                    else
                        vector[i][j] = 0.0;
                }
            }

            ortonormal(vector, distancia);

            // Lyapunov exponents
            for (i = 0; i < (DIM + 1); i++) exponentes[i] = 0.0;
        }

        time = 0.0;
        intey(time, inct, variables[0]);

        variables_act[Vm_X] = variables[0][Vm_X];
        variables_act[Vm_Y] = variables[0][Vm_Y];

        time += inct;
        intey(time, inct, variables[0]);

        variables_sig[Vm_X] = variables[0][Vm_X];
        variables_sig[Vm_Y] = variables[0][Vm_Y];

        for (time = 0.0; time < time_max; time += inct) {
            variables_ant[Vm_X] = variables_act[Vm_X];
            variables_ant[Vm_Y] = variables_act[Vm_Y];

            variables_act[Vm_X] = variables_sig[Vm_X];
            variables_act[Vm_Y] = variables_sig[Vm_Y];

            if ((time > 1000) && conLyapunov)
                compone(vector, variables, eal);

            intey(time, inct, variables[0]);

            if ((time > 1000) && conLyapunov) {
                for (i = 1; i < DIM + 1; i++) intey(time, inct, variables[i]);

                obtiene(vector, variables);
                ortonormal(vector, distancia);
                for (k = 0; k < DIM; k++) exponentes[k] += log(distancia[k] / eal);
                u = 1.0;
                for (k = 0; k < DIM; k++) u *= distancia[k] / eal;
                exponentes[DIM] += log(u);
            }

            punto += 1;

            if (punto == 5) {
                fprintf(salida, "%.4f\t%.4f\t%.4f\n", time, variables[0][Vm_X], variables[0][Vm_Y]);
                fprintf(s_corrientes_X, "%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\n",
                        time, IK_X, INa_X, INaV_X, IB_X, INaTTX_X, IKTEA_X, ICa_X, ICa_Ca_X);
                fprintf(s_corrientes_Y, "%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\n",
                        time, IK_Y, INa_Y, INaV_Y, IB_Y, INaTTX_Y, IKTEA_Y, ICa_Y, ICa_Ca_Y);
                fprintf(s_corrientes_con, "%.4f\t%.4f\t%.4f\n", time, I_s_X, I_f_Y);

                punto = 0;

                if ((time > 1000) && conLyapunov) {
                    fprintf(s_lyapunov, "%lf ", time);
                    for (i = 0; i < DIM + 1; i++)
                        fprintf(s_lyapunov, "%0.5lg ", exponentes[i] / time);
                    fprintf(s_lyapunov, "\n");
                }
            }

            variables_sig[Vm_X] = variables[0][Vm_X];
            variables_sig[Vm_Y] = variables[0][Vm_Y];

            if (variables_act[Vm_X] > 0) {
                if (((variables_act[Vm_X] - variables_ant[Vm_X]) > 0) &&
                    ((variables_sig[Vm_X] - variables_act[Vm_X]) < 0)) {
                    if (contX == 0) {
                        fprintf(spikes_X, "%d\n", 1);
                        contX++;
                    }
                    if (stopX == 0) {
                        fprintf(spikes_X, "\n%lf\t%lf\t%d\t%d\n", time, variables_act[Vm_X], 1, 0);
                        stopX = 1;
                    } else {
                        fprintf(spikes_X, "\n%lf\t%lf\t%d\t%d\n", time, variables_act[Vm_X], 0, 0);
                    }
                }
            }

            if (variables_act[Vm_X] < -50) {
                stopX = 0;
                contX = 0;
            }

            if (variables_act[Vm_Y] > 0) {
                if (((variables_act[Vm_Y] - variables_ant[Vm_Y]) > 0) &&
                    ((variables_sig[Vm_Y] - variables_act[Vm_Y]) < 0)) {
                    if (contY == 0) {
                        fprintf(spikes_Y, "%d\n", 1);
                        contY++;
                    }
                    if (stopY == 0) {
                        fprintf(spikes_Y, "\n%lf\t%lf\t%d\t%d\n", time, variables_act[Vm_Y], 1, 0);
                        stopY = 1;
                    } else {
                        fprintf(spikes_Y, "\n%lf\t%lf\t%d\t%d\n", time, variables_act[Vm_Y], 0, 0);
                    }
                }
            }
            if (variables_act[Vm_Y] < -50) {
                stopY = 0;
                contY = 0;
            }
            fflush(salida);
            fflush(spikes_X);
            fflush(spikes_Y);
        }
    }

    fclose(salida);
    fclose(spikes_X);
    fclose(spikes_Y);

    exit(1);
}

/*=======================================*/
/* Functions for Variable Initialization */
/*=======================================*/

void set_parameters(char *entrada) {
    FILE *puntero;

    puntero = fopen(entrada, "r");

    if (puntero == NULL) {
        printf("Error al abrir el fichero con los datos de entrada.\n");
        exit(0);
    } else {
        if (fscanf(puntero, "%lf", &V0) == -100) {
            fprintf(stderr, "Incorrect value\n");
        }
        if (fscanf(puntero, "%lf", &Ca0) == -100) {
            fprintf(stderr, "Incorrect value\n");
        }
        if (fscanf(puntero, "%lf", &gK_cbm) == -100) {
            fprintf(stderr, "Incorrect value\n");
        }
        if (fscanf(puntero, "%lf", &gNa_cbm) == -100) {
            fprintf(stderr, "Incorrect value\n");
        }
        if (fscanf(puntero, "%lf", &gNaV_cbm) == -100) {
            fprintf(stderr, "Incorrect value\n");
        }
        if (fscanf(puntero, "%lf", &gB_cbm) == -100) {
            fprintf(stderr, "Incorrect value\n");
        }
        if (fscanf(puntero, "%lf", &gNaTTX_cbm) == -100) {
            fprintf(stderr, "Incorrect value\n");
        }
        if (fscanf(puntero, "%lf", &gKTEA_cbm) == -100) {
            fprintf(stderr, "Incorrect value\n");
        }
        if (fscanf(puntero, "%lf", &gCa_cbm) == -100) {
            fprintf(stderr, "Incorrect value\n");
        }
        if (fscanf(puntero, "%lf", &gCa_Ca_cbm) == -100) {
            fprintf(stderr, "Incorrect value\n");
        }
    }

    fclose(puntero);

    return;
}

void set_conditions(double *variables, double *variables_ant) {
    variables_ant[Vm_X] = V0;
    variables[Vm_X] = V0 + ((double) rand() / RAND_MAX);
    variables[Ca_X] = Ca0;

    variables_ant[Vm_Y] = -V0;
    variables[Vm_Y] = -V0 + ((double) rand() / RAND_MAX);
    variables[Ca_Y] = Ca0;

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

    variables[ms_YX] = K1_X / (K1_X + K2_X * (1.0 + exp(s_s * (V_s - variables[Vm_Y]))));

    return;
}

/*======================================*/
/* Calculation functions of the model   */
/*======================================*/

void funcion(double tiempo, double *x, double *fvec) {
    INaV_X = gNaV_cbm * (1.0 / (1.0 + exp(-0.2 * (x[Vm_X] + 45.0)))) * (x[Vm_X] - VNa);
    IK_X = gK_cbm * (x[Vm_X] - VK);
    INa_X = gNa_cbm * (x[Vm_X] - VNa);
    IB_X = gB_cbm * x[mB_X] * x[hB_X] * (x[Vm_X] - VB);
    INaTTX_X = gNaTTX_cbm * x[mNaTTX_X] * x[mNaTTX_X] * x[mNaTTX_X] * x[hNaTTX_X] * (x[Vm_X] - VNa);
    IKTEA_X = gKTEA_cbm * x[nKTEA_X] * x[nKTEA_X] * x[nKTEA_X] * x[nKTEA_X] * (x[Vm_X] - VK);
    ICa_X = gCa_cbm * x[mCa_X] * x[mCa_X] * (x[Vm_X] - VCa);
    ICa_Ca_X = gCa_Ca_cbm * (x[Vm_X] - VCa) /
               ((1.0 + exp(-0.06 * (x[Vm_X] + 45.0))) * (1.0 + exp(kBeta * (x[Ca_X] - beta))));
    I_s_X = g_YX_s * x[ms_YX] * (x[Vm_X] - E_syn);

    INaV_Y = gNaV_cbm * (1.0 / (1.0 + exp(-0.2 * (x[Vm_Y] + 45.0)))) * (x[Vm_Y] - VNa);
    IK_Y = gK_cbm * (x[Vm_Y] - VK);
    INa_Y = gNa_cbm * (x[Vm_Y] - VNa);
    IB_Y = gB_cbm * x[mB_Y] * x[hB_Y] * (x[Vm_Y] - VB);
    INaTTX_Y = gNaTTX_cbm * x[mNaTTX_Y] * x[mNaTTX_Y] * x[mNaTTX_Y] * x[hNaTTX_Y] * (x[Vm_Y] - VNa);
    IKTEA_Y = gKTEA_cbm * x[nKTEA_Y] * x[nKTEA_Y] * x[nKTEA_Y] * x[nKTEA_Y] * (x[Vm_Y] - VK);
    ICa_Y = gCa_cbm * x[mCa_Y] * x[mCa_Y] * (x[Vm_Y] - VCa);
    ICa_Ca_Y = gCa_Ca_cbm * (x[Vm_Y] - VCa) /
               ((1.0 + exp(-0.06 * (x[Vm_Y] + 45.0))) * (1.0 + exp(kBeta * (x[Ca_Y] - beta))));
    I_f_Y = (g_XY_f * (x[Vm_Y] - E_syn)) / (1.0 + exp(s_f * (V_f - x[Vm_X])));

    fvec[Vm_X] =
        -(INaTTX_X + IKTEA_X + IK_X + INa_X + INaV_X + IB_X + ICa_X + ICa_Ca_X + I_s_X) / Cm;
    fvec[Ca_X] = ro * ((-ICa_X / cte) - (ks * x[Ca_X]));
    fvec[mB_X] = (1.0 / (1.0 + exp(0.4 * (x[Vm_X] + 34.0))) - x[mB_X]) / 0.05;
    fvec[hB_X] = (1.0 / (1.0 + exp(-0.55 * (x[Vm_X] + 43.0))) - x[hB_X]) / 1.5;
    fvec[mNaTTX_X] = (1.0 / (1.0 + exp(-0.4 * (x[Vm_X] + 31.0))) - x[mNaTTX_X]) / 0.0005;
    fvec[hNaTTX_X] = (1.0 / (1.0 + exp(0.25 * (x[Vm_X] + 45.0))) - x[hNaTTX_X]) / 0.01;
    fvec[nKTEA_X] = (1.0 / (1.0 + exp(-0.18 * (x[Vm_X] + 25.0))) - x[nKTEA_X]) / 0.015;
    fvec[mCa_X] = (1.0 / (1.0 + exp(-0.2 * x[Vm_X])) - x[mCa_X]) / 0.01;
    fvec[ms_YX] =
        ((K1_X * (1.0 - x[ms_YX])) / (1.0 + exp(s_s * (V_s - x[Vm_Y])))) - K2_X * x[ms_YX];

    fvec[Vm_Y] =
        -(INaTTX_Y + IKTEA_Y + IK_Y + INa_Y + INaV_Y + IB_Y + ICa_Y + ICa_Ca_Y + I_f_Y) / Cm;
    fvec[Ca_Y] = ro * ((-ICa_Y / cte) - (ks * x[Ca_Y]));
    fvec[mB_Y] = (1.0 / (1.0 + exp(0.4 * (x[Vm_Y] + 34.0))) - x[mB_Y]) / 0.05;
    fvec[hB_Y] = (1.0 / (1.0 + exp(-0.55 * (x[Vm_Y] + 43.0))) - x[hB_Y]) / 1.5;
    fvec[mNaTTX_Y] = (1.0 / (1.0 + exp(-0.4 * (x[Vm_Y] + 31.0))) - x[mNaTTX_Y]) / 0.0005;
    fvec[hNaTTX_Y] = (1.0 / (1.0 + exp(0.25 * (x[Vm_Y] + 45.0))) - x[hNaTTX_Y]) / 0.01;
    fvec[nKTEA_Y] = (1.0 / (1.0 + exp(-0.18 * (x[Vm_Y] + 25.0))) - x[nKTEA_Y]) / 0.015;
    fvec[mCa_Y] = (1.0 / (1.0 + exp(-0.2 * x[Vm_Y])) - x[mCa_Y]) / 0.01;

    return;
}

/*================================================*/
/* Integration routine, 6th order runge kutta     */
/*================================================*/

double intey(double tiempo, double inc_integracion, double *variables) {
    double apoyo[DIM], retorno[DIM], variables_hat[DIM];
    double k[6][DIM];
    double u = 0.0;
    int j;

    funcion(tiempo, variables, retorno);

    for (j = 0; j < DIM; ++j) k[0][j] = inc_integracion * retorno[j];
    for (j = 0; j < DIM; ++j) apoyo[j] = variables[j] + k[0][j] * .2;

    funcion(tiempo + inc_integracion / 5, apoyo, retorno);

    for (j = 0; j < DIM; ++j) k[1][j] = inc_integracion * retorno[j];
    for (j = 0; j < DIM; ++j) apoyo[j] = variables[j] + k[0][j] * .075 + k[1][j] * 0.225;

    funcion(tiempo + inc_integracion * 0.3, apoyo, retorno);

    for (j = 0; j < DIM; ++j) k[2][j] = inc_integracion * retorno[j];
    for (j = 0; j < DIM; ++j)
        apoyo[j] = variables[j] + k[0][j] * .3 - k[1][j] * 0.9 + k[2][j] * 1.2;

    funcion(tiempo + inc_integracion * 0.6, apoyo, retorno);

    for (j = 0; j < DIM; ++j) k[3][j] = inc_integracion * retorno[j];
    for (j = 0; j < DIM; ++j)
        apoyo[j] =
            variables[j] + k[0][j] * 0.075 + k[1][j] * 0.675 - k[2][j] * 0.6 + k[3][j] * 0.75;

    funcion(tiempo + inc_integracion * 0.9, apoyo, retorno);

    for (j = 0; j < DIM; ++j) k[4][j] = inc_integracion * retorno[j];
    for (j = 0; j < DIM; ++j)
        apoyo[j] = variables[j] + k[0][j] * 0.660493827160493 + k[1][j] * 2.5 -
                   k[2][j] * 5.185185185185185 + k[3][j] * 3.888888888888889 -
                   k[4][j] * 0.864197530864197;

    funcion(tiempo + inc_integracion, apoyo, retorno);

    for (j = 0; j < DIM; ++j) k[5][j] = inc_integracion * retorno[j];
    for (j = 0; j < DIM; ++j)
        variables_hat[j] = variables[j] + k[0][j] * 0.1049382716049382 +
                           k[2][j] * 0.3703703703703703 + k[3][j] * 0.2777777777777777 +
                           k[4][j] * 0.2469135802469135;
    for (j = 0; j < DIM; ++j)
        variables[j] += k[0][j] * 0.098765432098765 + k[2][j] * 0.396825396825396 +
                        k[3][j] * 0.231481481481481 + k[4][j] * 0.308641975308641 -
                        k[5][j] * 0.035714285714285;

    for (j = 0; j < DIM; ++j) u += fabs(variables[j] - variables_hat[j]);

    return u;
}

/*=========================================*/
/* Functions necessary for the calculation */
/* of the Lyapunov coefficients            */
/*=========================================*/

double modulo(double *y) {
    double u = 0.0;
    int i;
    for (i = 0; i < DIM; ++i) u += y[i] * y[i];
    u = sqrt(u);

    return u;
}

double escalar(double *y, double *y0) {
    double u = 0.0;
    int i;
    for (i = 0; i < DIM; ++i) u += y[i] * y0[i];

    return u;
}

void ortonormal(double y[DIM][DIM], double *distancia) {
    double y0[DIM][DIM];
    double u;
    int i, j, k;

    for (i = 0; i < DIM; ++i)
        for (j = 0; j < DIM; ++j) y0[i][j] = 0.0;

    distancia[0] = modulo(y[0]);
    for (i = 0; i < DIM; ++i) y0[0][i] = y[0][i] / distancia[0];

    for (j = 1; j < DIM; ++j) {
        for (i = 0; i < j; ++i) {
            u = escalar(y0[i], y[j]);
            for (k = 0; k < DIM; ++k) y0[j][k] -= u * y0[i][k];
        }
        for (k = 0; k < DIM; ++k) y0[j][k] += y[j][k];
        distancia[j] = modulo(y0[j]);
        for (k = 0; k < DIM; ++k) y0[j][k] = y0[j][k] / distancia[j];
    }

    for (i = 0; i < DIM; ++i)
        for (j = 0; j < DIM; ++j) y[i][j] = y0[i][j];
}

void compone(double vector[DIM][DIM], double y[DIM + 1][DIM], double eal) {
    int i, j;
    for (i = 0; i < DIM; ++i)
        for (j = 0; j < DIM; ++j) y[i + 1][j] = y[0][j] + vector[i][j] * eal;
    ;
}

void obtiene(double vector[DIM][DIM], double y[DIM + 1][DIM]) {
    int i, j;
    for (i = 0; i < DIM; ++i)
        for (j = 0; j < DIM; ++j) vector[i][j] = y[i + 1][j] - y[0][j];
    ;
}
