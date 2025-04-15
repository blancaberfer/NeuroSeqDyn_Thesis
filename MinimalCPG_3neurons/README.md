# Chapter 6 – Theoretical Bases for the Relation Between Excitability, Variability and Synchronization in Sequential Neural Dynamics

This folder contains the simulation code and analysis tools used for Chapter 6 of my thesis.

## 🧠 Overview

This simulation uses the Komendantov-Kononenko model for a network of **3 coupled neurons**, focusing on how excitability and variability influence sequential activation and synchronization.

This chapter explores two distinct configurations:

- **SIEC**: Slow Electrical Inhibitory Coupled neuron  
- **FIEC**: Fast Electrical Inhibitory Coupled neuron

Each folder contains the specific implementation and outputs for that configuration.

The system is solved using a **6th-order Runge-Kutta integrator**.

## 📁 Folder contents

- `KK_SIEC_neuron/`
	- `script_komendantov.sh`: Script to compile and run the C code.
	- `initial_parameters`: Initial conditions file.
	- `komendantov_SIEC.c`: C source code for the model.

- `KK_FIEC_neuron/`  
	- Same structure as above, adapted for the FIEC configuration.

## ▶️ How to run the code

```bash
chmod +x script_komendantov.sh
./script.sh

## 📊 Analysis and plotting

Use the scripts in analisis_python/ to generate plots and compute relevant metrics:

python3 analisis_python/plot_dynamics.py resultados_ejemplo/variables.txt

## 📎 Notes

No Lyapunov exponent calculation is included in this chapter.

Output includes time series and variables relevant to the analysis of variability and synchronization.