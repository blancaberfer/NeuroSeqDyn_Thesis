#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue May 21 09:27:00 2024

Last edit: Mon Jun 24 10:40:00 2024  

@author: Blanca Berbel 
"""

#-----------------------------------------------------------#
#                                                           #
# Interval trend and variability                            #
#                                                           #
#-----------------------------------------------------------#

import os 
import matplotlib.pyplot as plt
import spikes_utils as s_u
import seaborn as sns
import pandas as pd
import numpy as np

# Working directory

separador = os.path.sep
dir_actual = os.path.dirname(os.path.abspath(__file__))
dir = separador.join(dir_actual.split(separador)[:-1])


# Conductance values

P_ini = 0.0000
P_step = 0.0010
P_end = 0.0300

P1 = P_ini
P2 = 0.0000

P =  np.arange(P_ini, P_end + P_step, P_step)


gap_with = "Z1"

data_means = {r'$Period$': [], r'$IBI$': [], r'$Burst\,duration$': [], r'$\overline{ISI}^{-1}$': [], r'$\# spikes_{Burst}$': []}
data_stds = {r'$Period$': [], r'$IBI$': [], r'$Burst\,duration$': [], r'$\overline{ISI}^{-1}$': [], r'$\# spikes_{Burst}$': []}

while P1 <= P_end:


    periodX = s_u.get_time_interval(dir + "/TIME_INTERVALS/Period_X_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 
    hypX = s_u.get_time_interval(dir + "/TIME_INTERVALS/Hyp_X_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 
    burstX = s_u.get_time_interval(dir + "/TIME_INTERVALS/Burst_X_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 
    isiX = s_u.get_time_interval(dir + "/TIME_INTERVALS/ISI_X_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))
    nspikesX = s_u.get_nspikes(dir + "/TIME_INTERVALS/ISI_X_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))


    data_means[r'$Period$'].append(np.mean(periodX))
    data_means[r'$IBI$'].append(np.mean(hypX))
    data_means[r'$Burst\,duration$'].append(np.mean(burstX))
    data_means[r'$\overline{ISI}^{-1}$'].append(np.mean(isiX))
    data_means[r'$\# spikes_{Burst}$'].append(np.mean(nspikesX))

    data_stds[r'$Period$'].append(np.std(periodX))
    data_stds[r'$IBI$'].append(np.std(hypX))
    data_stds[r'$Burst\,duration$'].append(np.std(burstX))
    data_stds[r'$\overline{ISI}^{-1}$'].append(np.std(isiX))
    data_stds[r'$\# spikes_{Burst}$'].append(np.std(nspikesX))

    P1 = round(P1 + P_step, 4)


df_means = pd.DataFrame(data_means, index=P)
df_stds = pd.DataFrame(data_stds, index=P)

print(df_means)
print(df_stds)

# Figure
plt.rcParams['figure.dpi'] = 300
plt.rcParams["figure.figsize"] = (6.27, 3.78) 


plt.figure()

plt.xticks(rotation=24, ha='right')

plt.xlabel(r'$g^{\mathrm{ec}}(\mu \mathrm{S})$')
plt.ylabel(r'$t(\mathrm{s})$')

plt.tick_params(axis='both', labelsize=8)


# Define the styles for the lines and the fill
line_styles = ['-', '-', '-', '-', '-', '-']
palette = sns.color_palette("Set2", 6)

# Plot with error bands
for i, (col, style, color) in enumerate(zip(df_means.columns, line_styles, palette)):
    plt.plot(df_means.index, df_means[col], label=col, linestyle=style, color=color)
    plt.fill_between(df_means.index, df_means[col] - df_stds[col], df_means[col] + df_stds[col], color=color, alpha=0.2)

plt.xlim(P_ini, P_end)

plt.legend(fontsize=8, loc = 'upper right')
plt.tight_layout()
plt.savefig(dir + "/TENDENCIAS/intervals_tendencies.png")

