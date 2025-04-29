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

## 📊 Analysis Tools (Python)  
➡️ [`Python_analysis/`](./Python_analysis/)  
General-purpose scripts for plotting and analyzing simulation results across all chapters.

You can install the Python dependencies using:

```bash
pip install -r Python_analysis/requirements.txt
```
---

## 📂 Supplementary Material (in progress)

This section will include additional materials related to the thesis:

    Papers/ – Published articles based on the results presented (to be added).

    Thesis/ – The official version of the defended thesis (coming soon).

    Slides/ – Presentation slides used during the thesis defense (to be added).

    video/  - Multimedia files have been created, incorporing both the real invariant and the simulation.
---

## 💾 Requirements

- GCC or any standard C compiler
- Bash-compatible terminal
- Python 3.x with packages listed in `Python_analysis/requirements.txt` (e.g. `numpy`, `scipy`, `matplotlib`, `pyspike`, etc.)


## 🧪 Reproducibility

Each folder is self-contained and includes a `README.md` with specific instructions on how to run the code and reproduce the main results of that chapter.

If you encounter any issues or would like to collaborate, feel free to open an issue or contact me.

## 🧼 C Code Style

All C source files follow a consistent code style defined in the .clang-format file.

To apply the formatting to all .c files:

```bash 
find . -name "*.c" -exec clang-format -i {} \;
```

The style is based on the Google style guide, with custom indentation and spacing to improve clarity for neural simulations.

---

📬 _Author: Blanca Berbel Fernández_  
📅 _Thesis defense: [To be completed]_  
🔗 _Thesis repository: [Link to be added]_
