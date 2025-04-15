#!/bin/bash
#---------------------------------------------------------------------------------------
# Script to run the Komendantov-Kononenko model simulations for the FIEC configuration
#
# Name of the programme: komendantov_FIEC.c
#
# Execution permission: chmod +x script_komendantov.sh
#
# Run as: ./script_komendantov.sh
#--------------------------------------------------------------------------------------

clear
echo ----------------------------------------------------------------------------------  
echo							DATOS
echo ----------------------------------------------------------------------------------
echo "User		: $LOGNAME"
echo
echo "Home dir	: $HOME"
echo
echo -n "Date		:  "
date
echo

#------------------- End show data script_komendatov.sh --------------------------------

# Compiling the programme

gcc -Wall -O2 -o komendantov_FIEC komendantov_FIEC.c -lm
if [ $? -ne 0 ]; then
    echo "Compilation failed. Exiting."
    exit 1
fi

# Variables required for call
FINAL_G=0.1000   # Final value for electrical conductance
STEP_G=0.0005    # Step for electrical conductance
SIM_TIME=10000   # Simulation time

# Programme execution

./komendantov_FIEC initial_parameters $FINAL_G $STEP_G $SIM_TIME

