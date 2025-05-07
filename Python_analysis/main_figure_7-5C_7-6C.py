#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue May 21 09:27:00 2024

Last edit: Tue Dec 17 13:44:00 2024

@author: Blanca Berbel
"""

# ---------------------------------------------------------------------------------------------#
#                                                                                              #
# Interval trend and variability for AB,PD1,PD2 - (LP, PY): for P-values with rhythm3phase     #
#                                                                                              #
# ---------------------------------------------------------------------------------------------#

import os
import matplotlib.pyplot as plt
import spikes_utils as s_u
import seaborn as sns
import pandas as pd
import numpy as np

# Work directory

separador = os.path.sep
dir_actual = os.path.dirname(os.path.abspath(__file__))
dir = separador.join(dir_actual.split(separador)[:-1])


P_ini = 0.0120
P_step = 0.0005
P_end = 0.0155

P1 = P_ini
P2 = P1

P = np.arange(P_ini, P_end + P_step, P_step)


intervalo = r"Interval" #Use intervalo = r"Delay" to make the analogue plot for the Delay interval


data_means = {
    intervalo + r"$\,ABLP$": [],
    intervalo + r"$\,ABPY$": [],
    intervalo + r"$\,PD1LP$": [],
    intervalo + r"$\,PD1PY$": [],
    intervalo + r"$\,PD2LP$": [],
    intervalo + r"$\,PD2PY$": [],
}


data_stds = {
    intervalo + r"$\,ABLP$": [],
    intervalo + r"$\,ABPY$": [],
    intervalo + r"$\,PD1LP$": [],
    intervalo + r"$\,PD1PY$": [],
    intervalo + r"$\,PD2LP$": [],
    intervalo + r"$\,PD2PY$": [],
}

for P1 in P:
    P2 = P1

    intervaloABLP = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/"
        + intervalo
        + "_ABLP_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    intervaloABPY = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/"
        + intervalo
        + "_ABPY_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    intervaloPD1LP = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/"
        + intervalo
        + "_PD1LP_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    intervaloPD1PY = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/"
        + intervalo
        + "_PD1PY_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    intervaloPD2LP = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/"
        + intervalo
        + "_PD2LP_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    intervaloPD2PY = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/"
        + intervalo
        + "_PD2PY_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )

    data_means[intervalo + r"$\,ABLP$"].append(np.mean(intervaloABLP))
    data_means[intervalo + r"$\,ABPY$"].append(np.mean(intervaloABPY))
    data_means[intervalo + r"$\,PD1LP$"].append(np.mean(intervaloPD1LP))
    data_means[intervalo + r"$\,PD1PY$"].append(np.mean(intervaloPD1PY))
    data_means[intervalo + r"$\,PD2LP$"].append(np.mean(intervaloPD2LP))
    data_means[intervalo + r"$\,PD2PY$"].append(np.mean(intervaloPD2PY))

    data_stds[intervalo + r"$\,ABLP$"].append(np.std(intervaloABLP))
    data_stds[intervalo + r"$\,ABPY$"].append(np.std(intervaloABPY))
    data_stds[intervalo + r"$\,PD1LP$"].append(np.std(intervaloPD1LP))
    data_stds[intervalo + r"$\,PD1PY$"].append(np.std(intervaloPD1PY))
    data_stds[intervalo + r"$\,PD2LP$"].append(np.std(intervaloPD2LP))
    data_stds[intervalo + r"$\,PD2PY$"].append(np.std(intervaloPD2PY))


df_means = pd.DataFrame(data_means, index=P)
df_stds = pd.DataFrame(data_stds, index=P)


# Figure
plt.rcParams["figure.dpi"] = 300
plt.rcParams["figure.figsize"] = (10, 4)


plt.figure()

plt.xticks(rotation=24, ha="right")

plt.xlabel(r"$g^{\mathrm{ec}}(\mu \mathrm{S})$", fontsize=16)
plt.ylabel(r"$t(\mathrm{s})$", fontsize=16)

plt.tick_params(axis="both", labelsize=16)


line_styles = ["-", "-", "-", "-", "-", "-"]
palette = sns.color_palette("husl", 6)

# Plot with error bands
for i, (col, style, color) in enumerate(zip(df_means.columns, line_styles, palette)):
    plt.plot(df_means.index, df_means[col], label=col, linestyle=style, color=color)

    # Plot error bars representing the standard deviation
    plt.errorbar(
        df_means.index,
        df_means[col],
        yerr=df_stds[col],
        fmt="o",
        color=color,
        capsize=5,
        capthick=2,
        elinewidth=2,
    )


plt.legend(fontsize=10)
plt.tight_layout()
plt.savefig(
    dir + "/TENDENCIAS/Dobles_" + intervalo + "_media_y_errorbar_tendencia_ELEC_p1.png"
)
