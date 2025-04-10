# Thesis Code – Computational Models of Sequential Neural Dynamics

This repository contains all the simulation and analysis code developed for the results presented in my PhD thesis in Computational Neuroscience.

Each chapter is organized in its own folder and includes:
- C code implementing variants of the Komendantov-Kononenko neuron model
- Shell scripts to compile and run simulations
- Example input/output files
- Python scripts for visualization and post-processing

---

## 📚 Contents

### 🧠 Chapter 5  
**Emergence of Sequential Dynamical Invariants in Central Pattern Generators from Auto-organized Constraints in their Sequence Time Intervals**  
➡️ [`MinimalCPG_2neurons/`](./MinimalCPG_2neurons/)  
Simulations for 2 coupled neurons including Lyapunov exponent analysis.

---

### 🔄 Chapter 6  
**Theoretical Bases for the Relation Between Excitability, Variability and Synchronization in Sequential Neural Dynamics**  
➡️ [`MinimalCPG_3neurons/`](./MinimalCPG_3neurons/)  
Simulations with 3 neurons focusing on variability and synchronization.

---

### 🔌 Chapter 7  
**Effect of Electrical Synapses in the Cycle-by-cycle Sequential Dynamics of a Pyloric Central Pattern Generator Model**  
➡️ [`PyloricCPG/`](./PyloricCPG/)  
Simulations of a full pyloric CPG model including electrical (gap junction) connections.

---

### 🎓 Additional Materials  
➡️ [`MaterialAdicional/`](./MaterialAdicional/)  
Includes:
- Research articles
- Simulation videos
- Thesis defense slides (to be added)
- Link to the final published thesis (to be added)

---

## 💾 Requirements

- GCC or any standard C compiler
- Bash-compatible terminal
- Python 3.x with common packages (e.g. `numpy`, `matplotlib`) for plotting

## 🧪 Reproducibility

Each folder is self-contained and includes a `README.md` with specific instructions on how to run the code and reproduce the main results of that chapter.

If you encounter any issues or would like to collaborate, feel free to open an issue or contact me.

---

📬 _Author: Blanca Berbel Fernández_  
📅 _Thesis defense: [To be completed]_  
🔗 _Thesis repository: [Link to be added]_
