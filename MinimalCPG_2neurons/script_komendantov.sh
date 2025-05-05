#!/bin/bash
#----------------------------------------------------------------------------------------------------------------------
# Script to run the Komendantov-Kononenko model simulations for two neurons in an asymmetric (fast-slow) configuration.
#
# Name of the programme: komendantov_X_f-Y_s_lyap_corr.c
#
# Execution permission: chmod +x script_komendatov.sh
#
# Run as: ./script_komendantov.sh
#----------------------------------------------------------------------------------------------------------------------

clear
echo -------------------------------------------------------------------------------------------------------------------  
echo							DATOS
echo -------------------------------------------------------------------------------------------------------------------
echo "User		: $LOGNAME"
echo
echo "Home dir	: $HOME"
echo
echo -n "Date		:  "
date
echo

#------------------- End show data script_komendatov.sh -----------------------------------------------------------------

# Compiling the programme

g++ -Wall -O2 -o komendantov_X_f-Y_s_lyap_corr komendantov_X_f-Y_s_lyap_corr.c -lm

# Variables required for call
VAR1=10000	# Simulation time
VAR2=0		# Value for calculating Lyapunov coefficients (1 == ‘Yes’, 0 == ‘No’)

# Programme execution

./komendantov_X_f-Y_s_lyap_corr entrada_parametros $VAR1 $VAR2

