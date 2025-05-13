# Python_analysis

This folder contains general-purpose Python scripts used to analyze simulation results from the models described in the thesis.

Each script performs a type of analysis that may apply across different models, figures, or chapters. Analyses include, for example:

- Time interval extraction and statistical characterization
- Variability and synchrony quantification
- Phase relationship and correlation analysis
- Automated figure generation

These tools are designed to be modular and reusable across multiple experimental setups.

--

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
python main_XXX.py
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
