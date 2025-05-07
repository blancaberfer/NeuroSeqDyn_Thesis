#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue May 21 09:27:00 2024

Last edit: Tue Dec 18 10:06:00 2024

@author: Blanca Berbel
"""

# --------------------------------------------------------------------------------------------#
#                                                                                             #
# Tendencia de los intervalos y variabilidad: para los valores de P con ritmo3fásico          #
#                                                                                             #
# --------------------------------------------------------------------------------------------#

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


intervalo = r"ISI3"


data_means = {
    intervalo + r"$\,AB$": [],
    intervalo + r"$\,PD1$": [],
    intervalo + r"$\,PD2$": [],
    intervalo + r"$\,LP$": [],
    intervalo + r"$\,PY$": [],
}


data_stds = {
    intervalo + r"$\,AB$": [],
    intervalo + r"$\,PD1$": [],
    intervalo + r"$\,PD2$": [],
    intervalo + r"$\,LP$": [],
    intervalo + r"$\,PY$": [],
}

for P1 in P:
    P2 = P1

    intervaloAB = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/"
        + intervalo
        + "_AB_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )

    intervaloPD1 = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/"
        + intervalo
        + "_PD1_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )

    intervaloPD2 = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/"
        + intervalo
        + "_PD2_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )

    intervaloLP = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/"
        + intervalo
        + "_LP_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )

    intervaloPY = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/"
        + intervalo
        + "_PY_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )

    data_means[intervalo + r"$\,AB$"].append(np.mean(intervaloAB))
    data_means[intervalo + r"$\,PD1$"].append(np.mean(intervaloPD1))
    data_means[intervalo + r"$\,PD2$"].append(np.mean(intervaloPD2))
    data_means[intervalo + r"$\,LP$"].append(np.mean(intervaloLP))
    data_means[intervalo + r"$\,PY$"].append(np.mean(intervaloPY))
    data_stds[intervalo + r"$\,AB$"].append(np.std(intervaloAB))
    data_stds[intervalo + r"$\,PD1$"].append(np.std(intervaloPD1))
    data_stds[intervalo + r"$\,PD2$"].append(np.std(intervaloPD2))
    data_stds[intervalo + r"$\,LP$"].append(np.std(intervaloLP))
    data_stds[intervalo + r"$\,PY$"].append(np.std(intervaloPY))


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


line_styles = ["-", "-", "-", "-", "-"]
palette = sns.color_palette("Set2", 5)

labels = [
    r"$\overline{ISI}^{-1}\,AB$",
    r"$\overline{ISI}^{-1}\,PD1$",
    r"$\overline{ISI}^{-1}\,PD2$",
    r"$\overline{ISI}^{-1}\,LP$",
    r"$\overline{ISI}^{-1}\,PY$",
]

# Plot with error bands
for i, (col, style, color) in enumerate(zip(df_means.columns, line_styles, palette)):
    plt.plot(
        df_means.index, df_means[col], label=labels[i], linestyle=style, color=color
    )

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
plt.savefig(dir + "/TENDENCIAS/" + intervalo + "_media_y_errorbar_tendencia_p1.png")
