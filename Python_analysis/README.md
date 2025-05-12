# Python_analysis

This directory contains the data analysis scripts related to **Part II - Results** of Blanca Berbel Fernández's PhD thesis.

## Contents

### Chapter 6

- **main_figure_6-3.py**  
  Script to generate Figure 6-3, cycle-by-cycle pair comparison of all time intervals deined in the biphasic rhythm. 

- **main_figure_6-4.py**  
  Script to generate Figure 6-4, representin sequential ctivity for isolated two electrically coupled KK model neuron. 

- **main_figure_6-5.py**  
  Script to generate Figure 6-5, characterazing the time Interval variability and neuron excitability in the pacemaker group as a function of electrical coupling. 

- **main_figure_6-9.py**  
  Script to generate Figure 6-9, cycle-by-cycle ISI evolution for neurons in the SIEC configuration for different electrical coupling levels.

- **main_figure_6-12.py**  
  Script to generate Figure 6-12, summarizing cycle-by-cycle comparison of time intervals building the dynamical invariants under different coupling conditions.

### Chapter 7

- **main_figure_7-3.py**  
  Script to generate Figure 7-3, showing triphasic rhythm for a given conductance values in the pyloric CPG.

- **main_figure_7-4ABC.py**  
  Script to generate Figure 7-4ABC, showing the characterization of time interval variability of the Period(A), Burst Duration(B) and IBI(C) in the pyloric CPG circuit as a function of electrical coupling.

- **main_figure_7-5A_7-6A.py**  
  Script to generate the main Figures 7-5A(7-6A), illustrating the time interval variability of the measured Intervals(Delays) with respect to the LP neuron, PY neuron and AB, PD1, PD2 neurons in the pyloric CPG circuit as a function of electrical coupling.

- **main_figure_7-7A.py**  
  Script to generate Figure 7-7A, 

- **main_figure_7-7B.py**  
  Script to generate Figure 7-7B, showing comparisons between different temporal measures.

- **main_figure_7-8.py**  
  Script to generate figure 7.8 showing the cycle-by-cycle pair comparison of all time intervals defined between the Periods, Bursts, IBIs and Intervals for a given conductance value.

- **main_figure_7-9.py**  
  Script to generate figure 7.9 showing the cycle-by-cycle pair comparison of all time intervals defined between the Periods, Bursts, IBIs and Delays for a given conductance value.

- **main_figure_7-10.py**  
  Script to generate figure 7.10 showing the cycle-by-cycle pair comparison of all time intervals defined between the Intervals and Delays for a given conductance value.

- **main_figure_7-11A.py**  
  Script to generate figure 7.11A showing relationships between two time intervals (3 relationships).

- **main_figure_7-11B.py**  
  Script to generate figure 7.11B showing box-plots quantifying the cycle-by-cycle variability of the different time intervals analyzed

- **main_figure_7-12.py**  
  Script to generate 7.12 showing relationships between time intervals (2 relationships).

These scripts depend on the auxiliary module:
- **invariants_utils.py**
- **rhythm_utils.py**
- **spikes_utils.py**  

  (These files should be present at the project root or in the same directory.)

---

## Dependencies

The required Python packages are listed in `requirements.txt` and include:

- `numpy`
- `pandas`
- `matplotlib`
- `seaborn`

You can install all dependencies with:

```bash
pip install -r requirements.txt
```

## Usage

After running the C simulations and generating the required input data, you can execute the analysis scripts:

```bash
python main_figure_XXXX
```

The resulting figures will be saved automatically in the corresponding folder.


## Working Directory Configuration

Each script automatically sets its working directory to the parent folder of its location.
This ensures compatibility when running the code from different environments without manually adjusting file paths.

The working directory is configured inside each script using:

```bash
import os

separator = os.path.sep
current_dir = os.path.dirname(os.path.abspath(__file__))
parent_dir = separator.join(current_dir.split(separator)[:-1])
```

Thus, the scripts expect to find the data folders (e.g., TIME_INTERVALS/) and the output folders (e.g., SEABORN/) at the same level as the Python_analysis/ directory.

    ⚠️ Note: The data folders are not included in the repository.
    They must be created by running the C simulation codes first, and will be automatically populated when the Python scripts are executed.
