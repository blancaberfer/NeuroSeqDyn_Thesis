#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Apr 19 14:34:30 2022

Last edit: Fri Jun 21 11:15:06 2024 

@author: Blanca Berbel
"""

import os 
import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt
import spikes_utils as s_u
import numpy as np

separador = os.path.sep
dir_actual = os.path.dirname(os.path.abspath(__file__))
dir = separador.join(dir_actual.split(separador)[:-1])

P1 = 0.0200
P2 = 0.0000

# Time intervals (calculated using main_time_intervals.py)
periodX = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA_Period_X_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 
periodY = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA_Period_Y_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 
burstX = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA_Burst_X_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 
burstY = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA_Burst_Y_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))  
HypX = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA_Hyp_X_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))  
HypY = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA_Hyp_Y_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))  
intervalXY = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA_Interval_XY_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))  
intervalYX = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA_Interval_YX_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 
delayXY = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA_Delay_XY_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))  
delayYX = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA_Delay_YX_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 

# Number of neurons plotted 
minimo = min(len(periodX), len(periodY), len(burstX), len(burstY), len(HypX), len(HypY), len(intervalXY), len(intervalYX), len(delayXY), len(delayYX)) 

stats = {"X period" : periodX[:minimo-1], "Y period" : periodY[:minimo-1]}
stats.update({"X burst" : burstX[:minimo-1], "Y burst" : burstY[:minimo-1]})
stats.update({"X IBI" : HypX[:minimo-1], "Y IBI" : HypY[:minimo-1]})
stats.update({"X-Y interval" : intervalXY[1:minimo]})
stats.update({"Y-X interval" : intervalYX[:minimo-1]}) 
stats.update({"X-Y delay" : delayXY[:minimo-1]})
stats.update({"Y-X delay" : delayYX[:minimo-1]})

df = pd.DataFrame(stats)


# Generate colors based on a colormap
norm = plt.Normalize(0, len(df) - 1)
cmap = plt.get_cmap('rainbow') #coolwarm
colors = cmap(norm(np.arange(len(df))))


# Create a PairGrid instance
g = sns.PairGrid(df, diag_sharey=False)

# Define a scatter plot function with color mapping
def scatter_with_color_lower(x, y, **kwargs):
    ax = plt.gca()
    ax.scatter(x, y, s=10, c=colors, **{k: v for k, v in kwargs.items() if k != 'color'})

def scatter_with_color_upper(x, y, **kwargs):
    ax = plt.gca()
    ax.scatter(x, y, s=10, color='#3182d3', alpha=0.3, **{k: v for k, v in kwargs.items() if k != 'color'})



# Map the plots to the grid
g.map_lower(scatter_with_color_lower)
g.map_upper(scatter_with_color_upper)

# Customize the diagonal with specific colors
def custom_diag(x, **kwargs):
    ax = plt.gca()
    ax.hist(x, bins=10, color='#3182d3', edgecolor='black')  # Cambia 'orange' al color que desees

g.map_diag(custom_diag)


for ax in g.axes.flatten():
    if ax is not None:
        ax.set_xlabel(ax.get_xlabel(), fontsize = 20)
        ax.set_ylabel(ax.get_ylabel(), fontsize = 20)
        ax.tick_params(axis='both', which='major', labelsize=15)


fig = g.fig
cbar_ax = fig.add_axes([0.92, 0.15, 0.02, 0.7])
sm = plt.cm.ScalarMappable(cmap=cmap, norm=norm)
sm.set_array([])

n_rafagas = minimo
cbar = fig.colorbar(sm, cax=cbar_ax, label='Time (s)', ticks=[0, n_rafagas-2])
cbar.ax.tick_params(labelsize=20)  # Aumentar el tamaño de los ticks de la barra de color
cbar.set_label('Time (s)', fontsize = 25, rotation=90)
cbar.ax.set_yticklabels(['0', '10000'], fontsize=20)  # Etiquetas de ticks personalizadas con tamaño


# Fixed margens
plt.subplots_adjust(left=0.1, right=0.88, top=0.9, bottom=0.1, wspace=0.3, hspace=0.3)


plt.savefig(dir + "/SEABORN/Seaborn_gZ1X_" + "{:.4f}".format(P1) + "_gZ2Y_" + "{:.4f}".format(P2) + ".png")
plt.show(block=True)
plt.close()
