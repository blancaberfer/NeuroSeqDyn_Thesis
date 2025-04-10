# Chapter 7 – Effect of Electrical Synapses in the Cycle-by-cycle Sequential Dynamics of a Pyloric Central Pattern Generator Model

This directory includes all the code and tools used in Chapter 7 of my thesis, focusing on the impact of electrical coupling in a pyloric CPG model.

## 🧠 Overview

This simulation models a **pyloric central pattern generator** (typically involving 5 or more neurons), based on the Komendantov-Kononenko equations and using a **6th-order Runge-Kutta** method for integration.

It explores the role of electrical synapses in shaping cycle-by-cycle dynamics of neural sequences.

## 📁 Folder contents

- `script_komendantov.sh`: Compilation and execution script.
- `entrada_parametros`: Initial conditions of conductance, calcium concentration and for the firing modes of the KK model: regular, chaotic, chaotic burst.
- `komendantov_pyloric_CPG_elecSIM.c`: C source code specific to this model.
- `example_results/`: Sample output files.
- `codes_python/`: Python scripts for data visualization.

## ▶️ How to run the code

```bash
chmod +x script_komendantov.sh
./script_komendantov.sh

## 📊 Analysis and plotting

Plot dynamics using the included scripts:

python3 codes_python/plot_dynamics.py 

## 📎 Notes

    This version of the model includes electrical (gap junction) connections.

    Suitable for analyzing the impact of coupling strength and structure on timing and phase relations in the CPG.