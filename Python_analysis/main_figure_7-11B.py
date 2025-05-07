#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Mar 10 14:57:11 2022

Last edit: Mon Dec 23 16:04:03 2024

@author: Blanca Berbel
"""

# ------------------------------#
#                               #
# BOX PLOT                      #
#                               #
# ------------------------------#

import os
import matplotlib.pyplot as plt
import spikes_utils as s_u
import seaborn as sns
import pandas as pd

# Work directory

separador = os.path.sep
dir_actual = os.path.dirname(os.path.abspath(__file__))
dir = separador.join(dir_actual.split(separador)[:-1])


P1 = 0.0155
P2 = P1


plt.rcParams["figure.dpi"] = 300
plt.rcParams["figure.figsize"] = (36, 12)
plt.rcParams["font.size"] = 30


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

intervalPD1LP = s_u.get_time_interval(
    dir
    + "/TIME_INTERVALS/Interval_PD1LP_g_"
    + "{:.4f}".format(P1)
    + "_g_"
    + "{:.4f}".format(P2)
)
intervalPD1PY = s_u.get_time_interval(
    dir
    + "/TIME_INTERVALS/Interval_PD1PY_g_"
    + "{:.4f}".format(P1)
    + "_g_"
    + "{:.4f}".format(P2)
)

intervalLPPD1 = s_u.get_time_interval(
    dir
    + "/TIME_INTERVALS/Interval_LPPD1_g_"
    + "{:.4f}".format(P1)
    + "_g_"
    + "{:.4f}".format(P2)
)
intervalLPPY = s_u.get_time_interval(
    dir
    + "/TIME_INTERVALS/Interval_LPPY_g_"
    + "{:.4f}".format(P1)
    + "_g_"
    + "{:.4f}".format(P2)
)

intervalPYPD1 = s_u.get_time_interval(
    dir
    + "/TIME_INTERVALS/Interval_PYPD1_g_"
    + "{:.4f}".format(P1)
    + "_g_"
    + "{:.4f}".format(P2)
)
intervalPYLP = s_u.get_time_interval(
    dir
    + "/TIME_INTERVALS/Interval_PYLP_g_"
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
    len(intervalPD1LP),
    len(intervalPD1PY),
    len(intervalLPPD1),
    len(intervalLPPY),
    len(intervalPYPD1),
    len(intervalPYLP),
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
    "PD1-LP interval": intervalPD1LP[:minimo],
    "PD1-PY interval": intervalPD1PY[:minimo],
    "LP-PD1 interval": intervalLPPD1[:minimo],
    "LP-PY interval": intervalLPPY[:minimo],
    "PY-PD1 interval": intervalPYPD1[:minimo],
    "PY-LP interval": intervalPYLP[:minimo],
    "PD1-LP delay": delayPD1LP[:minimo],
    "PD1-PY delay": delayPD1PY[:minimo],
    "LP-PD1 delay": delayLPPD1[:minimo],
    "LP-PY delay": delayLPPY[:minimo],
    "PY-PD1 delay": delayPYPD1[:minimo],
    "PY-LP delay": delayPYLP[:minimo],
}

etiquetas = [
    r"$PD1\,period$",
    r"$LP\,period$",
    r"$PY\,period$",
    r"$PD1\,burst$",
    r"$LP\,burst$",
    r"$PY\,burst$",
    r"$PD1\,IBI$",
    r"$LP\,IBI$",
    r"$PY\,IBI$",
    r"$PD1-LP\,interval$",
    r"$PD1-PY\,interval$",
    r"$LP-PD1\,interval$",
    r"$LP-PY\,interval$",
    r"$PY-PD1\,interval$",
    r"$PY-LP\,interval$",
    r"$PD1-LP\,delay$",
    r"$PD1-PY\,delay$",
    r"$LP-PD1\,delay$",
    r"$LP-PY\,delay$",
    r"$PY-PD1\,delay$",
    r"$PY-LP\,delay$",
]

df = pd.DataFrame(stats)

# Figure
plt.figure(figsize=(36, 12), dpi=300)
plt.xticks(rotation=30, ha="right")
plt.ylabel(r"$t\,(s)$")

bplot = plt.boxplot(
    df,
    notch=False,
    sym="",
    vert=True,
    patch_artist=True,
    labels=etiquetas,
    showfliers=False,
)

colors_period = sns.color_palette("Greys", 3)
colors_burst = sns.color_palette("Blues", 3)
colors_IBI = sns.color_palette("Greens", 3)
colors_interval = sns.color_palette("Purples", 6)
colors_delays = sns.color_palette("Reds", 6)

colors = colors_period + colors_burst + colors_IBI + colors_interval + colors_delays

for patch, color in zip(bplot["boxes"], colors):
    patch.set_facecolor(color)

for whisker in bplot["whiskers"]:
    whisker.set(color="#111111", linewidth=0.5, linestyle=":")

for cap in bplot["caps"]:
    cap.set(linewidth=0.2)

for median in bplot["medians"]:
    median.set(color="#E66100", linewidth=0.7)

for flier in bplot["fliers"]:
    flier.set(marker="D", color="#e7298a", alpha=0.5)

for box in bplot["boxes"]:
    box.set(linewidth=0.5)


plt.tick_params(axis="both")

plt.tight_layout()
plt.savefig(
    dir
    + "/BOX_PLOTS/P1_BoxPlot_g_"
    + "{:.4f}".format(P1)
    + "_g_"
    + "{:.4f}".format(P2)
    + "_PD1.png"
)
