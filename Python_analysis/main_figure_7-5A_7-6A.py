#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue May 21 09:27:00 2024

Last edit: Tue Dec 18 09:55:00 2024

@author: Blanca Berbel
"""

# ---------------------------------------------------------------------------------------------#
#                                                                                              #
# Interval trend and variability for LP - (PY, AB, PD1, PD2): for P-values with rhythm3phase   #
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
    intervalo + r"$\,LPPY$": [],
    intervalo + r"$\,LPAB$": [],
    intervalo + r"$\,LPPD1$": [],
    intervalo + r"$\,LPPD2$": [],
}


data_stds = {
    intervalo + r"$\,LPPY$": [],
    intervalo + r"$\,LPAB$": [],
    intervalo + r"$\,LPPD1$": [],
    intervalo + r"$\,LPPD2$": [],
}

for P1 in P:
    P2 = P1

    intervaloLPPY = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/"
        + intervalo
        + "_LPPY_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    intervaloLPAB = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/"
        + intervalo
        + "_LPAB_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    intervaloLPPD1 = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/"
        + intervalo
        + "_LPPD1_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    intervaloLPPD2 = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/"
        + intervalo
        + "_LPPD2_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )

    data_means[intervalo + r"$\,LPPY$"].append(np.mean(intervaloLPPY))
    data_means[intervalo + r"$\,LPAB$"].append(np.mean(intervaloLPAB))
    data_means[intervalo + r"$\,LPPD1$"].append(np.mean(intervaloLPPD1))
    data_means[intervalo + r"$\,LPPD2$"].append(np.mean(intervaloLPPD2))

    data_stds[intervalo + r"$\,LPPY$"].append(np.std(intervaloLPPY))
    data_stds[intervalo + r"$\,LPAB$"].append(np.std(intervaloLPAB))
    data_stds[intervalo + r"$\,LPPD1$"].append(np.std(intervaloLPPD1))
    data_stds[intervalo + r"$\,LPPD2$"].append(np.std(intervaloLPPD2))

    # P1 = round(P1 + P_step, 4)
    # P2 = P1

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


line_styles = ["-", "-", "-", "-"]
palette = sns.color_palette("husl", 4)

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
    dir + "/TENDENCIAS/Dobles_" + intervalo + "_media_y_errorbar_tendencia_LP_p1.png"
)
