# Chapter 5 – Emergence of Sequential Dynamical Invariants in Central Pattern Generators from Auto-organized Constraints in their Sequence Time Intervals

This folder contains the source code and necessary files to reproduce the main simulations and results described in Chapter 5 of my thesis.

## 🧠 Overview

This simulation is based on the Komendantov-Kononenko model for a network of two chemical inhibitory neurons. Three 

The differential equations are integrated using an adapted **6th-order Runge-Kutta method**, and **Lyapunov exponents** are computed to assess the stability of the dynamics.

## 📁 Folder contents

- `script.sh`: Main execution script. It compiles and runs the simulation.
- `condiciones_iniciales.txt`: File containing the initial conditions for the model.
- `codigo_c/`: Folder containing the C source code.
- `resultados_ejemplo/`: Example output files from a representative simulation.
- `analisis_python/`: Python scripts for plotting and analyzing the simulation results.

## ▶️ How to run the code

1. Make sure you have a C compiler installed (e.g., `gcc`) and execution permissions.
2. Give execute permission to the script:
   ```bash
   chmod +x script.sh
3. Run the script:
   ./script.sh

The script compiles the code, reads initial conditions from condiciones_iniciales.txt, and produces output files containing the system's time evolution and Lyapunov exponents.

## 📊 Analysis and plotting

The output files can be analyzed using the Python scripts in analisis_python/. For example:

python3 analisis_python/plot_dynamics.py resultados_ejemplo/variables.txt

## 📎 Notes

This simulation focuses on the emergence of sequential invariants and dynamic constraints.

Initial conditions and parameters can be adjusted directly in the input files or code.