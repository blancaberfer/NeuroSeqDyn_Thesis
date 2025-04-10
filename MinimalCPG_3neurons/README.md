# Chapter 6 – Theoretical Bases for the Relation Between Excitability, Variability and Synchronization in Sequential Neural Dynamics

This folder contains the simulation code and analysis tools used for Chapter 6 of my thesis.

## 🧠 Overview

This simulation uses the Komendantov-Kononenko model for a network of **3 coupled neurons**, focusing on how excitability and variability influence sequential activation and synchronization.

The system is solved using a **6th-order Runge-Kutta integrator**.

## 📁 Folder contents

- `script.sh`: Script to compile and run the C code.
- `condiciones_iniciales.txt`: Initial conditions file.
- `codigo_c/`: C source code for the model.
- `resultados_ejemplo/`: Sample output files from a test simulation.
- `analisis_python/`: Python scripts for visualization and post-processing.

## ▶️ How to run the code

```bash
chmod +x script.sh
./script.sh

## 📊 Analysis and plotting

Use the scripts in analisis_python/ to generate plots and compute relevant metrics:

python3 analisis_python/plot_dynamics.py resultados_ejemplo/variables.txt

## 📎 Notes

No Lyapunov exponent calculation is included in this chapter.

Output includes time series and variables relevant to the analysis of variability and synchronization.