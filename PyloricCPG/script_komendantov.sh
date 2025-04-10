#!/bin/bash
#--------------------------------------------------------------------------------
# Program to run the Komendantov-Kononenko model simulations for the pyloric CPG
#
# Name of the programme: komendantov_pyloric_CPG_elecSIM.c
#
# Execution permission: chmod +x script_komendatov.sh
#
# Run as: : ./script_komendantov.sh
#--------------------------------------------------------------------------------

clear
echo ----------------------------------------------------------------------------  
echo							DATA
echo ----------------------------------------------------------------------------
echo Name       	: $LOGNAME
echo
echo Directory		: $HOME	
echo
echo -n Date		:
date
echo

#------------------- End show data script_komendatov.sh -------------------------

# Compiling the programme

g++ -Wall -O2 -o komendantov_pyloric_CPG_elecSIM komendantov_pyloric_CPG_elecSIM.c -lm

# Variables required for call

VAR1=0.0000	# Initial value for electrical conductance
VAR2=0.0250	# Final value for electrical conductance
VAR3=0.0005	# Step for electrical conductance
VAR4=5000	# Simulation time

# Program execution

./komendantov_pyloric_CPG_elecSIM entrada_parametros $VAR1 $VAR2 $VAR3 $VAR4

