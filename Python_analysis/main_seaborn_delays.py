#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Apr 19 14:34:30 2022

Last edit: Thu Mar 6 11:30:06 2025

@author: Blanca Berbel
"""

import os
import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt
import spikes_utils as s_u
from itertools import combinations
import numpy as np

# Work directory

separador = os.path.sep
dir_actual = os.path.dirname(os.path.abspath(__file__))
dir = separador.join(dir_actual.split(separador)[:-1])


P_ini = 0.0155
P_end = 0.0156

step = 0.0005

P1 = P_ini
P2 = P1

while P1 <= P_end:
    periodPD1 = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/Period_PD1_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    periodLP = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/Period_LP_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    periodPY = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/Period_PY_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )

    burstPD1 = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/Burst_PD1_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    burstLP = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/Burst_LP_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    burstPY = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/Burst_PY_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )

    HypPD1 = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/Hyp_PD1_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    HypLP = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/Hyp_LP_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    HypPY = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/Hyp_PY_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )

    delayPD1LP = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/Delay_PD1LP_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    delayPD1PY = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/Delay_PD1PY_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )

    delayLPPD1 = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/Delay_LPPD1_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    delayLPPY = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/Delay_LPPY_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )

    delayPYPD1 = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/Delay_PYPD1_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    delayPYLP = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/Delay_PYLP_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )

    isiAB = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/ISI2_AB_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    isiPD1 = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/ISI2_PD1_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    isiPD1 = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/ISI2_PD1_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    isiLP = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/ISI2_LP_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )
    isiPY = s_u.get_time_interval(
        dir
        + "/TIME_INTERVALS/ISI2_PY_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
    )

    minimo = min(
        len(periodPD1),
        len(periodLP),
        len(periodPY),
        len(burstPD1),
        len(burstLP),
        len(burstPY),
        len(HypPD1),
        len(HypLP),
        len(HypPY),
        len(delayPD1LP),
        len(delayPD1PY),
        len(delayLPPD1),
        len(delayLPPY),
        len(delayPYPD1),
        len(delayPYLP),
    )

    stats = {
        "PD1 period": periodPD1[:minimo],
        "LP period": periodLP[:minimo],
        "PY period": periodPY[:minimo],
        "PD1 burst": burstPD1[:minimo],
        "LP burst": burstLP[:minimo],
        "PY burst": burstPY[:minimo],
        "PD1 IBI": HypPD1[:minimo],
        "LP IBI": HypLP[:minimo],
        "PY IBI": HypPY[:minimo],
        "PD1-LP delay": delayPD1LP[:minimo],
        "PD1-PY delay": delayPD1PY[:minimo],
        "LP-PD1 delay": delayLPPD1[:minimo],
        "LP-PY delay": delayLPPY[:minimo],
        "PY-PD1 delay": delayPYPD1[:minimo],
        "PY-LP delay": delayPYLP[:minimo],
    }

    df = pd.DataFrame(stats)

    norm = plt.Normalize(0, len(df) - 1)
    cmap = plt.get_cmap("rainbow")
    colors = cmap(norm(np.arange(len(df))))

    g = sns.PairGrid(df, diag_sharey=False)

    def scatter_with_color_lower(x, y, **kwargs):
        ax = plt.gca()
        ax.scatter(
            x, y, s=10, c=colors, **{k: v for k, v in kwargs.items() if k != "color"}
        )

    def scatter_with_color_upper(x, y, **kwargs):
        ax = plt.gca()
        ax.scatter(
            x,
            y,
            s=10,
            color="#3182d3",
            alpha=0.3,
            **{k: v for k, v in kwargs.items() if k != "color"},
        )

    g.map_lower(scatter_with_color_lower)
    g.map_upper(scatter_with_color_upper)

    def custom_diag(x, **kwargs):
        ax = plt.gca()
        ax.hist(x, bins=10, color="#3182d3", edgecolor="black")

    g.map_diag(custom_diag)

    for ax in g.axes.flatten():
        if ax is not None:
            ax.set_xlabel(ax.get_xlabel(), fontsize=15)
            ax.set_ylabel(ax.get_ylabel(), fontsize=15)
            ax.tick_params(axis="both", which="major", labelsize=15)

    fig = g.fig
    cbar_ax = fig.add_axes([0.92, 0.15, 0.02, 0.7])
    sm = plt.cm.ScalarMappable(cmap=cmap, norm=norm)
    sm.set_array([])

    n_rafagas = minimo
    cbar = fig.colorbar(sm, cax=cbar_ax, label="Time (s)", ticks=[0, n_rafagas - 2])
    cbar.ax.tick_params(labelsize=20)
    cbar.set_label("Time (s)", fontsize=25, rotation=90)
    cbar.ax.set_yticklabels(["0", "5000"], fontsize=20)

    plt.subplots_adjust(
        left=0.1, right=0.88, top=0.9, bottom=0.1, wspace=0.3, hspace=0.3
    )

    plt.savefig(
        dir
        + "/SEABORN/Seaborn_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
        + "_2.png"
    )
    plt.show(block=True)
    plt.close()

    P1 = round(P1 + step, 4)
    P2 = P1
