#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Oct 27 17:05:00 2024

Last edit: Thu Dec 26 10:06:00 2024

@author: Blanca Berbel
"""

# --------------------------------------------------------------------#
#                                                                     #
# Comparison of 2 intervals, pyloric circuit                          #
#                                                                     #
# --------------------------------------------------------------------#

import os
import matplotlib.pyplot as plt
import spikes_utils as s_u
import seaborn as sns
import pandas as pd
import numpy as np
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import cross_val_score
from math import sqrt
import invariants_utils as i_u


# Work directory
separador = os.path.sep
dir_actual = os.path.dirname(os.path.abspath(__file__))
dir = separador.join(dir_actual.split(separador)[:-1])


# Conductance value
P1 = 0.0155
P2 = P1


name_intervalo_ejeY_1 = r"Interval_PYPD1"
name_intervalo_ejeY_2 = r"Interval_PYLP"

name_intervalo_ejeX_1 = r"Period_PY"
name_intervalo_ejeX_2 = r"Period_PY"



intervalo_ejeX_1 = s_u.get_time_interval(
    dir
    + "/TIME_INTERVALS/"
    + name_intervalo_ejeX_1
    + "_g_"
    + "{:.4f}".format(P1)
    + "_g_"
    + "{:.4f}".format(P2)
)
intervalo_ejeX_2 = s_u.get_time_interval(
    dir
    + "/TIME_INTERVALS/"
    + name_intervalo_ejeX_2
    + "_g_"
    + "{:.4f}".format(P1)
    + "_g_"
    + "{:.4f}".format(P2)
)


intervalo_ejeY_1 = s_u.get_time_interval(
    dir
    + "/TIME_INTERVALS/"
    + name_intervalo_ejeY_1
    + "_g_"
    + "{:.4f}".format(P1)
    + "_g_"
    + "{:.4f}".format(P2)
)
intervalo_ejeY_2 = s_u.get_time_interval(
    dir
    + "/TIME_INTERVALS/"
    + name_intervalo_ejeY_2
    + "_g_"
    + "{:.4f}".format(P1)
    + "_g_"
    + "{:.4f}".format(P2)
)



# Figure
plt.rcParams["figure.dpi"] = 300
plt.rcParams["figure.figsize"] = (36, 12)
plt.rcParams["font.size"] = 35


R2_1 = i_u.get_R2(intervalo_ejeX_1, intervalo_ejeY_1)
R2_2 = i_u.get_R2(intervalo_ejeX_2, intervalo_ejeY_2)


if R2_1 > 0.5:
    X_1, Y_pred_1 = i_u.get_X_Y_pred(intervalo_ejeX_1, intervalo_ejeY_1)
if R2_2 > 0.5:
    X_2, Y_pred_2 = i_u.get_X_Y_pred(intervalo_ejeX_2, intervalo_ejeY_2)



minimo = min(
    len(intervalo_ejeX_1),
    len(intervalo_ejeY_1),
    len(intervalo_ejeX_2),
    len(intervalo_ejeY_2),
)


fig, (ax1, ax2) = plt.subplots(1, 2)

ax1.scatter(
    intervalo_ejeX_1[:minimo],
    intervalo_ejeY_1[:minimo],
    marker="o",
    s=100,
    color="#E66100",#"#C70039",
    label=r"$PY-PD1\,interval\,$ vs. $PY\,period$",
)
ax1.plot(
    X_1,
    Y_pred_1,
    linestyle="solid",
    c="black",
    linewidth=2,
    label=r"$R^{2}\,=\,$" + str(R2_1.round(3)),
)  

ax2.scatter(
    intervalo_ejeX_2[:minimo],
    intervalo_ejeY_2[:minimo],
    marker="s",
    s=100,
    color="#5D3A9B",#"#3498db",
    label=r"$PY-LP\,interval\,$vs. $PY\,period$",
)
ax2.plot(
    X_2,
    Y_pred_2,
    linestyle="solid",
    c="black",
    linewidth=2,
    label=r"$R^{2}\,=\,$" + str(R2_2.round(3)),
)




ax1.set_xlabel(r"$PY\,period\,(s)$")
ax2.set_xlabel(r"$PY\,period\,(s)$")

ax1.set_ylabel(r"$PY-PD1\,interval\,(s)$")
ax2.set_ylabel(r"$PY-LP\,interval\,(s)$")


ax1.legend(loc="upper right")
ax2.legend(loc="upper right")


plt.tight_layout()
plt.savefig(
    dir
    + "/TENDENCIAS/paragithub_comparacion_invariantes_2intervalos_"
    + name_intervalo_ejeX_1
    + "_vs_"
    + name_intervalo_ejeY_1
    + "_poor_3neurons.png"
)
